#include "zSubNetService.h"
#include "Fir.h"
#include "zMisc.h"
#include "SceneServer.h"
#include "SceneTask.h"
#include "zConfile.h"
#include "SceneTaskManager.h"
#include "TimeTick.h"
#include "SceneUser.h"
#include "SceneUserManager.h"
#include "RecordClient.h"
#include "TradeCmdDispatcher.h"
#include "tbx.h"
#include "xmlconfig.h"
#include "extractProtoMsg.h"
#include "SceneMapDataManager.h"
#include "GmCmdDipatcher.h"
#include "SceneToOtherManager.h"
#include "FamilyCmdDispatcher.h"

SceneService *SceneService::instance = NULL;
zDBConnPool *SceneService::dbConnPool = NULL;

DWORD SceneService::cmd_record[4];
char SceneService::cmd_recordNew[zSocket::MAX_DATASIZE];
DWORD SceneService::cmd_len;

void load_tbx_config(const std::string &filename, byte *&buf, int &size)
{
    std::string path("tbx/");
    path += filename;
    FILE *fp = fopen(path.c_str(), "rb+");
    if (fp) {
        fseek(fp, SEEK_SET, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buf = new byte[size];   
        fread(buf, size, 1, fp);
        fclose(fp);
    }
}

const Fir::XMLParser::Node *load_xmlconfig(Fir::XMLParser &xml, const char *filename)
{
    std::string path = Fir::global["configdir"];
    path += filename;
    xml.load_from_file(path.c_str());
    return xml.root();
}

/* *
 * \brief 初始化各种表及逻辑的加载
 *
 * \return 是否成功
 */
bool SceneService::initLogic()
{
    // eg..
    //p =	Tbx::getMe().xxx().get(1001);
    //if (p)
    //	p->job()

    Fir::XMLParser xml;
    std::string path("tbx/tbx.xml");
    xml.load_from_file(path.c_str());
    tbx::mgr::getMe().init(xml, std::bind(&load_tbx_config, _1, _2, _3));
    //Tbx::getMe().init(xml, std::bind(&load_tbx_config, _1, _2, _3));

    //DWORD temp1 = BUILD_STRING;
    //std::string temp2 = VS;	
    //DWORD temp3 = ALL_SUPER_GM
    Fir::logger->error("version_string=%s",_S(BUILD_STRING));
    Fir::logger->error("vs=%s",_S(VS));
    Fir::logger->error("all_super_gm=%s",_S(_ALL_SUPER_GM));
    Fir::logger->error("macro_test=%s",_S(macro_test));

    /*
       if(!Sysconfig::getMe().loadconfig())
       {
       Fir::logger->error("[系统配置],0,0,0,加载t_sys_config基本表失败");
       return false;
       }
       */
    return true;
}

/**
 * \brief 初始化网络服务器程序
 *
 * 实现了虚函数<code>zService::init</code>
 *
 * \return 是否成功
 */
bool SceneService::init()
{
    strncpy(pstrIP, zSocket::getIPByIfName(Fir::global["ifname"].c_str()), MAX_IP_LENGTH - 1);
    if (!zSubNetService::init())
    {
        return false;
    }
    //初始化连接线程池
    int state = state_none;
    Fir::to_lower(Fir::global["initThreadPoolState"]);
    if ("repair" == Fir::global["initThreadPoolState"] || "maintain" == Fir::global["initThreadPoolState"])
    {
        state = state_maintain;
    }

    taskPool = new zTCPTaskPool(atoi(Fir::global["threadPoolCapacity"].c_str()), state);
    if (NULL == taskPool || !taskPool->init())
    {
        return false;
    }

    dbConnPool = zDBConnPool::newInstance(NULL);
    if (NULL == dbConnPool)
    {
        Fir::logger->error("连接数据库失败");
        return false;
    }
    if (!dbConnPool->putURL(0, Fir::global["mysql"].c_str(), false))
    {
        Fir::logger->error("连接数据库失败");
        return false;
    }

    
    zConfile::CreateLog("sceneserver","logfilename",wdServerID);
    Fir::logger->removeLocalFileLog(Fir::global["logfilename"]);
    Fir::logger->addLocalFileLog(Fir::global["logfilename"]);

    // 加入命令派发类
    cmd_handle_manager.add_handle(FIR_NEW TradeCmdHandle());
    cmd_handle_manager.add_handle(FIR_NEW GMCmdHandle());
    cmd_handle_manager.add_handle(FIR_NEW FamilyCmdHandle());

    // 统一初始化命令派发类
    cmd_handle_manager.init_all();


    const CMD::SUPER::ServerEntry *serverEntry = NULL;

    //连接所有的档案服务器
    serverEntry = getServerEntryByType(RECORDSERVER);
    if (NULL == serverEntry)
    {
        Fir::logger->error("不能找到Record服务器相关信息，不能连接Record服务器");
        return false;
    }
    while(serverEntry)
    {
        RecordClient* recordClient = new RecordClient("Record服务器", serverEntry->pstrExtIP, serverEntry->wdExtPort);
        if (NULL == recordClient)
        {
            Fir::logger->error("没有足够内存，不能建立Record服务器客户端实例");
            return false;
        }
        if (!recordClient->connectToRecordServer())
        {
            Fir::logger->error("连接Record服务器失败 %s", __PRETTY_FUNCTION__);
            return false;
        }
        recordClient->start();
        MgrrecordClient.addRecord(serverEntry->wdServerID,recordClient);
        serverEntry = getNextServerEntryByType(RECORDSERVER, &serverEntry);
    }

    if(!SceneClientToOtherManager::getMe().init())
    {
        Fir::logger->error("不能找到其他Scene");
        return false;

    }



    //初始化配置文件系统
    config::init(std::bind(&load_xmlconfig, _1, _2));

    if (!zMemDBPool::getMe().init() || (NULL == zMemDBPool::getMe().getMemDBHandle()))
    {
        Fir::logger->error("连接内存数据库失败");
        return false;
    }


    if (!initLogic())
    {
        Fir::logger->error("场景服务器加载基本配置失败");
        return false;
    }

    //加载地图配置信息
    Fir::XMLParser xml;
    std::string path("mapxml/map.xml");
    xml.load_from_file(path.c_str());
    SceneMapDataManager::getMe().init(xml);


    //各种加载配置等初始化 一定要再TIMETICK之前
    /* 初始化加载配置等必须在此之前 !!! !!! !!!*/
    SceneTimeTick::getMe().start();
    return true;
}

/**
 * \brief 新建立一个连接任务
 *
 * 实现纯虚函数<code>zNetService::newTCPTask</code>
 *
 * \param sock TCP/IP连接
 * \param addr 地址
 */
void SceneService::newTCPTask(const int sock, const struct sockaddr_in *addr)
{
    //Fir::logger->debug(__PRETTY_FUNCTION__);
    SceneTask *tcpTask = new SceneTask(taskPool, sock, addr);
    if (NULL == tcpTask)
        //内存不足，直接关闭连接
        TEMP_FAILURE_RETRY(::close(sock));
    else if(!taskPool->addVerify(tcpTask))
    {
        //得到了一个正确连接，添加到验证队列中
        SAFE_DELETE(tcpTask);
    }
}

bool SuperCmdQueue::cmdMsgParse(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    using namespace CMD::SUPER;
    switch(ptNullCmd->cmd)
    {
        case SUPERCMD:
            {
                return msgParseSuperCmd((SuperServerNull*)ptNullCmd,nCmdLen);
            }
            break;
    }

    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
    return false;
}

bool SuperCmdQueue::allZoneMsgParseProto(SceneUser *user,const BYTE *data,const DWORD cmdLen)
{
    const google::protobuf::Message *message = extraceProtoMsg(data,cmdLen);
    if(!message)
    {
        return false;
    }
    bool ret = SceneTask::scene_user_dispatcher.dispatch(user,message);
    SAFE_DELETE(message);
    return ret;

}

bool SuperCmdQueue::allZoneMsgParseStruct(SceneUser *user,const CMD::t_NullCmd *ptNullCmd,const DWORD cmdLen)
{
    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, cmdLen);
    return false;
}


bool SuperCmdQueue::allzoneMsgParse(SceneUser *user,const BYTE *data, const DWORD cmdLen)
{
    BYTE messageType = *(BYTE*)data;
    if(cmdLen <= sizeof(BYTE))
    {
        return false;
    }

    if(messageType == STRUCT_TYPE)
    {
        return allZoneMsgParseStruct(user,(CMD::t_NullCmd*)(data+sizeof(BYTE)),cmdLen-sizeof(BYTE));
    }
    else if(messageType == PROTOBUF_TYPE)
    {
        return allZoneMsgParseProto(user,data+sizeof(BYTE),cmdLen-sizeof(BYTE));
    }
    return false;
}

bool SuperCmdQueue::msgParseSuperCmd(const CMD::SUPER::SuperServerNull *superNull,const DWORD nCmdLen)
{
    using namespace CMD::SUPER;
    switch(superNull->para)
    {
        case PARA_ZONE_ID:
            {
                t_ZoneID *rev = (t_ZoneID *)superNull;
                SceneService::getMe().zoneID = rev->zone;
                Fir::logger->debug("收到区编号 %u(%u, %u)", SceneService::getMe().zoneID.id, SceneService::getMe().zoneID.game, SceneService::getMe().zoneID.zone);
                return true;
            }
            break;
        case PARA_FORWARD_SCENE_FROM_ALLZONE:
            {
                t_ForwardSceneFromAllZone* rev = (t_ForwardSceneFromAllZone*)superNull;
                SceneUser* user = SceneUserManager::getMe().getUserByID(rev->charid);
                if(user)
                {
                    return allzoneMsgParse(user,(BYTE*)rev->data,rev->datasize);
                }
                return true;
            }
        case PARA_GAMETIME:
            {
                unsigned long long grap = Fir::qwGameTime - SceneTimeTick::currentTime.sec();
                SceneTimeTick::currentTime.setgrap(grap * 1000);
                SceneTimeTick::currentTime.now();
                SceneUserManager::getMe().SceneUserManager::getMe().checkAndBrushDailyData();
                Fir::logger->debug("[修改时间]:%s,%llu",SceneTimeTick::currentTime.toString().c_str(),grap);
                return true;
            }
            break;
    }

    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, superNull->cmd, superNull->para, nCmdLen);
    return false;
}


bool SceneService::msgParse_SuperService(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
    using namespace CMD::SUPER;
    switch(ptNullCmd->cmd)
    {
        case SUPERCMD:
            {
                superCmd.put(ptNullCmd,nCmdLen);
                return true;
            }
            break;
    }

    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
    return false;
}

/**
 * \brief 结束网络服务器
 *
 * 实现了纯虚函数<code>zService::final</code>
 *
 */
void SceneService::final()
{
    SceneUserManager::getMe().saveAll();
    //手动析构，防止静态析构的先后顺序的确定性
    SceneUserManager::getMe().delAll();
    SceneTimeTick::getMe().final();
    SceneTimeTick::getMe().join();


    //----------------我是华丽的分隔线， 所有功能的释放，请加在上面------------------

    zArg::removeArg();

    zSubNetService::final();
    if(taskPool)
    {
        SAFE_DELETE(taskPool);
    }


    SceneClientToOtherManager::getMe().final();
    MgrrecordClient.final(); 
    CHECK_LEAKS;
    Fir::logger->debug(__PRETTY_FUNCTION__);
}

/**
 * \brief 命令行参数
 *
 */
static struct argp_option account_options[] =
{
    {"daemon",		'd',	0,			0,	"Run service as daemon",						0},
    {"log",			'l',	"level",	0,	"Log level",									0},
    {"logfilename",	'f',	"filename",	0,	"Log file name",								0},
    {"mysql",		'y',	"mysql",	0,	"MySQL[mysql://user:passwd@host:port/dbName]",	0},
    {"ifname",		'i',	"ifname",	0,	"Local network device",							0},
    {"server",		's',	"ip",		0,	"Super server ip address",						0},
    {"port",		'p',	"port",		0,	"Super server port number",						0},
    {0,				0,		0,			0,	0,												0}
};

/**
 * \brief 命令行参数解析器
 *
 * \param key 参数缩写
 * \param arg 参数值
 * \param state 参数状态
 * \return 返回错误代码
 */
static error_t account_parse_opt(int key, char *arg, struct argp_state *state)
{
    switch (key)
    {
        case 'd':
            {
                Fir::global["daemon"] = "true";
            }
            break;
        case 'p':
            {
                Fir::global["port"]=arg;
            }
            break;
        case 's':
            {
                Fir::global["server"]=arg;
            }
            break;
        case 'l':
            {
                Fir::global["log"]=arg;
            }
            break;
        case 'f':
            {
                Fir::global["logfilename"]=arg;
            }
            break;
        case 'y':
            {
                Fir::global["mysql"]=arg;
            }
            break;
        case 'i':
            {
                Fir::global["ifname"]=arg;
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

/**
 * \brief 简短描述信息
 *
 */
static char account_doc[] = "\nSceneServer\n" "\t小游戏服务器。";

/**
 * \brief 程序的版本信息
 *
 */
const char *argp_program_version = "Program version :\t" VERSION_STRING\
                                    "\nBuild version   :\t" _S(BUILD_STRING)\
                                    "\nBuild time      :\t" __DATE__ ", " __TIME__;

/**
 * \brief 读取配置文件
 *
 */
class MiniConfile:public zConfile
{
    bool parseYour(const xmlNodePtr node)
    {
        if (node)
        {
            xmlNodePtr child=parser.getChildNode(node,NULL);
            while(child)
            {
                parseNormal(child);
                child=parser.getNextNode(child,NULL);
            }
            return true;
        }
        else
            return false;
    }
};

/**
 * \brief 重新读取配置文件，为HUP信号的处理函数
 *
 */
void SceneService::reloadconfig()
{
    Fir::logger->debug("%s", __PRETTY_FUNCTION__);
    MiniConfile rc;
    rc.parse("sceneserver");

    //设置MD5验证开关
    if(Fir::global["md5Verify"] == "true" )
    {
        SceneService::getMe().md5Verify = true;
    }

    //设置存档间隔
    if(atoi(Fir::global["writebackgroup"].c_str()) && (atoi(Fir::global["writebackgroup"].c_str()) > 0))
    {
        SceneService::getMe().writeBackGroup= atoi(Fir::global["writebackgroup"].c_str());
    }

    //加载一些基本表
    Fir::XMLParser xml;
    std::string path("tbx/tbx.xml");
    xml.load_from_file(path.c_str());
    tbx::mgr::getMe().init(xml, std::bind(&load_tbx_config, _1, _2, _3));
    /*
       if(!Sysconfig::getMe().loadinvitcodeconfig())
       {
       Fir::logger->error("[邀请码配置],0,0,0,加载t_invit_code_config基本表失败");
       return;
       }
       */
}

int main(int argc, char **argv)
{
    Fir::initGlobal();
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    Fir::logger=new zLogger("sceneserver");

    //设置缺省参数
    Fir::global["mysql"] = "mysql://Fir:Fir@192.168.1.162:3306/SceneServer";
    //Fir::global["logfilename"] = "/home/flyer/newWorkPlace/kittyserver/log/sceneserver.log";
    Fir::global["configdir"] = "gametools/parseXmlTool/xmldir/";
    zConfile::CreateLog("sceneserver","logfilename");
    //解析配置文件参数
    MiniConfile rc;
    if (!rc.parse("sceneserver"))
        return EXIT_FAILURE;

    //解析命令行参数
    zArg::getArg()->add(account_options, account_parse_opt, 0, account_doc);
    zArg::getArg()->parse(argc, argv);
    //Fir::global.dump(std::cout);

    //设置日志级别
    Fir::logger->setLevel(Fir::global["log"]);
    //设置写本地日志文件
    if ("" != Fir::global["logfilename"])
        Fir::logger->addLocalFileLog(Fir::global["logfilename"]);


    //设置MD5验证开关
    if(Fir::global["md5Verify"] == "true")
    {
        SceneService::getMe().md5Verify = true;
    }

    //设置存档间隔
    if(atoi(Fir::global["writebackgroup"].c_str()) && (atoi(Fir::global["writebackgroup"].c_str()) > 0))
    {
        SceneService::getMe().writeBackGroup = atoi(Fir::global["writebackgroup"].c_str());
    }

    //是否以后台进程的方式运行
    if ("true" == Fir::global["daemon"]) {
        Fir::logger->info("Program will be run as a daemon");
        Fir::logger->removeConsoleLog();
        daemon(1, 1);
    }

    SceneService::getMe().main();

    google::protobuf::ShutdownProtobufLibrary();
    Fir::finalGlobal();
    return EXIT_SUCCESS;
}


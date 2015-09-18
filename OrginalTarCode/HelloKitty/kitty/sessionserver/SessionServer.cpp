/**
 * \file
 * \version  $Id: SessionServer.cpp 72 2013-04-24 03:55:51Z  $
 * \author   ,
 * \date 2013年03月26日 16时55分53秒 CST
 * \brief Fir项目，全局会话服务器，负责社会关系，场景负载均衡等全局功能
 *
 */

#include "zSubNetService.h"
#include "Fir.h"
#include "zMisc.h"
#include "SessionServer.h"
#include "SessionTask.h"
#include "zDBConnPool.h"
#include "zConfile.h"
#include "SessionTaskManager.h"
#include "TimeTick.h"
#include "zMetaData.h"
#include "SessionUser.h"
#include "SessionUserManager.h"
#include "RecordClient.h"
#include "GateCmdDispatcher.h"
#include "SceneCmdDispatcher.h"
#include "xmlconfig.h"
#include "tbx.h"
#include "TimerMgr.h"

zDBConnPool *SessionService::dbConnPool = NULL;
SessionService *SessionService::instance = NULL;
MetaData* SessionService::metaData = NULL;
zLogger* SessionService::billlog = NULL;
zLogger * SessionService::login_logger = NULL;

DWORD SessionService::online_num = 0;

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

/**
 * \brief 初始化网络服务器程序
 *
 * 实现了虚函数<code>zService::init</code>
 *
 * \return 是否成功
 */
bool SessionService::init()
{
	//Fir::logger->debug(__PRETTY_FUNCTION__);

	//初始化表格代码
	Fir::XMLParser xml;
	std::string path("tbx/tbx.xml");
	xml.load_from_file(path.c_str());
	tbx::mgr::getMe().init(xml, std::bind(&load_tbx_config, _1, _2, _3));
	//初始化配置文件系统
	config::init(std::bind(&load_xmlconfig, std::placeholders::_1, std::placeholders::_2));

	dbConnPool = zDBConnPool::newInstance(NULL);
	if (NULL == dbConnPool
			|| !dbConnPool->putURL(0, Fir::global["mysql"].c_str(), false))
	{
		Fir::logger->error("连接数据库失败");
		return false;
	}

	if (strncmp(Fir::global["time_version"].c_str(), "true", MAX_NAMESIZE) == 0)
	{
		Fir::logger->error("非免费版，禁止启动");
		return false;
	}

	metaData = MetaData::newInstance("");

	if (NULL == metaData
			|| !metaData->init(Fir::global["mysql"]))
	{
		Fir::logger->error("连接数据库失败");
		return false;
	}


	//初始化连接线程池
	int state = state_none;
	Fir::to_lower(Fir::global["initThreadPoolState"]);
	if ("repair" == Fir::global["initThreadPoolState"]
			|| "maintain" == Fir::global["initThreadPoolState"])
		state = state_maintain;
	taskPool = new zTCPTaskPool(atoi(Fir::global["threadPoolCapacity"].c_str()), state);
	if (NULL == taskPool
			|| !taskPool->init())
		return false;

	strncpy(pstrIP, zSocket::getIPByIfName(Fir::global["ifname"].c_str()), MAX_IP_LENGTH - 1);

	if (!zSubNetService::init())
		return false;


	// 加入命令派发类
	cmd_handle_manager.add_handle(FIR_NEW GateCmdHandle());
	cmd_handle_manager.add_handle(FIR_NEW SceneCmdHandle());

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

	recordClient = new RecordClient("Record服务器", serverEntry->pstrExtIP, serverEntry->wdExtPort);
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

	if (!zMemDBPool::getMe().init() || (NULL == zMemDBPool::getMe().getMemDBHandle()))
	{
		Fir::logger->error("连接内存数据库失败");
		return false;
	}
	
	if (!initAllData())
		return false;


	if(!initLogger())
		return false;

	//各种初始化必须放这上面！！！！！
	SessionTimeTick::getMe().start();
	return true;
}

bool SessionService::initLogger()
{
	char srv[256];
	bzero(srv, sizeof(srv));
	snprintf(srv , sizeof(srv)-1, "SessionServer[%d]",getServerID());
	billlog = FIR_NEW zLogger(srv);
	billlog->setLevel(Fir::global["log"]);
	if ("" != Fir::global["billlogfile"])
	{
		bzero(srv, sizeof(srv));
		char sub[256];
		bzero(sub, sizeof(sub));
		snprintf(srv , sizeof(srv),"%s",Fir::global["billlogfile"].c_str());
		char *tok = strstr(srv , ".");
		if( tok != NULL)
		{
			strncpy(sub,tok,sizeof(sub));
			bzero(tok , strlen(tok));
			snprintf(srv + strlen(srv) , sizeof(srv)-strlen(srv), "%d",getServerID());
			strncat(srv,sub,sizeof(srv) - strlen(srv));
		}
		else
		{
			snprintf(srv + strlen(srv) , sizeof(srv) - strlen(srv) , "%d",getServerID());
		}
		billlog->addLocalFileLog(srv);
		billlog->removeConsoleLog();
	}

	return initLoginLogger();
}

bool SessionService::initLoginLogger()
{
	char srv[256];
	bzero(srv, sizeof(srv));
	snprintf(srv , sizeof(srv)-1, "GS[%d]Login",getServerID());
	login_logger = FIR_NEW zLogger(srv);
	login_logger->setLevel(Fir::global["log"]);
	if ("" != Fir::global["loginlogname"])
	{   
		bzero(srv, sizeof(srv));
		char sub[256];
		bzero(sub, sizeof(sub));
		snprintf(srv , sizeof(srv),"%s",Fir::global["loginlogname"].c_str());
		char *tok = strstr(srv , ".");
		if( tok != NULL)
		{   
			strncpy(sub,tok,sizeof(sub));
			bzero(tok , strlen(tok));
			snprintf(srv + strlen(srv) , sizeof(srv)-strlen(srv), ".session%d",getServerID());
			strncat(srv,sub,sizeof(srv) - strlen(srv));
		}   
		else
		{   
			snprintf(srv + strlen(srv) , sizeof(srv) - strlen(srv) , "%d",getServerID());
		}   
		login_logger->addBasicFileLog(srv);
		login_logger->removeConsoleLog();
		return true;
	}   

	return false;
}

//初始化数据库和xml配置
bool SessionService::initAllData()
{
	
	return true;
}

void SessionService::newTCPTask(const int sock, const struct sockaddr_in *addr)
{
	//Fir::logger->debug(__PRETTY_FUNCTION__);
	SessionTask *tcpTask = new SessionTask(taskPool, sock, addr);
	if (NULL == tcpTask)
		//内存不足，直接关闭连接
		TEMP_FAILURE_RETRY(::close(sock));
	else if(!taskPool->addVerify(tcpTask))
	{
		//得到了一个正确连接，添加到验证队列中
		SAFE_DELETE(tcpTask);
	}
}

bool SessionService::msgParse_SuperService(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
	using namespace CMD::SUPER;

	if (CMD::SUPER::CMD_SESSION == ptNullCmd->cmd)
	{
		switch(ptNullCmd->para)
		{
			case CMD::SUPER::PARA_ZONE_ID_SESSION:
				{
					CMD::SUPER::t_ZoneID_Session *rev = (CMD::SUPER::t_ZoneID_Session *)ptNullCmd;					
					SessionService::getMe().zoneID = rev->zone;	
					SessionService::getMe().zonename = rev->name;
					Fir::logger->debug("收到区编号 %u(%u, %u),zonename=%s", SessionService::getMe().zoneID.id, SessionService::getMe().zoneID.game, SessionService::getMe().zoneID.zone,
							SessionService::getMe().zonename.c_str());
				}
				break;
		}
		return true;
	}

	return true;

	//Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	//return false;
}

/**
 * \brief 结束网络服务器
 *
 * 实现了纯虚函数<code>zService::final</code>
 *
 */
void SessionService::final()
{
	SessionTimeTick::getMe().final();
	SessionTimeTick::getMe().join();
	//增加释放处理
	
	TimerMgr::getMe().CancelAllTimers();

	//华丽分割线=== 各种释放都放上面 !!!!!!	

	if(taskPool)
	{
		SAFE_DELETE(taskPool);
	}


	zSubNetService::final();

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
static char account_doc[] = "\nSessionServer\n" "\t小游戏服务器。";

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
void SessionService::reloadconfig()
{
	Fir::logger->debug("%s", __PRETTY_FUNCTION__);
	MiniConfile rc;
	rc.parse("SessionServer");
}

/**
 * \brief 主程序入口
 *
 * \param argc 参数个数
 * \param argv 参数列表
 * \return 运行结果
 */
int main(int argc, char **argv)
{
	Fir::initGlobal();
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	Fir::logger=new zLogger("sessionserver");

	//设置缺省参数
	Fir::global["mysql"] = "mysql://Fir:Fir@192.168.1.162:3306/sessionserver";
	Fir::global["logfilename"] = "/home/flyer/newWorkPlace/kittyserver/log/sessionserver.log";
	Fir::global["configdir"] = "gametools/parseXmlTool/";

	//解析配置文件参数
	MiniConfile rc;
	if (!rc.parse("sessionserver"))
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

	//是否以后台进程的方式运行
	if ("true" == Fir::global["daemon"]) {
		Fir::logger->info("Program will be run as a daemon");
		Fir::logger->removeConsoleLog();
		daemon(1, 1);
	}

	SessionService::getMe().main();
	google::protobuf::ShutdownProtobufLibrary();
	Fir::finalGlobal();
	return EXIT_SUCCESS;
}

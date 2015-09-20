/**
 * \file
 * \version  $Id: AllZoneServer.cpp 75 2013-04-25 05:10:39Z  $
 * \author  ,@163.com
 * \date 2004年11月29日 17时19分12秒 CST
 * \brief 实现服务器管理器
 *
 * 对一个区中的所有服务器进行管理
 * 
 */

#include <iostream>
#include <string>
#include <ext/numeric>

#include "zService.h"
#include "zThread.h"
#include "zSocket.h"
#include "zTCPServer.h"
#include "zNetService.h"
#include "ZoneTask.h"
#include "zDBConnPool.h"
#include "AllZoneServer.h"
#include "Fir.h"
#include "zMisc.h"
#include "zArg.h"
#include "zConfile.h"
#include "TimeTick.h"
#include "xmlconfig.h"
#include "zMetaData.h"
#include "tbx.h"
#include "AllZoneCommand.h"
#include "ZoneManager.h"
#include "extractProtoMsg.h"
#include "sceneCmdDispatch.h"

zDBConnPool *AllZoneService::dbConnPool = NULL;
MetaData* AllZoneService::metaData = NULL;
AllZoneService *AllZoneService::instance = NULL;

const Fir::XMLParser::Node *load_xmlconfig(Fir::XMLParser &xml, const char *filename)
{
	std::string path = Fir::global["configdir"];
	path += filename;
	xml.load_from_file(path.c_str());
	return xml.root();
}

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

/**
 * \brief 初始化网络服务器程序
 *
 * 实现纯虚函数<code>zService::init</code>
 *
 * \return 是否成功
 */
bool AllZoneService::init()
{
	Fir::logger->debug("%s", __PRETTY_FUNCTION__);

	using namespace std::placeholders;
	//初始化配置文件系统
	//config::init(std::bind(&load_xmlconfig, _1, _2));
	
	Fir::XMLParser xml;
	std::string path("tbx/tbx.xml");
	xml.load_from_file(path.c_str());
	tbx::mgr::getMe().init(xml, std::bind(&load_tbx_config, _1, _2, _3));	

	dbConnPool = zDBConnPool::newInstance(NULL);
	if (NULL == dbConnPool
			|| !dbConnPool->putURL(0, Fir::global["mysql"].c_str(), false))
	{
		Fir::logger->error("连接数据库失败");
		return false;
	}

	metaData = MetaData::newInstance("");            

	if (NULL == metaData
			|| !metaData->init(Fir::global["mysql"]))
	{
		Fir::logger->error("连接数据库失败");
		return false;
	}
    
    //命令派发管理
    m_cmd_handle_manager.add_handle(FIR_NEW ZoneSceneCmdHandle());
	m_cmd_handle_manager.init_all();

    /*
	if (!zMemDBPool::getMe().init() || (NULL == zMemDBPool::getMe().getMemDBHandle()))
	{
		Fir::logger->error("连接内存数据库失败");
		return false;
	}
	zMemDBPool::getMe().flushALLMemDB();
	*/
	
	strncpy(pstrIP, zSocket::getIPByIfName(Fir::global["ifname"].c_str()), MAX_IP_LENGTH - 1);
	//Fir::logger->debug("%s", pstrIP);

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


	if (!zMNetService::init())
	{
		return false;
	}

	unsigned int inside_port = atoi(Fir::global["inside_port"].c_str());
    Fir::logger->debug("inside_port:%u",inside_port);
	if(!zMNetService::bind("AllZoneServer端口",inside_port))
	{
		Fir::logger->error("绑定AllZoneServer端口出错。");
		return false;
	}

	AZTimeTick::getMe().start();

	return true;
}

#ifdef _OP_TOOL_VERSION
//运维属性察看工具
bool AllZoneService::reSetDBPool(std::string str)
{
	zDBConnPool::delInstance(&dbConnPool);
	dbConnPool = zDBConnPool::newInstance(NULL);

	if(!dbConnPool->putURL(0,str.c_str(), false))
	{
		Fir::logger->error("连接数据库失败");
		return false;
	}
	return true;
}
#endif

bool AllZoneService::sendCmdToScene(const DWORD zoneid, const DWORD sceneid, const void *pstrCmd, const DWORD nCmdLen)
{
	using namespace CMD::ALLZONE;
	BYTE buf[zSocket::MAX_DATASIZE] = {0};
    t_AllZone2Super_Forward2Scene *scmd=(t_AllZone2Super_Forward2Scene *)buf;
    constructInPlace(scmd);
    
    scmd->sceneid = sceneid;
    scmd->datasize = nCmdLen;
    bcopy(pstrCmd, scmd->data, nCmdLen);
    
    std::string ret;
    encodeMessage(scmd,scmd->getSize(),ret);
	ZoneManager::getMe().broadcastByID(zoneid,ret.c_str(),ret.size());
	return true;
}

void AllZoneService::newTCPTask(const int sock, const unsigned short srcPort)
{
	zTCPTask* tcpTask = new ZoneTask(taskPool, sock, NULL);

	if (NULL == tcpTask)
		//内存不足，直接关闭连接
		TEMP_FAILURE_RETRY(::close(sock));
	else if(!taskPool->addVerify(tcpTask))
	{  
		//得到了一个正确连接，添加到验证队列中
		SAFE_DELETE(tcpTask);
	}   
}


/**
 * \brief 结束网络服务器
 *
 * 实现纯虚函数<code>zService::final</code>
 *
 */
void AllZoneService::final()
{
	AZTimeTick::getMe().final();
	AZTimeTick::getMe().join();

	if (taskPool)
	{
		taskPool->final();
		SAFE_DELETE(taskPool);
	}

	zMNetService::final();

	CHECK_LEAKS;
	Fir::logger->debug("%s", __PRETTY_FUNCTION__);
}

/**
 * \brief 命令行参数
 *
 */
static struct argp_option super_options[] =
{
	{"daemon",		'd',	0,			0,	"Run service as daemon",						0},
	{"log",			'l',	"level",	0,	"Log level",									0},
	{"logfilename",	'f',	"filename",	0,	"Log file name",								0},
	{"mysql",		'y',	"mysql",	0,	"MySQL[mysql://user:passwd@host:port/dbName]",	0},
	{"ifname",		'i',	"ifname",	0,	"Local network device",							0},
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
static error_t super_parse_opt(int key, char *arg, struct argp_state *state)
{
	switch (key)
	{
		case 'c':
			{
				Fir::global["configfile"] = arg;
			}
			break;
		case 'd':
			{
				Fir::global["daemon"] = "true";
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
static char super_doc[] = "\nSuperServer\n" "\t服务器管理器。";

/**
 * \brief 程序的版本信息
 *
 */
const char *argp_program_version = "Program version :\t" VERSION_STRING\
									"\nBuild version   :\t" _S(BUILD_STRING)\
									"\nBuild version_d :\t" _S(BUILD_STRING_D)\
									"\nBuild time      :\t" __DATE__ ", " __TIME__;

/**
 * \brief 读取配置文件
 *
 */
class AllZoneConfile:public zConfile
{
	public:
		AllZoneConfile(const char*confile) : zConfile(confile)
	{
	}

	private:
		bool parseYour(const xmlNodePtr node)
		{
			if(node)
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
void AllZoneService::reloadconfig()
{
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
	Fir::logger=new zLogger("AllZoneServer");

#if 0
	const int count = 10000;
	int tick = 5;
	while(--tick >= 0)
	{
		{
			FunctionTime func_time(0,__PRETTY_FUNCTION__,"整个任务遍历需要的时间" , 32);
			for(int i = 0; i < count; i++)
			{
				std::vector<int> v;
				v.resize(count, 1);
			}
		}
		{
			FunctionTime func_time(0,__PRETTY_FUNCTION__,"整个任务遍历需要的时间" , 32);
			for(int i = 0; i < count; i++)
			{
				std::vector<int> v(count, 1);
			}
		}
		{
			FunctionTime func_time(0,__PRETTY_FUNCTION__,"整个任务遍历需要的时间" , 32);
			for(int i = 0; i < count; i++)
			{
				std::vector<int> v;
				v.reserve(count);
				bzero(&v[0], v.size() * sizeof(int));
			}
		}
		{
			FunctionTime func_time(0,__PRETTY_FUNCTION__,"整个任务遍历需要的时间" , 32);
			for(int i = 0; i < count; i++)
			{
				std::vector<int> v;
				v.reserve(count);
				fill(v.begin(), v.begin() + v.capacity(), 1);
			}
		}
	}
	return 0;
#endif

	//设置缺省参数
	//Fir::global["loginServerListFile"] = "SuperServer/loginServerList.xml";
	//Fir::global["mysql"] = "mysql://Fir:Fir@192.168.1.162:3306/";
	//Fir::global["logfilename"] = "/tmp/superserver.log";
	Fir::global["configfile"] = "allzoneserver/config.xml";
	Fir::global["log"] = "debug";
    Fir::global["logfilename"] = "/home/flyer/newWorkPlace/tempKitty/log/allzoneserver.log";

	//解析命令行参数
	zArg::getArg()->add(super_options, super_parse_opt, 0, super_doc);
	zArg::getArg()->parse(argc, argv);
	//Fir::global.dump(std::cout);

	//解析配置文件参数
	AllZoneConfile sc(Fir::global["configfile"].c_str());
	if (!sc.parse("AllZoneServer"))
		return EXIT_FAILURE;
    
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

	AllZoneService::getMe().main();
	Fir::finalGlobal();
	return EXIT_SUCCESS;
}


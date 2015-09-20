/**
 * \file
 * \version  $Id: SessionServer.h 36 2013-04-07 11:42:48Z  $
 * \author  ,
 * \date 2013年04月07日 14时55分53秒 CST
 * \brief 会话服务器
 *
 */

#ifndef _SESSIONSERVER_H_
#define _SESSIONSERVER_H_

#include "zSubNetService.h"
#include "Fir.h"
#include "zMisc.h"
#include "zMemDBPool.h"
#include "zCmdHandle.h"

class zDBConnPool;
class MetaData;
class SessionUser;

/**
 * \brief 定义计费服务类
 *
 * 这个类使用了Singleton设计模式，保证了一个进程中只有一个类的实例
 *
 */
class SessionService : public zSubNetService, public Singleton<SessionService>
{
	friend class Singleton<SessionService>;
	public:

		bool msgParse_SuperService(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen);

		/**
		 * \brief 虚析构函数
		 *
		 */
		~SessionService()
		{
			instance = NULL;

			//关闭线程池
			if (taskPool)
			{
				taskPool->final();
				SAFE_DELETE(taskPool);
			}
		}

		const int getPoolSize() const
		{
			if(taskPool)
			{
				return taskPool->getSize();
			}
			else
			{
				return 0;
			}
		}

		void reloadconfig();
		bool isSequeueTerminate()
		{
			return (taskPool == NULL);
		}

		/**
		 * \brief 指向数据库连接池实例的指针
		 *
		 */
		static zDBConnPool *dbConnPool;

		/**
		 * \brief 指向数据库表管理器的指针
		 *
		 */
		static MetaData* metaData;		

		/**
		 * \brief 消息解析者管理器
		 */
		zCmdHandleManager cmd_handle_manager;

		/**
		 * \brief 指向交易日志的指针
		 *
				static zLogger* miniLogger;		
		 */

		//初始化加载数据库和配置
		bool initAllData();


		static zLogger* billlog;

		static zLogger* login_logger; // 登录日志
		
		static DWORD online_num;

		GameZone_t zoneID;
		std::string zonename;
    private:
        //处理superCmd消息
        bool msgParseSuperCmd(const CMD::SUPER::SuperServerNull *superNull,const DWORD nCmdLen);
        
        /**
		 * \brief 构造函数
		 *
		 */
		SessionService() : zSubNetService("会话服务器", SESSIONSERVER)
		{
			taskPool = NULL;
		}

		bool init();
		void newTCPTask(const int sock, const struct sockaddr_in *addr);
		void final();

		bool initLogger();
		bool initLoginLogger();
    
    private:

		/**
		 * \brief 类的唯一实例指针
		 *
		 */
		static SessionService *instance;

		zTCPTaskPool *taskPool;				/**< TCP连接池的指针 */

};

#endif


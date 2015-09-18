/**
 * \file
 * \version  $Id: SceneServer.h 67 2013-04-23 09:44:20Z  $
 * \author  ,
 * \date 2013年04月07日 15时55分53秒 CST
 * \brief Fir场景服务器
 *
 */

#ifndef _SCENESERVER_H_
#define _SCENESERVER_H_

#include "zSubNetService.h"
#include "Fir.h"
#include "zMisc.h"
#include "zMemDBPool.h"
#include "zCmdHandle.h"
#include "MessageQueue.h"

class SceneUser;

//SUPER指令缓冲
class SuperCmdQueue : public MessageBuffer<100>
{
	public:
		bool cmdMsgParse(const CMD::t_NullCmd *, const unsigned int);
		bool allzoneMsgParse(const CMD::t_NullCmd *, const unsigned int);
};

/**
 * \brief 定义计费服务类
 *
 * 这个类使用了Singleton设计模式，保证了一个进程中只有一个类的实例
 *
 */
class SceneService : public zSubNetService, public Singleton<SceneService>
{
	friend class Singleton<SceneService>;
	public:
		bool md5Verify;//MD5存档验证
		int writeBackGroup;
		GameZone_t zoneID;
		SuperCmdQueue superCmd;
	public:

		bool msgParse_SuperService(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen);
		
		WORD getZoneID () const
		{
			return zoneID.zone;
		}
		/**
		 * \brief 虚析构函数
		 *
		 */
		~SceneService()
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
			return taskPool == NULL;
		}

		
		/**
		 * \brief 指向交易日志的指针
		 *
				static zLogger* miniLogger;		
		 */
		static DWORD cmd_record[4];
		static char cmd_recordNew[zSocket::MAX_DATASIZE];
		static DWORD cmd_len;
		/**
		 * \brief 分布式内存数据库连接池
		 */
		zCmdHandleManager cmd_handle_manager;
	
		bool sendCmdToAllZone(const void *pstrCmd, const int nCmdLen);	
	private:

		/**
		 * \brief 类的唯一实例指针
		 *
		 */
		static SceneService *instance;

		zTCPTaskPool *taskPool;				/**< TCP连接池的指针 */

		/**
		 * \brief 构造函数
		 *
		 */
		SceneService() : zSubNetService("场景服务器", SCENESSERVER)
		{
			taskPool = NULL;
			md5Verify = false;
			writeBackGroup = 10;
		}

		bool init();
		bool initLogic();
		void newTCPTask(const int sock, const struct sockaddr_in *addr);
		void final();
};

#endif


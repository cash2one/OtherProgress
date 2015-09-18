/**
 * \file
 * \version  $Id: RecordServer.h 24 2013-03-30 08:04:25Z  $
 * \author  ,okyhc@263.sina.com
 * \date 2004年12月10日 10时55分53秒 CST
 * \brief Fir项目档案服务器，用于创建、储存和读取档案
 *
 */

#ifndef _RecordServer_h_
#define _RecordServer_h_

#include "zSubNetService.h"
#include "Fir.h"
#include "zMisc.h"
#include "zDBConnPool.h"
#include "zMemDBPool.h"



struct ProvideHome
{
	ProvideHome()
	{
		provideid = 0;
		mapid = 0;
		x = 0;
		y = 0;
//		bzero(mapName, sizeof(mapName));
	}

	DWORD provideid;
	DWORD mapid;
	DWORD x;
	DWORD y;
	std::string  mapName;
};

class MetaData;
/**
 * \brief 定义档案服务类
 *
 * 项目档案服务器，用于创建、储存和读取档案<br>
 * 这个类使用了Singleton设计模式，保证了一个进程中只有一个类的实例
 *
 */
class RecordService : public zSubNetService, public Singleton<RecordService>
{
	friend class Singleton<RecordService>;
	public:

		bool msgParse_SuperService(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen);

		/**
		 * \brief 虚析构函数
		 *
		 */
		~RecordService()
		{
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

		bool loadProvideHome();

		/**
		 * \brief 指向数据库连接池实例的指针
		 *
		 */
		static zDBConnPool *dbConnPool;
		static MetaData* metaData;

		/**
		 * \brief 服务器版本号，角色转区时使用，以校验是否能够转区
		 */
		DWORD verify_version;

		DWORD change_level; //允许转区的等级
		bool travel_limit;  //跨区旅游无等级限制

		DWORD limitRegisterDeadline;//限制注册人数的截止日期
		std::map<DWORD, ProvideHome> home_map;

		GameZone_t zoneID;
	private:

		
		/**
		 * \brief 类的唯一实例指针
		 *
		 */
		static RecordService *instance;

		zTCPTaskPool *taskPool;				/**< TCP连接池的指针 */

		/**
		 * \brief 构造函数
		 *
		 */
		RecordService() : zSubNetService("档案服务器", RECORDSERVER)
		{
			taskPool = NULL;
			change_level = 0;
			travel_limit = false;
		}

		bool init();
		void newTCPTask(const int sock, const struct sockaddr_in *addr);
		void final();
};

#endif


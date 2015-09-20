#ifndef _AllZoneClientManager_h_
#define _AllZoneClientManager_h_

#include <map>
#include <set>

#include "zTCPClientTask.h"
#include "zTCPClientTaskPool.h"
#include "AllZoneClient.h"
#include "zTime.h"
#include "zRWLock.h"

/**
 * \brief 定义服务器信息采集连接的客户端管理容器
 */
class AllZoneClientManager : public Singleton<AllZoneClientManager>
{
	friend class Singleton<AllZoneClientManager>;
	public:

		~AllZoneClientManager();

		bool init();
		void timeAction(const zTime &ct);
		void add(AllZoneClient *infoClient);
		void remove(AllZoneClient *infoClient);
		bool broadcastOne(const void *pstrCmd, int nCmdLen);
		bool broadcastRandom(const void *pstrCmd, int nCmdLen);
		bool sendTo(const DWORD tempid, const void *pstrCmd, int nCmdLen);
		void resetState();
		bool reload();

	private:

		AllZoneClientManager();
		static AllZoneClientManager *instance;

		/**
		 * \brief 客户端连接管理池
		 */
		zTCPClientTaskPool *infoClientPool;
		/**
		 * \brief 进行断线重连检测的时间记录
		 */
		zTime actionTimer;

		/**
		 * \brief 存放连接已经成功的连接容器类型
		 */
		typedef std::map<const DWORD, AllZoneClient *> AllZoneClient_map;
		typedef AllZoneClient_map::iterator iter;
		typedef AllZoneClient_map::const_iterator const_iter;
		typedef AllZoneClient_map::value_type value_type;
		/**
		 * \brief 存放连接已经成功的连接容器
		 */
		AllZoneClient_map allClients;

		struct lt_client
		{
			bool operator()(AllZoneClient *s1, AllZoneClient *s2) const
			{
				return s1->getNetType() < s2->getNetType();
			}
		};
		typedef std::multiset<AllZoneClient *, lt_client> AllZoneClient_set;
		AllZoneClient_set setter;

		/**
		 * \brief 容器访问读写锁
		 */
		zRWLock rwlock;

};

#endif


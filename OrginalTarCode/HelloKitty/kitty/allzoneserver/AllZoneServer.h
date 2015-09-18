/**
 * \file
 * \version  $Id: SuperServer.h 75 2013-04-25 05:10:39Z  $
 * \author  ,@163.com
 * \date 2004年11月29日 17时19分12秒 CST
 * \brief 实现服务器管理器
 *
 * 对一个区中的所有服务器进行管理
 * 
 */

#ifndef _AllZoneServer_h_
#define _AllZoneServer_h_

#include <iostream>
#include <string>
#include <ext/numeric>

#include "zService.h"
#include "zThread.h"
#include "zSocket.h"
#include "zTCPServer.h"
#include "zMNetService.h"
#include "ZoneTask.h"
#include "zDBConnPool.h"
#include "zMisc.h"
#include "zMemDBPool.h"
#include "zTCPTaskPool.h"
#include "zNewHttpTaskPool.h"

class MetaData;
/**
 * \brief 服务器管理器类
 *
 * 派生了基类<code>zNetService</code>
 *
 */
class AllZoneService : public zMNetService, public Singleton<AllZoneService>
{
	friend class Singleton<AllZoneService>;
	public:

		/**
		 * \brief 析构函数
		 *
		 * 虚函数
		 *
		 */
		~AllZoneService()
		{
			instance = NULL;

			//关闭线程池
			if (taskPool)
			{
				taskPool->final();
				SAFE_DELETE(taskPool);
			}
		}

#ifdef _OP_TOOL_VERSION
		//运维属性察看工具
		bool reSetDBPool(std::string str);//重置数据库池
#endif
		const int getPoolSize() const
		{
			if (taskPool)
				return taskPool->getSize();
			else
				return 0;
		}

		void reloadconfig();

		/**
		 * \brief 获取ip地址
		 * \return 返回ip地址
		 */
		const char *getIP() const
		{
			return pstrIP;
		}

		/**
		 * \brief 获取端口
		 * \return 返回端口
		 */
		const WORD getPort() const
		{
			return wdPort;
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

		bool sendCmdToScene(DWORD zoneid, DWORD sceneid, const void *pstrCmd, const int nCmdLen);
	private:

		//记录执行过的gm工具指令
		std::map<std::string,QWORD> gmtoolcommandsmap;

		char pstrName[MAX_NAMESIZE];		/**< 服务器名称 */
		char pstrIP[MAX_IP_LENGTH];			/**< 服务器内网地址 */
		WORD wdPort;						/**< 服务器内网端口，也就是邦定端口 */
		char pstrExtIP[MAX_IP_LENGTH];		/**< 服务器外网地址，也就是防火墙地址 */
		WORD wdExtPort;						/**< 服务器外网端口，也就是映射到防火墙的端口 */
		/**
		 * \brief 类的唯一实例指针
		 *
		 */
		static AllZoneService *instance;

		zTCPTaskPool *taskPool;				/**< TCP连接池的指针 */
		/**
		 * \brief 构造函数
		 *
		 */
		AllZoneService() : zMNetService("服务器管理器")
	{
		bzero(pstrName, sizeof(pstrName));
		bzero(pstrIP, sizeof(pstrIP));
		wdPort = 0;
		bzero(pstrExtIP, sizeof(pstrExtIP));
		wdExtPort = 0;
		taskPool = NULL;
	}

		bool init();

		void newTCPTask(const int sock, const unsigned short srcPort);
		//void newTCPTask(const int sock, const struct sockaddr_in *addr);
		void final();
};


#endif


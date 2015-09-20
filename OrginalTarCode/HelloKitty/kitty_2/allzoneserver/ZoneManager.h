/**
 * \file
 * \version  $Id: ZoneManager.h 70 2013-04-23 13:26:44Z  $
 * \author  ,@163.com
 * \date 2004年12月13日 18时44分39秒 CST
 * \brief 定义服务器管理容器
 *
 * 这个容器包括全局容器和唯一性验证容器
 * 
 */


#ifndef _ZoneManager_h_
#define _ZoneManager_h_

#include <iostream>
#include <list>
#include <unordered_map>

#include "ZoneTask.h"
#include "zMutex.h"
#include "zNoncopyable.h"
#include "zRWLock.h"

/**
 * \brief 服务器管理容器类
 *
 * 这个容器包括全局容器和唯一性验证容器
 *
 */
class ZoneManager : public Singleton<ZoneManager>
{
	friend class Singleton<ZoneManager>;
	public:

		/**
		 * \brief 缺省析构函数
		 *
		 */
		~ZoneManager() {};

		void addServer(ZoneTask *task);
		void removeServer(ZoneTask *task);
		ZoneTask* getServer(DWORD dwServerID);
		bool uniqueAdd(ZoneTask *task);
		bool uniqueVerify(const DWORD dwServerID);
		bool uniqueRemove(ZoneTask *task);
		bool broadcast(const void *pstrCmd, int nCmdLen);
		bool broadcastByID(const DWORD dwServerID, const void *pstrCmd, int nCmdLen);

		void execEvery();
	private:

		/**
		 * \brief 定义服务器容器类型
		 *
		 */
		typedef std::list<ZoneTask *> Container;
		/**
		 * \brief 定义服务器容器类型的迭代器
		 *
		 */
		typedef Container::iterator Container_iterator;
		/**
		 * \brief 定义服务器容器类型的常量迭代器
		 *
		 */
		typedef Container::const_iterator Containter_const_iterator;
		/**
		 * \brief 定义了服务器的唯一性验证容器类型
		 * 
		 **/
		typedef std::unordered_map<DWORD, ZoneTask *> ZoneTaskHashmap;
		/**
		 * \brief 定义容器的迭代器类型
		 *
		 */
		typedef ZoneTaskHashmap::iterator ZoneTaskHashmap_iterator;
		/**
		 * \brief 定义了容器的常量迭代器类型
		 *
		 */
		typedef ZoneTaskHashmap::const_iterator ZoneTaskHashmap_const_iterator;
		/**
		 * \brief 定义了容器的键值对类型
		 *
		 */
		typedef ZoneTaskHashmap::value_type ZoneTaskHashmap_pair;
		/**
		 * \brief 容器访问的互斥变量
		 *
		 */
		zMutex mutex;
		/**
		 * \brief 服务器全局容器的实例
		 *
		 */
		Container container;
		/**
		 * \brief 唯一性容器实例
		 *
		 */
		ZoneTaskHashmap taskUniqueContainer;

		/**
		 * \brief 保存连接成功的场景<ID,IP> 类型容器
		 *
		 */
		typedef std::unordered_map<DWORD, std::string> SceneInfoHashmap;
		SceneInfoHashmap sceneinfo;


		/**
		 * \brief 定义迭代器类型
		 */
		typedef SceneInfoHashmap::iterator SceneInfoHashmap_iterator;

		/**
		 * \brief 定义窗口的键值对类型
		 */
		typedef SceneInfoHashmap::value_type SceneInfohashmap_pair;


		/**
		 * \brief 类的唯一实例指针
		 *
		 */
		static ZoneManager *instance;

		/**
		 * \brief 构造函数
		 *
		 */
		ZoneManager() {};

		zRWLock rwlock;

};

#endif


/**
 * \file
 * \version  $Id: SessionTaskManager.h 72 2013-04-24 03:55:51Z  $
 * \author  ，
 * \date 2013年04月07日 14时28分53秒 CST
 * \brief 管理子连接的容器
 *
 * 
 */


#ifndef _SESSIONTASKMANAGER_H_
#define _SESSIONTASKMANAGER_H_

#include <iostream>
#include <set>
#include <unordered_map>

#include "SessionTask.h"
#include "zRWLock.h"
#include "zSingleton.h"

/**
 * \brief 计费服务器子连接管理器
 *
 */
class SessionTaskManager : public Fir::Singleton<SessionTaskManager>
{
	public:

		/**
		 * \brief 析构函数
		 *
		 */
		~SessionTaskManager() {};

		/**
		 * \brief 构造函数
		 *
		 */
		SessionTaskManager() {};

		bool uniqueAdd(SessionTask *task);
		bool uniqueRemove(SessionTask *task);
		void addSessionTask(SessionTask *task);		
		void removeSessionTask(SessionTask *task);
		bool broadcastByID(const WORD wdServerID, const void *pstrCmd, int nCmdLen);
		bool broadcastByType(const WORD wdType, const void *pstrCmd, int nCmdLen);
		bool broadcastGateway(const void *pstrCmd, int nCmdLen);
		bool sendCmdToWorld(const void *pstrCmd, int nCmdLen,bool worldChat = false);
		std::set<DWORD> getServerIds(const WORD wdType);
		SessionTask *getTaskByID(const WORD wdServerID);
		void execEvery();
		SessionTask* getMinLoad();
		SessionTask* getOneGateway();
	private:

		/**
		 * \brief 类的唯一实例指针
		 *
		 */
		static SessionTaskManager *instance;

				/**
		 * \brief 定义容器类型
		 *
		 */
		typedef std::unordered_map<WORD, SessionTask *> SessionTaskHashmap;
		/**
		 * \brief 定义容器迭代器类型
		 *
		 */
		typedef SessionTaskHashmap::iterator SessionTaskHashmap_iterator;
		/**
		 * \brief 定义容器常量迭代器类型
		 *
		 */
		typedef SessionTaskHashmap::const_iterator SessionTaskHashmap_const_iterator;
		/**
		 * \brief 定义容器键值对类型
		 *
		 */
		typedef SessionTaskHashmap::value_type SessionTaskHashmap_pair;
		/**
		 * \brief 容器访问互斥变量
		 *
		 */
		zRWLock rwlock;
		/**
		 * \brief 声明一个容器，存放所有的子连接
		 *
		 */
		SessionTaskHashmap sessionTaskSet;

		/**
		 * \brief 与网关服务器连接的链表
		 *
		 */
		typedef std::list<SessionTask *> TaskContainer;
		TaskContainer gatewayTaskList;

};

#endif


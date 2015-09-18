/**
 * \file
 * \version  $Id: SceneTaskManager.h 36 2013-04-07 11:42:48Z  $
 * \author  ,
 * \date 2013年04月07日 15时28分53秒 CST
 * \brief 管理场景连接的容器
 *
 * 
 */


#ifndef _SCENETASKMANAGER_H_
#define _SCENETASKMANAGER_H_

#include <iostream>
#include <unordered_map>

#include "SceneTask.h"
#include "zRWLock.h"

/**
 * \brief 计费服务器子连接管理器
 *
 */
class SceneTaskManager : public Singleton<SceneTaskManager>
{
	friend class Singleton<SceneTaskManager>;
	public:

		/**
		 * \brief 析构函数
		 *
		 */
		~SceneTaskManager() {};

		bool uniqueAdd(SceneTask *task);
		bool uniqueRemove(SceneTask *task);
		bool broadcastByID(const WORD wdServerID, const void *pstrCmd, int nCmdLen);
		SceneTask *getTaskByID(const WORD wdServerID);
		void execEvery();

	private:

		/**
		 * \brief 类的唯一实例指针
		 *
		 */
		static SceneTaskManager *instance;

		/**
		 * \brief 构造函数
		 *
		 */
		SceneTaskManager() {};

		/**
		 * \brief 定义容器类型
		 *
		 */
		typedef std::unordered_map<WORD, SceneTask *> SceneTaskHashmap;
		/**
		 * \brief 定义容器迭代器类型
		 *
		 */
		typedef SceneTaskHashmap::iterator SceneTaskHashmap_iterator;
		/**
		 * \brief 定义容器常量迭代器类型
		 *
		 */
		typedef SceneTaskHashmap::const_iterator SceneTaskHashmap_const_iterator;
		/**
		 * \brief 定义容器键值对类型
		 *
		 */
		typedef SceneTaskHashmap::value_type SceneTaskHashmap_pair;
		/**
		 * \brief 容器访问互斥变量
		 *
		 */
		zRWLock rwlock;
		/**
		 * \brief 声明一个容器，存放所有的子连接
		 *
		 */
		SceneTaskHashmap sceneTaskSet;

};

#endif


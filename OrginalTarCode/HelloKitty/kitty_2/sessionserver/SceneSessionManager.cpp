/*
 * \file
 * \version  $Id: SceneSessionManager.cpp 29 2013-04-07 01:39:43Z  $
 * \author  ,
 * \date 2013年03月31日 09时53分30秒 CST
 * \brief 实现场景会话管理器
 *
 * 
 */

#include "SceneSessionManager.h"
#include "Fir.h"
#include "SessionCommand.h"
#include "SessionTaskManager.h"
#include "zDBConnPool.h"
#include "zMetaData.h"
#include "SessionServer.h"
#include "zXMLParser.h"
#include "TimeTick.h"
#include  <ext/iterator>


/**
 * \brief 构造函数
 */
SceneSessionManager::SceneSessionManager():zSceneManager()
{
	inited=false;
}

/**
 * \brief 析构函数
 */
SceneSessionManager::~SceneSessionManager()
{
	final();
}


/**
 * \brief 得到一个唯一id
 * \param tempid 输出，得到的id
 * \return 是否成功
 */
bool SceneSessionManager::getUniqeID(DWORD &tempid)
{
	return true;
}

/**
 * \brief 释放一个唯一的id
 * \param tempid 要释放的id
 */
void SceneSessionManager::putUniqeID(const DWORD &tempid)
{
}

/**
 * \brief 初始化场景会话管理器
 * \return 是否成功
 */
bool SceneSessionManager::init()
{
	if(inited)
	{
		Fir::logger->warn("Scene Session管理器已经被初始化过...");
		return true;
	}
	inited=true;
	Fir::logger->info("初始化Scene Session管理器成功...");
	return inited;
}

/**
 * \brief 结束场景管理器
 */
void SceneSessionManager::final()
{
	if(inited)
	{
		inited=false;
	}
}

/**
 * \brief 向管理器中添加一个场景
 * \param scene 要添加的场景
 * \return 是否添加成功
 */
bool SceneSessionManager::addScene(SceneSession *scene)
{
	rwlock.wrlock();
	bool ret= addEntry(scene);
	rwlock.unlock();
	return ret;
}


/**
 * \brief 根据id得到场景指针
 * \param id 场景id
 * \return 场景指针，失败返回0
 */
SceneSession * SceneSessionManager::getSceneByID(DWORD id)
{
	return (SceneSession *)zSceneManager::getSceneByID(id);
}

/**
 * \brief 从管理器移除一个场景
 * \param scene 要移除的场景
 */
void SceneSessionManager::removeScene(SceneSession *scene)
{
	rwlock.wrlock();
	removeEntry(scene);
	rwlock.unlock();
}

/**
 * \brief 场景服务器关闭，需要注销一些地图
 * \param task 该场景服务器连接的SessionTask
 */
void SceneSessionManager::removeAllSceneByTask(SessionTask *task)
{
	
	//struct removeAllSceneByTask :public removeEntry_Pred<SceneSession>
	//{
		//SessionTask *task;
		//bool isIt(SceneSession *ss)
		//{
			//return (ss->getTask()==task);
		//}
	//};
	//if(task==NULL || task->getType()!=SCENESSERVER) return;
	//removeAllSceneByTask rust;
	//rust.task=task;
	//removeScene_if(rust);
	//for(unsigned int i=0,n=rust.removed.size();i<n;i++)
	//{
		//if (((SceneSession *)rust.removed[i])->isDynMap())
			//removeDynScene((SceneSession *)rust.removed[i]);
		//BossManager::getMe().removeScene((SceneSession *)rust.removed[i]);
		//BaoBaoBossManager::getMe().removeScene((SceneSession *)rust.removed[i]);
		//SAFE_DELETE(rust.removed[i]);
	//}
	//PkGradeManager::getMe().setMapNums();
}

SessionTask* SceneSessionManager::getMinLoad()
{
	struct GetSceneByMinActive: public execEntry<SceneSession>
	{
		SceneSession *ret;
		DWORD min_active;

		GetSceneByMinActive() : ret(NULL)
		{ 
			min_active = 0;
		}
		
		bool exec(SceneSession *scene)
		{
			if (min_active == 0) {ret = scene; min_active = scene->total_active; return true;}

			if (min_active !=0 && scene->total_active<min_active)
			{
				ret = scene;
				min_active = scene->total_active;
			}

			return true;
		}
	};

	GetSceneByMinActive gsma;
	execEveryScene(gsma);
	return gsma.ret->getTask();
}


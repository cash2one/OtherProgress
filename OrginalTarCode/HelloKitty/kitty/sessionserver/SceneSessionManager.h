/**
 * \file
 * \version  $Id: SceneSessionManager.h 34 2013-04-07 06:21:36Z  $
 * \author  ,
 * \date 2013年3月30日 11时19分09秒 CST
 * \brief 场景会话管理器，管理会话上注册的场景服务器
 *
 * 
 */

#ifndef _SESSIONMANAGER_H_
#define _SESSIONMANAGER_H_

#include "Session.h"
#include "zUniqueID.h"
#include "SessionTask.h"
#include "zSceneManager.h"
#include "SceneSession.h"


/**
 * \brief 场景会话管理器
 *
 */
class SceneSessionManager:public zSceneManager, public Singleton<SceneSessionManager>
{
	friend class Singleton<SceneSessionManager>;
	private:
		///是否初始化成功
		bool inited;

		SceneSessionManager();
		~SceneSessionManager();
		bool getUniqeID(DWORD &tempid);
		void putUniqeID(const DWORD &tempid);

	public:
		bool init();
		void final();

		bool addScene(SceneSession *scene);
		SceneSession * getSceneByID(DWORD id);
		//取当前负载最小的场景服务器
		SessionTask*  getMinLoad();
		void removeScene(SceneSession *scene);
		void removeAllSceneByTask(SessionTask *task);
};

#endif

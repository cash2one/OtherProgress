/**
 * \file	SceneUser.h
 * \version  	$Id: SceneUserManager.h 37 2013-04-08 01:52:56Z  $
 * \author  	,
 * \date 	2013年04月07日 15时48分31秒 CST
 * \brief 	场景用户管理器定义
 *
 * 
 */

#ifndef _SCENEUSERMANAGER_H_
#define _SCENEUSERMANAGER_H_
#include <functional>
#include "SceneUser.h"
#include "zRWLock.h"

class SceneUserManager : public Singleton<SceneUserManager>
{
	friend class Singleton<SceneUserManager>;
	private:
		zRWLock rwlock;

		SceneUserManager();
		~SceneUserManager();

	protected:
		std::unordered_map<DWORD,SceneUser*> m_mapUsers;

	public:
		bool addUser(SceneUser *user);

		SceneUser* getUserByID(QWORD charid);
		
		void removeUser(QWORD charid);

		void update();

		void saveAll();
		void delAll();

		typedef std::function<void (SceneUser*)> UserFunction;
		void execAll(UserFunction func);
};
#endif

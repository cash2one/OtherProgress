/**
 * \file	SceneUser.h
 * \version  	$Id: SceneUserManager.cpp 37 2013-04-08 01:52:56Z  $
 * \author  	,
 * \date 	2013年04月07日 15时48分31秒 CST
 * \brief 	场景用户管理器定义
 *
 * 
 */

#include "SceneUserManager.h"
#include "SceneServer.h"
#include "SceneTaskManager.h"
#include "zMetaData.h"


SceneUserManager::SceneUserManager()
{
}

SceneUserManager::~SceneUserManager()
{
	for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
	{
		SAFE_DELETE(itr->second);
	}
	m_mapUsers.clear();
}

bool SceneUserManager::addUser(SceneUser *user)
{   
	if(NULL == user) return false;

	zRWLock_scope_wrlock lock(rwlock); // 获取写锁
	
	if(m_mapUsers.find(user->charid) != m_mapUsers.end())
		return false;

	return m_mapUsers.insert(std::make_pair(user->charid,user)).second;
	
}   

SceneUser* SceneUserManager::getUserByID(QWORD charid)
{
	zRWLock_scope_rdlock lock(rwlock); // 获取读锁

	auto itr=m_mapUsers.find(charid);
	if(itr == m_mapUsers.end())
		return NULL;

	return itr->second;
}

void SceneUserManager::update()
{
	static DWORD saveGroup = 0;
	
	saveGroup = (saveGroup+1)%SceneService::getMe().writeBackGroup;
	
	zRWLock_scope_rdlock lock(rwlock); // 获取读锁

	for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
	{
		SceneUser* u = itr->second;
		if(NULL == u) continue;
		if(u->charid%SceneService::getMe().writeBackGroup == saveGroup)
			u->save();
	}	
}

void SceneUserManager::saveAll()
{
	zRWLock_scope_rdlock lock(rwlock); // 获取读锁
	for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
	{
		SceneUser* u = itr->second;
		if(NULL == u) continue;
		u->save();
	}
}

void SceneUserManager::execAll(UserFunction func)
{
	zRWLock_scope_rdlock lock(rwlock); // 获取读锁
	for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
	{
		SceneUser* u = itr->second;
		if(NULL == u) continue;
		func(u);
	}
}
void SceneUserManager::delAll()
{
	zRWLock_scope_rdlock lock(rwlock); // 获取读锁
	for (auto it = m_mapUsers.begin(); it != m_mapUsers.end(); ++it)
	{
		SAFE_DELETE(it->second);
	}
	m_mapUsers.clear();
}

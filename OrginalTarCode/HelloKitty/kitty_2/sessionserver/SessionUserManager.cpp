#include "SessionUserManager.h"
#include "SessionServer.h"
#include "SessionTaskManager.h"
#include "zMetaData.h"
#include "TimeTick.h"

SessionUserManager::SessionUserManager()
{
}
SessionUserManager::~SessionUserManager()
{
}

SessionUser* SessionUserManager::getUserByID(QWORD charid)
{
	zRWLock_scope_rdlock lock(rwlock); // 获取读锁
	
	auto itr=m_mapUsers.find(charid);
	if(itr == m_mapUsers.end())
		return NULL;

	return itr->second;
}

SessionUser* SessionUserManager::getUserByName(std::string nickname)
{
	zRWLock_scope_rdlock lock(rwlock); // 获取读锁

	auto itr_charid = m_mapCharids.find(nickname);
	if(itr_charid == m_mapCharids.end())
		return NULL;

	QWORD charid = itr_charid->second;

	auto itr=m_mapUsers.find(charid);
	if(itr == m_mapUsers.end())
		return NULL;

	return itr->second;
}

bool SessionUserManager::addUser(SessionUser *user)
{
	if(NULL == user) return false;

	zRWLock_scope_wrlock lock(rwlock); // 获取写锁
	if (m_mapCharids.find(user->nickname) != m_mapCharids.end())
		return false;

	if(m_mapUsers.find(user->charid) != m_mapUsers.end())
		return false;

	m_mapCharids.insert(std::make_pair(user->nickname, user->charid));
	m_mapUsers.insert(std::make_pair(user->charid,user));

	return true;
}

void SessionUserManager::execAll(UserFunction func)
{
	zRWLock_scope_rdlock lock(rwlock); // 获取读锁
	for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
	{   
		SessionUser* u = itr->second;
		if(NULL == u) continue;
		func(u);
	}
}

void OnlineUserExec(SessionUser* u, DWORD onlinetime, DWORD* pCount)
{
	if(u==NULL || pCount==NULL) return;

	if(u->lastOnlineTime > onlinetime)
	{
		(*pCount)++;
	}
}

// 获得在线人数
DWORD SessionUserManager::getonlinenum(DWORD second)
{
	DWORD onlinetime = SessionTimeTick::currentTime.sec() - second;

	DWORD result = 0;
	execAll(std::bind(&OnlineUserExec,std::placeholders::_1,onlinetime,&result));

	return result;
}

void SessionUserManager::removeUser(QWORD charid)
{
	zRWLock_scope_wrlock lock(rwlock); // 获取写锁

	auto itrfind = m_mapUsers.find(charid);
	if(itrfind == m_mapUsers.end())
		return;

	SessionUser* u = itrfind->second;
	if(u != NULL)
	{
		m_mapCharids.erase(u->nickname);
	}
	SAFE_DELETE(u);
	m_mapUsers.erase(charid);
}

void SessionUserManager::removeUserBySceneID(SessionTask *task)
{
	if (NULL == task) return;
	
	std::vector<DWORD> vecDels;
	for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
	{
		SessionUser* u = itr->second;
		if(NULL == u) continue;
		if(u->m_scene_id == task->getID())
		{
			vecDels.push_back(u->charid);
		}
	}
	
	for(DWORD i=0; i<vecDels.size(); i++)
	{
		SessionUser *pUser = SessionUserManager::getMe().getUserByID(vecDels[i]);
		if(NULL != pUser)
		{
			pUser->unreg();
			pUser->update_scene(0);
			SessionUserManager::getMe().removeUser(pUser->charid);
		}
	}
}


void SessionUserManager::removeUserByGatewayID(SessionTask *task)
{
	std::vector<DWORD> vecDels;
	for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
	{
		SessionUser* u = itr->second;
		if(NULL == u) continue;
		if(u->m_gate_id == task->getID())
		{
			vecDels.push_back(u->charid);
		}   
	}
		
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	for(DWORD i=0; i<vecDels.size(); i++)
	{
		SessionUser *pUser = SessionUserManager::getMe().getUserByID(vecDels[i]);
		if(pUser)
		{
			//清除网关状态
			if (handle)
			{
				handle->setInt("gatewaylogin", pUser->acctype, pUser->account.c_str(), "state", 0);
			}

			pUser->unreg();
		}
	}
}

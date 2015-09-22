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
#include "RedisMgr.h"


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

    bool result = m_mapUsers.insert(std::make_pair(user->charid,user)).second;
    if(result)
    {
        zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(user->charid % MAX_MEM_DB+1);
        if(handle2)
            handle2->setInt("playerscene",user->charid,"sceneid",SceneService::getMe().getServerID());  
        zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
        if(handle)
            handle->setInt("playerscene",SceneService::getMe().getServerID(),"secnenum",getSize());
    }
    return result;

}   

SceneUser* SceneUserManager::getUserByID(QWORD charid)
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁

    auto itr=m_mapUsers.find(charid);
    if(itr == m_mapUsers.end())
        return NULL;

    return itr->second;
}

void SceneUserManager::removeUser(QWORD charid)
{

    zRWLock_scope_rdlock lock(rwlock); // 获取读锁

    auto itr = m_mapUsers.find(charid); 
    if(itr == m_mapUsers.end())
        return;
    zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(charid % MAX_MEM_DB+1);
    if(handle2)
        handle2->setInt("playerscene",charid,"sceneid",0);  
    //保存数据
    SceneUser *temp = itr->second;
    if(temp)
    {
        temp->save();
    }
    SAFE_DELETE(itr->second);
    m_mapUsers.erase(itr);
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if(handle)
        handle->setInt("playerscene",SceneService::getMe().getServerID(),"secnenum",getSize());
    Fir::logger->info("删除 %lu", charid);  


}


void SceneUserManager::loop()
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    std::vector<QWORD> vecDel;
    for(auto itr = m_mapUsers.begin(); itr != m_mapUsers.end();itr++ )
    {
        SceneUser* user = itr->second;
        if(NULL == user) 
        {
            vecDel.push_back(itr->first);
            continue;
        }
        if(!user->loop())
        {
            vecDel.push_back(itr->first);
        }

    }	
    for(auto iter = vecDel.begin();iter != vecDel.end(); iter++)
    {
        zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(*iter % MAX_MEM_DB+1);
        if( handle2 && handle2->isLock("playerlock",*iter,"newplayer"))
        {
            continue;
        }
        removeUser(*iter);
    }
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

void SceneUserManager::oneDay()
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SceneUser* u = itr->second;
        if(NULL == u) continue;
        u->brushDailyData();
    }	
}

void SceneUserManager::oneHour()
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SceneUser* u = itr->second;
        if(NULL == u) continue;
        u->m_burstEventManager.loop();
    }	
}

void SceneUserManager::checkAndBrushDailyData()
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SceneUser* u = itr->second;
        if(!u)
        {
            continue;
        }
        u->changeTime();
    }	
}

DWORD SceneUserManager::getSize()
{
    return m_mapUsers.size();
}

SceneUser* SceneUserManager::CreateTempUser(QWORD charid)
{
    zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(charid % MAX_MEM_DB+1);
    if(!handle2)
    {
        Fir::logger->error("用户临时创建, memdb 连接失败, %lu", charid);
        return NULL;
    }
    SceneUser* u  =  FIR_NEW SceneUser(NULL);
    if (!u)
    {
        return NULL;
    }
    if (handle2->getBin("charbase",charid,"charbase",(char*)&(u->charbase)) == 0)
    {
        Fir::logger->error("账号不存在 %lu", charid);  
        SAFE_DELETE(u);
        return NULL;
    }
    u->charid = u->charbase.charid;
    strncpy(u->nickname, u->charbase.nickname, sizeof(u->nickname));

    HelloKittyMsgData::Serialize binary;
    if(!RedisMgr::getMe().get_binary(u->charid,binary))
    {
        Fir::logger->error("[登录]:%u,%lu,%s 玩家临时创建场景，binary数据异常",u->accid,u->charid,u->nickname);
        SAFE_DELETE(u);
        return NULL;
    }
    u->setupBinaryArchive(binary);
    if(SceneUserManager::getMe().addUser(u))
    {
        return u;
    }
    Fir::logger->error("[登录]:%u,%lu,%s 角色临时创建失败", u->accid, u->charid, u->nickname);
    SAFE_DELETE(u);
    return NULL;

}

/**
 * \file
 * \version  $Id: SessionTaskManager.cpp 75 2013-04-25 05:10:39Z  $
 * \author  ,@163.com
 * \date 2004年12月20日 17时28分53秒 CST
 * \brief 管理子连接的容器
 *
 * 
 */


#include <iostream>

#include "SessionTask.h"
#include "SessionTaskManager.h"
#include "extractProtoMsg.h"

SessionTaskManager *SessionTaskManager::instance = NULL;

/**
 * \brief 添加一个子连接到容器中
 *
 * 如果子连接是网关，需要添加到网关连接链表中
 * 如果子连接是场景服务器，需要添加到场景连接链表中
 *
 * \param task 子连接任务
 */
void SessionTaskManager::addSessionTask(SessionTask *task)
{
	rwlock.wrlock();
	if (GATEWAYSERVER == task->getType())
	{
		gatewayTaskList.push_back(task);
	}
	rwlock.unlock();
}

/**
 * \brief 从容器中移除子连接任务
 *
 * 如果子连接是网关，需要从网关链表中移除
 * 如果子连接是场景服务器，需要从场景连接链表中移除
 *
 * \param task 子连接任务
 */
void SessionTaskManager::removeSessionTask(SessionTask *task)
{
	rwlock.wrlock();
	if (GATEWAYSERVER == task->getType())
	{
		gatewayTaskList.remove(task);
	}
	rwlock.unlock();
}
/**
 * \brief 向唯一性验证容器中添加一个子连接任务
 *
 * \param task 子连接任务
 * \return 添加连接是否成功
 */
bool SessionTaskManager::uniqueAdd(SessionTask *task)
{
	SessionTaskHashmap_const_iterator it;
	rwlock.wrlock();
	it = sessionTaskSet.find(task->getID());
	if (it != sessionTaskSet.end())
	{
		Fir::logger->error(__PRETTY_FUNCTION__);
		rwlock.unlock();
		return false;
	}
	sessionTaskSet.insert(SessionTaskHashmap_pair(task->getID(), task));
	rwlock.unlock();
	return true;
}

/**
 * \brief 从唯一性容器中移除一个子连接任务
 *
 * \param task 子连接任务
 * \return 移除是否成功
 */
bool SessionTaskManager::uniqueRemove(SessionTask *task)
{
	SessionTaskHashmap_iterator it;
	rwlock.wrlock();
	it = sessionTaskSet.find(task->getID());
	if (it != sessionTaskSet.end())
	{
		sessionTaskSet.erase(it);
	}
	else
		Fir::logger->warn(__PRETTY_FUNCTION__);
	rwlock.unlock();
	return true;
}

/**
 * \brief 向所有的网关连接广播指令
 *
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 指令长度                                      
 * \return 广播是否成功                                                 
 */
bool SessionTaskManager::broadcastGateway(const void *pstrCmd, int nCmdLen)
{                                                                       
	bool retval = true;                                                     
	rwlock.rdlock();                                                        
	for(auto it = gatewayTaskList.begin(); it != gatewayTaskList.end(); it++)            
	{                                                                       
		retval = (retval && (*it)->sendCmd(pstrCmd, nCmdLen));  
	}                                                               
	rwlock.unlock();                                                
	return retval;                                                          
}                                                                       
/**
 * \brief 向所有的网关发送世界指令                                      
 *                                                              
 * \param pstrCmd 待广播的指令                                  
 * \param nCmdLen 指令长度     
 * \param worldChat 是否只有需要公共聊天的玩家接受
 * \return 广播是否成功                                         
 */                                                             
bool SessionTaskManager::sendCmdToWorld(const void *pstrCmd, int nCmdLen,bool worldChat)
{                                                               
	using namespace CMD::SESSION;                                   
	char buf[zSocket::MAX_DATASIZE];                                
	t_Session_ForwardWorld * sfw =(t_Session_ForwardWorld*)buf;             
	constructInPlace(sfw);                                                  
	sfw->size=nCmdLen;                                              
	bcopy(pstrCmd,sfw->data,nCmdLen);
    
    std::string ret;
    encodeMessage(sfw,sizeof(t_Session_ForwardWorld) + sfw->size,ret);
	return broadcastGateway(ret.c_str(),ret.size());
}

/**
 * \brief 根据服务器编号广播指令
 *
 * \param wdServerID 待广播指令的服务器编号
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 指令长度
 * \return 广播是否成功
 */
bool SessionTaskManager::broadcastByID(const WORD wdServerID, const void *pstrCmd, int nCmdLen)
{
	bool retval = true;
	SessionTaskHashmap_iterator it;
	rwlock.rdlock();
	it = sessionTaskSet.find(wdServerID);
	if (it != sessionTaskSet.end())
	{
		retval = it->second->sendCmd(pstrCmd, nCmdLen);
	}
	rwlock.unlock();
	return retval;
}

/**
 * \brief 根据服务器编号广播指令
 *
 * \param wdServerID 待广播指令的服务器编号
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 指令长度
 * \return 广播是否成功
 */
bool SessionTaskManager::broadcastByType(const WORD wdType, const void *pstrCmd, int nCmdLen)
{
	bool retval = true;
	rwlock.rdlock();
	for (auto it = sessionTaskSet.begin(); it != sessionTaskSet.end(); ++it)
	{
		if (it->second && it->second->getType() == wdType)
		{
			retval = it->second->sendCmd(pstrCmd, nCmdLen);
		}
	}
	rwlock.unlock();
	return retval;
}

std::set<DWORD> SessionTaskManager::getServerIds(const WORD wdType)
{
	std::set<DWORD> setServers;
	rwlock.rdlock();
	for (auto it = sessionTaskSet.begin(); it != sessionTaskSet.end(); ++it)
	{   
		if (it->second && it->second->getType() == wdType)
		{   
			setServers.insert(it->first);
		}   
	}   
	rwlock.unlock();
	return setServers;
}

/**
 * \brief 根据服务器编号查找task
 *
 * \param wdServerID 待查找的服务器编号
 * \return 广播是否成功
 */
SessionTask *SessionTaskManager::getTaskByID(const WORD wdServerID)
{
	SessionTask *ret=NULL;
	SessionTaskHashmap_iterator it;
	rwlock.rdlock();
	it = sessionTaskSet.find(wdServerID);
	if (it != sessionTaskSet.end())
	{
		ret = it->second;
	}
	rwlock.unlock();
	return ret;
}

void SessionTaskManager::execEvery()
{
	SessionTaskHashmap_iterator it;
	SessionTask *task=NULL;
	rwlock.rdlock();
	it = sessionTaskSet.begin();
	for (; it != sessionTaskSet.end() ; it ++)
	{
		task=it->second;
		if(!task->checkRecycle())
		{
			task->doCmd();
		}
	}
	rwlock.unlock();

}


SessionTask* SessionTaskManager::getMinLoad()
{
	SessionTaskHashmap_iterator it;
	SessionTask *task=NULL;
	DWORD min_load = 0;

	rwlock.rdlock();
	it = sessionTaskSet.begin();
	for (; it != sessionTaskSet.end() ; it ++)
	{
		if (it->second && it->second->getType() == SCENESSERVER)
		{
#ifdef _ZJW_DEBUG
			Fir::logger->debug("挑选最小负载场景:%d", it->second->total_all);
#endif		

			if (NULL == task)
			{
				task = it->second;
				min_load = task->total_all;
				continue;
			}

			if (task->total_all == 0) break;

			if (min_load > it->second->total_all)
			{
				task = it->second;
				min_load = task->total_all;
			}
		}
	}
	rwlock.unlock();
	return task;
}

SessionTask* SessionTaskManager::getOneGateway()
{
	SessionTask *task=NULL;

	rwlock.rdlock();

	for (auto itr=sessionTaskSet.begin(); itr != sessionTaskSet.end() ; itr ++) 
	{
		if (itr->second && itr->second->getType() == GATEWAYSERVER)
		{
			task = itr->second;
		}
	}

	rwlock.unlock();
	return task;
}

/**
 * \file
 * \version  $Id: ZoneManager.cpp 70 2013-04-23 13:26:44Z  $
 * \author  ,@163.com
 * \date 2004年12月13日 18时44分39秒 CST
 * \brief 实现服务器管理容器
 *
 * 这个容器包括全局容器和唯一性验证容器
 * 
 */


#include <iostream>
#include <list>

#include "ZoneTask.h"
#include "zMutex.h"
#include "zNoncopyable.h"
#include "ZoneManager.h"
#include "Fir.h"

ZoneManager *ZoneManager::instance = NULL;

/**
 * \brief 添加一个服务器连接任务到容器中
 *
 * \param task 服务器连接任务
 */
void ZoneManager::addServer(ZoneTask *task)
{
	if (task)
	{
		zRWLock_scope_wrlock scope_wrlock(rwlock);
		//Fir::logger->debug("%s: %u", __FUNCTION__, task->getID());
		container.push_front(task);
	}
}

/**
 * \brief 从容器中删除一个服务器连接任务
 *
 * \param task 服务器连接任务
 */
void ZoneManager::removeServer(ZoneTask *task)
{
	if (task)
	{
		zRWLock_scope_wrlock scope_wrlock(rwlock);
		//Fir::logger->debug("%s: %u", __FUNCTION__, task->getID());
		container.remove(task);
	}
}

/**
 * \brief 根据编号查找一个服务器连接任务
 *
 * \param wdServerID 服务器编号
 * \return 返回适合的服务器连接任务
 */
ZoneTask *ZoneManager::getServer(DWORD dwServerID)
{
	Containter_const_iterator it;
	ZoneTask *retval = NULL;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(it = container.begin(); it != container.end(); it++)
	{
		if ((*it)->getID() == dwServerID)
		{
			retval = *it;
			break;
		}
	}

	return retval;
}


/**
 * \brief 把一个服务器连接任务添加到唯一性容器中
 *
 * \param task 服务器连接任务
 * \return 添加是否成功，也就是唯一性验证是否成功
 */
bool ZoneManager::uniqueAdd(ZoneTask *task)
{
	ZoneTaskHashmap_const_iterator it;
	zRWLock_scope_wrlock scope_wrlock(rwlock);
	it = taskUniqueContainer.find(task->getID());
	if (it != taskUniqueContainer.end())
	{
		Fir::logger->error("%s", __PRETTY_FUNCTION__);
		return false;
	}
	taskUniqueContainer.insert(ZoneTaskHashmap_pair(task->getID(), task));
	return true;
}

/**
 * \brief 验证这个服务器是否已经启动
 *
 * \param wdServerID 服务器编号
 * \return 验证是否成功
 */
bool ZoneManager::uniqueVerify(const DWORD dwServerID)
{
	ZoneTaskHashmap_const_iterator it;
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	it = taskUniqueContainer.find(dwServerID);
	if (it != taskUniqueContainer.end())
	{
		return false;
	}
	return true;
}

/**
 * \brief 从唯一性容器中删除一个连接任务
 *
 * \param task 服务器连接任务
 * \return 删除是否成功
 */
bool ZoneManager::uniqueRemove(ZoneTask *task)
{
	ZoneTaskHashmap_iterator it;
	zRWLock_scope_wrlock scope_wrlock(rwlock);
	it = taskUniqueContainer.find(task->getID());
	if (it != taskUniqueContainer.end())
	{
		taskUniqueContainer.erase(it);
	}
	else
		Fir::logger->warn("%s", __PRETTY_FUNCTION__);
	return true;
}

/**
 * \brief 向容器中所有的服务器广播指令
 *
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 指令长度
 * \return 广播是否成功
 */
bool ZoneManager::broadcast(const void *pstrCmd, int nCmdLen)
{
	bool retval = true;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		if (!(*it)->sendCmd(pstrCmd, nCmdLen))
			retval = false;
	}

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
bool ZoneManager::broadcastByID(const DWORD dwServerID, const void *pstrCmd, int nCmdLen)
{
	bool retval = false;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		if ((*it)->getID() == dwServerID)
		{
			retval = (*it)->sendCmd(pstrCmd, nCmdLen);
			break;
		}
	}

	return retval;
}

void ZoneManager::execEvery()
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		if (*it)
		{
			(*it)->doCmd();
		}
	}
}

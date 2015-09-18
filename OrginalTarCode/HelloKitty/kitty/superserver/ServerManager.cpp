/**
 * \file
 * \version  $Id: ServerManager.cpp 70 2013-04-23 13:26:44Z  $
 * \author  ,@163.com
 * \date 2004年12月13日 18时44分39秒 CST
 * \brief 实现服务器管理容器
 *
 * 这个容器包括全局容器和唯一性验证容器
 * 
 */


#include <iostream>
#include <list>

#include "ServerTask.h"
#include "zMutex.h"
#include "zNoncopyable.h"
#include "ServerManager.h"
#include "Fir.h"

ServerManager *ServerManager::instance = NULL;

/**
 * \brief 添加一个服务器连接任务到容器中
 *
 * \param task 服务器连接任务
 */
void ServerManager::addServer(ServerTask *task)
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
void ServerManager::removeServer(ServerTask *task)
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
ServerTask *ServerManager::getServer(WORD wdServerID)
{
	Containter_const_iterator it;
	ServerTask *retval = NULL;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(it = container.begin(); it != container.end(); it++)
	{
		if ((*it)->getID() == wdServerID)
		{
			retval = *it;
			break;
		}
	}

	return retval;
}

/**
 * \brief 根据类型查找服务器
 *   	  如果该 类型有多个服务器,则返回找到的第一个
 *
 * \param wdServerID 服务器编号
 * \return 返回适合的服务器连接任务
 */
ServerTask *ServerManager::getServerByType(WORD wdType)
{
	Containter_const_iterator it;
	ServerTask *retval = NULL;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(it = container.begin(); it != container.end(); it++)
	{
		if ((*it)->getType() == wdType)
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
bool ServerManager::uniqueAdd(ServerTask *task)
{
	ServerTaskHashmap_const_iterator it;
	zRWLock_scope_wrlock scope_wrlock(rwlock);
	it = taskUniqueContainer.find(task->getID());
	if (it != taskUniqueContainer.end())
	{
		Fir::logger->error("%s", __PRETTY_FUNCTION__);
		return false;
	}
	taskUniqueContainer.insert(ServerTaskHashmap_pair(task->getID(), task));
	return true;
}

/**
 * \brief 验证这个服务器是否已经启动
 *
 * \param wdServerID 服务器编号
 * \return 验证是否成功
 */
bool ServerManager::uniqueVerify(const WORD wdServerID)
{
	ServerTaskHashmap_const_iterator it;
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	it = taskUniqueContainer.find(wdServerID);
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
bool ServerManager::uniqueRemove(ServerTask *task)
{
	ServerTaskHashmap_iterator it;
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
bool ServerManager::broadcast(const void *pstrCmd, int nCmdLen)
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
 *\brief 根据ip广播指令，一个ip只发送一次
 */
bool ServerManager::broadcastIP(const void *pstrCmd,int nCmdLen)
{
	std::map<std::string,ServerTask*> iptask;
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		iptask.insert(std::make_pair((*it)->getIP(),*it));
	}

	bool ret = true;
	for(std::map<std::string,ServerTask*>::iterator iter = iptask.begin();iter != iptask.end();++iter)
	{
#ifdef _HL_DEBUG
		Fir::logger->trace("[监控]发送收集消息%s",iter->first.c_str());
#endif
		if(!iter->second->sendCmd(pstrCmd,nCmdLen))
			ret = false;
	}
	return ret;
}


/**
 * \brief 根据服务器编号广播指令
 *
 * \param wdServerID 待广播指令的服务器编号
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 指令长度
 * \return 广播是否成功
 */
bool ServerManager::broadcastByID(const WORD wdServerID, const void *pstrCmd, int nCmdLen)
{
	bool retval = false;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		if ((*it)->getID() == wdServerID)
		{
			retval = (*it)->sendCmd(pstrCmd, nCmdLen);
			break;
		}
	}

	return retval;
}

/**
 * \brief 根据服务器类型广播指令
 *
 * \param wdType 待广播指令的服务器类型
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 指令长度
 * \return 广播是否成功
 */
bool ServerManager::broadcastByOne(const WORD wdType, const void *pstrCmd, int nCmdLen)
{
	bool retval = false;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		///Fir::logger->debug("%s %u %u %u", __PRETTY_FUNCTION__, (*it)->wdServerType, wdType, nCmdLen);
		if ((*it)->getType() == wdType)
		{
			(*it)->sendCmd(pstrCmd, nCmdLen);
			retval = true;
			break;
		}
	}

	return retval;
}

/**
 * \brief 根据服务器类型广播指令
 *
 * \param wdType 待广播指令的服务器类型
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 指令长度
 * \return 广播是否成功
 */
bool ServerManager::broadcastByType(const WORD wdType, const void *pstrCmd, int nCmdLen)
{
	bool retval = true;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		//Fir::logger->debug("%s %u %u %u", __PRETTY_FUNCTION__, (*it)->wdServerType, wdType, nCmdLen);
		if ((*it)->getType() == wdType
				&& !(*it)->sendCmd(pstrCmd, nCmdLen))
			retval = false;
	}

	return retval;
}

/**
 * \brief 统计一个区的在线人数
 * \return 得到一个区的当前总在线人数
 */
const DWORD ServerManager::caculateOnlineNum()
{
	DWORD retval = 0;

	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		if ((*it)->getType() == GATEWAYSERVER)
			retval += (*it)->getOnlineNum();
	}

	return retval;
}

/**
 * \brief 收到notifyOther回复
 * \param srcID 源服务器编号
 * \param wdServerID 目的服务器编号
 */
void ServerManager::responseOther(const WORD srcID, const WORD wdServerID)
{
	ServerTaskHashmap_const_iterator it;
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	it = taskUniqueContainer.find(srcID);
	if (it != taskUniqueContainer.end())
	{
		if (it->second)
			it->second->responseOther(wdServerID);
	}
}

/*
 *\brief 检查死锁
 */
void ServerManager::checkDeadLock(DWORD now)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++)
	{
		(*it)->checkDeadLock(now);
	}
}

void ServerManager::sendAllGatewayToMe(ServerTask *task)
{
	if (!task)
		return;

	unsigned char pBuffer[zSocket::MAX_DATASIZE];
    bzero(pBuffer,sizeof(pBuffer));
    *(BYTE*)pBuffer = STRUCT_TYPE;
	CMD::SUPER::t_Startup_ServerEntry_NotifyMe *ptCmd = (CMD::SUPER::t_Startup_ServerEntry_NotifyMe *)(pBuffer+sizeof(BYTE)); 
	constructInPlace(ptCmd);
	ptCmd->size = 0;
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(Containter_const_iterator it = container.begin(); it != container.end(); it++) 
	{
		if ((*it) && (*it)->getType() == GATEWAYSERVER)
		{
			bzero(&ptCmd->entry[ptCmd->size], sizeof(ptCmd->entry[ptCmd->size]));
			ptCmd->entry[ptCmd->size].wdServerID = (*it)->getID();
			ptCmd->entry[ptCmd->size].wdServerType = GATEWAYSERVER;
			strncpy(ptCmd->entry[ptCmd->size].pstrName, (*it)->getPstrName(), MAX_NAMESIZE - 1);
			strncpy(ptCmd->entry[ptCmd->size].pstrIP, (*it)->getIP(), MAX_IP_LENGTH - 1);
			ptCmd->entry[ptCmd->size].wdPort = (*it)->getWdPort();
			strncpy(ptCmd->entry[ptCmd->size].pstrExtIP, (*it)->getExtIP(), MAX_IP_LENGTH - 1);
			ptCmd->entry[ptCmd->size].wdExtPort = (*it)->getWdExtPort();
			ptCmd->entry[ptCmd->size].state = (*it)->getState();
			ptCmd->size++;
		}
	}   
	if (ptCmd->size)
	{
		task->sendCmd(pBuffer, sizeof(BYTE) + sizeof(CMD::SUPER::t_Startup_ServerEntry_NotifyMe) + ptCmd->size * sizeof(CMD::SUPER::ServerEntry));
	}
}

/**
 * \brief 检查是否要通知网关重连场景,如需重连，则通知网关
 */
void ServerManager::notifyGatewayReconnectScene(ServerTask *task)
{
	if (task->getType() == SCENESSERVER)
	{
		SceneInfoHashmap_iterator it = sceneinfo.find(task->getID());
		if (it == sceneinfo.end())
		{
			// 动态新加服务器
			sceneinfo.insert(SceneInfohashmap_pair(task->getID(), std::string(task->getIP())));
#ifdef _PQQ_DEBUG
			Fir::logger->debug("[重连场景] SuperServre添加连接好的场景到容器中 id:%d,场景名:%s,ip:%s,port:%d"
					,task->getID(),task->getPstrName(),task->getIP(),task->getWdPort());
#endif
            char buffer[zSocket::MAX_DATASIZE];
            bzero(buffer,sizeof(buffer));
            *(BYTE*)buffer = STRUCT_TYPE;
			CMD::SUPER::t_GateReconnectScene *send = (CMD::SUPER::t_GateReconnectScene*)(buffer+sizeof(BYTE));
			constructInPlace(send);
            bzero(&send->entry, sizeof(send->entry));
			send->entry.wdServerID = task->getID();
			send->entry.wdServerType = task->getType();
			strncpy(send->entry.pstrName, task->getPstrName(), MAX_NAMESIZE - 1);
			strncpy(send->entry.pstrIP, task->getIP(), MAX_IP_LENGTH - 1);
			send->entry.wdPort = task->getWdPort();
			strncpy(send->entry.pstrExtIP, task->getExtIP(), MAX_IP_LENGTH - 1);
			send->entry.wdExtPort = task->getWdExtPort();
			send->entry.state = task->getState();
			broadcastByType(GATEWAYSERVER, buffer, sizeof(send) + sizeof(BYTE));
		}
		else
		{
			// 动态更换IP重新连接,断开旧的
			if (strncmp(it->second.c_str(), task->getIP(), MAX_IP_LENGTH ) != 0)
			{
                char buffer[zSocket::MAX_DATASIZE];
                bzero(buffer,sizeof(buffer));
                *(BYTE*)buffer = STRUCT_TYPE;

				CMD::SUPER::t_GateTerminateConnect &s = *(CMD::SUPER::t_GateTerminateConnect*)(buffer+sizeof(BYTE));
                constructInPlace(&s);

				strncpy(s.pstrIP, it->second.c_str(), MAX_IP_LENGTH - 1);
				s.port = task->getWdPort();
				broadcastByType(GATEWAYSERVER, buffer, sizeof(s)+sizeof(BYTE));
                
                bzero(buffer+sizeof(BYTE),sizeof(buffer)-sizeof(BYTE)); 
				CMD::SUPER::t_GateReconnectScene &send = *(CMD::SUPER::t_GateReconnectScene*)(buffer+sizeof(BYTE));
                constructInPlace(&send);
				bzero(&send.entry, sizeof(send.entry));
				send.entry.wdServerID = task->getID();
				send.entry.wdServerType = task->getType();
				strncpy(send.entry.pstrName, task->getPstrName(), MAX_NAMESIZE - 1);
				strncpy(send.entry.pstrIP, task->getIP(), MAX_IP_LENGTH - 1);
				send.entry.wdPort = task->getWdPort();
				strncpy(send.entry.pstrExtIP, task->getExtIP(), MAX_IP_LENGTH - 1);
				send.entry.wdExtPort = task->getWdExtPort();
				send.entry.state = task->getState();
				broadcastByType(GATEWAYSERVER, buffer, sizeof(send) + sizeof(BYTE));
				sceneinfo[task->getID()] = std::string(task->getIP());
#ifdef _PQQ_DEBUG
				Fir::logger->debug("[重连场景] SuperServer处理场景重连，通知网关 id:%d,场景名:%s,ip:%s, port:%d"
									,task->getID(),task->getPstrName(),task->getIP(),task->getWdPort());
#endif
			}
		}
	}
}

void ServerManager::addSceneInfo(WORD id, const std::string& ip)
{
	sceneinfo.insert(SceneInfohashmap_pair(id, ip));
}

void ServerManager::execEvery()
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

/**
 * \file
 * \version  $Id: ServerTask.cpp 64 2013-04-23 02:05:08Z  $
 * \author  Songsiliang,
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 实现服务器连接类
 *
 * 
 */


#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "ServerTask.h"
#include "SuperCommand.h"
#include "ServerManager.h"
#include "Fir.h"
#include "zDBConnPool.h"
#include "SuperServer.h"
#include "zString.h"
#include "SuperServer.h"
#include "FLCommand.h"
#include "FLClient.h"
#include "FLClientManager.h"
#include "TimeTick.h"
#include "zServerInfo.h"
#include "AllZoneClientManager.h"

/**
 * \brief 验证一个服务器连接是否合法
 *
 * 每一台服务器的信息在数据库中都有记录，如果数据库中没有相应的记录，那么这个服务器连接任务就是不合法的，需要立即断开连接<br>
 * 这样保证了一个区中的服务器之间的信任关系
 *
 * \param wdType 服务器类型
 * \param pstrIP 服务器地址
 * \return 验证是否成功
 */
bool ServerTask::verify(WORD wdType, const char *pstrIP)
{
	char where[64];

	this->wdServerType = wdType;
	strncpy(this->pstrIP, pstrIP, sizeof(this->pstrIP) - 1);
	Fir::logger->debug("%s \t%u, %s", __FUNCTION__, wdType, pstrIP);

	connHandleID handle = SuperService::dbConnPool->getHandle();
	if ((connHandleID)-1 == handle)
	{
		Fir::logger->error("不能从数据库连接池获取连接句柄");
		return false;
	}

	bzero(where, sizeof(where));
	std::string escapeIP;
	snprintf(where, sizeof(where) - 1, "`TYPE`=%u AND `IP`='%s'", wdType, SuperService::dbConnPool->escapeString(handle,pstrIP,escapeIP).c_str());
	static const dbCol col_define[] =
	{
		{"ID",zDBConnPool::DB_WORD,sizeof(WORD)},
		{"NAME",zDBConnPool::DB_STR,sizeof(char[MAX_NAMESIZE])},
		{"PORT",zDBConnPool::DB_WORD,sizeof(WORD)},
		{"EXTIP",zDBConnPool::DB_STR,sizeof(char[MAX_IP_LENGTH])},
		{"EXTPORT",zDBConnPool::DB_WORD,sizeof(WORD)},
		{"NETTYPE",zDBConnPool::DB_WORD,sizeof(WORD)},
		{NULL, 0, 0}
	};
	struct
	{
		WORD wdServerID;
		char pstrName[MAX_NAMESIZE];
		WORD wdPort;
		char pstrExtIP[MAX_IP_LENGTH];
		WORD wdExtPort;
		WORD wdNetType;
	} __attribute__ ((packed))
	*pData = NULL;

	unsigned int retcode = SuperService::dbConnPool->exeSelect(handle, "`t_serverlist`", col_define, where, "`ID`",(unsigned char **)&pData);
	if (retcode == (unsigned int)-1
			|| retcode == 0
			|| NULL == pData)
	{
		Fir::logger->error("数据库中没有相应的服务器记录");
		SuperService::dbConnPool->putHandle(handle);
		return false;
	}

	SuperService::dbConnPool->putHandle(handle);

	//某些类型服务器在一个区中只能由一台
	if (retcode > 1
			&& (wdType == BILLSERVER
			|| wdType == SESSIONSERVER)
	)
	{
		SAFE_DELETE_VEC(pData);
		Fir::logger->error("这种类型的服务器只能有一台 %u", wdType);
		return false;
	}

	//从数据库中取数据成功，需要从这些数据中取得一个可用项
	unsigned int i;
	for(i = 0; i < retcode; i++)
	{
		if (ServerManager::getMe().uniqueVerify(pData[i].wdServerID))
		{
			wdServerID = pData[i].wdServerID;
			strncpy(pstrName, pData[i].pstrName, sizeof(pstrName) - 1);
			wdPort = pData[i].wdPort;
			strncpy(pstrExtIP, pData[i].pstrExtIP, sizeof(pstrExtIP) - 1);
			wdExtPort = pData[i].wdExtPort;
			wdNetType = pData[i].wdNetType;
			break;
		}
	}
	SAFE_DELETE_VEC(pData);
	if (i == retcode)
	{
		Fir::logger->error("服务器已经启动完成了，没有可用记录");
		return false;
	}

	//返回服务器信息到服务器

    char buffer[zSocket::MAX_DATASIZE];
    bzero(buffer,sizeof(buffer));
    *(BYTE*)buffer = STRUCT_TYPE;
    int len = sizeof(BYTE);

	using namespace CMD::SUPER;
	t_Startup_Response *tCmd = (t_Startup_Response*)(buffer+len);
    constructInPlace(tCmd);
	tCmd->wdServerID = wdServerID;
	tCmd->wdPort = wdPort;
	bcopy(pstrExtIP, tCmd->pstrExtIP, sizeof(pstrExtIP));
	tCmd->wdExtPort = wdExtPort;
	tCmd->wdNetType = wdNetType;
    len += sizeof(t_Startup_Response);
	if (!sendCmd(buffer, len))
	{
		Fir::logger->error("向服务器发送指令失败");
		return false;
	}

	return true;
}

/**
 * \brief 等待接受验证指令并进行验证
 *
 * 实现虚函数<code>zTCPTask::verifyConn</code>
 *
 * \return 验证是否成功，或者超时
 */
int ServerTask::verifyConn()
{
	int retcode = mSocket.recvToBuf_NoPoll();
	if (retcode > 0)
	{
		BYTE acceptCmd[zSocket::MAX_DATASIZE];
		int nCmdLen = mSocket.recvToCmd_NoPoll(acceptCmd, sizeof(acceptCmd));
        //这里只是从缓冲取数据包，所以不会出错，没有数据直接返回
		if (nCmdLen <= 0)
        {
			return 0;
        }
        
        using namespace CMD::SUPER;
        BYTE messageType = *(BYTE*)acceptCmd;
        nCmdLen -= sizeof(BYTE);
        if(messageType != STRUCT_TYPE || nCmdLen <= 0)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, messageType,nCmdLen-1);
            return -1;
        }
        
        BYTE *pstrCmd = acceptCmd + sizeof(BYTE);
        t_Startup_Request *ptCmd = (t_Startup_Request *)pstrCmd;
        if (CMD_STARTUP == ptCmd->cmd && PARA_STARTUP_REQUEST == ptCmd->para)
        {
            if (verify(ptCmd->wdServerType, ptCmd->pstrIP))
            {
                Fir::logger->debug("客户端连接通过验证");
                return 1;
            }
        }
        Fir::logger->error("客户端连接验证失败"); 
        return -1;
	}
	else
		return retcode;
}

/**
 * \brief 保存服务器之间的依赖关系
 *
 */
//static std::unordered_map<int, std::vector<int> > serverSequence;
//
///**
// * \brief 初始化服务器之间的依赖关系
// *
// */
//static void initServerSequence() __attribute__ ((constructor));
//void initServerSequence()
//{
//	serverSequence[UNKNOWNSERVER]	=	std::vector<int>();
//	serverSequence[SUPERSERVER]	=	std::vector<int>();
//	serverSequence[LOGINSERVER]	=	std::vector<int>();
//	serverSequence[RECORDSERVER]	=	std::vector<int>();
//	serverSequence[GATEWAYSERVER] = std::vector<int>(); //测试用
//
//	int data0[] = { RECORDSERVER};
//	//会话依赖档案服务器
//	serverSequence[SESSIONSERVER]   =   std::vector<int>(data0, data0 + sizeof(data0) / sizeof(int));
//	std::cout<<"初始化serverSequence[SESSIONSERVER]:"<<serverSequence[SESSIONSERVER].size()<<std::endl;
//	int data1[] = { RECORDSERVER, SESSIONSERVER};
//	//场景服务器依赖档案服务器，会话服务器
//	serverSequence[SCENESSERVER]	=	std::vector<int>(data1, data1 + sizeof(data1) / sizeof(int));
//	int data2[] = { RECORDSERVER, SESSIONSERVER, SCENESSERVER};
//	//网关依赖档案服务器，会话服务器，场景服务器
//	serverSequence[GATEWAYSERVER]	=	std::vector<int>(data2, data2 + sizeof(data2) / sizeof(int));
//	std::cout<<"初始化serverSequence[SESSIONSERVER]:"<<serverSequence[SESSIONSERVER].size()<<std::endl;
//}

/**
 * \brief 验证某种类型的所有服务器是否完全启动完成
 *
 * \param wdType 服务器类型
 * \param sv 容器，容纳启动成功的服务器列表
 * \return 验证是否成功
 */
bool ServerTask::verifyTypeOK(const WORD wdType, std::vector<ServerTask *> &sv)
{
	static const dbCol col_define[] =
	{
		{"ID",zDBConnPool::DB_WORD,sizeof(WORD)},
		{NULL, 0, 0}
	};
	char where[64];
	WORD *ID = NULL;

	if (0 == wdType)
		return true;

	bzero(where, sizeof(where));
	snprintf(where, sizeof(where) - 1, "`TYPE`=%u", wdType);

	connHandleID handle = SuperService::dbConnPool->getHandle();
	if ((connHandleID)-1 == handle)
	{
		Fir::logger->error("不能从数据库连接池获取连接句柄");
		return false;
	}

	unsigned int retcode = SuperService::dbConnPool->exeSelect(handle, "`t_serverlist`", col_define, where, "`ID`",(unsigned char **)&ID);
	if (retcode == (unsigned int)-1
			|| retcode == 0
			|| NULL == ID)
	{
		Fir::logger->error("数据库中没有相应的服务器记录");
		SuperService::dbConnPool->putHandle(handle);
		return false;
	}
	SuperService::dbConnPool->putHandle(handle);

	bool retval = true;
	for(unsigned int i = 0; i < retcode; i++)
	{
		//这个容器里面的肯定是OK状态
		ServerTask * pServer = ServerManager::getMe().getServer(ID[i]);
		if (NULL == pServer)
		{
			retval = false;
			break;
		}
		else
		{
			sv.push_back(pServer);
		}
	}
	SAFE_DELETE_VEC(ID);

	return retval;
}

/**
 * \brief 通知所有依赖的服务器
 * \return 通知是否成功
 */
bool ServerTask::notifyOther(WORD dstID)
{
    char buffer[zSocket::MAX_DATASIZE];
    bzero(buffer,sizeof(buffer));
    *(BYTE*)buffer = STRUCT_TYPE;
	using namespace CMD::SUPER;
	t_Startup_ServerEntry_NotifyOther *Cmd = (t_Startup_ServerEntry_NotifyOther*)(buffer+sizeof(BYTE));
    constructInPlace(Cmd);

	bzero(&Cmd->entry, sizeof(Cmd->entry));
	Cmd->entry.wdServerID = wdServerID;
	Cmd->entry.wdServerType = wdServerType;
	strncpy(Cmd->entry.pstrName, pstrName, MAX_NAMESIZE - 1);
	strncpy(Cmd->entry.pstrIP, pstrIP, MAX_IP_LENGTH - 1);
	Cmd->entry.wdPort = wdPort;
	strncpy(Cmd->entry.pstrExtIP, pstrExtIP, MAX_IP_LENGTH - 1);
	Cmd->entry.wdExtPort = wdExtPort;
	Cmd->entry.state = state;

	for(Container::iterator it = ses.begin(); it != ses.end(); ++it)
	{
		if(dstID == it->first.wdServerID)
		{
			ServerTask * pDst = ServerManager::getMe().getServer(dstID);
			if(pDst)
			{
				pDst->sendCmd(buffer, sizeof(BYTE) + sizeof(Cmd));
			}
			break;
		}
	}

	return true;
}
/**
 * \brief 通知所有依赖的服务器
 * \return 通知是否成功
 */
bool ServerTask::notifyOther()
{
    char buffer[zSocket::MAX_DATASIZE];
    bzero(buffer,sizeof(buffer));
    *(BYTE*)buffer = STRUCT_TYPE;
    int len = sizeof(BYTE);

	using namespace CMD::SUPER;
	t_Startup_ServerEntry_NotifyOther *Cmd = (t_Startup_ServerEntry_NotifyOther*)(buffer+len);
    constructInPlace(Cmd);
	bool retval = true;

	bzero(&Cmd->entry, sizeof(Cmd->entry));
	Cmd->entry.wdServerID = wdServerID;
	Cmd->entry.wdServerType = wdServerType;
	strncpy(Cmd->entry.pstrName, pstrName, MAX_NAMESIZE - 1);
	strncpy(Cmd->entry.pstrIP, pstrIP, MAX_IP_LENGTH - 1);
	Cmd->entry.wdPort = wdPort;
	strncpy(Cmd->entry.pstrExtIP, pstrExtIP, MAX_IP_LENGTH - 1);
	Cmd->entry.wdExtPort = wdExtPort;
	Cmd->entry.state = state;
    len += sizeof(t_Startup_ServerEntry_NotifyOther);

	for(Container::iterator it = ses.begin(); it != ses.end(); ++it)
	{
		Cmd->srcID = it->first.wdServerID;
		retval &= ServerManager::getMe().broadcastByID(Cmd->srcID,buffer,len);
	}

	
	/*//Fir::logger->debug("%u", wdServerType);
	std::vector<int> sequence = serverSequence[wdServerType];
	for(std::vector<int>::const_iterator it = sequence.begin(); it != sequence.end(); it++)
	{
		//广播指令
		//Fir::logger->debug("%u", (*it));
		Cmd.srcID = wdServerID;
		retval &= ServerManager::getMe().broadcastByType(*it, &Cmd, sizeof(Cmd));
	}*/

	return retval;
}

/**
 * \brief 收到notifyOther回复
 * \param wdServerID 目的服务器编号
 */
void ServerTask::responseOther(const WORD wdServerID)
{
	for(Container::iterator it = ses.begin(); it != ses.end(); ++it)
	{
		if (it->first.wdServerID == wdServerID)
		{
			//Fir::logger->debug("回复成功 %s, %d", it->first.pstrName, it->first.wdServerID);
			it->second = true;
		}
	}
}

/**
 * \brief 通知服务器其依赖的服务器信息列表
 * \return 通知是否成功
 */
bool ServerTask::notifyMe()
{
	if (hasNotifyMe) return true;

	using namespace CMD::SUPER;

	//Fir::logger->debug(__PRETTY_FUNCTION__);
	unsigned char pBuffer[zSocket::MAX_DATASIZE];
    bzero(pBuffer,sizeof(pBuffer));
    *(BYTE*)pBuffer = STRUCT_TYPE;
	t_Startup_ServerEntry_NotifyMe *ptCmd = (t_Startup_ServerEntry_NotifyMe *)(pBuffer+sizeof(BYTE));
	constructInPlace(ptCmd);
	ptCmd->size = 0;

	//check for notify other response
	for(Container::iterator it = ses.begin(); it != ses.end(); ++it)
	{
		if (it->second)
		{
			bzero(&ptCmd->entry[ptCmd->size], sizeof(ptCmd->entry[ptCmd->size]));
			ptCmd->entry[ptCmd->size].wdServerID = it->first.wdServerID;
			ptCmd->entry[ptCmd->size].wdServerType = it->first.wdServerType;
			strncpy(ptCmd->entry[ptCmd->size].pstrName, it->first.pstrName, MAX_NAMESIZE - 1);
			strncpy(ptCmd->entry[ptCmd->size].pstrIP, it->first.pstrIP, MAX_IP_LENGTH - 1);
			ptCmd->entry[ptCmd->size].wdPort = it->first.wdPort;
			strncpy(ptCmd->entry[ptCmd->size].pstrExtIP, it->first.pstrExtIP, MAX_IP_LENGTH - 1);
			ptCmd->entry[ptCmd->size].wdExtPort = it->first.wdExtPort;
			ptCmd->entry[ptCmd->size].state = it->first.state;

			ptCmd->size++;
		}
		else
			return false;
	}

	if (sendCmd(pBuffer, sizeof(t_Startup_ServerEntry_NotifyMe) + ptCmd->size * sizeof(ServerEntry) + sizeof(BYTE)))
		hasNotifyMe = true;

	if (this->wdServerType == SCENESSERVER)
	{
		ServerManager::getMe().sendAllGatewayToMe(this);
	}

	return hasNotifyMe;
}

/**
 * \brief 处理服务器的依赖关系，也就是启动顺序
 * \return 是否所有所依赖的服务器已经启动完成
 */
bool ServerTask::processSequence()
{
	using namespace CMD::SUPER;

	ses.clear();

	Fir::logger->debug("%s,servertype=%u", __PRETTY_FUNCTION__, wdServerType);

	std::vector<int> sequence = SuperService::getMe().getServerSes(wdServerType);
	for(std::vector<int>::const_iterator it = sequence.begin(); it != sequence.end(); it++)
	{
		std::vector<ServerTask *> sv;
		if (verifyTypeOK(*it, sv))
		{
			for(std::vector<ServerTask *>::const_iterator sv_it = sv.begin(); sv_it != sv.end(); sv_it++)
			{
				ServerEntry se;
				bzero(&se, sizeof(se));
				se.wdServerID = (*sv_it)->wdServerID;
				se.wdServerType = (*sv_it)->wdServerType;
				strncpy(se.pstrName, (*sv_it)->pstrName, MAX_NAMESIZE - 1);
				strncpy(se.pstrIP, (*sv_it)->pstrIP, MAX_IP_LENGTH - 1);
				se.wdPort = (*sv_it)->wdPort;
				strncpy(se.pstrExtIP, (*sv_it)->pstrExtIP, MAX_IP_LENGTH - 1);
				se.wdExtPort = (*sv_it)->wdExtPort;
				se.state = (*sv_it)->state;

				ses.insert(Container::value_type(se, false));
			}
		}
		else
		{
			Fir::logger->debug("%s,false,servertype=%u", __PRETTY_FUNCTION__, wdServerType);
			return false;
		}
	}

	Fir::logger->debug("%s,true,servertype=%u", __PRETTY_FUNCTION__, wdServerType);
	return true;
}

/**
 * \brief 等待服务器启动完成
 *
 * 服务器接受到服务器管理器返回的自身信息，会进行自身的初始化，初始化完毕发送启动完成指令到服务器管理器<br>
 * 当服务器管理器接受到确认启动完成的指令就会把这个服务器加入到完成启动的队列中，这样服务器就完成了整个启动过程<br>
 * 实现了虚函数<code>zTCPTask::waitSync</code>
 *
 * \return 服务器启动是否通过，如果超时还要继续等待
 */
int ServerTask::waitSync()
{
	int retcode = mSocket.checkIOForRead();
	if (-1 == retcode)
	{
		Fir::logger->error("%s", __PRETTY_FUNCTION__);
		return -1;
	}
	else if (retcode > 0)
	{
		//套接口准备好了接收数据，接收数据到缓冲，并尝试处理指令
		retcode = mSocket.recvToBuf_NoPoll();
		if (-1 == retcode)
		{
			Fir::logger->error("%s", __PRETTY_FUNCTION__);
			return -1;
		}
	}

	unsigned char acceptCmd[zSocket::MAX_DATASIZE];
	int nCmdLen = mSocket.recvToCmd_NoPoll(acceptCmd, sizeof(acceptCmd));
	if (nCmdLen > 0)
	{
        BYTE messageType = *(BYTE*)acceptCmd;
        nCmdLen -= sizeof(BYTE);
        if(nCmdLen > 0)
        {
            BYTE *pstrCmd = acceptCmd + sizeof(BYTE);
            if(messageType == STRUCT_TYPE)
            {
		        using namespace CMD::SUPER;
		        t_Startup_OK *ptCmd = (t_Startup_OK *)pstrCmd;
		        Fir::logger->debug("%u, %u, %u, %u", ptCmd->cmd, ptCmd->para, ptCmd->wdServerID, wdServerID);
		        if (((CMD_STARTUP == ptCmd->cmd	&& PARA_STARTUP_OK == ptCmd->para) && (wdServerID == ptCmd->wdServerID)) || (ptCmd->cmd==5 && ptCmd->para==3))
		        {
			        Fir::logger->debug("客户端连接同步验证成功");
			        return 1;
		        }
		        else
		        {
			        Fir::logger->error("客户端连接同步验证失败");
			        return 0;
		        }
            }
            else if(messageType == PROTOBUF_TYPE)
            {
                //protobuf消息
            }
        }
	}

	//首先检查处理启动顺序
	if (checkSequenceTime()
			&& processSequence()
			&& notifyOther())
		sequenceOK = true;
	if (sequenceOK)
		notifyMe();

	//等待超时
	return 0;
}

/**
 * \brief 确认一个服务器连接的状态是可以回收的
 *
 * 当一个连接状态是可以回收的状态，那么意味着这个连接的整个生命周期结束，可以从内存中安全的删除了：）<br>
 * 实现了虚函数<code>zTCPTask::recycleConn</code>
 *
 * \return 是否可以回收
 */
int ServerTask::recycleConn()
{
	return 1;
}

/**
 * \brief 添加到全局容器中
 *
 * 实现了虚函数<code>zTCPTask::addToContainer</code>
 *
 */
void ServerTask::addToContainer()
{
	ServerManager::getMe().addServer(this);
    char buffer[zSocket::MAX_DATASIZE];
    bzero(buffer,sizeof(buffer));
    *(BYTE*)buffer = STRUCT_TYPE;
	if (this->getType()==RECORDSERVER)
	{
		CMD::SUPER::t_ZoneID_Record &send = *(CMD::SUPER::t_ZoneID_Record*)(buffer+sizeof(BYTE));
        constructInPlace(&send);
		send.zone = SuperService::getMe().getZoneID();
		sendCmd(buffer, sizeof(send)+sizeof(BYTE));
	}
	else if (this->getType()==SCENESSERVER)
	{
		CMD::SUPER::t_ZoneID_Scene &send = *(CMD::SUPER::t_ZoneID_Scene*)(buffer+sizeof(BYTE));
        constructInPlace(&send);
		send.zone = SuperService::getMe().getZoneID();
		sendCmd(buffer, sizeof(send)+sizeof(BYTE));

		ServerManager::getMe().notifyGatewayReconnectScene(this);
	}
	else if (this->getType()==SESSIONSERVER)
	{
		CMD::SUPER::t_ZoneID_Session &send = *(CMD::SUPER::t_ZoneID_Session*)(buffer+sizeof(BYTE));
        constructInPlace(&send);
		send.zone =  SuperService::getMe().getZoneID();
		strncpy(send.name,SuperService::getMe().getZoneName().c_str(),MAX_NAMESIZE);
		sendCmd(buffer, sizeof(send)+sizeof(BYTE));	
	}
	else if (this->getType() == GATEWAYSERVER)
	{
		CMD::SUPER::t_ZoneID_Gate &send = *(CMD::SUPER::t_ZoneID_Gate*)(buffer+sizeof(BYTE));
		send.zone = SuperService::getMe().getZoneID();
		sendCmd(buffer, sizeof(send)+sizeof(BYTE));
	}	
}

/**
 * \brief 从全局容器中删除
 *
 * 实现了虚函数<code>zTCPTask::removeToContainer</code>
 *
 */
void ServerTask::removeFromContainer()
{
	//如果是网关服务器关闭，首先通知所有的登陆服务器网关关闭
	if (GATEWAYSERVER == wdServerType)
	{
        char buffer[zSocket::MAX_DATASIZE];
        bzero(buffer,sizeof(buffer));
        *(BYTE*)buffer = STRUCT_TYPE;
		CMD::FL::t_GYList_FL &tCmd = *(CMD::FL::t_GYList_FL*)(buffer+sizeof(BYTE));
        constructInPlace(&tCmd);
		tCmd.wdServerID = wdServerID;
		bzero(tCmd.pstrIP, sizeof(tCmd.pstrIP));
		tCmd.wdPort = 0;
		tCmd.wdNumOnline = 0;
		tCmd.state = state_maintain;
		tCmd.zoneGameVersion = 0;

		Fir::logger->trace("GatewayServer停机 发送维护状态到FLServer!");

		FLClientManager::getMe().broadcast(buffer, sizeof(tCmd)+sizeof(BYTE));
	}

	ServerManager::getMe().removeServer(this);
}

/**
 * \brief 添加到唯一性验证容器中
 *
 * 实现了虚函数<code>zTCPTask::uniqueAdd</code>
 *
 */
bool ServerTask::uniqueAdd()
{
	return ServerManager::getMe().uniqueAdd(this);
}

/**
 * \brief 从唯一性验证容器中删除
 *
 * 实现了虚函数<code>zTCPTask::uniqueRemove</code>
 *
 */
bool ServerTask::uniqueRemove()
{
	return ServerManager::getMe().uniqueRemove(this);
}


/*
 *\brief 判断是不是死锁了
 */
void ServerTask::checkDeadLock(DWORD now)
{
	if(tickFlag)
	{
		if(m_tickTime && now > m_tickTime + 120)
		{
			tickFlag = false;
			m_tickTime = now + 10 * 60;
		}
	}
	else if(now > m_tickTime + HEARTBEAT_TICK)
	{
		//CMD::SUPER::t_heartBeatCmd send;
		//sendCmd(&send,sizeof(send));
		tickFlag = true;
		m_tickTime = now;
	}
}


/**
 * \brief 解析来自服务器管理器的关于启动的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 指令长度
 * \return 解析是否成功
 */
bool ServerTask::msgParse_Startup(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
	using namespace CMD::SUPER;

	switch(ptNullCmd->para)
	{
		case PARA_STARTUP_SERVERENTRY_NOTIFYOTHER:
			{
				t_Startup_ServerEntry_NotifyOther *ptCmd = (t_Startup_ServerEntry_NotifyOther *)ptNullCmd;

				//Fir::logger->debug("%u, %u, %u, %s, %s, %u, %s, %u, %u",
				//		ptCmd->srcID,
				//		ptCmd->entry.wdServerID,
				//		ptCmd->entry.wdServerType,
				//		ptCmd->entry.pstrName,
				//		ptCmd->entry.pstrIP,
				//		ptCmd->entry.wdPort,
				//		ptCmd->entry.pstrExtIP,
				//		ptCmd->entry.wdExtPort,
				//		ptCmd->entry.state);
				ServerManager::getMe().responseOther(ptCmd->entry.wdServerID, ptCmd->srcID);

				return true;
			}
			break;
		case PARA_RESTART_SERVERENTRY_NOTIFYOTHER:
			{
				t_restart_ServerEntry_NotifyOther *notify = (t_restart_ServerEntry_NotifyOther*)ptNullCmd;
				ServerTask * pSrc = ServerManager::getMe().getServer(notify->srcID);
				if(pSrc)
				{
					pSrc->notifyOther(notify->dstID);
					return true;
				}
				
			}
			break;
		default:
			break;
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}

/**
 * \brief 解析来自网关服务器的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 指令长度
 * \return 处理是否成功
 */
bool ServerTask::msgParse_Gateway(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
	using namespace CMD::SUPER;

	switch(ptNullCmd->para)
	{
		case PARA_GATEWAY_GYLIST:
			{
				t_GYList_Gateway *ptCmd = (t_GYList_Gateway *)ptNullCmd;
                
                char buffer[zSocket::MAX_DATASIZE];
                bzero(buffer,sizeof(buffer));
                *(BYTE*)buffer = STRUCT_TYPE;
				CMD::FL::t_GYList_FL &tCmd = *(CMD::FL::t_GYList_FL*)(buffer+sizeof(BYTE)); 
                constructInPlace(&tCmd);

				OnlineNum = ptCmd->wdNumOnline;

				//Fir::logger->debug("GYList:%u, %s, %u, %u, %u", ptCmd->wdServerID, ptCmd->pstrIP, ptCmd->wdPort, ptCmd->wdNumOnline, ptCmd->state);
				tCmd.wdServerID = ptCmd->wdServerID;
				bcopy(ptCmd->pstrIP, tCmd.pstrIP, sizeof(pstrIP));
				tCmd.wdPort = ptCmd->wdPort;
				tCmd.wdNumOnline = ptCmd->wdNumOnline;
				tCmd.state = ptCmd->state;
				tCmd.zoneGameVersion = ptCmd->zoneGameVersion;
				tCmd.wdNetType = ptCmd->wdNetType;
				FLClientManager::getMe().broadcast(buffer, sizeof(tCmd)+sizeof(BYTE));

				return true;
			}
			break;
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}

bool ServerTask::msgParse_Scene(const CMD::t_NullCmd *cmd, const unsigned int len)
{
	using namespace CMD::SUPER;

	switch (cmd->para)
	{
		case PARA_FORWARD_ALLZONE_FROM_SCENE:
			{
				t_ForwardAllZoneFromScene *ptCmd = (t_ForwardAllZoneFromScene *)cmd;
				AllZoneClientManager::getMe().broadcastOne(ptCmd->data,ptCmd->size);
				Fir::logger->debug("t_ForwardAllZoneFromScene,size=%u",ptCmd->size);	
			}
			break;
	
		default:
			return false;
	}
	return false;
}

bool ServerTask::msgParse_Record(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
	using namespace CMD::SUPER;

	switch (ptNullCmd->para)
	{
		default:
			return false;
	}
	return false;
}

bool ServerTask::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("ServerTask::msgParseProto 消息处理");
    return true;
}

/**
 * \brief 解析来自各个服务器连接的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 指令长度
 * \return 处理是否成功
 */
bool ServerTask::msgParse(const BYTE *message, const DWORD nCmdLen)
{
	return MessageQueue::msgParse(message,nCmdLen);
}

bool ServerTask::cmdMsgParse(const BYTE *message, const DWORD nCmdLen)
{
    return zProcessor::msgParse(message,nCmdLen);
}

bool ServerTask::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

	switch(ptNullCmd->cmd)
	{
		case CMD::SUPER::CMD_SCENE:
			{
				if (msgParse_Scene(ptNullCmd, nCmdLen)) return true;
			}
			break;
		case CMD::SUPER::CMD_STARTUP:
			if (msgParse_Startup(ptNullCmd, nCmdLen))
			{
				return true;
			}
			break;
		case CMD::SUPER::CMD_GATEWAY:
			if (msgParse_Gateway(ptNullCmd, nCmdLen))
			{
				return true;
			}
			break;
		case CMD::SUPER::CMD_SESSION:
			{
				return true;
			}
			break;
		case CMD::SUPER::CMD_RECORD:
			{
				if (msgParse_Record(ptNullCmd, nCmdLen)) return true;
			}
			break;
		default:
			break;
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}


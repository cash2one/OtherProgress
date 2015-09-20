/**
 * \file
 * \version  $Id: SessionTask.cpp 72 2013-04-24 03:55:51Z  $
 * \author  ,
 * \date 2013年04月23日 10时20分01秒 CST
 * \brief 实现会话任务,网关和场景的连接，既是会话任务
 *
 * 
 */


#include "SessionTask.h"
#include "SessionCommand.h"
#include "SessionServer.h"
#include "SessionTaskManager.h"
#include "SessionUserManager.h"
#include "SceneSessionManager.h"
#include "SessionUser.h"
#include "SceneSession.h"
#include "zMetaData.h"
#include "GateCmdDispatcher.h"
#include "MassiveCommand.h"
#include "extractProtoMsg.h"

TaskCmdDispatcher SessionTask::gate_cmd_dispatcher("gatecmd");
TaskCmdDispatcher SessionTask::scene_cmd_dispatcher("scenecmd");
UserCmdDispatcher SessionTask::user_dispatcher("usercmd");

/**
 * \brief 验证登陆会话服务器的连接指令
 *
 * 如果验证不通过直接断开连接
 *
 * \param ptCmd 登陆指令
 * \return 验证是否成功
 */
bool SessionTask::verifyLogin(const CMD::SESSION::t_LoginSession *ptCmd)
{
	using namespace CMD::SESSION;

	if (SESSIONCMD == ptCmd->cmd && PARA_LOGIN == ptCmd->para)
	{
		const CMD::SUPER::ServerEntry *entry = SessionService::getMe().getServerEntry(ptCmd->wdServerID);
		char strIP[32];
		strncpy(strIP, getIP(), 31);
		if (entry && ptCmd->wdServerType == entry->wdServerType && 0 == strcmp(strIP, entry->pstrIP))
		{
			wdServerID = ptCmd->wdServerID;
			wdServerType = ptCmd->wdServerType;
		}

		return true;
	}

	return false;
}


/**
 * \brief 等待接受验证指令并进行验证
 *
 * 实现虚函数<code>zTCPTask::verifyConn</code>
 *
 * \return 验证是否成功，或者超时
 */
int SessionTask::verifyConn()
{
	int retcode = mSocket.recvToBuf_NoPoll();
	if (retcode > 0)
	{
		BYTE pstrCmd[zSocket::MAX_DATASIZE];
		int nCmdLen = mSocket.recvToCmd_NoPoll(pstrCmd, sizeof(pstrCmd));
        //这里只是从缓冲取数据包，所以不会出错，没有数据直接返回
		if (nCmdLen <= 0)
        {
			return 0;
        }
        
        BYTE messageType = *(BYTE*)pstrCmd;
        nCmdLen -= sizeof(BYTE);
        if(messageType != STRUCT_TYPE || nCmdLen <= 0)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, messageType,nCmdLen-1);
            return -1;
        }

        using namespace CMD::SESSION;
        if (verifyLogin((t_LoginSession *)(pstrCmd+sizeof(BYTE))))
        {
            Fir::logger->debug("客户端连接通过验证:%s(%u %u)", this->getIP(), ((t_LoginSession*)pstrCmd)->wdServerID,   ((t_LoginSession*)pstrCmd)->wdServerType);
			veriry_ok=true;
            return 1;
        }
        Fir::logger->error("客户端连接验证失败:%s", this->getIP());
        return -1;
	}
	else
		return retcode;
}

bool SessionTask::checkRecycle()
{
	if(recycle_state == 0)
	{
		return false;
	}
	if(recycle_state == 1)
	{
		if (this->getType() == SCENESSERVER)
		{
			SessionUserManager::getMe().removeUserBySceneID(this);
		}
		else
		{
			Fir::logger->info("[注销网关服务器],0,0,0, %u:%u 成功", this->getType(), this->getID());
			SessionUserManager::getMe().removeUserByGatewayID(this);
		}

		recycle_state=2;
		return true;
	}
	return true;
}
/**
 * \brief 确认一个服务器连接的状态是可以回收的
 *
 * 当一个连接状态是可以回收的状态，那么意味着这个连接的整个生命周期结束，可以从内存中安全的删除了：）<br>
 * 实现了虚函数<code>zTCPTask::recycleConn</code>
 *
 * \return 是否可以回收
 */
int SessionTask::recycleConn()
{
	if(veriry_ok)
	{
		switch(recycle_state)
		{
			case 0:
				{
					recycle_state=1;
					return 0;
				}
				break;
			case 1:
				{
					return 0;
				}
				break;
			case 2:
				{
					return 1;
				}
				break;
		}
	}
	return 1;
}
/*
   {

   SessionUserManager::getMe().removeUserByGatewayID(wdServerID);
   return 1;
   }
// */
void SessionTask::addToContainer()
{
	SessionTaskManager::getMe().addSessionTask(this);
}

void SessionTask::removeFromContainer()
{
	SessionTaskManager::getMe().removeSessionTask(this);
}

bool SessionTask::uniqueAdd()
{
	return SessionTaskManager::getMe().uniqueAdd(this);
}

bool SessionTask::uniqueRemove()
{
	return SessionTaskManager::getMe().uniqueRemove(this);
}

bool SessionTask::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("SessionTask::msgParseProto 消息没有处理");
    return true;
}


/**
 * \brief 解析来自各个服务器连接的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 指令长度
 * \return 处理是否成功
 */

bool SessionTask::msgParse(const BYTE *data, const DWORD nCmdLen)
{
	return MessageQueue::msgParse(data , nCmdLen);
}

bool SessionTask::cmdMsgParse(const BYTE *data, const DWORD nCmdLen)
{
	return zProcessor::msgParse(data , nCmdLen);
}

bool SessionTask::msgParseSessionCmd(const CMD::SESSION::SessionNull *sessionNull,const DWORD nCmdLen)
{
    using namespace CMD::SESSION;
    switch(sessionNull->para)
    {
        case PARA_UNREG_USER_SCENE_SESSION:
            {
                return this->scene_cmd_dispatcher.dispatch(this,sessionNull,nCmdLen);
            }
            break;
        case PARA_REG_USER_GATE_SESSION:
            {
                return this->gate_cmd_dispatcher.dispatch(this,sessionNull,nCmdLen);
            }
            break;
        case PARA_GATE_SESSION_FORWARD_USER:
            {
                t_Session_ForwardUser* rev = (CMD::SESSION::t_Session_ForwardUser*)sessionNull;
            	CMD::NullCmd* cmd = (CMD::NullCmd*)(rev->data);
	            DWORD cmdlen = rev->size;
                SessionUser *sessionUser = SessionUserManager::getMe().getUserByID(rev->dwID);
                if (!sessionUser)
                {
                    Fir::logger->error("[消息处理]:(%u), 用户不存在失败", rev->dwID);
                    return true;
                }
                return this->user_dispatcher.dispatch(sessionUser,cmd,cmdlen);
            }
            break;
        case PARA_REG_USER_SUCCESS_SCENE_SESSION:
            {
                return this->scene_cmd_dispatcher.dispatch(this,sessionNull,nCmdLen);
            }
            break;
        case PARA_UNREG_USER_GATE_SESSION:
            {
                return this->gate_cmd_dispatcher.dispatch(this,sessionNull,nCmdLen);
            }
            break;
    }
    
    Fir::logger->error("%s(%u,%u,%u)", __PRETTY_FUNCTION__, sessionNull->cmd, sessionNull->para, nCmdLen);
	return false;
}


bool SessionTask::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

	using namespace CMD::SESSION;
    switch(ptNullCmd->cmd)
    {
        case SESSIONCMD:
            {
                return msgParseSessionCmd((SessionNull*)ptNullCmd,nCmdLen);
            }
            break;
    }

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}

/**
 * \brief 发送命令给用户
 *
 * \param id 用户id
 * \param pstrCmd 命令指令
 * \param nCmdLen 命令长度
 */
bool SessionTask::sendCmdToUser(const DWORD id, const void *pstrCmd, const DWORD nCmdLen)
{

	using namespace CMD::SESSION;
	using namespace CMD;

	BYTE buf[zSocket::MAX_DATASIZE] = {0};
	t_Session_ForwardUser *scmd=(t_Session_ForwardUser *)buf;
	constructInPlace(scmd);

	scmd->dwID = id;
	scmd->size = nCmdLen;
	bcopy(pstrCmd, scmd->data, nCmdLen);
    
    std::string ret;
    encodeMessage(scmd,sizeof(t_Session_ForwardUser)+nCmdLen,ret);
	return sendCmd(ret.c_str(),ret.size());
}



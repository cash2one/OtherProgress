/**
 * \file
 * \version  $Id: SceneTask.cpp 51 2013-04-16 00:37:19Z  $
 * \author  ,
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 实现场景连接处理
 *
 * 
 */


#include "SceneTask.h"
#include "SceneCommand.h"
#include "SceneServer.h"
#include "SceneTaskManager.h"
#include "SceneUserManager.h"
#include "SceneUser.h"
#include "zMetaData.h"
#include "MassiveCommand.h"
#include "extractProtoMsg.h"
#include "login.pb.h"

SceneUserCmdDispatcher SceneTask::scene_user_dispatcher("sceneusercmd");
/**
 * \brief 验证登陆档案服务器的连接指令
 *
 * 如果验证不通过直接断开连接
 *
 * \param ptCmd 登陆指令
 * \return 验证是否成功
 */
bool SceneTask::verifyLogin(const CMD::SCENE::t_LoginScene *ptCmd)
{
	using namespace CMD::SCENE;

	if (SCENECMD == ptCmd->cmd && PARA_LOGIN == ptCmd->para)
	{
		const CMD::SUPER::ServerEntry *entry = SceneService::getMe().getServerEntry(ptCmd->wdServerID);
		char strIP[32];
		strncpy(strIP, getIP(), 31);
		if (entry && ptCmd->wdServerType == entry->wdServerType	&& 0 == strcmp(strIP, entry->pstrIP))
		{
			wdServerID = ptCmd->wdServerID;
			wdServerType = ptCmd->wdServerType;
			return true;
		}
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
int SceneTask::verifyConn()
{
	int retcode = mSocket.recvToBuf_NoPoll();
	if (retcode > 0)
	{
		BYTE pstrCmd[zSocket::MAX_DATASIZE];
        //这里只是从缓冲取数据包，所以不会出错，没有数据直接返回
		int nCmdLen = mSocket.recvToCmd_NoPoll(pstrCmd, sizeof(pstrCmd));
		if (nCmdLen <= 0)
        {
            return 0;
        }
        
        BYTE messageType = *(BYTE*)pstrCmd;
        if((DWORD)nCmdLen <= sizeof(BYTE) || messageType != STRUCT_TYPE)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, messageType,nCmdLen-1);
            return -1;
        }
        
        using namespace CMD::SCENE;
        if (verifyLogin((t_LoginScene *)(pstrCmd+sizeof(BYTE))))
        {
            Fir::logger->debug("客户端连接通过验证");
            veriry_ok=true;
            return 1;
        }
        Fir::logger->error("客户端连接验证失败");
        return -1;
	}
	else
		return retcode;
}

bool SceneTask::checkRecycle()
{
	if(recycle_state == 0)
	{
		return false;
	}
	if(recycle_state == 1)
	{
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
int SceneTask::recycleConn()
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

bool SceneTask::uniqueAdd()
{
	return SceneTaskManager::getMe().uniqueAdd(this);
}

bool SceneTask::uniqueRemove()
{
	return SceneTaskManager::getMe().uniqueRemove(this);
}

void SceneTask::addToContainer()
{
	//场景启动完成
    CMD::SCENE::t_StartOKSceneGate send;
    std::string ret;
    encodeMessage(&send,sizeof(send),ret);
	this->sendCmd(ret.c_str(),ret.size());
}

bool SceneTask::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    google::protobuf::Message *message = extraceProtoMsg(data,nCmdLen);
    if(!message)
    {
        return false;
    }
    bool ret = false;
    if(!ret)
    {
        Fir::logger->error("%s(%s, %u)", __PRETTY_FUNCTION__, message->GetTypeName().c_str(),nCmdLen);
    }
    SAFE_DELETE(message);
	return ret;
}

/**
 * \brief 解析来自各个服务器连接的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 指令长度
 * \return 处理是否成功
 */

bool SceneTask::msgParse(const BYTE *data, const DWORD nCmdLen)
{
	return MessageQueue::msgParse(data,nCmdLen);
}

bool SceneTask::msgParseUserProto(const BYTE *data, const DWORD nCmdLen,SceneUser *user)
{
    google::protobuf::Message *message = extraceProtoMsg(data,nCmdLen);
    if(!message || !user)
    {
        return false;
    }
    bool ret = this->scene_user_dispatcher.dispatch(user,message);
    if(!ret)
    {
        Fir::logger->error("%s(%s, %u)", __PRETTY_FUNCTION__, message->GetTypeName().c_str(),nCmdLen);
    }
    SAFE_DELETE(message);
	return ret;
}

bool SceneTask::gate_user_cmd_parse(const CMD::SCENE::t_Scene_ForwardScene *rev, const DWORD nCmdLen)
{
    const char *data = rev->data;
	DWORD cmdlen = rev->size;
	SceneUser* user = SceneUserManager::getMe().getUserByID(rev->charid);
	if (!user || !cmdlen) 
	{
		Fir::logger->error("[消息处理]:(%u,%lu), 用户不存在失败", rev->accid, rev->charid);
		return false;
	}
    BYTE messageType = *(BYTE*)data;
  
    //暂且不支持c++消息
    if(messageType == STRUCT_TYPE)
    {
        const CMD::t_NullCmd *readCmd = (CMD::t_NullCmd*)(data+sizeof(BYTE));
        Fir::logger->error("%s(%u,%u,%lu)", __PRETTY_FUNCTION__, readCmd->cmd,readCmd->para,cmdlen-sizeof(BYTE));
        return false;
    }
    else if(messageType == PROTOBUF_TYPE)
    {
        return msgParseUserProto((BYTE*)(data+sizeof(BYTE)),cmdlen-sizeof(BYTE),user);
    }
    return false;
}

bool SceneTask::cmdMsgParse(const BYTE *message,const DWORD nCmdLen)
{
    return zProcessor::msgParse(message,nCmdLen);
}


bool SceneTask::msgParseSceneCmd(const CMD::SCENE::SceneNull *sceneNull,const DWORD nCmdLen)
{
    using namespace CMD::SCENE;
    switch(sceneNull->para)
    {
        case PARA_LOGIN:
            {
            }
            break;
        case PARA_REFRESH_LOGIN_SCENE:
            {
            }
            break;
        //处理转发过来的消息
        case PARA_FORWARD_SCENE:
            {
                return msgParseForwardCmd((CMD::SCENE::t_Scene_ForwardScene*)sceneNull,nCmdLen);
            }
            break;
        case PARA_SCENE_USER:
            {
            }
            break;
        case PARA_START_OK_SCENE_GATE:
            {
            }
            break;
    }
    Fir::logger->error("%s(%u,%u,%u)", __PRETTY_FUNCTION__, sceneNull->cmd,sceneNull->para,nCmdLen);
    return true;
}

bool SceneTask::msgParseForwardCmd(const CMD::SCENE::t_Scene_ForwardScene *cmd,const DWORD nCmdLen)
{
    return gate_user_cmd_parse(cmd,nCmdLen);
}

bool SceneTask::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }
    switch(ptNullCmd->cmd)
    {
        case SCENECMD:
            {
                return msgParseSceneCmd((CMD::SCENE::SceneNull*)ptNullCmd,nCmdLen);
            }
            break;
    }
	Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, ptNullCmd->_id, nCmdLen);
	return true;
}


/**
 * \brief 发送命令给用户
 *
 * \param id 用户id
 * \param pstrCmd 命令指令
 * \param nCmdLen 命令长度
 */
bool SceneTask::sendCmdToUser(const DWORD id, const void *pstrCmd, const DWORD nCmdLen)
{
	using namespace CMD::SCENE;
	using namespace CMD;

	BYTE buf[zSocket::MAX_DATASIZE] = {0};
    t_User_FromScene *scmd=(t_User_FromScene *)(buf);
	constructInPlace(scmd);

	scmd->charid = id;
	scmd->size = nCmdLen;
	bcopy(pstrCmd, scmd->data, nCmdLen);
    
    std::string ret;
    if(encodeMessage(scmd,sizeof(t_User_FromScene)+scmd->size,ret))
    {
        return sendCmd(ret.c_str(),ret.size());
    }
    return false;
}


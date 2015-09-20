/**
 * \file
 * \version  $Id: SessionClient.cpp 36 2013-04-07 11:42:48Z  $
 * \author  ,
 * \date 2013年03月31日 10时20分55秒 CST
 * \brief 定义Session服务器连接客户端
 *
 */

#include <unistd.h>
#include <iostream>
#include "zTCPClient.h"
#include "SessionCommand.h"
#include "SessionClient.h"
#include "SceneServer.h"
#include "Fir.h"
#include "SceneTaskManager.h"
#include "RecordClient.h"
#include "TimeTick.h"
#include "extractProtoMsg.h"

SessionClient *sessionClient = NULL;
std::map<DWORD, QWORD> SessionClient::cmdCount;
std::map<DWORD, DWORD> SessionClient::tmEffectMap;
std::map<DWORD, DWORD> SessionClient::townStarMap;
std::map<DWORD, DWORD> SessionClient::userSortMap;
BYTE SessionClient::cmdCountSwitch = 0;
CmdAnalysis SessionClient::analysis(1, "SessionClient", 300);
UserLoginCmdDispatcher SessionClient::user_login_dispatcher("logincmd");
UserLoginCmdDispatcher SessionClient::session_client_dispatcher("sessionclientcmd");

/**
 * \brief 重载zThread中的纯虚函数，是线程的主回调函数，用于处理接收到的指令
 *
 */
void SessionClient::run()
{
	zTCPBufferClient::run();

	//与Session之间的连接断开，需要关闭服务器
	SceneService::getMe().Terminate();
	while(!SceneService::getMe().isSequeueTerminate())
	{
		zThread::msleep(10);
	}

}

bool SessionClient::msgParseProto(const BYTE *data, const DWORD nCmdLen)
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
 * \brief  处理会话发送过来的消息处理内容包括
 1 社会关系战
 2 场景的注册注销
 3 角色的注册注销
 4 动态加载，卸载地图
 5 用户临时存档
 6 帮会，家族，门派的相关处理
 7 私聊消息处理
 * \param  
 * \return  
 */
bool SessionClient::msgParse(const BYTE *data, const DWORD nCmdLen)
{
	return MessageQueue::msgParse(data, nCmdLen);
}

bool SessionClient::cmdMsgParse(const BYTE *data, const DWORD nCmdLen)
{
	return zProcessor::msgParse(data, nCmdLen);
}

bool SessionClient::msgParseSessionCmd(const CMD::SESSION::SessionNull *sessionNull,const DWORD nCmdLen)
{
    using namespace CMD::SESSION;
    switch(sessionNull->para)
    {
        case PARA_REG_USER_SESSION_SCENE:
            {
                return this->user_login_dispatcher.dispatch(this, sessionNull, nCmdLen);
            }
            break;
        case PARA_UNREG_USER_SESSION_SCENE:
            {
                return this->user_login_dispatcher.dispatch(this, sessionNull, nCmdLen);
            }
            break;
    }
    
    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, sessionNull->cmd, sessionNull->para, nCmdLen);
    return true;
}


bool SessionClient::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

#ifdef _ZJW_DEBUG
	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
#endif	
#ifdef _DEBUG_WCX
	Fir::logger->debug("%u",ptNullCmd->_id);
#endif
#ifdef _COMMAND_TIME
    CommandTime func_time(400000, "SessionClient", ptNullCmd->cmd, ptNullCmd->para);
#endif

	SceneService::cmd_record[2] = ptNullCmd->cmd;
	SceneService::cmd_record[3] = ptNullCmd->para;


	My_Address_wrapper((void *)ptNullCmd);
	
	if (cmdCountSwitch)
    {
        analysis.add(ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
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
 * \brief  登录会话服务器
 * \return  true 登录消息发送成功， false 无法发送消息
 */
bool SessionClient::connectToSessionServer()
{
	if (!connect())
	{
		Fir::logger->error("连接Session服务器失败");
		return false;
	}

	using namespace CMD::SESSION;
	t_LoginSession tCmd;
	tCmd.wdServerID = SceneService::getMe().getServerID();
	tCmd.wdServerType = SceneService::getMe().getServerType();
    
    std::string ret;
    if(encodeMessage(&tCmd,sizeof(t_LoginSession),ret))
    {
        return sendCmd(ret.c_str(),ret.size());
    }
    return false;
}
	

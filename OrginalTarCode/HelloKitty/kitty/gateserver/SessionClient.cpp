/**
 * \file
 * \version  $Id: SessionClient.cpp 42 2013-04-10 07:33:59Z  $
 * \author  ,@163.com
 * \date 2004年11月05日 13时58分55秒 CST
 * \brief 定义Session服务器连接客户端
 *
 */

#include <unistd.h>
#include <iostream>

#include "zTCPClient.h"
#include "SessionCommand.h"
#include "SessionClient.h"
#include "GatewayServer.h"
#include "SceneClient.h"
#include "GateUserManager.h"
#include "Fir.h"
#include "RecordClient.h"
#include "zSocket.h"
#include "extractProtoMsg.h"

std::map<DWORD, QWORD> SessionClient::cmdCount;
std::map<DWORD, QWORD> SessionClient::forwardCount;
BYTE SessionClient::cmdCountSwitch = 0;
CmdAnalysis SessionClient::analysisSession(7, "SessionClient", 300);
CmdAnalysis SessionClient::analysisForward(8, "SessionForward", 300);

/**
 * \brief Session服务器连接客户端
 *
 * 一个区中只有一个Session服务器，所以这里只需要保留一个指针，不需要连接管理器之类的东东
 *
 */
SessionClient *sessionClient = NULL;

/**
 * \brief 建立到Session服务器的连接
 *
 * \return 连接是否成功
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
	tCmd.wdServerID = GatewayService::getMe().getServerID();
	tCmd.wdServerType = GatewayService::getMe().getServerType();
    
    std::string ret;
    if(encodeMessage(&tCmd,sizeof(t_LoginSession),ret))
    {
        return sendCmd(ret.c_str(),ret.size());
    }
	return false;
}

/**
 * \brief 重载zThread中的纯虚函数，是线程的主回调函数，用于处理接收到的指令
 *
 */
void SessionClient::run()
{
	zTCPBufferClient::run();

	//与Session之间的连接断开，需要关闭服务器
	GatewayService::getMe().Terminate();
	while(!GatewayService::getMe().isSequeueTerminate())
	{
		zThread::msleep(10);
	}
	// */
}

bool SessionClient::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("SessionClient::msgParseProto 消息没处理");
    return true;
}


/**
 * \brief 解析来自Session服务器的所有指令
 *
 * \param ptNullCmd 待解析的指令
 * \param nCmdLen 待解析的指令长度
 * \return 解析是否成功
 */
bool SessionClient::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

	using namespace CMD::SESSION;
	this->last_para = ptNullCmd->para;
	this->last_cmd = ptNullCmd->cmd;
	this->last_cmd_len = nCmdLen;

	if (cmdCountSwitch) analysisSession.add(ptNullCmd->cmd, ptNullCmd->para, nCmdLen);

	if (ptNullCmd->_id == CMD::SESSION::ID::t_Session_ForwardUser)
	{
		t_Session_ForwardUser *rev=(t_Session_ForwardUser *)ptNullCmd;
		GateUser *pUser=(GateUser *)GateUserManager::getMe().getUserCharid(rev->dwID);
		this->last_user_cmd = ((CMD::NullCmd *)rev->data)->_id;
		this->last_user_para = 0;
		this->last_user_cmd_len = rev->size;
		if (pUser)
			pUser->sendCmd(rev->data,rev->size);
		return true;
	}
	else if (ptNullCmd->_id == CMD::SESSION::ID::t_Session_ForwardWorld)
	{
		t_Session_ForwardWorld *rev=(t_Session_ForwardWorld *)ptNullCmd;
		GateUserManager::getMe().sendCmdToWorld(rev->data,rev->size);
		return true;
	}
	else if(ptNullCmd->_id == CMD::SESSION::ID::t_KickOutUser_SessionGate)
	{
		t_KickOutUser_SessionGate* rev = (t_KickOutUser_SessionGate*)ptNullCmd;
		// 踢玩家下线
		GateUser* pUser =  GateUserManager::getMe().getUserAccount(rev->acctype,rev->account);
		if(pUser != NULL)
		{   
			CMD::stNotifyUserKickOut_SC send;

			pUser->sendCmd(&send,sizeof(send));

			pUser->Terminate();
		}   
		return true;
	}

	Fir::logger->error("%s(%u, %u, %u), _id:%d", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen, ptNullCmd->_id);
	return false;
}


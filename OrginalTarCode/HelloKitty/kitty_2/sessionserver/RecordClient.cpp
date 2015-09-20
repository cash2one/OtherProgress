/**
 * \file
 * \version  $Id: RecordClient.cpp 29 2013-04-07 01:39:43Z  $
 * \author  ,@163.com
 * \date 2004年11月05日 13时58分55秒 CST
 * \brief 定义档案服务器连接客户端
 *
 * 负责与档案服务器交互，存取档案
 * 
 */

#include <unistd.h>
#include <iostream>

#include "zTCPClient.h"
#include "RecordCommand.h"
#include "RecordClient.h"
#include "SessionServer.h"
#include "Fir.h"
#include "SessionTask.h"
#include "extractProtoMsg.h"

///RecordClient的唯一实例
RecordClient *recordClient = NULL;

/**
 * \brief 创建到档案服务器的连接
 *
 * \return 连接是否成功
 */
bool RecordClient::connectToRecordServer()
{
	if (!connect())
	{
		Fir::logger->error("连接档案服务器失败");
		return false;
	}

	using namespace CMD::RECORD;
	t_LoginRecord tCmd;
	tCmd.wdServerID = SessionService::getMe().getServerID();
	tCmd.wdServerType = SessionService::getMe().getServerType();
    
    std::string ret;
    if(encodeMessage(&tCmd,sizeof(t_LoginRecord),ret))
    {
        return sendCmd(ret.c_str(),ret.size());
    }
    return false;
}

/**
 * \brief 重载zTCPBufferClient的run方法
 *
 *
 */
void RecordClient::run()
{
	zTCPBufferClient::run();

	//与档案服务器的连接断开，关闭服务器
	SessionService::getMe().Terminate();
	while (!SessionService::getMe().isSequeueTerminate())
	{
		zThread::msleep(10);
	}
}

bool RecordClient::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->debug("sessionserver RecordClient::msgParseProto 消息没有处理");
    return true;
}


/**
 * \brief 解析来自档案服务器的指令
 *
 * \param ptNullCmd 待解析的指令
 * \param nCmdLen 待解析的指令长度
 * \return 解析指令是否成功
 */
bool RecordClient::msgParse(const BYTE *data, const DWORD nCmdLen)
{
	return MessageQueue::msgParse(data , nCmdLen);
}

bool RecordClient::cmdMsgParse(const BYTE *data, const DWORD nCmdLen)
{
    return zProcessor::msgParse(data,nCmdLen);
}

bool RecordClient::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);

	return false;
}


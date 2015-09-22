/**
 * \file
 * \version  $Id: RecordClient.cpp 37 2013-04-08 01:52:56Z  $
 * \author  ,
 * \date 2013年04月05日 13时58分55秒 CST
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
#include "SceneServer.h"
#include "Fir.h"
#include "SceneTask.h"
#include "SessionClient.h"
#include "extractProtoMsg.h"

///RecordClient的唯一实例
RecordClient *recordClient = NULL;
/**
 * \brief 解压角色需要保存的数据
 *
 * \param pUser 角色指针
 * \param data 输入：压缩的数据 / 输出：解压后的数据 
 * \param dataSize 输入 数据大小
 * \return 解压后的数据大小
 */
//bool uncompressSaveData(SceneUser *pUser , const unsigned char *data ,const DWORD dataSize, unsigned char * petData); 

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
	tCmd.wdServerID = SceneService::getMe().getServerID();
	tCmd.wdServerType = SceneService::getMe().getServerType();
    
    std::string ret;
    return encodeMessage(&tCmd,sizeof(tCmd),ret) && sendCmd(ret.c_str(),ret.size());
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
	SceneService::getMe().Terminate();
	while (sessionClient)
	{
		zThread::msleep(10);
	}
}

bool RecordClient::msgParseProto(const BYTE *data, const DWORD nCmdLen)
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
 * \brief 解析来自档案服务器的指令
 *
 * \param ptNullCmd 待解析的指令
 * \param nCmdLen 待解析的指令长度
 * \return 解析指令是否成功
 */
bool RecordClient::msgParse(const BYTE *data, const DWORD nCmdLen)
{
	return MessageQueue::msgParse(data, nCmdLen);
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

	using namespace CMD::RECORD;

#ifdef _COMMAND_TIME
    CommandTime func_time(400000, "RecordClient", ptNullCmd->cmd, ptNullCmd->para);
#endif

#if 0
	if(ptNullCmd->cmd==CMD_SCENE)
	{//处理档案<->场景的消息

		
	}
#endif
	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);

	return false;
}

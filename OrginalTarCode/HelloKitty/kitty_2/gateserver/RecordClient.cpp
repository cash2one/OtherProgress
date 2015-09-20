/**
 * \file
 * \version  $Id: RecordClient.cpp 64 2013-04-23 02:05:08Z  $
 * \author  ,@163.com
 * \date 2005年04月01日 11时57分23秒 CST
 * \brief 实现网关服务器到档案服务器的连接客户端
 */

#include "RecordClient.h"
#include "RecordCommand.h"
#include "GatewayServer.h"
#include "Fir.h"
#include "GateUserManager.h"
#include "SuperCommand.h"
#include "GatewayServer.h"
#include "SceneClient.h"
#include "TimeTick.h"
#include "GatewayTaskManager.h"
#include "extractProtoMsg.h"

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
	tCmd.wdServerID = GatewayService::getMe().getServerID();
	tCmd.wdServerType = GatewayService::getMe().getServerType();
    
    std::string ret;
    if(encodeMessage(&tCmd,sizeof(t_LoginRecord),ret))
    {
        return sendCmd(ret.c_str(),ret.size());
    }
    return false;
}

/**
 * \brief 线程回调函数
 *
 */
void RecordClient::run()
{
	zTCPBufferClient::run();

	//与档案服务器的连接断开，关闭服务器
	GatewayService::getMe().Terminate();
}

bool RecordClient::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("RecordClient::msgParseProto 消息没处理");
    return true;
}

bool RecordClient::msgParseRecordCmd(const CMD::RECORD::RecordNull *recordNull,const DWORD nCmdLen)
{
    using namespace CMD::RECORD;
    switch(recordNull->para)
    {
        case PARA_GATE_CREATECHAR_RETURN:
            {
                t_CreateChar_Return_GateRecord* cmd = (t_CreateChar_Return_GateRecord*)recordNull;
                GateUser* gateUser = GateUserManager::getMe().getUserAccount(cmd->acctype, cmd->account);
	
				if (!gateUser || !gateUser->gatewaytask)
				{
                    Fir::logger->debug("[创建角色], charid=%lu,acctype=%u,account=%s 角色已下线", cmd->charid,cmd->acctype,cmd->account);
					return true;
				}

				if (gateUser->isTerminateWait() || gateUser->isTerminate() || !gateUser->isCreateState())
				{
					Fir::logger->debug("[创建角色], charid=%lu,acctype=%u,account=%s 角色已不在创建角色状态", cmd->charid,cmd->acctype,cmd->account);
					gateUser->gatewaytask->login_return(HelloKittyMsgData::TimeOut);
					return true;
				}

				if (cmd->retcode == 0)
				{
                    //创建成功,先写个简单版，但这儿是线程不安全的，回头，在task上，再加个定时器，用来处理这类事件
					gateUser->accid = cmd->accid;
					gateUser->charid = cmd->charid;
					Fir::logger->trace("[创建角色],charid=%lu,acctype=%u,account=%s 角色创建成功", cmd->charid,cmd->acctype,cmd->account);

					if (gateUser->gatewaytask) 
					{
						gateUser->gatewaytask->setACCID(cmd->accid);
						gateUser->gatewaytask->setCharID(cmd->charid);
						gateUser->onCreateCharSuccess();
						gateUser->beginSelect();
						GatewayService::getMe().notifyLoginServer();
                    }
                    return true;
                }
                if (3 == cmd->retcode)
				{
					gateUser->nameRepeat();
				}
				else
				{
					gateUser->noCharInfo();
				}
                return true;
            }
            break;
    }
    
    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, recordNull->cmd, recordNull->para, nCmdLen);
	return false;
}

/**
 * \brief 解析来自档案服务器的指令
 *
 * \param ptNullCmd 待解析的指令
 * \param nCmdLen 待解析的指令长度
 * \return 解析指令是否成功
 */
bool RecordClient::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }
	using namespace CMD::RECORD;
    switch(ptNullCmd->cmd)
    {
        case RECORDCMD:
            {
                return msgParseRecordCmd((RecordNull*)ptNullCmd,nCmdLen);
            }
            break;
    }
   
    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}

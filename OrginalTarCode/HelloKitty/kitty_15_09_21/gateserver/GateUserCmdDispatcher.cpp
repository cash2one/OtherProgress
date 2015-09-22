/**
 * \file
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义用户登录相关命令处理文件，注册给dispatcher
 *
 */

#include "GatewayTask.h"
#include "GateUserCmdDispatcher.h"
#include "GatewayServer.h"
#include "SceneClientManager.h"
#include "RecordClient.h"
#include "zMisc.h"

bool GateUserCmdHandle::create_role(GateUser* u, const HelloKittyMsgData::ReqCreateRole *message)
{
	if (!u)
    {
        return true;
    }

	if (!u->isCreateState())
	{ 
        Fir::logger->debug("[客户端登录_3]:网关请求db创建角色失败(用户不在创建状态,%u,%s)",u->acctype,u->account.c_str());
		return true;
	}
	if (!u->gatewaytask)
	{
        Fir::logger->debug("[客户端登录_3]:网关请求db创建角色失败(gatewaytask为空,%u,%s)",u->acctype,u->account.c_str());
		return true;
	}

	if (!u->gatewaytask->checkNewName(const_cast<char*>(message->name().c_str())))
	{
		u->gatewaytask->login_return(HelloKittyMsgData::NameIllega);
        Fir::logger->debug("[客户端登录_3]:网关请求db创建角色失败(创建角色昵称重名,%u,%s)",u->acctype,u->account.c_str());
		return true;
	}
    RecordClient* recordClient= MgrrecordClient.GetMinPlayerRecord();
    if(recordClient == NULL)
    {
        Fir::logger->debug("[客户端登录_3]:网关请求db创建角色失败(创建角色db出错,%u,%s)",u->acctype,u->account.c_str());
		return true;
    }

	std::string account = u->gatewaytask->account;
	u->heroid = message->heroid();
    
    CMD::RECORD::t_CreateChar_GateRecord req;
	strncpy(req.name, message->name().c_str(), MAX_NAMESIZE);
	strncpy(req.password, u->gatewaytask->password.c_str(), MAX_PASSWORD);
	req.bySex = message->sex();
	strncpy(req.phone_uuid,u->strPhoneUuid.c_str(),sizeof(req.phone_uuid));
	req.type = u->acctype;
	strncpy(req.account, u->gatewaytask->account.c_str(), MAX_ACCNAMESIZE);

    std::string ret;
    encodeMessage(&req,sizeof(req),ret);
	recordClient->sendCmd(ret.c_str(),ret.size());
    Fir::logger->debug("[客户端登录_3]:网关请求db创建角色成功(向db注册新角色,%u,%s)",u->acctype,u->account.c_str());
	return true;
}

bool GateUserCmdHandle::op_receive_world_chat(GateUser* u,const HelloKittyMsgData::ReqOpReceiveWorldChatCmd *message)
{
    if (NULL == u)
    {
        return true;
    }

    u->needReceiveWorldChat = message->switchflg();
    
    std::string ret;
    if(encodeMessage(message,ret))
    {
        u->sendCmd(ret.c_str(),ret.size());
    }
    return true;
}
/*
bool GateUserCmdHandle::reqEnterGarden(GateUser* u,const HelloKittyMsgData::ReqEnterGarden *message)
{
}
*/


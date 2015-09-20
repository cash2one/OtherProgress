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

bool GateUserCmdHandle::create_role(GateUser* u, const HelloKittyMsgData::RequireCreateRole *message)
{
	if (!u)
    {
        return true;
    }

	if (!u->isCreateState())
	{ 
		Fir::logger->trace("[创建角色],acctype=%u,account=%s,0,0, 用户不在创建状态", u->acctype, u->account.c_str());
		return true;
	}
	if (!u->gatewaytask)
	{
		Fir::logger->trace("[创建角色],acctype=%u,account=%s,0,0, 玩家已经下线", u->acctype, u->account.c_str());
		return true;
	}

	if (!u->gatewaytask->checkNewName(const_cast<char*>(message->name().c_str())))
	{
		u->gatewaytask->login_return(HelloKittyMsgData::NameIllega);
		Fir::logger->trace("[创建角色],acctype=%u,account=%s,nick_name,%s,0, 角色名不合法", u->acctype, u->account.c_str(), message->name().c_str());
		return true;
	}

	DWORD acctype = u->acctype;
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

	Fir::logger->trace("[创建角色],acctype=%u,account=%s,nick_name=%s,0, 用户创建角色,登陆类型:%u", acctype, account.c_str(), req.name, req.type);
	return true;
}

bool GateUserCmdHandle::op_receive_world_chat(GateUser* u,const HelloKittyMsgData::OpReceiveWorldChatCmd *message)
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


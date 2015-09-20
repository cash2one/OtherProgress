/**
 * \file
 * \version  $Id: LoginCmdDispatcher.cpp 64 2013-04-23 02:05:08Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义用户登录相关命令处理文件，注册给dispatcher
 *
 */

#include "LoginCmdDispatcher.h"
#include "SceneUser.h"
#include "SceneUserManager.h"
#include "SceneTaskManager.h"

bool LoginCmdHandle::userreg(SessionClient* task, const CMD::SESSION::t_regUser_SceneSession* cmd, DWORD nCmdLen)
{
	SceneUser* u = SceneUserManager::getMe().getUserByID(cmd->charid);
	SceneTask* gate = SceneTaskManager::getMe().getTaskByID(cmd->gate_id);

	//if(cmd->reg_type == 0)
	//{
		if (!gate)
		{
			//网关已不存在，注册失败
			if (u) u->reg_unreg(CMD::SESSION::UNREGUSER_RET_ERROR);
			Fir::logger->error("[登录],charid=%lu,0,0,玩家登录 网关已经不在,gateid=%u",cmd->charid,cmd->gate_id);
			return true;
		}
	//}

	if (!u)
	{
        //没有玩家数据，玩家首次登录
		u = FIR_NEW SceneUser(gate);

		if (u)
		{
#ifdef _ALL_SUPER_GM
			Fir::logger->error("[登录]:%u,%lu,%s 玩家开始在场景注册",u->accid,u->charid,u->nickname);
#endif
			if (u->reg(cmd))
			{
				//通知会话，场景上线成功
				std::string phone_uuid(cmd->phone_uuid);
				if(!u->online(phone_uuid,gate))
				{
					Fir::logger->error("[登录]:%u,%lu,%s 玩家上线处理失败", cmd->accid, cmd->charid, cmd->name);
				}
				return true;
			}
			else
			{
				Fir::logger->error("[登录]:%u,%lu,%s 角色注册失败", cmd->accid, cmd->charid, cmd->name);
				u->reg_unreg(CMD::SESSION::UNREGUSER_RET_ERROR);
				SAFE_DELETE(u);
				return true;
			}
		}
		else
		{
			Fir::logger->error("[登录]:%u,%lu,%s 分配内存错误", cmd->accid, cmd->charid, cmd->name);
			//通知会话注销
			return true;
		}
	}

	if (u && !u->is_online())
	{//已有玩家数据，并且玩家并不在线，允许上线流程 //每次上线，更新最新accid和ip
		u->accid = cmd->accid;
		//u->ip = cmd->ip;
		std::string phone_uuid(cmd->phone_uuid);
		u->online(phone_uuid,gate);
	}
	else if (u && u->is_online())
	{//已有玩家数据，并且玩家已经在线，重复登录,消息忽略
		Fir::logger->error("[登录]:%u,%lu,%s 玩家已在线", cmd->accid, cmd->charid, cmd->name);
	}

	return true;
}

bool LoginCmdHandle::user_unreg(SessionClient* task, const CMD::SESSION::t_unregUser_SessionScene* cmd, DWORD nCmdLen)
{
	SceneUser* u = SceneUserManager::getMe().getUserByID(cmd->charid);
	if (!u) 
	{
		return true;
	}

	Fir::logger->error("[注销]:%u,%lu,%s 会话通知玩家注销", u->accid, u->charid, u->nickname);
	u->unreg();

	return true;
}

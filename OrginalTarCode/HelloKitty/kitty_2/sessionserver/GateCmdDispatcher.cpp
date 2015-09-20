/**
 * \file
 * \version  $Id: GateCmdDispatcher.cpp 75 2013-04-25 05:10:39Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义网关服务器间命令处理文件，注册给dispatcher
 *
 */

#include "GateCmdDispatcher.h"
#include "SessionUserManager.h"
#include "SceneSessionManager.h"
#include "SessionTaskManager.h"
#include "TimeTick.h"

bool GateCmdHandle::user_reg(SessionTask*task, const CMD::SESSION::t_regUser_GateSession* cmd, DWORD cmd_size)
{
	if (NULL == task)
    {
        return false;
    }

	SessionUser* u = SessionUserManager::getMe().getUserByID(cmd->charid);

	if (!u)
	{
        //没有玩家数据，玩家首次登录
		SessionTask* scene = SessionTaskManager::getMe().getMinLoad();//查找最小负载服务器,肯定
		if (scene)
		{
			u = FIR_NEW SessionUser(task->getID(), scene->getID());

			if (u)
			{
				Fir::logger->error("[登录]:%u,%lu,%s 注册到 %d 场景", cmd->accid, cmd->charid, cmd->name, scene->getID());
				if (u->reg(cmd,true))
				{
					SessionUserManager::getMe().addUser(u);
				}
				return true;
			}
			else
			{
				Fir::logger->error("[登录]:%u,%lu,%s 分配内存错误", cmd->accid, cmd->charid, cmd->name);
			}
		}
		return true;
	}

	if (u && !u->is_online())
	{   
        //已有玩家数据，并且玩家不在线，允许继续注册
		u->update_gate(task->getID());
	
        if (!u->getSceneTask()) 
		{
            //如果玩家之前所在场景无效，重新分配场景
			SessionTask* scene = SessionTaskManager::getMe().getMinLoad();
			if (scene)
			{
				Fir::logger->error("[登录]:%u,%lu,%s 注册到 %d 场景", cmd->accid, cmd->charid, cmd->name, scene->getID());
				u->update_scene(scene->getID());
				return true;
			}
			return true;
		}
		u->reg(cmd,false);
	}
	return true;
}

bool GateCmdHandle::user_unreg(SessionTask*task, const CMD::SESSION::t_unregUser_GateSession* cmd, DWORD cmd_size)
{
	SessionUser* u = SessionUserManager::getMe().getUserByID(cmd->charid);
	if (!u) return true;

	Fir::logger->trace("[注销],(charid=%lu,nickname=%s) 网关通知玩家注销", u->charid, u->nickname);
	u->unreg();

	return true;
}

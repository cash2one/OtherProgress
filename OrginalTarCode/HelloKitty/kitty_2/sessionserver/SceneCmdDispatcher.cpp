/**
 * \file
 * \version  $Id: SceneCmdDispatcher.cpp 46 2013-04-11 06:32:18Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义场景服务器间命令处理文件，注册给dispatcher
 *
 */

#include "SceneCmdDispatcher.h"
#include "SessionUserManager.h"
#include "SceneSessionManager.h"
#include "tbx.h"
#include "Fir.h"

bool SceneCmdHandle::user_regsuccess(SessionTask*task, const CMD::SESSION::t_regUserSuccess_SceneSession* cmd, const DWORD cmd_size)
{
	SessionUser* sessionUser = SessionUserManager::getMe().getUserByID(cmd->charid);

    //没有玩家数据,通知网关注销
	if (!sessionUser)
	{
		Fir::logger->debug("[登录]:charid=%lu 用户不存在，注册失败", cmd->charid);
		return true;
	}

    //不在注册状态，收到消息不处理
	if (!sessionUser->is_reg())
	{
		return true;
	}

	sessionUser->scene_online(task->getID());

	return true;
}

bool SceneCmdHandle::user_unreg(SessionTask* task, const CMD::SESSION::t_unregUser_SceneSession* cmd, const DWORD cmd_size)
{

	return true;
}

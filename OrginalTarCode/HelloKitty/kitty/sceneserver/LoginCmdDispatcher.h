/**
 * \file
 * \version  $Id: LoginCmdDispatcher.h 42 2013-04-10 07:33:59Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义用户登录相关命令处理文件，注册给dispatcher
 *
 */

#ifndef _LOGIN_USER_CMD_DISPATCHER
#define _LOGIN_USER_CMD_DISPATCHER

#include <string.h>
#include "Fir.h"
#include "Command.h"
#include "SceneServer.h"
#include "dispatcher.h"
#include "zCmdHandle.h"
#include "SessionCommand.h"
#include "SessionClient.h"



class LoginCmdHandle : public zCmdHandle
{
	public:
		LoginCmdHandle()
		{

		}

		void init()
		{

		SessionClient::user_login_dispatcher.func_reg<CMD::SESSION::t_regUser_SceneSession>(
					CmdCallback<SessionClient, const CMD::SESSION::t_regUser_SceneSession>::Function(this, &LoginCmdHandle::userreg));

		SessionClient::user_login_dispatcher.func_reg<CMD::SESSION::t_unregUser_SessionScene>(
					CmdCallback<SessionClient, const CMD::SESSION::t_unregUser_SessionScene>::Function(this, &LoginCmdHandle::user_unreg));

		}

		bool userreg(SessionClient* task, const CMD::SESSION::t_regUser_SceneSession* cmd, DWORD nCmdLen);
		bool user_unreg(SessionClient* task, const CMD::SESSION::t_unregUser_SessionScene* cmd, DWORD nCmdLen);
};

#endif

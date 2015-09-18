/**
 * \file
 * \version  $Id: GateCmdDispatcher.h 42 2013-04-10 07:33:59Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义网关服务器间命令处理文件，注册给dispatcher
 *
 */

#ifndef _GATE_CMD_DISPATCHER
#define _GATE_CMD_DISPATCHER

#include "Fir.h"
#include "Command.h"
#include "SessionServer.h"
#include "dispatcher.h"
#include "zCmdHandle.h"
#include <string.h>
#include "SessionCommand.h"
#include "SessionTask.h"

class SessionUser;
class SessionTask;


class GateCmdHandle : public zCmdHandle
{
	public:
		GateCmdHandle()
		{}

		void init()
		{
			Fir::logger->debug("func_reg1 %d", CMD::SESSION::ID::t_regUser_GateSession);
			Fir::logger->debug("func_reg1 %d", CMD::SESSION::ID::t_unregUser_GateSession);

			SessionTask::gate_cmd_dispatcher.func_reg<CMD::SESSION::t_regUser_GateSession>(
					CmdCallback<SessionTask, const CMD::SESSION::t_regUser_GateSession>::Function(this, &GateCmdHandle::user_reg));

			SessionTask::gate_cmd_dispatcher.func_reg<CMD::SESSION::t_unregUser_GateSession>(
					CmdCallback<SessionTask, const CMD::SESSION::t_unregUser_GateSession>::Function(this, &GateCmdHandle::user_unreg));
		}

		/**
		 * \brief 处理网关注册用户命令
		 *
		 * \return 是否处理成功
		 */
		bool user_reg(SessionTask*task, const CMD::SESSION::t_regUser_GateSession* cmd, DWORD cmd_size);

		/**
		 * \brief 处理网关注销用户户命令
		 *
		 * \return 是否处理成功
		 */

		bool user_unreg(SessionTask*task, const CMD::SESSION::t_unregUser_GateSession* cmd, DWORD cmd_size);
};

#endif

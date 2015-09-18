/**
 * \file
 * \version  $Id: SceneCmdDispatcher.h 42 2013-04-10 07:33:59Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义场景服务器间命令处理文件，注册给dispatcher, 只允许将系统级命令放在这里，与业务逻辑相关命令，独立成另外的文件
 *
 */

#ifndef _SCENE_CMD_DISPATCHER
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


class SceneCmdHandle : public zCmdHandle
{
	public:
		SceneCmdHandle()
		{}

		void init()
		{
			SessionTask::scene_cmd_dispatcher.func_reg<CMD::SESSION::t_regUserSuccess_SceneSession>(
					CmdCallback<SessionTask, const CMD::SESSION::t_regUserSuccess_SceneSession>::Function(this, &SceneCmdHandle::user_regsuccess));

			SessionTask::scene_cmd_dispatcher.func_reg<CMD::SESSION::t_unregUser_SceneSession>(
					CmdCallback<SessionTask, const CMD::SESSION::t_unregUser_SceneSession>::Function(this, &SceneCmdHandle::user_unreg));
		}

		/**
		 * \brief 处理场景注册用户成功
		 *
		 * \return 是否处理成功
		 */
		bool user_regsuccess(SessionTask*task, const CMD::SESSION::t_regUserSuccess_SceneSession* cmd, DWORD cmd_size);
		
		/**
		 * \brief 处理场景注册失败
		 *
		 * \return 是否处理成功
		 */
		bool user_unreg(SessionTask*task, const CMD::SESSION::t_unregUser_SceneSession* cmd, DWORD cmd_size);
		
};

#endif

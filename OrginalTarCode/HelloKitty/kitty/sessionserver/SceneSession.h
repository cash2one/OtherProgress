/**
 * \file
 * \version  $Id: SceneSession.h 32 2013-04-07 02:10:33Z  $
 * \author  ,
 * \date 2013年3月30日 11时19分09秒 CST
 * \brief 场景会话
 *
 * 
 */

#ifndef _SCENE_SESSION_H
#define _SCENE_SESSION_H

#include "Session.h"
#include "zScene.h"

/**
 * \brief 场景会话
 *
 */
class SceneSession:public zScene,public Session
{

	public:
		/**
		 * \brief 构造函数
		 */
		SceneSession(SessionTask *task):zScene(),Session(task)
		{
		}

		/**
		 * \brief 通过消息注册一个地图
		 * \param reginfo 地图注册消息
		 * \return 是否注册成功
		 */
		bool reg(const CMD::SESSION::t_LoginSession* cmd)
		{
			this->id = cmd->wdServerID;
			return true;
		}

		void sendCmdToAll(const void *cmd, const DWORD len);
		void sendInfoToAll(const DWORD info_type, const char* message, ...);

		DWORD total_active;//当前活跃玩家，在线玩家
		DWORD total_all;//统计总人数
};

#endif

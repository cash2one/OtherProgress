#ifndef _SESSIONUSER_H_
#define _SESSIONUSER_H_

#include "SessionTask.h"
#include <map>
#include <unordered_map>
#include "Session.h"
#include "RecordCommand.h"
#include "TimeTick.h"
#include <list>
enum
{
	SESSION_PLAYER_STATE_NONE,//玩家不存在
	SESSION_PLAYER_STATE_OFFLINE,//玩家离线
	SESSION_PLAYER_STATE_REG,//等待场景注册
	SESSION_PLAYER_STATE_ONLINE,//玩家完成注册，进入在线状态
	SESSION_PLAYER_STATE_UNREG,//处理玩家下线注销
};

class SessionUser 
{
	public:
		WORD acctype;
		std::string account;
		QWORD charid;
		DWORD accid;
		char nickname[MAX_NAMESIZE];

		BYTE sex;
		DWORD level;
		DWORD lastOnlineTime;
		
		SessionUser(DWORD gateid,DWORD sceneid);
		~SessionUser();

		bool sendCmd(const void *pstrCmd, const int nCmdLen) const;
		bool sendCmdToScene(const void *pstrCmd, const int nCmdLen) const;
		bool reg(const CMD::SESSION::t_regUser_GateSession* cmd,bool bFirst);

		bool is_online()
		{
			return (player_state==SESSION_PLAYER_STATE_ONLINE);
		}

		bool is_unreg()
		{
			return (player_state==SESSION_PLAYER_STATE_UNREG);
		}

		bool is_offline()
		{
			return (player_state==SESSION_PLAYER_STATE_OFFLINE);
		}

		bool is_reg()
		{
			return (player_state==SESSION_PLAYER_STATE_REG);
		}


		void online(DWORD gateid);
		void update_gate(DWORD gateid)
		{
			m_gate_id = gateid;
		}

		void update_scene(DWORD sceneid)
		{
			m_scene_id = sceneid;
		}

		void scene_online(DWORD sceneid);
		bool unreg();
		void offline();

		friend class SessionUserManager;
		SessionTask* getGatewayTask() const;
		SessionTask* getSceneTask() const;
	private:
		DWORD m_gate_id;
		DWORD m_scene_id;
		
		void _online()
		{
			player_state=SESSION_PLAYER_STATE_ONLINE;
			this->sync_play_state();
		}

		void _offline()
		{
			player_state=SESSION_PLAYER_STATE_OFFLINE;
			this->sync_play_state();
		}

		void _unreg()
		{
			player_state=SESSION_PLAYER_STATE_UNREG;
			this->sync_play_state();
		}

		void _reg()
		{
			player_state=SESSION_PLAYER_STATE_REG;
			this->sync_play_state();
		}

		void sync_play_state();
		

		bool needSave;
		BYTE player_state;
		bool first_online;//是否第一次上线
};

#endif

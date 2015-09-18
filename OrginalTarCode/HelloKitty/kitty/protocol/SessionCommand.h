/**
 * \file
 * \author  ,@163.com
 * \date 2004年12月11日 14时36分43秒 CST
 * \brief 定义Session服务器相关指令
 *
 */


#ifndef _SessionCommand_h_
#define _SessionCommand_h_

#include "zNullCmd.h"
#include "Command.h"
#include "common.h"

#pragma pack(1)


namespace CMD
{
	namespace SESSION
	{
		const BYTE CMD_LOGIN = 1;
		//const BYTE CMD_GATE = 3;
		//const BYTE CMD_FORWARD = 4;
		//const BYTE CMD_SCENE = 5;
		//const BYTE CMD_SESSION = 6;

		namespace ID
		{
			enum 
			{
				session_cmd_min = 100,
				t_regUser_GateSession,   // gate    -> session reg   user
				t_unregUser_GateSession,       // gate    -> session unreg user
				t_unregUser_SessionGate,       // session -> gate    unreg user
				t_regUserSuccess_GateSession,  // session -> gate    reg   success 
				t_saveLoginLog_GateSession,  // gateway -> session  登录日志
				t_KickOutUser_SessionGate,  // 把玩家踢下线

				t_regUser_SceneSession,        // session -> scene   reg   user
				t_unregUser_SceneSession,      // scene   -> session unreg user
				t_unregUser_SessionScene,      // session -> scene   unreg user
				t_regUserSuccess_SceneSession, // scene   -> session reg   success
				t_refreshGate_SceneSession,    // session -> scene   refresh gate

				t_DelChar_GateSession,
				t_ClientPingStat_GateSession,
				t_OpenTime_GateSession,


				t_forwardUser_GateSession,//在会话上，直接给玩家发送命令,经由网关转发
				t_Session_ForwardUser,//从网关转发用户命令到会话
				t_Session_ForwardWorld,//会话广播消息到所有玩家

				session_cmd_max = 65535,
			};
		}

		//////////////////////////////////////////////////////////////
		/// 登陆Session服务器指令,会话，场景，等sessionClient使用者，连接SessionServer后，发送连接验证消息
		//////////////////////////////////////////////////////////////
		const BYTE PARA_LOGIN = 1;
		struct t_LoginSession : t_NullCmd
		{
			WORD wdServerID;
			WORD wdServerType;
			t_LoginSession()
				: t_NullCmd(CMD_LOGIN, PARA_LOGIN) {};
		};
		//////////////////////////////////////////////////////////////
		/// 登陆Session服务器指令
		//////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////
		/// 网关服务器指令
		//////////////////////////////////////////////////////////////
		struct DECLARE_CMD(t_regUser_GateSession, SESSION::ID)
		{
			DWORD accid;
			QWORD charid;
			char  name[MAX_NAMESIZE+1];
			char  flat[MAX_FLAT_LENGTH];
			char phone_uuid[100];
			BYTE byCreate; // 0正常登陆 1创建登陆
			DWORD heroid; // 选择英雄 id
			//char ip[MAX_IP_LENGTH]; // 客户端ip
			WORD acctype;//登陆类型
			char account[MAX_ACCNAMESIZE+1];
			t_regUser_GateSession()
			{
				accid = 0;
				charid = 0;
				bzero(name,sizeof(name));
				bzero(flat, sizeof(flat));
				bzero(phone_uuid,sizeof(phone_uuid));
				byCreate = 0;
				heroid = 0;
				//bzero(ip,sizeof(ip));
				acctype = 0;
				bzero(account, sizeof(account));
			};
		};

		struct DECLARE_CMD(t_unregUser_SessionGate, SESSION::ID)
		{
			QWORD charid;
			DWORD accid;
			BYTE retcode;
			t_unregUser_SessionGate()
			{};
		};

		struct DECLARE_CMD(t_unregUser_GateSession, SESSION::ID)
		{
			QWORD charid;
			DWORD accid;
			BYTE retcode;
			DWORD scene_id;
			t_unregUser_GateSession()
			{};
		};


		struct DECLARE_CMD(t_regUserSuccess_GateSession,SESSION::ID)
		{
			QWORD charid;
			DWORD accid;
			DWORD scene_id;

			t_regUserSuccess_GateSession()
			{};
		};
		///直接转发到用户的指令
		struct DECLARE_CMD(t_forwardUser_GateSession, SESSION::ID)
		{
			DWORD id;
			DWORD tempid;
			char name[MAX_NAMESIZE];
			DWORD cmd_len;
			BYTE cmd[0];
			t_forwardUser_GateSession()
			{
				id = 0;
				tempid = 0;
				bzero(name, MAX_NAMESIZE);
			}
		};


		struct DECLARE_CMD(t_DelChar_GateSession, SESSION::ID)
		{
			DWORD accid;						/// 账号
			DWORD id;							/// 角色编号
			char name[MAX_NAMESIZE+1];
			DWORD status;
			DWORD type; //0,普通删除, 1,转区删除
			t_DelChar_GateSession()
			{
				bzero(name, sizeof(name));
				accid = 0;
				id = 0;
				type = 0;
			};
		};		


		struct DECLARE_CMD(t_ClientPingStat_GateSession, SESSION::ID)
		{
			t_ClientPingStat_GateSession(DWORD dwUserID=0, BYTE non_accur=0, WORD min=0, WORD mid=0, WORD max=0 )
				:dwUserID(dwUserID), non_accur(non_accur), min(min), mid(mid), max(max)
			{
				dwUserID=non_accur=min=mid=max=0;
				bzero(ip, sizeof(ip));
			}
			DWORD dwUserID;
			BYTE non_accur;
			WORD min;
			WORD mid;
			WORD max;
			char ip[MAX_IP_LENGTH];
		};

		struct DECLARE_CMD(t_OpenTime_GateSession, SESSION::ID)
		{
			t_OpenTime_GateSession()
			{
				time = 0;
			}
			DWORD time;
		};

		struct DECLARE_CMD(t_saveLoginLog_GateSession, SESSION::ID)
		{
			t_saveLoginLog_GateSession()
			{
				bzero(flat,sizeof(flat));
				bzero(uuid,sizeof(uuid));
				bzero(ip,sizeof(ip));
				bzero(logstep,sizeof(logstep));
				accid = 0;
				charid = 0;
				type = 0;
			}

			BYTE  type; // 0注册 1登录
			char  flat[MAX_FLAT_LENGTH]; // 平台
			DWORD accid; // 账号id
			QWORD charid;
			char  uuid[MAX_NAMESIZE+1];
			char  ip[MAX_IP_LENGTH];
			char  logstep[MAX_NAMESIZE];
			char phone_uuid[100];
		};

		struct DECLARE_CMD(t_KickOutUser_SessionGate, SESSION::ID)
		{    
			t_KickOutUser_SessionGate()
			{    
				acctype = 0; 
				bzero(account,sizeof(account));
			}    

			DWORD acctype;    //用户所属平台类型
			char account[MAX_ACCNAMESIZE]; //平台账号
		};   

		//////////////////////////////////////////////////////////////
		/// 网关服务器指令结束
		//////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////
		/// 会话服务器转发指令
		//////////////////////////////////////////////////////////////
		/// 网关到Session
		struct DECLARE_CMD(t_Session_ForwardUser, SESSION::ID)
		{
			DWORD dwID;
			WORD  size;
			BYTE  data[0];
			t_Session_ForwardUser()
			{};
		};

		/// Session到全世界
		struct DECLARE_CMD(t_Session_ForwardWorld, SESSION::ID)
		{
			WORD  size;
			BYTE  worldChat;
			BYTE  data[0];
			t_Session_ForwardWorld()
			{
				worldChat = 0;
				size = 0;
			}
		};

		//////////////////////////////////////////////////////////////
		/// 会话服务器转发指令
		//////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////
		/// 场景服务器指令
		//////////////////////////////////////////////////////////////
		struct DECLARE_CMD(t_regUser_SceneSession, SESSION::ID)
		{
			DWORD accid;
			QWORD charid;
			char  name[MAX_NAMESIZE+1];
			DWORD gate_id;
			DWORD heroid;
			char  phone_uuid[100];
			DWORD reg_type; // 0玩家登陆，1gm预加载 2gm加载创建
		
			t_regUser_SceneSession()
			{
				accid = 0;
				charid = 0;
				bzero(name, sizeof(name));
				gate_id = 0;
				reg_type = 0;
				bzero(phone_uuid,sizeof(phone_uuid));
			};
		};

		const BYTE UNREGUSER_RET_LOGOUT=0;
		const BYTE UNREGUSER_RET_ERROR=1;
		struct DECLARE_CMD(t_unregUser_SceneSession, SESSION::ID)
		{
			DWORD accid;
			QWORD charid;
			BYTE retcode;
			t_unregUser_SceneSession()
			{
				accid = 0;
				charid = 0;
				retcode = 0;
			};
		};

		struct DECLARE_CMD(t_unregUser_SessionScene, SESSION::ID)
		{
			DWORD accid;
			QWORD charid;
			BYTE retcode;
			t_unregUser_SessionScene()
			{
				accid = 0;
				charid = 0;
				retcode = 0;
			};
		};

		struct DECLARE_CMD(t_regUserSuccess_SceneSession, SESSION::ID)
		{
			DWORD accid;
			QWORD charid;
			DWORD gate_id;

			 t_regUserSuccess_SceneSession()
			 {
			 	 accid = 0;
			 	 charid = 0;
			 	 gate_id = 0;
			 }
		};

	};
};
#pragma pack()
#endif


#ifndef _RecordCommand_h_
#define _RecordCommand_h_

#include "zNullCmd.h"
#include "Command.h"
#include "CharBase.h"
#include "common.h"

#pragma pack(1)

namespace CMD
{

	namespace RECORD
	{
		const BYTE CMD_LOGIN = 1;
		const BYTE CMD_GATE = 2;
		const BYTE CMD_SCENE = 3;
		const BYTE CMD_SESSION = 4;
		const BYTE CMD_SUPER = 5;

		namespace ID
		{
			enum
			{
				record_cmd_min = 100,
				t_CreateChar_GateRecord,
				t_CreateChar_Return_GateRecord,
				t_WriteUser_SceneRecord,
				t_WriteUser_SceneRecord_Ok,
				t_ChangeSceneNoSave,
				t_RemoveUserNoSave,
				t_UserInfo_SceneRecord,
				t_freshUser_SceneRecord,

				record_cmd_max = 65535, 
			};
		};

		//////////////////////////////////////////////////////////////
		/// 登陆档案服务器指令
		//////////////////////////////////////////////////////////////
		const BYTE PARA_LOGIN = 1;
		struct t_LoginRecord : t_NullCmd
		{
			WORD wdServerID;
			WORD wdServerType;
			t_LoginRecord()
				: t_NullCmd(CMD_LOGIN, PARA_LOGIN) {};
		};
		//////////////////////////////////////////////////////////////
		/// 登陆档案服务器指令
		//////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////
		/// 档案服务器和网关交互的指令
		//////////////////////////////////////////////////////////////
		const BYTE PARA_GATE_CREATECHAR  = 23;
		struct t_CreateChar_GateRecord : public t_NullCmd
		{
			DWORD accid;
			char  name[MAX_NAMESIZE];		/// 角色名称
			DWORD createip;				/// 创建角色时的ip
			char  password[MAX_PASSWORD];
			BYTE  bySex;  // 性别 0未定义 1男 2女
			DWORD flatid; // 平台id
			char  phone_uuid[100]; // 设备uuid
			WORD  type;//帐号登陆
			char  account[MAX_ACCNAMESIZE];//数字帐号
			t_CreateChar_GateRecord() : t_NullCmd(CMD_GATE, PARA_GATE_CREATECHAR)
			{
				bzero(name, sizeof(name));
				bzero(password, sizeof(password));
				createip = 0;
				accid = 0;
				bySex = 0;
				flatid = 0;
				bzero(phone_uuid,sizeof(phone_uuid));
				type = 0;
				bzero(account, sizeof(account));
			};
		};

		const BYTE PARA_GATE_CREATECHAR_RETURN = 24;
		struct t_CreateChar_Return_GateRecord : public t_NullCmd
		{
			DWORD accid;						/// 账号
			QWORD charid;
			WORD acctype;	                  //平台类型
			char account[MAX_ACCNAMESIZE+1];  //玩家账号
			BYTE retcode;						/// 返回代码，0成功 1失败 2账号已有角色 3角色名称重复

			t_CreateChar_Return_GateRecord() : t_NullCmd(CMD_GATE, PARA_GATE_CREATECHAR_RETURN)
			{
				accid = 0;
				charid = 0;
				acctype = 0;
				bzero(account, sizeof(account));
				retcode = 0;
			};
		};		

		//////////////////////////////////////////////////////////////
		/// 档案服务器和网关交互的指令
		//////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////
		/// 档案服务器和场景交互的指令
		//////////////////////////////////////////////////////////////

		const BYTE PARA_SCENE_FRESHUSER = 23; 
		struct t_freshUser_SceneRecord : t_NullCmd
		{   
			QWORD charid;
			DWORD accid;
			DWORD scene_id;

			t_freshUser_SceneRecord()
				: t_NullCmd(CMD_SCENE, PARA_SCENE_FRESHUSER)
			{}; 
		};

		// 克隆角色，向数据库插入记录
		const BYTE PARA_CLONE_USER_WRITE = 24; 
		struct t_Clone_WriteUser_SceneRecord : t_NullCmd
		{   
			DWORD accid;
			QWORD charid;/// 角色
			char prefix[MAX_NAMESIZE];
			DWORD start_index;
			DWORD finish_index;
			CharBase    charbase;               /// 存档的基本信息
			DWORD      dataSize;                ///存档二进制的大小
			char        data[0];                ///存档的二进制数据
			t_Clone_WriteUser_SceneRecord() : t_NullCmd(CMD_SCENE, PARA_CLONE_USER_WRITE)
			{   
				bzero(&charbase , sizeof(charbase));
				dataSize = 0;
				accid = 0;
				charid = 0;
				bzero(prefix,MAX_NAMESIZE);
				start_index = 0;
				finish_index = 0;
			}
			DWORD getSize() {return sizeof(*this) + dataSize;}
		};

		// 保存角色数据
		const BYTE PARA_SCENE_USER_WRITE = 25;
		struct t_WriteUser_SceneRecord : t_NullCmd
		{
			QWORD charid;
			DWORD dwMapTempID;					/// 地图临时ID
			CharBase    charbase;				/// 存档的基本信息
			DWORD      dataSize;				///存档二进制的大小
			char        data[0];				///存档的二进制数据
			t_WriteUser_SceneRecord() : t_NullCmd(CMD_SCENE, PARA_SCENE_USER_WRITE)
			{
				charid = 0;
				dwMapTempID = 0;
				bzero(&charbase , sizeof(charbase));
				dataSize = 0;
			}
		};

	
#ifdef _TEST_DATA_LOG
		enum enumWriteBackTest_Type
		{
			NEWCHAR_WRITEBACK,//新角色插入
			LEVELUP_WRITEBACK,//升级
			DEATH_WRITEBACK,//死亡
			HP_WRITEBACK,//HP
			MP_WRITEBACK,//MP
			SP_WRITEBACK,//SP
		};
		const BYTE PARA_SCENE_INSERT_CHARTEST = 4;
		struct t_Insert_CharTest_SceneRecord : t_NullCmd
		{
			char name[MAX_NAMESIZE];				/// 角色名称
			DWORD level;							/// 角色等级
			CharTest    chartest;				///存档数据
			t_Insert_CharTest_SceneRecord()
				: t_NullCmd(CMD_SCENE, PARA_SCENE_INSERT_CHARTEST)
				{
					bzero(&chartest , sizeof(chartest));
					bzero(name, sizeof(name));
				}
		};
		const BYTE PARA_SCENE_UPDATE_CHARTEST = 5;
		struct t_Update_CharTest_SceneRecord : t_NullCmd
		{
			char name[MAX_NAMESIZE];				/// 角色名称
			DWORD level;							/// 角色等级
			CharTest    chartest;				///存档数据
			t_Update_CharTest_SceneRecord()
				: t_NullCmd(CMD_SCENE, PARA_SCENE_UPDATE_CHARTEST)
				{
					bzero(&chartest , sizeof(chartest));
					bzero(name, sizeof(name));
				}
		};
		const BYTE PARA_SCENE_DELETE_CHARTEST = 6;
		struct t_Delete_CharTest_SceneRecord : t_NullCmd
		{
			char name[MAX_NAMESIZE];				/// 角色名称
			DWORD level;							/// 角色等级
			t_Delete_CharTest_SceneRecord()
				: t_NullCmd(CMD_SCENE, PARA_SCENE_DELETE_CHARTEST)
				{
					bzero(name, sizeof(name));
				}
		};
		const BYTE PARA_SCENE_READ_CHARTEST = 7;
		struct t_Read_CharTest_SceneRecord : t_NullCmd
		{
			char name[MAX_NAMESIZE];				/// 角色名称
			DWORD level;							/// 角色等级
			CharTest    chartest;				///存档数据
			t_Read_CharTest_SceneRecord()
				: t_NullCmd(CMD_SCENE, PARA_SCENE_READ_CHARTEST)
				{
					bzero(&chartest , sizeof(chartest));
					bzero(name, sizeof(name));
				}
		};
#endif

		//////////////////////////////////////////////////////////////
		/// 档案服务器和场景交互的指令
		//////////////////////////////////////////////////////////////
		
		//////////////////////////////////////////////////////////////
		/// 档案服务器和Super服务器交互的指令开始
		//////////////////////////////////////////////////////////////


	};

};

#pragma pack()

#endif


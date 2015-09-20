#ifndef _AllZoneCommand_h
#define _AllZoneCommand_h

#include "zType.h"
#include "zNullCmd.h"
#include "common.h"
#include "messageType.h"

#pragma pack(1)
namespace CMD
{
	namespace ALLZONE 
	{
#if 0
		const BYTE CMD_LOGIN = 1;//登陆服务器指令
		
		namespace ID
        {
            enum
            {
                allzone_cmd_min = 1000,

				// 大区指令
				t_Super2AllZone_SaleCells = 1001,   
				t_Super2AllZone_ReqSomePlayerSaleCells = 1002,			
				t_AllZone2Super_RetSomePlayerSaleCells = 1003,
				t_AllZone2Super_Forward2Scene = 1004,
                allzone_cmd_max = 65535,
            };
        }
#endif   
        struct AllZoneNull : t_NullCmd
        {
            AllZoneNull()
            {
                cmd = ZONECMD;
            }
        };

		///////////////////////////////////////
		///登入服务器指令
		//////////////////////////////////////
		const BYTE PARA_LOGIN = 1;
		struct t_LoginAllZone : AllZoneNull 
		{
			GameZone_t zoneID;
			t_LoginAllZone() 
			{
                para = PARA_LOGIN;
			}
		};

		const BYTE PARA_LOGIN_OK = 2;
		struct t_LoginCmd_OK : AllZoneNull 
		{
			t_LoginCmd_OK()
            {
                para = PARA_LOGIN_OK;
            }
		};
        
        //zone发送给scene的消息,经super流转
        const BYTE PARA_ALL_ZONE_SUPER_FORWARD_SCENE = 3;
        struct t_AllZone2Super_Forward2Scene : AllZoneNull
        {   
            DWORD sceneid;
            DWORD datasize;
            char data[0];
            t_AllZone2Super_Forward2Scene()
            {
                para = PARA_ALL_ZONE_SUPER_FORWARD_SCENE;
                sceneid = 0;
                datasize = 0;
            };
            DWORD getSize()
            {
                return (sizeof(*this) + datasize);
            }
        };

#if 0
		// 玩家销售道具
		struct DECLARE_CMD(t_Super2AllZone_SaleCells, ALLZONE::ID)
        {
            t_Super2AllZone_SaleCells()
            {
				charid = 0;
				count = 0;
			};
			QWORD charid;
			DWORD count;
			stSaleCell data[0];
			DWORD getSize() const { return sizeof(*this) + count * sizeof(stSaleCell); }
		};

		// 请求一批其他玩家的销售道具格子信息
		struct DECLARE_CMD(t_Super2AllZone_ReqSomePlayerSaleCells, ALLZONE::ID)
        {
            t_Super2AllZone_ReqSomePlayerSaleCells()
            {
                sceneid = 0;
				charid = 0;
            };
			DWORD sceneid;
			QWORD charid;
        };
	
		struct DECLARE_CMD(t_AllZone2Super_RetSomePlayerSaleCells, ALLZONE::ID)
        {
            t_AllZone2Super_RetSomePlayerSaleCells()
            {
                charid = 0;
				datasize = 0;
            };
            QWORD charid;
			DWORD datasize;
			char data[0];   //结构参考MsgAllRoleCell
			DWORD getSize()
            {
                return (sizeof(*this) + datasize);
            }
        };
			
		struct DECLARE_CMD(t_AllZone2Super_Forward2Scene, ALLZONE::ID)
        {
            t_AllZone2Super_Forward2Scene()
            {
                sceneid = 0;
                datasize = 0;
            };
            DWORD sceneid;
            DWORD datasize;
            char data[0];
            DWORD getSize()
            {
                return (sizeof(*this) + datasize);
            }
        };
#endif
	};
};
#pragma pack()

#endif

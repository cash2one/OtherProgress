#ifndef _SuperCommand_h_
#define _SuperCommand_h_

#include "zType.h"
#include "zNullCmd.h"
#include "FLCommand.h"
#include <string.h>

#pragma pack(1)

namespace CMD
{

	namespace SUPER
	{
		const BYTE CMD_STARTUP	= 1;
		const BYTE CMD_GATEWAY	= 4;
		const BYTE CMD_SESSION	= 5;
		const BYTE CMD_RECORD	= 6;
		const BYTE CMD_SCENE	= 7;

		//////////////////////////////////////////////////////////////
		// 定义启动相关指令
		//////////////////////////////////////////////////////////////
		const BYTE PARA_STARTUP_REQUEST = 1;
		struct t_Startup_Request : t_NullCmd
		{
			WORD wdServerType;
			char pstrIP[MAX_IP_LENGTH];
			t_Startup_Request()
				: t_NullCmd(CMD_STARTUP, PARA_STARTUP_REQUEST) 
			{
				bzero(pstrIP, sizeof(pstrIP));
			};
		};

		const BYTE PARA_STARTUP_RESPONSE = 2;
		struct t_Startup_Response : t_NullCmd
		{
			WORD wdServerID;
			WORD wdPort;
			char pstrExtIP[MAX_IP_LENGTH];
			WORD wdExtPort;
			WORD wdNetType; // 服务器，所以在网络，0电信，1网通 
			t_Startup_Response()
				: t_NullCmd(CMD_STARTUP, PARA_STARTUP_RESPONSE) 
			{
				bzero(pstrExtIP, sizeof(pstrExtIP));
				wdServerID = 0;
				wdPort = 0;
				wdExtPort = 0;
				wdNetType = 0;
			};
		};

		struct ServerEntry
		{
			WORD wdServerID;
			WORD wdServerType;
			char pstrName[MAX_NAMESIZE];
			char pstrIP[MAX_IP_LENGTH];
			WORD wdPort;
			char pstrExtIP[MAX_IP_LENGTH];
			WORD wdExtPort;
			WORD state;
			ServerEntry()
			{
				wdServerID = 0;
				wdServerType = 0;
				bzero(pstrName, sizeof(pstrName));
				bzero(pstrIP, sizeof(pstrIP));
				wdPort = 0;
				bzero(pstrExtIP, sizeof(pstrExtIP));
				wdExtPort = 0;
				state = 0;
			}
			ServerEntry(const ServerEntry& se)
			{
				wdServerID = se.wdServerID;
				wdServerType = se.wdServerType;
				bcopy(se.pstrName, pstrName, sizeof(pstrName));
				bcopy(se.pstrIP, pstrIP, sizeof(pstrIP));
				wdPort = se.wdPort;
				bcopy(se.pstrExtIP, pstrExtIP, sizeof(pstrExtIP));
				wdExtPort = se.wdExtPort;
				state = se.state;
			}
			ServerEntry & operator= (const ServerEntry &se)
			{
				wdServerID = se.wdServerID;
				wdServerType = se.wdServerType;
				bcopy(se.pstrName, pstrName, sizeof(pstrName));
				bcopy(se.pstrIP, pstrIP, sizeof(pstrIP));
				wdPort = se.wdPort;
				bcopy(se.pstrExtIP, pstrExtIP, sizeof(pstrExtIP));
				wdExtPort = se.wdExtPort;
				state = se.state;
				return *this;
			}
		};
		const BYTE PARA_STARTUP_SERVERENTRY_NOTIFYME = 3;
		struct t_Startup_ServerEntry_NotifyMe : t_NullCmd
		{
			WORD size;
			ServerEntry entry[0];
			t_Startup_ServerEntry_NotifyMe()
				: t_NullCmd(CMD_STARTUP, PARA_STARTUP_SERVERENTRY_NOTIFYME), size(0) {};
		};
		const BYTE PARA_STARTUP_SERVERENTRY_NOTIFYOTHER = 4;
		struct t_Startup_ServerEntry_NotifyOther : t_NullCmd
		{
			WORD srcID;
			ServerEntry entry;
			t_Startup_ServerEntry_NotifyOther()
				: t_NullCmd(CMD_STARTUP, PARA_STARTUP_SERVERENTRY_NOTIFYOTHER) {};
		};

		const BYTE PARA_STARTUP_OK = 5;
		struct t_Startup_OK : t_NullCmd
		{
			WORD wdServerID;
			t_Startup_OK()
				: t_NullCmd(CMD_STARTUP, PARA_STARTUP_OK) {};
		};

		const BYTE PARA_GAMETIME = 6;
		struct t_GameTime : t_NullCmd
		{
			QWORD qwGameTime;
			QWORD qwStartTime;
			t_GameTime()
				: t_NullCmd(CMD_STARTUP, PARA_GAMETIME) {};
		};

		const BYTE PARA_RESTART_SERVERENTRY_NOTIFYOTHER = 9;
		struct t_restart_ServerEntry_NotifyOther : t_NullCmd
		{
			WORD srcID;
			WORD dstID;
			t_restart_ServerEntry_NotifyOther()
				: t_NullCmd(CMD_STARTUP, PARA_RESTART_SERVERENTRY_NOTIFYOTHER) {};
		};
		//////////////////////////////////////////////////////////////
		// 定义启动相关指令
		//////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////
		// 定义服务器管理器与网关服务器交互的指令
		//////////////////////////////////////////////////////////////
		const BYTE PARA_GATEWAY_GYLIST = 1;
		struct t_GYList_Gateway : t_NullCmd
		{
			WORD wdServerID;			/**< 服务器编号 */
			BYTE pstrIP[MAX_IP_LENGTH];	/**< 服务器地址 */
			WORD wdPort;				/**< 服务器端口 */
			WORD wdNumOnline;			/**< 网关在线人数 */
			int  state;					/**< 服务器状态 */
			DWORD zoneGameVersion;
			WORD wdNetType;				/**< 网关网络类型:0电信，1网通 */
			t_GYList_Gateway()
				: t_NullCmd(CMD_GATEWAY, PARA_GATEWAY_GYLIST) {};
		};

		const BYTE PARA_GATEWAY_RQGYLIST = 2;
		struct t_RQGYList_Gateway : t_NullCmd
		{
			t_RQGYList_Gateway()
				: t_NullCmd(CMD_GATEWAY, PARA_GATEWAY_RQGYLIST) {};
		};

		// 设置区ID
		const BYTE PARA_ZONE_ID_GATE = 12;
		struct t_ZoneID_Gate : t_NullCmd
		{
			GameZone_t zone;
			t_ZoneID_Gate(): t_NullCmd(CMD_GATEWAY, PARA_ZONE_ID_GATE)
			{
			}
		};
		
		// Super -> Gateway
		const BYTE PARA_GATE_RECONNECT_SCENE = 17;
		struct t_GateReconnectScene :t_NullCmd
		{
			ServerEntry entry;
			t_GateReconnectScene()
				:t_NullCmd(CMD_GATEWAY, PARA_GATE_RECONNECT_SCENE){}

		};

		// Super->Gateway 通知网关结束掉某个ip和端口的连接
		const BYTE PARA_GATE_TERMINATE_CONNECT = 18;
		struct t_GateTerminateConnect :t_NullCmd
		{
			char pstrIP[MAX_IP_LENGTH];
			WORD port;
			t_GateTerminateConnect()
				:t_NullCmd(CMD_GATEWAY, PARA_GATE_TERMINATE_CONNECT)
			{
				bzero(pstrIP,sizeof(pstrIP));
				port = 0;
			}
		};

		const BYTE PARA_SUPER2GATE_KICK_OUT_USER  = 25;
                struct t_Super2GateKickOutUser : t_NullCmd
                {
                        t_Super2GateKickOutUser() : t_NullCmd(CMD_GATEWAY,PARA_SUPER2GATE_KICK_OUT_USER)
                        {
                                acctype = 0;
                                bzero(account,sizeof(account));
                        }

                        DWORD acctype;    //用户所属平台类型
                        char account[MAX_ACCNAMESIZE]; //平台账号
                };
		
		//////////////////////////////////////////////////////////////
		// 定义服务器管理器与会话服务器交互的指令
		//////////////////////////////////////////////////////////////

		// 设置区ID
		const BYTE PARA_ZONE_ID_SESSION = 5;
		struct t_ZoneID_Session : t_NullCmd
		{
			GameZone_t zone;
			char name[MAX_NAMESIZE];
			t_ZoneID_Session(): t_NullCmd(CMD_SESSION, PARA_ZONE_ID_SESSION)
			{
				bzero(name,sizeof(name));
			}
		};


		//////////////////////////////////////////////////////////////
		// 定义服务器管理器与场景服务器交互的指令
		//////////////////////////////////////////////////////////////

		// 设置区ID
		const BYTE PARA_ZONE_ID_SCENE = 1;
		struct t_ZoneID_Scene : t_NullCmd
		{
			GameZone_t zone;
			t_ZoneID_Scene(): t_NullCmd(CMD_SCENE, PARA_ZONE_ID_SCENE)
			{
			}
		};
		
		// 来自场景转发给AllZone的消息
		const BYTE PARA_FORWARD_ALLZONE_FROM_SCENE = 2;
		struct t_ForwardAllZoneFromScene : t_NullCmd
                {
                       	t_ForwardAllZoneFromScene(): t_NullCmd(CMD_SCENE, PARA_FORWARD_ALLZONE_FROM_SCENE)
                        {
				size = 0;
                        }
			DWORD size;
                        char data[0];
                        DWORD getSize() const { return sizeof(*this) + size; }
                };
		
		const BYTE PARA_FORWARD_SCENE_FROM_ALLZONE = 3;
                struct t_ForwardSceneFromAllZone : t_NullCmd
                {
                        t_ForwardSceneFromAllZone(): t_NullCmd(CMD_SCENE, PARA_FORWARD_SCENE_FROM_ALLZONE)
                        {
                                datasize = 0;
                        }
                        DWORD datasize;
                        char data[0];
                        DWORD getSize() const { return sizeof(*this) + datasize; }
                };

		//////////////////////////////////////////////////////////////
		// 定义服务器管理器与Record服务器交互的指令
		//////////////////////////////////////////////////////////////
		const BYTE PARA_ZONE_ID_RECORD = 3;
                struct t_ZoneID_Record : t_NullCmd
                {
                        GameZone_t zone;
                        t_ZoneID_Record(): t_NullCmd(CMD_RECORD, PARA_ZONE_ID_RECORD)
                        {
                        }
                };
		
	};

};

#pragma pack()

#endif


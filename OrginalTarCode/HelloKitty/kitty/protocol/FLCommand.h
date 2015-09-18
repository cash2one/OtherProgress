#ifndef _FLCommand_h_
#define _FLCommand_h_

#include "zType.h"
#include "zNullCmd.h"
#include "EncDec.h"

#pragma pack(1)

struct t_NewLoginSession
{
	DWORD loginTempID;

	WORD wdGatewayID;
	char pstrIP[MAX_IP_LENGTH];
	WORD wdPort;

	GameZone_t gameZone;

	char passwd[MAX_PASSWORD];

	DES_cblock des_key;//des密钥

	char client_ip[MAX_IP_LENGTH];
	WORD wdNetType;             /**< 网关网络类型，0电信，1网通 */

	DWORD acctype;    //用户所属平台类型
	char account[MAX_ACCNAMESIZE]; //平台账号

	DWORD login_ret; // 登录结果 0正常 1把同账号踢下线
	
	t_NewLoginSession()
	{
		bzero(this,sizeof(*this));
	}

	t_NewLoginSession(const t_NewLoginSession& session)
	{   
		*this = session;
	}   
	t_NewLoginSession & operator= (const t_NewLoginSession &session)
	{   
		loginTempID = session.loginTempID;

		wdGatewayID = session.wdGatewayID;
		bcopy(session.pstrIP, pstrIP, sizeof(pstrIP));
		wdPort = session.wdPort;

		gameZone = session.gameZone;

		bcopy(session.passwd, passwd, sizeof(passwd));

		bcopy(session.des_key, des_key, sizeof(des_key));

		bcopy(session.client_ip, client_ip, sizeof(client_ip));
		wdNetType = session.wdNetType;

		acctype = session.acctype;
		bcopy(session.account, account, sizeof(account));

		login_ret = 0;

		return *this;
	} 
};

namespace CMD
{
	namespace FL
	{
		const BYTE CMD_LOGIN = 1;
		const BYTE CMD_GYLIST = 2;
		const BYTE CMD_SESSION = 3;


		//////////////////////////////////////////////////////////////
		/// 登陆FL服务器指令
		//////////////////////////////////////////////////////////////
		const BYTE PARA_LOGIN = 1;
		struct t_LoginFL : t_NullCmd
		{
			char strIP[MAX_IP_LENGTH];
			unsigned short port;

			t_LoginFL()
				: t_NullCmd(CMD_LOGIN, PARA_LOGIN) {};
		};

		const BYTE PARA_LOGIN_OK = 2;
		struct t_LoginFL_OK : t_NullCmd
		{
			GameZone_t gameZone;
			char name[MAX_NAMESIZE];
			BYTE netType;

			t_LoginFL_OK()
				: t_NullCmd(CMD_LOGIN, PARA_LOGIN_OK) 
			{
				bzero(name, sizeof(name));
                netType = 0;
			};
		};
		//////////////////////////////////////////////////////////////
		/// 登陆FL服务器指令
		//////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////
		/// 定义网关信息相关指令
		//////////////////////////////////////////////////////////////
		const BYTE PARA_FL_GYLIST = 1;
		struct t_GYList_FL : t_NullCmd
		{
			WORD wdServerID;			/**< 服务器编号 */
			BYTE pstrIP[MAX_IP_LENGTH];	/**< 服务器地址 */
			WORD wdPort;				/**< 服务器端口 */
			WORD wdNumOnline;			/**< 网关在线人数 */
			int  state;					/**< 服务器状态 */
			DWORD zoneGameVersion;
			WORD wdNetType;				/**< 网关网络类型，0电信，1网通 */
			t_GYList_FL()
				: t_NullCmd(CMD_GYLIST, PARA_FL_GYLIST) {};
		};

		const BYTE PARA_FL_RQGYLIST = 2;
		struct t_RQGYList_FL : t_NullCmd
		{
			t_RQGYList_FL()
				: t_NullCmd(CMD_GYLIST, PARA_FL_RQGYLIST) {};
		};
		//////////////////////////////////////////////////////////////
		/// 定义网关信息相关指令
		//////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////
		/// 定义与登陆session相关指令
		//////////////////////////////////////////////////////////////
		const BYTE PARA_SESSION_NEWSESSION = 1;
		struct t_NewSession_Session : t_NullCmd
		{
			t_NewLoginSession session;

			t_NewSession_Session()
				: t_NullCmd(CMD_SESSION, PARA_SESSION_NEWSESSION) {};
		};

		const BYTE PARA_SESSION_IDINUSE = 2;
		struct t_idinuse_Session : t_NullCmd
		{
			DWORD loginTempID;

			t_idinuse_Session()
				: t_NullCmd(CMD_SESSION, PARA_SESSION_IDINUSE) 
			{
				loginTempID = 0;
			};
		};

		// 大区注册人数
		const BYTE PARA_SESSION_REG_ROLE_COUNT = 3;
                struct t_RegRoleCount_Session : t_NullCmd
                {
                        t_RegRoleCount_Session()
                                : t_NullCmd(CMD_SESSION,PARA_SESSION_REG_ROLE_COUNT)
                        {
                                role_count = 0;
                        }
                        DWORD role_count;
                };

		//////////////////////////////////////////////////////////////
		/// 定义与登陆session相关指令
		//////////////////////////////////////////////////////////////
	};
};


#pragma pack()

#endif


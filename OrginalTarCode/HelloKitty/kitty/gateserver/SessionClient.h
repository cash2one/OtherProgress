/**
 * \file
 * \version  $Id: SessionClient.h 37 2013-04-08 01:52:56Z  $
 * \author  ,@163.com
 * \date 2004年11月05日 13时58分55秒 CST
 * \brief 定义Session服务器连接客户端
 *
 */

#ifndef _SessionClient_h_
#define _SessionClient_h_

#include <unistd.h>
#include <iostream>

#include "zTCPClient.h"
#include "SessionCommand.h"
#include "CmdAnalysis.h"
#include "dispatcher.h"

class SessionClient;

typedef Dispatcher<SessionClient> SessionUserLoginCmdDispatcher;
/**
 * \brief 定义Session服务器连接客户端类
 *
 */
class SessionClient : public zTCPBufferClient
{

	public:
		static std::map<DWORD, QWORD> cmdCount;
		static std::map<DWORD, QWORD> forwardCount;
		static BYTE cmdCountSwitch;
		static CmdAnalysis analysisSession;
		static CmdAnalysis analysisForward;
		static SessionUserLoginCmdDispatcher user_login_dispatcher;

		SessionClient(
				const std::string &name, 
				const std::string &ip, 
				const unsigned short port)
			: zTCPBufferClient(name, ip, port,false, 25000) 
		{
			last_para = 0;
			last_cmd = 0;
			last_cmd_len = 0;

			last_user_cmd = 0;
			last_user_para = 0;
			last_user_cmd_len = 0;
		};

		bool connectToSessionServer();
		void run();
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
		bool msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen);

		DWORD last_para;
		DWORD last_cmd;
		DWORD last_cmd_len;

		DWORD last_user_cmd;
		DWORD last_user_para;
		DWORD last_user_cmd_len;
};

extern SessionClient *sessionClient;

#endif


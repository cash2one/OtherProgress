/**
 * \file
 * \version  $Id: SessionClient.h 37 2013-04-08 01:52:56Z  $
 * \author  , 
 * \date 2013年04月05日 13时58分55秒 CST
 * \brief 定义Session服务器连接客户端
 *
 */

#ifndef _SessionClient_h_
#define _SessionClient_h_

#include <unistd.h>
#include <iostream>

#include "zTCPClient.h"
#include "SessionCommand.h"
#include "zMisc.h"
#include "zSocket.h"
#include "MessageQueue.h"
#include "CmdAnalysis.h"
#include "dispatcher.h"

class SceneUser;

class SessionClient;

typedef Dispatcher<SessionClient> UserLoginCmdDispatcher;

#define SESSIONCLIENT_DISPATCHER_REG(cmd, fun)\
SessionClient::session_client_dispatcher.func_reg<cmd>(CmdCallback<SessionClient, const cmd>::Function(this, &fun));

class SessionClient : public zTCPBufferClient , public MessageQueue
{

	public:
		static std::map<DWORD, DWORD> tmEffectMap;	//各国太庙效果
		static std::map<DWORD, DWORD> userSortMap;	//各国名次排行榜数据
		static CmdAnalysis analysis;
		static std::map<DWORD, QWORD> cmdCount;
		static BYTE cmdCountSwitch;
		static std::map<DWORD, DWORD> townStarMap;      //每个城的星数,

		static UserLoginCmdDispatcher user_login_dispatcher;
		static UserLoginCmdDispatcher session_client_dispatcher;
		

		/**
		* \brief 构造函数
		* \param  name 名称
		* \param  ip   地址
		* \param  port 端口
		*/
		SessionClient(
				const std::string &name, 
				const std::string &ip, 
				const unsigned short port)
			: zTCPBufferClient(name, ip, port) {};

		bool connectToSessionServer();
		void run();
        bool msgParse(const BYTE *data, const DWORD nCmdLen);
        bool msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen);
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
		bool cmdMsgParse(const BYTE *data, const DWORD nCmdLen);
};

/// 声明
extern SessionClient *sessionClient;

#endif


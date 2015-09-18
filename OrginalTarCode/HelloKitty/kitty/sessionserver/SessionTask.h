/**
 * \file
 * \version  $Id: SessionTask.h 75 2013-04-25 05:10:39Z  $
 * \author  ,
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 定义会话连接任务
 *
 */

#ifndef _SESSIONTASK_H_
#define _SESSIONTASK_H_

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "zMisc.h"
#include "SessionCommand.h"
#include "MessageQueue.h"
#include "dispatcher.h"


class SessionTask;
class SessionUser;

typedef Dispatcher<SessionTask> TaskCmdDispatcher;
typedef Dispatcher<SessionUser> UserCmdDispatcher;

#define USER_DISPATCHER_REG(cmd, fun)\
SessionTask::user_dispatcher.func_reg<cmd>(CmdCallback<SessionUser, const cmd>::Function(this, &fun));

#define SCENE_DISPATCHER_REG(cmd, fun)\
SessionTask::scene_cmd_dispatcher.func_reg<cmd>(CmdCallback<SessionTask, const cmd>::Function(this, &fun));
/**
 * \brief 定义计费连接任务类
 *
 */
class SessionTask : public zTCPTask , public MessageQueue
{

	public:

		/**
		 * \brief 构造函数
		 *
		 * \param pool 所属连接池指针
		 * \param sock TCP/IP套接口
		 * \param addr 地址
		 */
		SessionTask(
				zTCPTaskPool *pool,
				const int sock,
				const struct sockaddr_in *addr = NULL) : zTCPTask(pool, sock, addr)
		{
			wdServerID = 0;
			wdServerType = UNKNOWNSERVER;
			recycle_state=0;
			veriry_ok=false; 
			total_all = 0;
			total_online = 0;
		}

		/**
		 * \brief 虚析构函数
		 *
		 */
		~SessionTask() {};

		int verifyConn();
		int recycleConn();
		void addToContainer();
		void removeFromContainer();
		bool uniqueAdd();
		bool uniqueRemove();
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
        bool msgParse(const BYTE *data, const DWORD nCmdLen);
        bool cmdMsgParse(const BYTE *data, const DWORD nCmdLen);
		bool msgParseStruct(const CMD::t_NullCmd *, const DWORD);
		bool checkRecycle();

		static TaskCmdDispatcher gate_cmd_dispatcher;
		static TaskCmdDispatcher scene_cmd_dispatcher;

		/**
		 * \brief 获取服务器编号
		 *
		 * \return 服务器编号
		 */
		const WORD getID() const
		{
			return wdServerID;
		}

		/**
		 * \brief 获取服务器类型
		 *
		 * \return 服务器类型
		 */
		const WORD getType() const
		{
			return wdServerType;
		}

		
		//SessionUser类，另有发送函数
		bool sendCmdToUser(DWORD id, const void *pstrCmd, const unsigned int nCmdLen);
		
		//活跃玩家总数
		DWORD total_online;
		//分配玩家总数
		DWORD total_all;

		//解析网关过来的用户消息
		bool gate_user_cmdparse(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen);

		static UserCmdDispatcher user_dispatcher;

	private:

		/**
		 * \brief 容器访问互斥变量
		 *
		 */
		zMutex mlock;
				
		WORD wdServerID;					/**< 服务器编号，一个区唯一的 */
		WORD wdServerType;					/**< 服务器类型 */

	    bool verifyLogin(const CMD::SESSION::t_LoginSession *ptCmd);
		int recycle_state;
		bool veriry_ok;

		bool addDBMoney(DWORD userID, DWORD num);
		void change_name(DWORD userid, char *name);
};

#endif


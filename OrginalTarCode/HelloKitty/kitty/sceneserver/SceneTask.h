/**
 * \file
 * \version  $Id: SceneTask.h 51 2013-04-16 00:37:19Z  $
 * \author  ,
 * \date 2013年04月07日 15时20分01秒 CST
 * \brief 定义场景连接任务
 *
 */

#ifndef _SCENETASK_H_
#define _SCENETASK_H_

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "zMisc.h"
#include "SceneCommand.h"
#include "MessageQueue.h"
#include "dispatcher.h"


class SceneUser;
#define USER_DISPATCHER_REG(cmd, fun)\
SceneTask::scene_user_dispatcher.func_reg<cmd>(CmdCallback<SceneUser, const cmd>::Function(this, &fun));
typedef Dispatcher<SceneUser> SceneUserCmdDispatcher;

/**
 * \brief 定义计费连接任务类
 *
 */
class SceneTask : public zTCPTask , public MessageQueue
{

	public:

		/**
		 * \brief 构造函数
		 *
		 * \param pool 所属连接池指针
		 * \param sock TCP/IP套接口
		 * \param addr 地址
		 */
		SceneTask(
				zTCPTaskPool *pool,
				const int sock,
				const struct sockaddr_in *addr = NULL) : zTCPTask(pool, sock, addr)
		{
			wdServerID = 0;
			wdServerType = UNKNOWNSERVER;
			recycle_state=0;
			veriry_ok=false; 
		}

		/**
		 * \brief 虚析构函数
		 *
		 */
		~SceneTask() {};

		int verifyConn();
		int recycleConn();
		bool uniqueAdd();
		bool uniqueRemove();
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
		bool msgParse(const BYTE *data, const DWORD nCmdLen);
		bool cmdMsgParse(const BYTE *data, const DWORD nCmdLen); 
        bool msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen);
		bool parseGateMsg(const CMD::t_NullCmd *, const unsigned int);
		bool parseForwardMsg(const CMD::t_NullCmd *, const unsigned int);
		bool parseSessionMsg(const CMD::t_NullCmd * cmd, const unsigned int len);
		bool user_cmdparse(const CMD::t_NullCmd* cmd, const unsigned int len);
		bool checkRecycle();

		bool sendCmdToUser(DWORD id, const void *pstrCmd, const unsigned int nCmdLen);

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

		void addToContainer();
    
    public:
		static SceneUserCmdDispatcher scene_user_dispatcher;

    private:

		/**
		 * \brief 容器访问互斥变量
		 *
		 */
		zMutex mlock;
				
		WORD wdServerID;					/**< 服务器编号，一个区唯一的 */
		WORD wdServerType;					/**< 服务器类型 */

		bool verifyLogin(const CMD::SCENE::t_LoginScene *ptCmd);
		int recycle_state;
		bool veriry_ok;
};

#endif


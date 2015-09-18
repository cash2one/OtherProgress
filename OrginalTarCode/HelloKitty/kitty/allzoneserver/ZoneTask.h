/**
 * \file
 * \version  $Id: ZoneTask.h 35 2013-04-07 07:18:55Z  $
 * \author  ,@163.com
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 定义服务器连接任务
 *
 * 一个区中的每一个服务器都需要和服务器管理器建立连接
 * 
 */

#ifndef _ZoneTask_h_
#define _ZoneTask_h_

#include <unordered_map>

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "zMisc.h"
#include "zTime.h"
#include "SuperCommand.h"
#include "MessageQueue.h"

/**
 * \brief 服务器连接任务
 *
 * 一个区中的每一个服务器都需要和服务器管理器建立连接
 * 
 */
class ZoneTask : public zTCPTask , public MessageQueue
{

	public:

		/**
		 * \brief 构造函数
		 *
		 * 用于创建一个服务器连接任务
		 *
		 * \param pool 所属连接池指针
		 * \param sock TCP/IP套接口
		 * \param addr 地址
		 */
		ZoneTask(
				zTCPTaskPool *pool,
				const int sock,
				const struct sockaddr_in *addr = NULL) : zTCPTask(pool, sock, addr)
		{
			_zone_id = 0;
		}

		/**
		 * \brief 虚析构函数
		 *
		 */
		virtual ~ZoneTask() {};

		int verifyConn();
		int waitSync();
		int recycleConn();
		void addToContainer();
		void removeFromContainer();
		bool uniqueAdd();
		bool uniqueRemove();
        bool msgParse(const BYTE *data, const DWORD nCmdLen);
        bool cmdMsgParse(const BYTE *data, const DWORD nCmdLen);
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
		bool msgParseStruct(const CMD::t_NullCmd *, const unsigned int);
		
		/**
		 * \brief 获取服务器编号
		 *
		 * \return 服务器编号
		 */
		const DWORD getID() const
		{
			return _zone_id;
		}

	private:

		DWORD _zone_id;					/**< 服务器编号，一个区唯一的 */
};

#endif


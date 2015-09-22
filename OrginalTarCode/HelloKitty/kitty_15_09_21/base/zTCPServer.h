/**
 * \file
 * \version  $Id: zTCPServer.h 13 2013-03-20 02:35:18Z  $
 * \author  ,@163.com
 * \date 2004年11月02日 17时05分07秒 CST
 * \brief 封装TCP的服务器监听模块
 *
 * 
 */

#ifndef _zTCPServer_h_
#define _zTCPServer_h_

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string>

#include "zNoncopyable.h"
#include "zSocket.h"

/**
 * \brief zTCPServer类，封装了服务器监听模块，可以方便的创建一个服务器对象，等待客户端的连接
 *
 */
class zTCPServer : private zNoncopyable
{

	public:

		zTCPServer(const std::string &name);
		~zTCPServer();
		bool bind(const std::string &name, const unsigned short port);
		int accept(struct sockaddr_in *addr);

	private:

		static const int T_MSEC =2100;			/**< 轮询超时，毫秒 */
		static const int MAX_WAITQUEUE = 2000;	/**< 最大等待队列 */

		std::string name;						/**< 服务器名称 */
		int sock;								/**< 套接口 */
		int kdpfd;

}; 


#endif

/**
 * \file
 * \version  $Id: zTCPServer.cpp 13 2013-03-20 02:35:18Z  $
 * \author  ,@163.com
 * \date 2004年11月02日 17时31分02秒 CST
 * \brief 实现类zTCPServer
 *
 * 
 */

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#include "zSocket.h"
#include "zTCPServer.h"
#include "Fir.h"

/**
 * \brief 构造函数，用于构造一个服务器zTCPServer对象
 * \param name 服务器名称
 */
zTCPServer::zTCPServer(const std::string &name)
: name(name),
	sock(-1)
{
	kdpfd = epoll_create(1);
	assert(-1 != kdpfd);
}

/**
 * \brief 析构函数，用于销毁一个zTCPServer对象
 *
 *
 */
zTCPServer::~zTCPServer() 
{
	TEMP_FAILURE_RETRY(::close(kdpfd));
	if (-1 != sock) 
	{
		::shutdown(sock, SHUT_RD);
		TEMP_FAILURE_RETRY(::close(sock));
		sock = -1;
	}
}

/**
 * \brief 绑定监听服务到某一个端口
 * \param name 绑定端口名称
 * \param port 具体绑定的端口
 * \return 绑定是否成功
 */
bool zTCPServer::bind(const std::string &name, const unsigned short port)
{
	struct sockaddr_in addr;

	if (-1 != sock) 
	{
		Fir::logger->error("服务器可能已经初始化");;
		return false;
	}

	sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (-1 == sock) 
	{
		Fir::logger->error("创建套接口失败");
		return false;
	}

	//设置套接口为可重用状态
	int reuse = 1;
	if (-1 == ::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))) 
	{
		Fir::logger->error("不能设置套接口为可重用状态");
		TEMP_FAILURE_RETRY(::close(sock));
		sock = -1;
		return false;
	}

	//设置套接口发送接收缓冲，并且服务器的必须在accept之前设置
	socklen_t window_size = 128 * 1024;
	if (-1 == ::setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &window_size, sizeof(window_size)))
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	if (-1 == ::setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &window_size, sizeof(window_size)))
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int retcode = ::bind(sock, (struct sockaddr *) &addr, sizeof(addr));
	if (-1 == retcode) 
	{
		Fir::logger->error("不能绑定服务器端口");
		TEMP_FAILURE_RETRY(::close(sock));
		sock = -1;
		return false;
	}

	retcode = ::listen(sock, MAX_WAITQUEUE);
	if (-1 == retcode) 
	{
		Fir::logger->error("监听套接口失败");
		TEMP_FAILURE_RETRY(::close(sock));
		sock = -1;
		return false;
	}

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = NULL;
	assert(0 == epoll_ctl(kdpfd, EPOLL_CTL_ADD, sock, &ev));

	Fir::logger->info("初始化 %s:%u 成功", name.c_str(), port);

	return true;
}

/**
 * \brief 接受客户端的连接
 *
 *
 * \param addr 返回的地址
 * \return 返回的客户端套接口
 */
int zTCPServer::accept(struct sockaddr_in *addr)
{
	socklen_t len = sizeof(struct sockaddr_in);
	bzero(addr, sizeof(struct sockaddr_in));

	struct epoll_event ev;
	int rc = epoll_wait(kdpfd, &ev, 1, T_MSEC);
	if (1 == rc && (ev.events & EPOLLIN))
		//准备好接受
		return TEMP_FAILURE_RETRY(::accept(sock, (struct sockaddr *)addr, &len));

	return -1;
}


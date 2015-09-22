/**
 * \file
 * \version  $Id: zTCPClientTask.cpp 42 2013-04-10 07:33:59Z  $
 * \author  ,@163.com
 * \date 2004年11月04日 17时25分13秒 CST
 * \brief 实现类zTCPClientTask，TCP连接客户端。
 *
 * 
 */


#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

#include "zTCPClientTask.h"
#include "Fir.h"
#include "extractProtoMsg.h"

/**
 * \brief 建立一个到服务器的TCP连接
 *
 *
 * \return 连接是否成功
 */
bool zTCPClientTask::connect()
{
	int retcode;
	int nSocket;
	struct sockaddr_in addr;

	nSocket = ::socket(PF_INET, SOCK_STREAM, 0);
	if (-1 == nSocket)
	{
		Fir::logger->error("创建套接口失败: %s", strerror(errno));
		return false;
	}

	//设置套接口发送接收缓冲，并且客户端的必须在connect之前设置
	socklen_t window_size = 128 * 1024;
	retcode = ::setsockopt(nSocket, SOL_SOCKET, SO_RCVBUF, &window_size, sizeof(window_size));
	if (-1 == retcode)
	{
		TEMP_FAILURE_RETRY(::close(nSocket));
		return false;
	}
	retcode = ::setsockopt(nSocket, SOL_SOCKET, SO_SNDBUF, &window_size, sizeof(window_size));
	if (-1 == retcode)
	{
		TEMP_FAILURE_RETRY(::close(nSocket));
		return false;
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);

	retcode = TEMP_FAILURE_RETRY(::connect(nSocket, (struct sockaddr *) &addr, sizeof(addr)));
	if (-1 == retcode)
	{
		Fir::logger->error("创建到服务器 %s(%u) 的连接失败", ip.c_str(), port);
		TEMP_FAILURE_RETRY(::close(nSocket));
		return false;
	}
	Fir::logger->info("创建到服务器 %s(%u) 的连接成功", ip.c_str(), port);

	pSocket = FIR_NEW zSocket(nSocket, &addr, compress);
	if (NULL == pSocket)
	{
		Fir::logger->fatal("没有足够的内存，不能创建zSocket实例");
		TEMP_FAILURE_RETRY(::close(nSocket));
		return false;
	}

	Fir::logger->info("创建到服务器 %s:%u 的连接成功", ip.c_str(), port);

	return true;
}

/**
 * \brief 向套接口发送指令
 * \param pstrCmd 待发送的指令
 * \param nCmdLen 待发送指令的大小
 * \param _if_buffer 是否缓冲
 * \return 发送是否成功
 */
bool zTCPClientTask::sendCmd(const void *pstrCmd, const int nCmdLen, const bool _if_buffer)
{
	switch(state)
	{
		case close:
		case sync:
			if (NULL == pSocket) 
				return false;
			else
				return pSocket->sendCmd(pstrCmd, nCmdLen, _if_buffer);
			break;
		case okay:
		case recycle:
			if (NULL == pSocket)
				return false;
			else
				return pSocket->sendCmd(pstrCmd, nCmdLen, true);
			break;
	}

	return false;
}

/**
 * \brief 从套接口中接受数据，并且拆包进行处理，在调用这个函数之前保证已经对套接口进行了轮询
 *
 * \param needRecv 是否需要真正从套接口接受数据，false则不需要接收，只是处理缓冲中剩余的指令，true需要实际接收数据，然后才处理
 * \return 接收是否成功，true表示接收成功，false表示接收失败，可能需要断开连接 
 */
bool zTCPClientTask::ListeningRecv(bool needRecv)
{
	if(!pSocket)    return false;

	int retcode = 0;
	if (needRecv) {
		retcode = pSocket->recvToBuf_NoPoll();
	}
	if (-1 == retcode)
	{
		Fir::logger->error("%s", __PRETTY_FUNCTION__);
		return false;
	}
	else
	{
		do
		{
			BYTE acceptCmd[zSocket::MAX_DATASIZE];
			int nCmdLen = pSocket->recvToCmd_NoPoll(acceptCmd, sizeof(acceptCmd));
			
			//这里只是从缓冲取数据包，所以不会出错，没有数据直接返回
            if (nCmdLen <= 0)
            {
				break;
            }

			msgParse(acceptCmd,nCmdLen);
		}
		while(true);
	}
	return true;
}

/**
 * \brief 发送缓冲中的数据到套接口，再调用这个之前保证已经对套接口进行了轮询
 *
 * \return 发送是否成功，true表示发送成功，false表示发送失败，可能需要断开连接
 */
bool zTCPClientTask::ListeningSend()
{
	if (pSocket)
		return pSocket->sync();
	else
		return false;
}

/**
 * \brief 把TCP连接任务交给下一个任务队列，切换状态
 *
 */
void zTCPClientTask::getNextState()
{
	ConnState old_state = getState();

	lifeTime.now();
	switch(old_state)
	{
		case close:
			setState(sync);
			break;
		case sync:
			addToContainer();
			setState(okay);
			break;
		case okay:
			removeFromContainer();
			setState(recycle);
			break;
		case recycle:
			if (terminate == TM_service_close)
				recycleConn();
			setState(close);
			final();
			break;
	}

	Fir::logger->debug("%s(%s, %u, %s -> %s)", __FUNCTION__,  ip.c_str(), port, getStateString(old_state), getStateString(getState()));
}

void zTCPClientTask::reconn()
{
	removeFromContainer();
	setState(recycle);
}

/**
 * \brief 重值连接任务状态，回收连接
 *
 */
void zTCPClientTask::resetState()
{
	ConnState old_state = getState();

	lifeTime.now();
	setState(close);
	final();

	Fir::logger->debug("%s(%s, %u, %s -> %s)", __FUNCTION__,  ip.c_str(), port, getStateString(old_state), getStateString(getState()));
}

bool zTCPClientTask::msgParseNullCmd(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if (CMD::CMD_NULL == ptNullCmd->cmd)
    {
        if (CMD::SERVER_PARA_NULL == ptNullCmd->para)
        {
            //接收到服务器的测试指令，需要按照原始指令返回
            std::string ret;
            encodeMessage(ptNullCmd,nCmdLen,ret);
            sendCmd(ret.c_str(),ret.size());
            Fir::logger->debug("客户端收到服务器发送的测试信号(%u,%u,%lu,%lu),反射回服务器", ptNullCmd->para, ptNullCmd->cmd,sizeof(*ptNullCmd),ret.size());
        }
        else if (CMD::CLIENT_PARA_NULL == ptNullCmd->para)
        {
            Fir::logger->debug("[网络]:收到 %s:%d 返回的心跳信号", this->ip.c_str(), this->port);
            clearTick();
        }
        return true;
    }
    return false;
}



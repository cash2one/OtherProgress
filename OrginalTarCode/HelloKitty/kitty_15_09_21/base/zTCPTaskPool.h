/**
 * \file
 * \version  $Id: zTCPTaskPool.h 13 2013-03-20 02:35:18Z  $
 * \author  ,@163.com
 * \date 2004年11月17日 13时02分13秒 CST
 * \brief 封装实现线程池，用于处理多连接服务器
 *
 * 
 */


#ifndef _zTCPTaskPool_h_
#define _zTCPTaskPool_h_

#include <string>
#include <vector>
#include <queue>
#include <list>
#include <unistd.h>
#include <sys/timeb.h>

#include "zSocket.h"
#include "zThread.h"
#include "zTCPTask.h"
#include "Fir.h"
#include "zString.h"

class zSyncThread;
class zRecycleThread;

/**
 * \brief 连接线程池类，封装了一个线程处理多个连接的线程池框架
 *
 */
class zTCPTaskPool : private zNoncopyable
{

	public:

		/**
		 * \brief 构造函数
		 * \param maxConns 线程池并行处理有效连接的最大数量
		 * \param state 初始化的时候连接线程池的状态
		 */
		explicit zTCPTaskPool(const int maxConns, const int state,const unsigned long us=50000L) : maxConns(maxConns), state(state)
		{
			setUsleepTime(us);
			syncThread = NULL;
			recycleThread = NULL;
			maxThreadCount = minThreadCount;
		};

		/**
		 * \brief 析构函数，销毁一个线程池对象
		 *
		 */
		~zTCPTaskPool()
		{
			final();
		}

		/**
		 * \brief 获取连接线程池当前状态
		 *
		 * \return 返回连接线程池的当前状态
		 */
		const int getState() const
		{
			return state;
		}

		/**
		 * \brief 设置连接线程池状态
		 *
		 * \param state 设置的状态标记位
		 */
		void setState(const int state)
		{
			this->state |= state;
		}

		/**
		 * \brief 清楚连接线程池状态
		 *
		 * \param state 清楚的状态标记位
		 */
		void clearState(const int state)
		{
			this->state &= ~state;
		}

		const int getSize();
		inline const int getMaxConns() const { return maxConns; }
		bool addVerify(zTCPTask *task);
		void addSync(zTCPTask *task);
		bool addOkay(zTCPTask *task);
		void addRecycle(zTCPTask *task);
		static void  setUsleepTime(const unsigned long time)
		{
			usleep_time=time;
		}

		bool init();
		void final();

	private:

		const int maxConns;										/**< 线程池并行处理连接的最大数量 */

		static const int maxVerifyThreads = 4;					/**< 最大验证线程数量 */
		zThreadGroup verifyThreads;								/**< 验证线程，可以有多个 */

		zSyncThread *syncThread;								/**< 等待同步线程 */

		static const int minThreadCount = 1;					/**< 线程池中同时存在主处理线程的最少个数 */
		int maxThreadCount;										/**< 线程池中同时存在主处理线程的最大个数 */
		zThreadGroup okayThreads;								/**< 处理主线程，多个 */

		zRecycleThread *recycleThread;							/**< 连接回收线程 */

		int state;												/**< 连接池状态 */
	public:
		static unsigned long usleep_time;						/**< 循环等待时间 */

};

#endif


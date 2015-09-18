/**
 * \file
 * \version  $Id: zHttpTaskPool.h 13 2013-03-20 02:35:18Z  $
 * \author  ,@163.com
 * \date 2004年11月17日 13时02分13秒 CST
 * \brief 定义实现轻量级(lightweight)的http服务框架
 */


#ifndef _zHttpTaskPool_h_
#define _zHttpTaskPool_h_

#include <string>
#include <vector>
#include <queue>
#include <list>
#include <unistd.h>
#include <sys/timeb.h>

#include "zSocket.h"
#include "zThread.h"
#include "zHttpTask.h"
#include "Fir.h"
#include "zString.h"

/**
 * \brief 定义实现轻量级(lightweight)的http服务框架类
 */
class zHttpTaskPool : private zNoncopyable
{

	public:

		/**
		 * \brief 构造函数
		 */
		zHttpTaskPool()
		{
		};

		/**
		 * \brief 析构函数，销毁一个线程池对象
		 *
		 */
		~zHttpTaskPool()
		{
			final();
		}

		bool addHttp(zHttpTask *task);
		bool init();
		void final();

	private:

		static const int maxHttpThreads = 8;					/**< 最大验证线程数量 */
		zThreadGroup httpThreads;								/**< http服务处理线程组 */

};

#endif

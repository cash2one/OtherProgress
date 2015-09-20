/**
 * \file
 * \version  $Id: TimeTick.h 13 2013-03-20 02:35:18Z  $
 * \author  ,@163.com
 * \date 2005年01月05日 21时03分02秒 CST
 * \brief 时间回调函数
 *
 * 
 */


#ifndef _TimeTick_h_
#define _TimeTick_h_

#include <iostream>
#include <string>
#include <sys/timeb.h>

#include "Fir.h"
#include "zThread.h"
#include "zTime.h"

class AZTimeTick : public zThread, public Singleton<AZTimeTick>
{
	friend class Singleton<AZTimeTick>;
	public:

		~AZTimeTick(){};

		void run();

		static zRTime currentTime;
	private:

		static AZTimeTick *instance;

		zRTime startTime;
		Timer one_sec;
		
		AZTimeTick() : zThread("TimeTick"), startTime(),one_sec(1)
		{
		}
};

#endif


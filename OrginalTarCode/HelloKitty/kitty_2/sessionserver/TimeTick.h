/**
 * \file
 * \version  $Id: TimeTick.h 29 2013-04-07 01:39:43Z  $
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

#include "Fir.h"
#include "zTime.h"
#include "zThread.h"

class SessionTimeTick : public zThread, public Singleton<SessionTimeTick>
{
	friend class Singleton<SessionTimeTick>;
	public:

		~SessionTimeTick() {};

		/// 当前时间
		static zRTime currentTime;
		
		void run();
		static bool checkInSameDay(DWORD t1, DWORD t2)
		{
			struct tm tm1,tm2;
			zRTime::getLocalTime(tm1, (time_t)t1);
			zRTime::getLocalTime(tm2, (time_t)t2);
			if (tm1.tm_year == tm2.tm_year && tm1.tm_yday == tm2.tm_yday)
				return true;
			return false;
		}
	private:

		static SessionTimeTick *instance;

		SessionTimeTick();
		bool isUpdate;

		Timer _10_min;
		Timer _1_min;
		Timer _1_sec;
		Timer _30_min;

		zClocker _20_Hour;
		zClocker _22_Clock;
		zClocker _4_Clock;
		zClocker _1_min_Clock;
};

#endif


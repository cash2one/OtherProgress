/**
 * \file
 * \version  $Id: TimeTick.h 62 2013-04-22 13:00:09Z chengxie $
 * \author  , 
 * \date 2005年01月05日 21时03分02秒 CST
 * \brief 存档定时器
 *
 * 
 */


#ifndef _TimeTick_h_
#define _TimeTick_h_

#include <iostream>
#include <string>

#include "Fir.h"
#include "zThread.h"
#include "zTime.h"
#include "zSingleton.h"

class RecordTimeTick : public zThread,
					   public Fir::Singleton<RecordTimeTick> 
{
	public:

		static zRTime currentTime;

		RecordTimeTick() : zThread("RecordTimeTick"),  _one_min(60) {};
		~RecordTimeTick() {};

		void run();

	private:
		Timer _one_min;


};

#endif


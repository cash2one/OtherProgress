/**
 * \file
 * \version  $Id: TimeTick.cpp 13 2013-03-20 02:35:18Z  $
 * \author  ,@163.com
 * \date 2005年01月05日 21时03分02秒 CST
 * \brief 时间回调函数
 *
 * 
 */


#include <iostream>
#include <string>
#include <sys/timeb.h>

#include "Fir.h"
#include "zThread.h"
#include "TimeTick.h"
#include "AllZoneServer.h"
#include "Fir.h"
#include "zDBConnPool.h"
#include "ZoneManager.h"

zRTime AZTimeTick::currentTime;
AZTimeTick *AZTimeTick::instance = NULL;

void AZTimeTick::run()
{
	const int timeout_value = 500;

	while(!isFinal())
	{
		zThread::msleep(50);

		currentTime.now();


		{
			ZoneManager::getMe().execEvery();
		}

		zRTime e;
		int t = currentTime.elapse(e);
		if (t > timeout_value)
		{
			Fir::logger->debug("[ALLZONE TIMETICK超时],0,0,0,处理时间过长 %u",t);
		}
		
	}
}


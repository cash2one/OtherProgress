/**
 * \file
 * \version  $Id: TimeTick.cpp 24 2013-03-30 08:04:25Z  $
 * \author  ，
 * \date 2006年12月27日 21时03分02秒 CST
 * \brief 存档定时器实现
 *
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Fir.h"
#include "zThread.h"
#include "TimeTick.h"
#include "RecordUserManager.h"
#include "RecordTask.h"
#include "RecordServer.h"

zRTime RecordTimeTick::currentTime;

void RecordTimeTick::run()
{
	//int rush = 0;
	while(!isFinal())
	{
		zThread::msleep(50);

		//获取当前时间
		currentTime.now();

		if (_one_min(currentTime))
		{
			/*struct tm tv1;
			time_t timValue = time(NULL);
			zRTime::getLocalTime(tv1, timValue);

			if (tv1.tm_hour==6 && tv1.tm_min==54)	
			{
				RecordService::getMe().change_level = RecordTask::calcTravelLevel();
			}
			*/
		}
	}
}

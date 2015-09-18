/**
 * \file
 * \version  $Id: TimeTick.cpp 67 2013-04-23 09:44:20Z  $
 * \author  ,
 * \date 2013年04月05日 21时03分02秒 CST
 * \brief 时间回调函数
 *
 * 
 */


#include <iostream>
#include <string>

#include "zThread.h"
#include "TimeTick.h"
#include "SceneServer.h"
#include "SceneUserManager.h"
#include "SceneTaskManager.h"
#include "SessionClient.h"
#include "RecordClient.h"
#include "TimerMgr.h"

SceneTimeTick *SceneTimeTick::instance = NULL;
zRTime SceneTimeTick::currentTime;

WORD SceneTimeTick::secCountNum = 0;
SceneTimeTick::SceneTimeTick() :
	zThread("TimeTick")
	,_1_min(60)
	,_1_sec(1)
	,_1_card_sec(1,1)
	,_1_hour(3600,3600)
{
}
void SceneTimeTick::run()
{
	const int timeout_value = 500;
	int t = 0;
	while(!isFinal())
	{
		zThread::msleep((10-t)>0?(10-t):1);
		currentTime.now();

		if (_1_card_sec(currentTime))
		{//这个要在场景消息解析前
			secCountNum = 0;
		}

		{
			//My_FunctionTime_wrapperMT("RU"_S(__LINE__));
			sessionClient->doCmd();
		}

		{
			//My_FunctionTime_wrapperMT("RU"_S(__LINE__));
			recordClient->doCmd();
		}

		{
			//My_FunctionTime_wrapperMT("RU"_S(__LINE__));
			SceneService::getMe().superCmd.doCmd();
		}

		{
			//My_FunctionTime_wrapperMT("RU"_S(__LINE__));
			SceneTaskManager::getMe().execEvery();
		}

		if(_1_sec(currentTime))
		{
			//Fir::logger->error("[lbs2],%s",currentTime.toNumber().c_str());
			{
				//My_FunctionTime_wrapperMT("RU"_S(__LINE__));
				if(_1_min(currentTime))
				{
					SceneUserManager::getMe().update();
				}
			}

			TimerMgr::getMe().Update();
		}


		zRTime e;
		t = currentTime.elapse(e);
		if (t > timeout_value)
		{
			Fir::logger->debug("[场景TIMETICK超时],0,0,0,处理时间过长 %u",t);
		}

#if defined (__MY_FUNCTIONTIME_WRAPPER__)
		My_FunctionTime_wrapper::my_func.reset(currentTime, t > timeout_value);
#endif
	}
}


void My_Address_wrapper::showLog()
{
	if(_oldPoint != sessionClient->getMsgAddress())
	{
		Fir::logger->debug("[宕机检测],指针不一致.当前处理消息:%u,%u", SceneService::cmd_record[2], SceneService::cmd_record[3]);
	}
}

#if defined (__MY_FUNCTIONTIME_WRAPPER__)
My_FunctionTime My_FunctionTime_wrapper::my_func(600);
#endif

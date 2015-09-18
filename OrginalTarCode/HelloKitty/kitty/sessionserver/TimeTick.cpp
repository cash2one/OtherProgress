#include <iostream>
#include <string>

#include "Fir.h"
#include "zThread.h"
#include "TimeTick.h"
#include "SessionServer.h"
#include "SessionTaskManager.h"
#include "RecordClient.h"
#include "TimerMgr.h"

SessionTimeTick *SessionTimeTick::instance = NULL;
zRTime SessionTimeTick::currentTime;

SessionTimeTick::SessionTimeTick() : 
	zThread("TimeTick")
	,_10_min(600)
	,_1_min(60)
	,_1_sec(1)
	,_30_min(1800)
#ifdef _DEBUG_WCX
	,_20_Hour(14*3600+2400,24*3600)
#else
	,_20_Hour(20*3600,24*3600)
#endif
	,_22_Clock(22*3600,24*3600)
	,_4_Clock(4*3600,24*3600)
	,_1_min_Clock(60, 24*3600)
{
}
void SessionTimeTick::run()
{
	while(!isFinal())
	{
		zThread::msleep(50);
		currentTime.now();

		recordClient->doCmd();

		SessionTaskManager::getMe().execEvery();

		TimerMgr::getMe().Update();
	}
}


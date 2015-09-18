#include <iostream>
#include <string>

#include "Fir.h"
#include "zThread.h"
#include "zTime.h"
#include "TimeTick.h"
#include "GatewayServer.h"
#include "GatewayTaskManager.h"

zRTime GatewayTimeTick::currentTime;

struct GatewayTaskCheckTime : public GatewayTaskManager::GatewayTaskCallback
{
	bool exec(GatewayTask *gt)
	{
		return gt->checkTime(GatewayTimeTick::currentTime);
		return true;
	}
};

/**
 * \brief 线程主函数
 *
 */
void GatewayTimeTick::run()
{
	while(!isFinal())
	{
		zThread::sleep(1);

		//获取当前时间
		currentTime.now();

		if (one_second(currentTime) ) 
		{
			
			if (five_second(currentTime))
			{
			}

//			GatewayTaskCheckTime gtct;
//			GatewayTaskManager::getMe().execAll(gtct);
			GatewayTaskManager::getMe().execAllCheckTime();
		}
	}
}


/**
 * \file    CounterManager.cpp
 * \version $Id: CounterManager.cpp 43 2013-04-10 10:29:18Z  $
 * \autor   ,
 * \date    2013年04月10日 10时23分40秒 CST
 * \brief   计数管理器实现 
 *
 */

#include "CounterManager.h"
#include "TimeTick.h"
#include <math.h>

CounterManager::CounterManager()
{
	
}

CounterManager::~CounterManager()
{

}

QWORD CounterManager::getCounter(DWORD id)
{
    return 0;
#if 0
	counter_iter iter = counter_map.find(id);
	if (iter==counter_map.end()) return 0;

	if (iter->second.type() == CHANGE_DAY)
	{
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.last_time());

		if ( (tm_cur.tm_yday != tm_last.tm_yday || tm_cur.tm_year != tm_last.tm_year)
				&& (SceneTimeTick::currentTime.sec() > iter->second.last_time()))
		{//如果已经到达切换条件，则重新计数
			iter->second.set_count(0);
			iter->second.set_last_time(SceneTimeTick::currentTime.sec());
		}
	}
	else if (iter->second.type() == CHANGE_SIXHOUR)
	{
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.last_time());

		if ((tm_cur.tm_year != tm_last.tm_year)
				|| ((tm_cur.tm_yday == tm_last.tm_yday) && ((tm_last.tm_hour < 6) && (tm_cur.tm_hour >= 6)))
				|| ((tm_cur.tm_yday != tm_last.tm_yday) && ((tm_cur.tm_hour >= 6) || (SceneTimeTick::currentTime.sec() - iter->second.last_time() >= 24*60*60))))
		{//当前日期不在同一年,或者同一天内在6点前后，或者不在同一天但过了6点或者超过24个小时
			iter->second.set_count(0);
			iter->second.set_last_time(SceneTimeTick::currentTime.sec());
		}
	}else if (iter->second.type() == CHANGE_WEEK)
	{
		DWORD cur = SceneTimeTick::currentTime.sec();
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.last_time());
		WORD cur_wday = tm_cur.tm_wday?tm_cur.tm_wday:7;
		WORD last_wday = tm_last.tm_wday?tm_last.tm_wday:7;

		time_t cur_monday = cur - (cur_wday-1)*24*60*60;
		time_t last_monday = iter->second.last_time() - (last_wday-1)*24*60*60;
		struct tm tm_cur_monday, tm_last_monday;
		zRTime::getLocalTime(tm_cur_monday, cur_monday);
		zRTime::getLocalTime(tm_last_monday, last_monday);

		if ( (cur>iter->second.last_time())
				&& ((tm_cur_monday.tm_yday!=tm_last_monday.tm_yday) || (cur-iter->second.last_time() >= 7*24*60*60 )))
		{//如果已经到达切换条件，则重新计数
			iter->second.set_count(0);
			iter->second.set_last_time(cur);
		}
	}
	return iter->second.count();
#endif
}


bool CounterManager::addCounter(DWORD id, QWORD num)
{
#if 0
	counter_iter iter = counter_map.find(id);
	if (iter==counter_map.end())
	{
		PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(CHANGE_NONE);
		tmp.set_count(num);
		tmp.set_last_time(SceneTimeTick::currentTime.sec());
		counter_map[id] = tmp;

		return true;
	}
	else
		iter->second.set_count(iter->second.count()+num);
#endif
	return true;
}

/*
 * \brief 指定数值给计数器
 *
 */
void CounterManager::setCounter(DWORD id, QWORD num)
{
#if 0
	counter_iter iter = counter_map.find(id);
	if (iter==counter_map.end())
	{
		PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(CHANGE_NONE);
		tmp.set_count(num);
		tmp.set_last_time(SceneTimeTick::currentTime.sec());
		counter_map[id] = tmp;
	}
	else
	{
		iter->second.set_count(num);
	}
#endif
}


bool CounterManager::clearCounter(DWORD id)
{
#if 0
	counter_iter iter = counter_map.find(id);
	if (iter==counter_map.end())
	{
	}
	else
		iter->second.set_count(0);
#endif
	return true;

}

bool CounterManager::addCounterMonth(DWORD id, QWORD num)
{
#if 0
	counter_iter iter = counter_map.find(id);
	if (iter == counter_map.end())
	{
		PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(CHANGE_MONTH);
		tmp.set_count(num);
		tmp.set_last_time(SceneTimeTick::currentTime.sec());
		counter_map[id] = tmp;

		return true;
	}
	else if (iter->second.type() == CHANGE_MONTH)
	{
		DWORD cur = SceneTimeTick::currentTime.sec();
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.last_time());
		
		if ( tm_cur.tm_mon == tm_last.tm_mon && tm_cur.tm_year == tm_last.tm_year )
		{
			iter->second.set_count(iter->second.count()+num);
		}
		else
		{
			iter->second.set_count(num);
			iter->second.set_last_time(cur);
		}
		
		return true;
	}
#endif
	return false;
}


bool CounterManager::addCounterWeek(DWORD id, QWORD num)
{
#if 0
	counter_iter iter = counter_map.find(id);
	if (iter==counter_map.end())
	{
		PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(CHANGE_WEEK);
		tmp.set_count(num);
		tmp.set_last_time(SceneTimeTick::currentTime.sec());
		counter_map[id] = tmp;

		return true;
	}
	else if (iter->second.type() == CHANGE_WEEK)
	{
		DWORD cur = SceneTimeTick::currentTime.sec();
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.last_time());
		WORD cur_wday = tm_cur.tm_wday?tm_cur.tm_wday:7;
		WORD last_wday = tm_last.tm_wday?tm_last.tm_wday:7;

		time_t cur_monday = cur - (cur_wday-1)*24*60*60;
		time_t last_monday = iter->second.last_time() - (last_wday-1)*24*60*60;
		struct tm tm_cur_monday, tm_last_monday;
		zRTime::getLocalTime(tm_cur_monday, cur_monday);
		zRTime::getLocalTime(tm_last_monday, last_monday);
		
		if ( (cur>iter->second.last_time()) 
				&& ((tm_cur_monday.tm_yday!=tm_last_monday.tm_yday) || (cur-iter->second.last_time() >= 7*24*60*60 )))
		{//如果已经到达切换条件，则重新计数
			iter->second.set_count(num);
		}
		else
		{
			iter->second.set_count(iter->second.count()+num);
		}
		iter->second.set_last_time(cur);
#ifdef _PQQ_DEBUG
		Fir::logger->debug("[CounterWeek],0,0,0,tm_cur_monday.tm_yday:%u, tm_last_monday.tm_yday:%u",tm_cur_monday.tm_yday, tm_last_monday.tm_yday); 
#endif		
		
		return true;
	}
#endif
	return false;
}

bool CounterManager::addCounterDay(DWORD id, QWORD num)
{
#if 0
	counter_iter iter = counter_map.find(id);
	if (iter==counter_map.end())
	{
		PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(CHANGE_DAY);
		tmp.set_count(num);
		tmp.set_last_time(SceneTimeTick::currentTime.sec());
		counter_map[id] = tmp;

		return true;
	}
	else if (iter->second.type() == CHANGE_DAY)
	{
 		  struct tm tm_cur,tm_last;
			zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
			zRTime::getLocalTime(tm_last, iter->second.last_time());
			
			if ( (tm_cur.tm_yday != tm_last.tm_yday || tm_cur.tm_year != tm_last.tm_year)
					&& (SceneTimeTick::currentTime.sec() > iter->second.last_time()))
			{//当前日期比上次访问的日期大于24小时，或者，不在同一天，则进行重新计数
				iter->second.set_count(num);
			}
			else
			{
				iter->second.set_count(iter->second.count()+num);
			}

			iter->second.set_last_time(SceneTimeTick::currentTime.sec());
			return true;
	}
#endif
	return false;
}

bool CounterManager::addCounterSixHour(DWORD id, QWORD num/*=1*/)
{
#if 0
	counter_iter iter = counter_map.find(id);
	if (iter==counter_map.end())
	{
		PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(CHANGE_SIXHOUR);
		tmp.set_count(num);
		tmp.set_last_time(SceneTimeTick::currentTime.sec());
		counter_map[id] = tmp;
		return true;
	}
	else if (iter->second.type() == CHANGE_SIXHOUR)
	{
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.last_time());

		if ((tm_cur.tm_year != tm_last.tm_year)
				|| ((tm_cur.tm_yday == tm_last.tm_yday) && ((tm_last.tm_hour < 6) && (tm_cur.tm_hour >= 6)))
				|| ((tm_cur.tm_yday != tm_last.tm_yday) && ((tm_cur.tm_hour >= 6) || (SceneTimeTick::currentTime.sec() - iter->second.last_time() >= 24*60*60))))
		{//当前日期不在同一年,或者同一天内在6点前后，或者不在同一天但过了6点或者超过24个小时
			iter->second.set_count(num);
		}
		else
		{
			iter->second.set_count(iter->second.count()+num);
		}
		iter->second.set_last_time(SceneTimeTick::currentTime.sec());
		return true;
	}
#endif
	return false;
}

int CounterManager::getSize()
{
    return 0;
#if 0
	return this->counter_map.size();
#endif
}

#if 0
void CounterManager::save(Serialize& binary)
{
	int size =  this->counter_map.size();
	if (0 == size)
		return;
	counter_iter iter = this->counter_map.begin();
	for(; iter != this->counter_map.end(); ++iter)
	{
		PbCounter* tmp = binary.add_pb_counters();
		tmp->CopyFrom(iter->second);
	}

}

void CounterManager::load(const Serialize& binary)
{
	for (int i = 0; i < binary.pb_counters_size(); ++i)
	{
		const PbCounter& counterinfo = binary.pb_counters(i);
		PbCounter tmp;
		tmp.CopyFrom(counterinfo);
		counter_map[tmp.id()] = tmp;
	}
}

#endif


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

DWORD CounterManager::getCounter(const DWORD id)
{
	counter_iter iter = m_counterMap.find(id);
	if (iter == m_counterMap.end()) 
    {
        return 0;
    }
    
    struct tm tm_cur,tm_last;
    zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
    zRTime::getLocalTime(tm_last, iter->second.lasttime());
    
    bool isSameYearFlg = tm_cur.tm_year == tm_last.tm_year;    //是否同年
    bool isSameDayFlg = tm_cur.tm_yday == tm_last.tm_yday;     //是否同日
    bool isPassTimeFlg = SceneTimeTick::currentTime.sec() > iter->second.lasttime();  //是否现在时间大

    bool ret = false;
	if (iter->second.type() == HelloKittyMsgData::Reset_Day)
	{
        //每天只刷新一次
        if((!isSameYearFlg || !isSameDayFlg) && isPassTimeFlg)
        {
            ret = true;
		}
	}
	else if (iter->second.type() == HelloKittyMsgData::Reset_SixHour)
	{
        //当前日期不在同一年,或者同一天内在6点前后，或者不在同一天但过了6点或者超过24个小时
        if(!isSameYearFlg || (isSameDayFlg && tm_last.tm_hour < 6 && tm_cur.tm_hour >= 6) || (!isSameDayFlg && (tm_cur.tm_hour >= 6 || SceneTimeTick::currentTime.sec() - iter->second.lasttime() >= 24*60*60)))
		{
            ret = true;
		}
	}
    else if (iter->second.type() == HelloKittyMsgData::Reset_Week)
	{
		DWORD cur = SceneTimeTick::currentTime.sec();
		WORD cur_wday = tm_cur.tm_wday?tm_cur.tm_wday:7;
		WORD last_wday = tm_last.tm_wday?tm_last.tm_wday:7;

		time_t cur_monday = cur - (cur_wday-1)*24*60*60;
		time_t last_monday = iter->second.lasttime() - (last_wday-1)*24*60*60;
		struct tm tm_cur_monday, tm_last_monday;
		zRTime::getLocalTime(tm_cur_monday, cur_monday);
		zRTime::getLocalTime(tm_last_monday, last_monday);

		if (isPassTimeFlg && ((tm_cur_monday.tm_yday != tm_last_monday.tm_yday) || ( cur - iter->second.lasttime() >= 7*24*60*60)))
		{
            ret = true;
		}
	}

    //如果已经到达切换条件，则重新计数
    if(ret)
    {
        iter->second.set_count(0);
        iter->second.set_lasttime(SceneTimeTick::currentTime.sec());
    }

	return iter->second.count();
}


bool CounterManager::setCounter(const DWORD id, const QWORD num)
{
	counter_iter iter = m_counterMap.find(id);
    if(iter != m_counterMap.end())
    {
        iter->second.set_count(iter->second.count()+num);
        return true;
    }
    
    HelloKittyMsgData::PbCounter tmp;
    tmp.set_id(id);
    tmp.set_type(HelloKittyMsgData::Reset_No);
    tmp.set_count(num);
    tmp.set_lasttime(SceneTimeTick::currentTime.sec());
    m_counterMap[id] = tmp;

	return true;
}

bool CounterManager::retsetCounter(const DWORD id)
{
	counter_iter iter = m_counterMap.find(id);
	if (iter != m_counterMap.end())
	{
        iter->second.set_count(0);
	}
	return true;
}

#if 0
bool CounterManager::addCounterMonth(const DWORD id, const QWORD num)
{
	counter_iter iter = m_counterMap.find(id);
	if (iter == m_counterMap.end())
	{
        HelloKittyMsgData::PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(HelloKittyMsgData::Reset_No);
		tmp.set_count(num);
		tmp.set_lasttime(SceneTimeTick::currentTime.sec());
		m_counterMap[id] = tmp;

		return true;
	}
	else if (iter->second.type() == HelloKittyMsgData::Reset_Month)
	{
		DWORD cur = SceneTimeTick::currentTime.sec();
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.lasttime());
		
		if ( tm_cur.tm_mon == tm_last.tm_mon && tm_cur.tm_year == tm_last.tm_year )
		{
			iter->second.set_count(iter->second.count()+num);
		}
		else
		{
			iter->second.set_count(num);
			iter->second.set_lasttime(cur);
		}
		
		return true;
	}
	return false;
}


bool CounterManager::addCounterWeek(const DWORD id, const QWORD num)
{
	counter_iter iter = m_counterMap.find(id);
	if (iter==m_counterMap.end())
	{
        HelloKittyMsgData::PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(HelloKittyMsgData::Reset_Week);
		tmp.set_count(num);
		tmp.set_lasttime(SceneTimeTick::currentTime.sec());
		m_counterMap[id] = tmp;

		return true;
	}
	else if (iter->second.type() == HelloKittyMsgData::Reset_Week)
	{
		DWORD cur = SceneTimeTick::currentTime.sec();
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.lasttime());
		WORD cur_wday = tm_cur.tm_wday?tm_cur.tm_wday:7;
		WORD last_wday = tm_last.tm_wday?tm_last.tm_wday:7;

		time_t cur_monday = cur - (cur_wday-1)*24*60*60;
		time_t last_monday = iter->second.lasttime() - (last_wday-1)*24*60*60;
		struct tm tm_cur_monday, tm_last_monday;
		zRTime::getLocalTime(tm_cur_monday, cur_monday);
		zRTime::getLocalTime(tm_last_monday, last_monday);
		
		if ( (cur>iter->second.lasttime()) 
				&& ((tm_cur_monday.tm_yday!=tm_last_monday.tm_yday) || (cur-iter->second.lasttime() >= 7*24*60*60 )))
		{
            //如果已经到达切换条件，则重新计数
			iter->second.set_count(num);
		}
		else
		{
			iter->second.set_count(iter->second.count()+num);
		}
		iter->second.set_lasttime(cur);
#ifdef _PQQ_DEBUG
		Fir::logger->debug("[CounterWeek],0,0,0,tm_cur_monday.tm_yday:%u, tm_last_monday.tm_yday:%u",tm_cur_monday.tm_yday, tm_last_monday.tm_yday); 
#endif		
		
		return true;
	}
	return false;
}

bool CounterManager::addCounterDay(const DWORD id, const QWORD num)
{
	counter_iter iter = m_counterMap.find(id);
	if (iter==m_counterMap.end())
	{
        HelloKittyMsgData::PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(HelloKittyMsgData::Reset_Day);
		tmp.set_count(num);
		tmp.set_lasttime(SceneTimeTick::currentTime.sec());
		m_counterMap[id] = tmp;

		return true;
	}
	else if (iter->second.type() == HelloKittyMsgData::Reset_Day)
	{
        struct tm tm_cur,tm_last;
        zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
        zRTime::getLocalTime(tm_last, iter->second.lasttime());
        
        if ( (tm_cur.tm_yday != tm_last.tm_yday || tm_cur.tm_year != tm_last.tm_year) && (SceneTimeTick::currentTime.sec() > iter->second.lasttime()))
        {
            //当前日期比上次访问的日期大于24小时，或者，不在同一天，则进行重新计数
            iter->second.set_count(num);
        }
        else
        {
            iter->second.set_count(iter->second.count()+num);
        }
        iter->second.set_lasttime(SceneTimeTick::currentTime.sec());
        return true;
	}
	return false;
}

bool CounterManager::addCounterSixHour(const DWORD id, const QWORD num)
{
	counter_iter iter = m_counterMap.find(id);
	if (iter==m_counterMap.end())
	{
        HelloKittyMsgData::PbCounter tmp;
		tmp.set_id(id);
		tmp.set_type(HelloKittyMsgData::Reset_SixHour);
		tmp.set_count(num);
		tmp.set_lasttime(SceneTimeTick::currentTime.sec());
		m_counterMap[id] = tmp;
		return true;
	}
	else if (iter->second.type() == HelloKittyMsgData::Reset_SixHour)
	{
		struct tm tm_cur,tm_last;
		zRTime::getLocalTime(tm_cur, SceneTimeTick::currentTime.sec());
		zRTime::getLocalTime(tm_last, iter->second.lasttime());

		if ( (tm_cur.tm_year != tm_last.tm_year) || ( (tm_cur.tm_yday == tm_last.tm_yday) && ( (tm_last.tm_hour < 6) && (tm_cur.tm_hour >= 6) ) ) || ( (tm_cur.tm_yday != tm_last.tm_yday) && ( (tm_cur.tm_hour >= 6) || (SceneTimeTick::currentTime.sec() - iter->second.lasttime() >= 24*60*60 ) ) ) )
		{
            //当前日期不在同一年,或者同一天内在6点前后，或者不在同一天但过了6点或者超过24个小时
			iter->second.set_count(num);
		}
		else
		{
			iter->second.set_count(iter->second.count()+num);
		}
		iter->second.set_lasttime(SceneTimeTick::currentTime.sec());
		return true;
	}
	return false;
}
#endif

DWORD CounterManager::getSize()
{
	return this->m_counterMap.size();
}

void CounterManager::save(HelloKittyMsgData::Serialize& binary)
{
    if(!m_counterMap.size())
    {
        return;
    }
	counter_iter iter = this->m_counterMap.begin();
	for(; iter != this->m_counterMap.end(); ++iter)
	{
        HelloKittyMsgData::PbCounter* tmp = binary.add_pb_counters();
		tmp->CopyFrom(iter->second);
	}
}

void CounterManager::load(const HelloKittyMsgData::Serialize& binary)
{
	for (int i = 0; i < binary.pb_counters_size(); ++i)
	{
		const HelloKittyMsgData::PbCounter& counterinfo = binary.pb_counters(i);
        m_counterMap[counterinfo.id()] = counterinfo;
	}
}



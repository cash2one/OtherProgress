/**
 * \file    CounterManager.h
 * \version $Id: CounterManager.h 43 2013-04-10 10:29:18Z  $
 * \autor   ,
 * \date    2013年04月10日 10时16分15秒 CST
 * \brief   计数管理器定义 
 *
 */

#ifndef _COUNTER_MANAGER_H
#define _COUNTER_MANAGER_H

#include "zType.h"
#include "CharBase.h"
#include <map>
#include <set>
#include <bitset>
#include "serialize.pb.h"

class SceneUser;

/**
 * \brief 计数管理器
 *
 */
class CounterManager
{
	public:
		CounterManager();
		~CounterManager();
        
        //获得计数器的次数
		DWORD getCounter(const DWORD id);
	    
        //序列化保存数据
        void save(HelloKittyMsgData::Serialize& binary);
        
        //发序列化加载数据
        void load(const HelloKittyMsgData::Serialize& binary);
	    
        //设置计数器
        bool setCounter(const DWORD id, const QWORD num);

#if 0
        // 需要按月切换的使用该函数进行计数
		bool  addCounterMonth(DWORD id, QWORD num=1); 

		// 需要按周切换的使用该函数进行计数
		bool  addCounterWeek(DWORD id, QWORD num=1);

		// 需要按天切换的使用该函数进行计数
		bool  addCounterDay(DWORD id, QWORD num=1);

		//需要按每天6点的使用该函数进行计数
		bool addCounterSixHour(DWORD id, QWORD num=1);

		// 不需要切换，只进行计数，使用该函数 
		bool  addCounter(DWORD id, QWORD num=1);
		inline bool setCounterDay(DWORD id, QWORD num = 1)
		{
			clearCounter(id);
			return addCounterDay(id, num);
		}
#endif

    private:
        //重置计数器
        bool retsetCounter(const DWORD id);
        //获得计数器数量
        DWORD getSize();
	
    private:
        //计数器容器
		std::map<DWORD,HelloKittyMsgData::PbCounter> m_counterMap;
		typedef std::map<DWORD,HelloKittyMsgData::PbCounter>::iterator counter_iter;

};

#endif


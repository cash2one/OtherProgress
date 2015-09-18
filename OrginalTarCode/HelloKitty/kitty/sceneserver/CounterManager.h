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

		QWORD getCounter(DWORD id);
		
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

		// 计数器归零
		bool  clearCounter(DWORD id);
		int getSize();
#if 0
		void save(Serialize& binary);
		void load(const Serialize& binary);
#endif
		void setCounter(DWORD id, QWORD num = 1);
		inline bool setCounterDay(DWORD id, QWORD num = 1)
		{
			clearCounter(id);
			return addCounterDay(id, num);
		}
#if 0
	protected:
		std::map<DWORD, PbCounter> counter_map;
		typedef std::map<DWORD, PbCounter>::iterator counter_iter;
#endif

};

#endif


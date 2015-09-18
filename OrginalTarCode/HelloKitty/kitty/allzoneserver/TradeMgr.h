#ifndef _TRADE_MGR_H_
#define _TRADE_MGR_H_

#include <string>
#include <map>
#include <vector>
#include <set>
#include <unordered_map>

#include "zType.h"
#include "zMisc.h"
#include "Fir.h"
#include "zRWLock.h"
#include "common.h"

class TradeMgr : public Singleton<TradeMgr>
{
	private:
		friend class Singleton<TradeMgr>;
		TradeMgr();
		~TradeMgr();

	public:
		void addSaleInfo(DWORD charid, const std::vector<CMD::stSaleCell>& vecCells);

		void reqSomePlayersSaleCells(DWORD zoneid,DWORD sceneid,QWORD charid);		
	protected:
		typedef std::vector<CMD::stSaleCell> SaleCellVector;
		struct stSaleInfo
		{
			DWORD charid;
			DWORD modify_time; // 修改时间 
			SaleCellVector vecCells;
			stSaleInfo()
			{
				charid = 0;
				modify_time = 0;
				vecCells.clear();
			}
		};

		std::unordered_map<DWORD,stSaleInfo> _mapSaleInfos;
		
		zRWLock rwlock;
};

#endif


#ifndef _UTRADE_H
#define _UTRADE_H

#include "zType.h"
#include <map>
#include <set>
#include <bitset>
#include "TradeCommand.h"

class SceneUser;

/**
 * \brief 计数管理器
 *
 */
class UTrade
{
	public:
		UTrade(SceneUser* u);
		~UTrade();
#if 0
		void save(Serialize& binary);
		void load(const Serialize& binary);
#endif
		bool req_sale_cells();
		bool req_salecell_putitem(DWORD cellid, DWORD itemid, DWORD itemcount);
		bool ret_someplayer_salecells(const std::vector<char>& vecBinary);
				
		bool initTradeInfo();
			
		bool req_itemconfig();
	protected:

		SceneUser* owner;

		std::map<DWORD,CMD::stSaleCell> _mapSaleCells; // 寄售道具格子

		
		bool addSaleCell(const CMD::stSaleCell& cell);
		bool hasCell(DWORD cellid);
		CMD::stSaleCell& getCell(DWORD cellid);	
};

#endif


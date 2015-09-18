#ifndef _USTORE_HOUSE_H
#define _USTORE_HOUSE_H

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
class UStoreHouse
{
	public:
		UStoreHouse(SceneUser* u);
		~UStoreHouse();
#if 0
		void save(Serialize& binary);
		void load(const Serialize& binary);
#endif
		bool req_item_list();
		
		DWORD addItem(DWORD itemid, DWORD itemcount);
		bool hasEnoughSpace(DWORD itemcount);
		DWORD getItemCount();

		bool hasEnoughItem(DWORD itemid, DWORD itemcount);
		void consumeItem(DWORD itemid, DWORD itemcount);	
	protected:
		void addItemInner(DWORD itemid, DWORD itemcount);
		
	private:
		SceneUser* owner;

		std::map<DWORD,DWORD> _mapItems; // 仓库道具
};

#endif


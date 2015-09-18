#include "UStoreHouse.h"
#include "tbx.h"
#include "SceneUser.h"
#include "TradeCommand.h"

UStoreHouse::UStoreHouse(SceneUser* u)
{
	owner = u;
}

UStoreHouse::~UStoreHouse()
{

}
#if 0
void UStoreHouse::save(Serialize& binary)
{
	for(auto itr=_mapItems.begin(); itr!=_mapItems.end(); itr++)
    {
        PbStoreItem* pitem = binary.add_store_items();
        pitem->set_itemid(itr->first); // 道具id
        pitem->set_itemcount(itr->second); // 道具数量
    }
}

void UStoreHouse::load(const Serialize& binary)
{
	_mapItems.clear();
    for(int i=0; i<binary.store_items_size(); i++)
    {
        const PbStoreItem& item = binary.store_items(i);
        DWORD itemid = item.itemid();
        DWORD itemcount = item.itemcount();
        _mapItems.insert(std::make_pair(itemid,itemcount));
    }
}
#endif
bool UStoreHouse::req_item_list()
{
	zCmdBufferAdapterT<CMD::stRetItemList_SC> send;
    for (auto itr = _mapItems.begin(); itr != _mapItems.end(); ++itr)
    {
        CMD::stStoreItem *item = send.constructTail<CMD::stStoreItem>();
        if(NULL == item)
        {
            break;
        }
        item->itemid = itr->first;
        item->itemcount = itr->second;
        send->count++;
    }
    owner->sendCmdToMe(send.data(), send.size());
	return true;	
}

DWORD UStoreHouse::addItem(DWORD itemid, DWORD itemcount)
{
    return 0;
#if 0
	const pb::item_config::t_item_config* base = tbx::item_config().get_base(itemid);	
	if(NULL == base)
		return false;
	
	DWORD remain_space = 0;
	DWORD store_limit = owner->getStoreLimit();
	DWORD cur_item_count = getItemCount();
	DWORD real_add_count = 0;
	if(store_limit > cur_item_count)
		remain_space = store_limit - cur_item_count;
	if(itemcount > remain_space)
	{
		real_add_count = remain_space;
	}
	else
	{
		real_add_count = itemcount;
	}
		
	addItemInner(itemid,itemcount);

	return real_add_count;	
 #endif
}

void UStoreHouse::addItemInner(DWORD itemid, DWORD itemcount)
{
	auto itr=_mapItems.find(itemid);
	if(itr == _mapItems.end())
	{
		_mapItems.insert(std::make_pair(itemid,itemcount));
	}
	else
	{
		itr->second += itemcount;
	}
}

DWORD UStoreHouse::getItemCount()
{
	DWORD itemcount = 0;
	for(auto itr=_mapItems.begin(); itr!=_mapItems.end(); itr++)
	{
		itemcount += itr->second;
	}
	return itemcount;
}


bool UStoreHouse::hasEnoughSpace(DWORD itemcount)
{
	DWORD remain_space = 0;
	DWORD store_limit = owner->getStoreLimit();
        DWORD cur_item_count = getItemCount();
        if(store_limit > cur_item_count)
                remain_space = store_limit - cur_item_count;
	
	if(remain_space >= itemcount)
		return true;

	return false;
}

bool UStoreHouse::hasEnoughItem(DWORD itemid, DWORD itemcount)
{
	auto itr=_mapItems.find(itemid);
	if(itr == _mapItems.end())
	{
		return false;
	}

	if(itr->second < itemcount)
	{
		return false;
	}

	return true;
}

void UStoreHouse::consumeItem(DWORD itemid, DWORD itemcount)
{
	auto itr=_mapItems.find(itemid);
	if(itr == _mapItems.end())
	{
		return ;
	}

	if(itr->second > itemcount)
	{
		itr->second -= itemcount;
	}	
	
	_mapItems.erase(itemid);
}

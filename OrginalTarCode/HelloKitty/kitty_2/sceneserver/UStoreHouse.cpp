#include "UStoreHouse.h"
#include "tbx.h"
#include "SceneUser.h"
#include "TradeCommand.h"
#include "extractProtoMsg.h"

std::map<DWORD,UStoreHouse::ITEM_FUN> UStoreHouse::s_itemFumMap;
bool UStoreHouse::s_initItemFunFlg = false;

UStoreHouse::UStoreHouse(SceneUser* u)
{
	m_owner = u;
    initItemFun();
}

UStoreHouse::~UStoreHouse()
{

}

void UStoreHouse::save(HelloKittyMsgData::Serialize& binary)
{
	for(auto iter = m_itemMap.begin(); iter != m_itemMap.end(); iter++)
    {
        HelloKittyMsgData::PbStoreItem* item = binary.add_store_items();
        *item = iter->second;
    }
}

void UStoreHouse::load(const HelloKittyMsgData::Serialize& binary)
{
	m_itemMap.clear();
    for(int i=0; i<binary.store_items_size(); i++)
    {
        const HelloKittyMsgData::PbStoreItem& item = binary.store_items(i);
        m_itemMap.insert(std::make_pair(item.itemid(),item));
    }
}

bool UStoreHouse::flushWareHouse()
{
    HelloKittyMsgData::FlushWareHouse message;
    for (auto iter = m_itemMap.begin(); iter != m_itemMap.end(); ++iter)
    {
        HelloKittyMsgData::PbStoreItem *item = message.add_store_items();
        *item = iter->second; 
    }
    std::string ret;
    if(encodeMessage(&message,ret))
    {
        return m_owner->sendCmdToMe(ret.c_str(),ret.size());
    }
	return false;	
}

bool UStoreHouse::addItem(const HelloKittyMsgData::PbStoreItem &item)
{
    const pb::Conf_t_itemInfo *confBase = tbx::itemInfo().get_base(item.itemid());
	if(NULL == confBase)
    {
        Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, item.itemid(),item.itemcount());
		return false;
    }
    return hasEnoughSpace(item.itemcount()) ? addItemInner(item) : false;	
}

bool UStoreHouse::addItemInner(const HelloKittyMsgData::PbStoreItem &item)
{
    if(!item.itemcount())
    {
        return false;
    }
	auto iter = m_itemMap.find(item.itemid());
    if(iter == m_itemMap.end())
    {
        m_itemMap.insert(std::make_pair(item.itemid(),item));
    }
    else
    {
        iter->second.set_itemcount(iter->second.itemcount() + item.itemcount());
    }
    return true;
}

DWORD UStoreHouse::getItemCount()
{
	DWORD itemcount = 0;
	for(auto iter = m_itemMap.begin(); iter != m_itemMap.end(); ++iter)
	{
        itemcount += iter->second.itemcount();
	}
	return itemcount;
}


bool UStoreHouse::hasEnoughSpace(const DWORD itemcount)
{
	DWORD store_limit = m_owner->getStoreLimit();
    DWORD cur_item_count = getItemCount();
    DWORD remain_space = store_limit > cur_item_count ? store_limit > cur_item_count : 0;

    return remain_space >= itemcount;
}

bool UStoreHouse::hasEnoughItem(const DWORD itemid, const DWORD itemcount)
{
	auto iter = m_itemMap.find(itemid);
	if(iter == m_itemMap.end())
	{
		return false;
	}
    return iter->second.itemcount() >= itemcount;
}

bool UStoreHouse::consumeItem(const DWORD itemid, const DWORD itemcount)
{
	auto iter = m_itemMap.find(itemid);
	if(iter == m_itemMap.end() || iter->second.itemcount() < itemcount)
	{
		return false;
	}
    iter->second.set_itemcount(iter->second.itemcount() - itemcount);
    if(!iter->second.itemcount())
    {
        m_itemMap.erase(iter);
    }
    return true;
}

bool UStoreHouse::useItem(const DWORD itemid,const DWORD num)
{
    bool ret = true;
    HelloKittyMsgData::UseItemReturn message;
    message.set_ret(true);

    const pb::Conf_t_itemInfo* base = tbx::itemInfo().get_base(itemid);
    if(!base)
    {
        Fir::logger->debug("使用道具错误 道具不存在 %u",itemid);
        message.set_reason(HelloKittyMsgData::Fail_Item_Illeay);
        ret = false;
    }
    
    if(ret && !consumeItem(itemid,num))
    {
        message.set_reason(HelloKittyMsgData::Fail_Item_Not_Enough);
    }
    
    message.set_ret(ret);
    std::string str;
    encodeMessage(&message,str);
    m_owner->sendCmdToMe(str.c_str(),str.size());
    
    if(!ret)
    {
        return false;
    }
    
    Fir::logger->debug("玩家%s,%lu使用道具%s,%u,%u",m_owner->nickname,m_owner->charid,base->itemInfo->item().c_str(),base->itemInfo->id(),num);
    std::map<DWORD,ITEM_FUN>::iterator iter = s_itemFumMap.find(base->itemInfo->kind());
    if(iter == s_itemFumMap.end())
    {
        Fir::logger->debug("使用道具错误 道具没有注册使用函数 %s,%u",base->itemInfo->item().c_str(),base->itemInfo->id());
        return false;
    }
    return iter->second(m_owner,itemid,num);
}




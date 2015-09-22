#include "UStoreHouse.h"
#include "tbx.h"
#include "SceneUser.h"
#include "TradeCommand.h"
#include "extractProtoMsg.h"
#include "warehouse.pb.h"
#include "atlasManager.h"
#include "itemFunRegister.h"

std::map<DWORD,UStoreHouse::ITEM_FUN> UStoreHouse::s_itemFumMap;
bool UStoreHouse::s_initItemFunFlg = false;

UStoreHouse::UStoreHouse(SceneUser* u)
{
    reset();
	m_owner = u;
    initItemFun();
}

UStoreHouse::~UStoreHouse()
{

}

void UStoreHouse::reset()
{
    m_attrMap.clear();
    m_itemMap.clear();
}

bool UStoreHouse::init(const std::map<DWORD,DWORD> &itemMap)
{
    addOrConsumeItem(itemMap,"新建角色",true);
    return true;
}


void UStoreHouse::save(HelloKittyMsgData::Serialize& binary)
{
    for(auto iter = m_attrMap.begin(); iter != m_attrMap.end(); iter++)
    {
        HelloKittyMsgData::PbStoreItem* item = binary.add_store_items();
        if(item)
        {
            item->set_itemid(iter->first);
            item->set_itemcount(iter->second);
        }
    }
	for(auto iter = m_itemMap.begin(); iter != m_itemMap.end(); iter++)
    {
        HelloKittyMsgData::PbStoreItem* item = binary.add_store_items();
        *item = iter->second;
    }
}

void UStoreHouse::load(const HelloKittyMsgData::Serialize& binary)
{
    for(int index = 0; index < binary.store_items_size(); index++)
    {
        const HelloKittyMsgData::PbStoreItem &item = binary.store_items(index);
        if(item.itemid() > HelloKittyMsgData::Attr_Max)
        {
            m_itemMap.insert(std::make_pair(item.itemid(),item));
        }
        else
        {
            m_attrMap.insert(std::pair<DWORD,DWORD>(item.itemid(),item.itemcount()));
        }
    }
}

bool UStoreHouse::flushWareHouse()
{
    HelloKittyMsgData::AckFlushWareHouse message;
    for (auto iter = m_itemMap.begin(); iter != m_itemMap.end(); ++iter)
    {
        HelloKittyMsgData::PbStoreItem *item = message.add_store_items();
        *item = iter->second; 
    }
    std::string ret;
    encodeMessage(&message,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

bool UStoreHouse::flushItem(const DWORD itemID)
{   
    HelloKittyMsgData::AckUpdateItem updateItem;
    HelloKittyMsgData::PbStoreItem* item = updateItem.mutable_item();
    item->set_itemid(itemID);
    auto iter = m_itemMap.find(itemID);
	if(iter == m_itemMap.end())
	{
        item->set_itemcount(0);
	}
    else
    {
        item->set_itemcount(iter->second.itemcount());
    }
    
    std::string ret;
    encodeMessage(&updateItem,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

bool UStoreHouse::addOrConsumeItem(const std::map<DWORD,DWORD> itemMap,const char *reMark,const bool opAdd,const bool logFlg)
{
    for(auto iter = itemMap.begin();iter != itemMap.end();++iter)
    {
        addOrConsumeItem(iter->first,iter->second,reMark,opAdd,logFlg);
    }
    return true;
}

bool UStoreHouse::addOrConsumeItem(const DWORD itemID,const DWORD num,const char *reMark,const bool opAdd,const bool logFlg)
{
    const pb::Conf_t_itemInfo *confBase = tbx::itemInfo().get_base(itemID);
	if(NULL == confBase)
    {
        Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__,itemID,num);
		return false;
    }
    bool ret = false;
    DWORD oldNum = 0,newNum = num;
    if(itemID < HelloKittyMsgData::Attr_Max)
    {
        oldNum = m_attrMap.find(itemID) == m_attrMap.end() ? 0 : m_attrMap[itemID];
        ret = opAttrVal(HelloKittyMsgData::AttrType(itemID),num,opAdd);
        newNum = m_attrMap.find(itemID) == m_attrMap.end() ? 0 : m_attrMap[itemID];
        if(ret)
        {
            m_owner->updateAttrVal(HelloKittyMsgData::AttrType(itemID),m_attrMap[itemID]);
        }
    }
    else if(confBase->itemInfo->kind() == Item_Type_Dress)
    {
        if(opAdd)
        {
            m_owner->m_dressManager.addDressByItem(itemID);
        }
    }
    else if(confBase->itemInfo->kind() == Item_Type_Paper)
    {
        if(opAdd)
        {
            m_owner->m_paperManager.addPaperByItem(itemID);
        }
    }
    else
    {
        oldNum = m_itemMap.find(itemID) == m_itemMap.end() ? 0 : m_itemMap[itemID].itemcount();
        ret = addOrConsumeItem(itemID,num,opAdd);
        newNum = m_itemMap.find(itemID) == m_itemMap.end() ? 0 : m_itemMap[itemID].itemcount();
        if(ret)
        {
            flushItem(itemID);
        }
    }
    if(ret && logFlg)
    {
        Fir::logger->debug("[%s道具(%u)]:%s,%lu,%s,%u,%u,%u",opAdd ? "增加" : "消耗",itemID,m_owner->nickname,m_owner->charid,reMark,oldNum,num,newNum);
    }
    return ret;
}

bool UStoreHouse::checkAttr(const HelloKittyMsgData::AttrType &attrID,const DWORD value)
{
    if(m_attrMap.find(attrID) == m_attrMap.end() || m_attrMap[attrID] < value)
    {
        return false;
    }
    return true;
}

DWORD UStoreHouse::getAttr(const HelloKittyMsgData::AttrType &attrID)
{
    return m_attrMap.find(attrID) == m_attrMap.end() ? 0 : m_attrMap[attrID];
}

bool UStoreHouse::opAttrVal(const HelloKittyMsgData::AttrType &attrID,const DWORD value,const bool opAdd)
{
    bool ret = true;
    if(opAdd)
    {
        if(m_attrMap.find(attrID) == m_attrMap.end())
        {
            m_attrMap.insert(std::pair<DWORD,DWORD>(attrID,value));
        }
        else
        {
            m_attrMap[attrID] += value;
        }
        targetTaskOrAchieve(attrID,m_attrMap[attrID]);
    }
    else
    {
        if(!checkAttr(attrID,value))
        {
            ret = false;
        }
        else
        {
            m_attrMap[attrID] -= value;
        }
    }
    return ret;
}

bool UStoreHouse::addOrConsumeItem(const DWORD itemID,const DWORD num,const bool opAdd)
{
    bool ret = true;
	auto iter = m_itemMap.find(itemID);
    if(opAdd)
    {
        if(!hasEnoughSpace(itemID,num))
        {
            return false;
        }
        if(iter == m_itemMap.end())
        {
            HelloKittyMsgData::PbStoreItem temp;
            temp.set_itemid(itemID);
            temp.set_itemcount(num);
            m_itemMap.insert(std::make_pair(itemID,temp));
        }
        else
        {
            iter->second.set_itemcount(iter->second.itemcount() + num);
        }
    }
    else
    {
        if(iter == m_itemMap.end() || iter->second.itemcount() < num)
        {
            ret = false;
        }
        else
        {
            iter->second.set_itemcount(iter->second.itemcount() - num);
        }
        if(!iter->second.itemcount())
        {
            m_itemMap.erase(iter);
        }
    }
    return ret;
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

bool UStoreHouse::hasEnoughSpace(const DWORD itemID,const DWORD itemcount)
{
    const pb::Conf_t_itemInfo *confBase = tbx::itemInfo().get_base(itemID);
	if(NULL == confBase)
    {
        Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__,itemID,itemcount);
		return false;
    }
    if(itemID <= HelloKittyMsgData::Attr_Max || capSpace(confBase->itemInfo->kind()))
    {
        return true;
    }
	DWORD store_limit = m_owner->getStoreLimit();
    DWORD cur_item_count = getItemCount();
    DWORD remain_space = store_limit > cur_item_count ? store_limit - cur_item_count : 0;
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

bool UStoreHouse::capSpace(const DWORD itemType)
{
    if(itemType == Item_Type_Money || itemType == Item_Type_Dress || itemType == Item_Type_Paper)
    {
        return true;
    }
    return false;
}

bool UStoreHouse::hasEnoughSpace(const std::map<DWORD,DWORD>&itemMap)
{
    DWORD needSpace = 0;
    for(auto iter = itemMap.begin();iter != itemMap.end();++iter)
    {
        const pb::Conf_t_itemInfo *confBase = tbx::itemInfo().get_base(iter->first);
        if(NULL == confBase)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__,iter->first,iter->second);
            return false;
        }
        if(iter->first <= HelloKittyMsgData::Attr_Max || capSpace(confBase->itemInfo->kind()))
        {
            continue;
        }
        needSpace += iter->second;
    }
	DWORD store_limit = m_owner->getStoreLimit();
    DWORD cur_item_count = getItemCount();
    DWORD remain_space = store_limit > cur_item_count ? store_limit - cur_item_count : 0;
    return remain_space >= needSpace;
}

bool UStoreHouse::sallSystem(const DWORD itemid,const DWORD num)
{
    const pb::Conf_t_itemInfo* base = tbx::itemInfo().get_base(itemid);
    if(!base)
    {
        Fir::logger->debug("[出售道具错误] 道具不存在 %u",itemid);
        return false;
    }
    DWORD price = SALL_SYSTEM_PRICE * num; 
    if(!addOrConsumeItem(itemid,num,"出售道具给系统",true))
    {
        return false;
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"出售道具给系统(%u,%u)",itemid,num);
    return addOrConsumeItem(HelloKittyMsgData::Attr_Gold,price,temp,false);
}

bool UStoreHouse::targetTaskOrAchieve(const HelloKittyMsgData::AttrType &attrID,const DWORD value)
{
    HelloKittyMsgData::DailyData *dailyData = m_owner->charbin.mutable_dailydata();
    if(!dailyData)
    {
        return false;
    }
    
    bool target = true;
    TaskArgue arg(Target_Add_Source),argDaily(Target_Add_Source);
    switch(attrID)
    {
        case HelloKittyMsgData::Attr_Gold:
            {
                arg.attrID = Attr_Money_Gold;
                arg.key = Attr_Money_Gold;
                arg.value = value; 

                argDaily.attrID = Attr_Money_Gold;
                argDaily.key = Attr_Add_Money_Gold;
                argDaily.value = dailyData->addgold();
            }
            break;
        case HelloKittyMsgData::Attr_Gem:
            {
                arg.attrID = Attr_Money_Gem;
                arg.key = Attr_Money_Gem;
                arg.value = value;

                argDaily.attrID = Attr_Add_Money_Gem;
                argDaily.key = Attr_Add_Money_Gem;
                argDaily.value = dailyData->addgem();
            }
            break;
        case HelloKittyMsgData::Attr_Exp:
            {
                arg.attrID = Attr_Visitor;
                arg.key = Attr_Visitor;
                arg.value = value;

                argDaily.attrID = Attr_Visitor;
                argDaily.key = Attr_Visitor;
                argDaily.value = dailyData->addexp();
                m_owner->upgrade();
            }
            break;
        case HelloKittyMsgData::Attr_Happy_Val:
            {
                arg.attrID = Attr_Happy_val;
                arg.key = Attr_Happy_val;
                arg.value = value;
                
                argDaily.attrID = Attr_Happy_val;
                argDaily.key = Attr_Add_Happy_Val;
                argDaily.key = dailyData->addhappy();
                m_owner->changeHappyData();
            }
            break;
        case HelloKittyMsgData::Attr_Friend_Val:
            {
                target = false;
            }
            break;
        case HelloKittyMsgData::Attr_Carnival_Val:
            {
                target = false;
            }
            break;
        case HelloKittyMsgData::Attr_Sweet_Val:
            {
                target = false;
            }
            break;
        case HelloKittyMsgData::Attr_Sall_Grid_Val:
            {
                target = false;
            }
        default:
            {
                target = false;
                break;
            }
    }
    if(target)
    {
        m_owner->m_taskManager.target(arg);
        m_owner->m_taskManager.target(argDaily);
    }
    return true;
}




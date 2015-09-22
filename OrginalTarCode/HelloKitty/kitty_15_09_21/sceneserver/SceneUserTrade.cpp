#include "SceneUser.h"
#include "SceneUserManager.h"
#include "SceneToOtherManager.h"
#include "SceneCommand.h"
#include "tbx.h"

bool SceneUser::deductPrice(const CMD::SCENE::t_UserPurchasePrice *cmd)
{
    CMD::SCENE::t_UserPurchaseUnlockeItem unLockItem;
    unLockItem.reqcharid = cmd->reqcharid;
    unLockItem.ackcharid = cmd->ackcharid;
    strncpy(unLockItem.name,charbase.account,sizeof(unLockItem.name));
    unLockItem.cellID = cmd->cellID;
    unLockItem.deductFlg = true;
    if(!m_store_house.checkAttr(HelloKittyMsgData::Attr_Gold,cmd->price))
    {
        opErrorReturn(HelloKittyMsgData::Gold_Not_Enough);
        unLockItem.deductFlg = false;
    }
    if(!m_store_house.hasEnoughSpace(cmd->item,cmd->num))
    {
        opErrorReturn(HelloKittyMsgData::WareHouse_Is_Full);
        unLockItem.deductFlg = false;
    }
    
    if(unLockItem.deductFlg)
    {
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"购买道具扣除(%lu,%u,%u)",cmd->ackcharid,cmd->price,cmd->num);
        m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,cmd->price,temp,false);
    }
    SceneUser* sceneUser = SceneUserManager::getMe().getUserByID(cmd->ackcharid);
    if(sceneUser)
    {
        sceneUser->m_trade.purchaseUnLockItem(&unLockItem);
    }
    else
    {
        SceneClientToOtherManager::getMe().SendMsgToOtherSceneCharID(cmd->ackcharid,&unLockItem,sizeof(unLockItem));
    }
    return true;
}

bool SceneUser::purchaseAddItem(const CMD::SCENE::t_UserPurchaseShiftItem *cmd)
{
    bool ret = true;
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"交易获得");
    if(!m_store_house.addOrConsumeItem(cmd->itemID,cmd->itemNum,temp,true))
    {
        std::map<DWORD,DWORD> itemMap;
        itemMap.insert(std::pair<DWORD,DWORD>(cmd->itemID,cmd->itemNum));
        EmailManager::sendEmailBySys(nickname,"购买道具","购买道具",itemMap);
        ret = false;
    }
    Fir::logger->debug("[购买道具] %s (%u,%u)",ret ? "包裹" : "邮件",cmd->itemID,cmd->itemNum);
    return ret;
}

bool SceneUser::purchaseItem(const DWORD itemid,const DWORD num)
{
    const pb::Conf_t_itemInfo *confBase = tbx::itemInfo().get_base(itemid);
    if(!confBase)
    {
        return false;
    }
    if(!m_store_house.hasEnoughSpace(itemid,num))
    {
        return opErrorReturn(HelloKittyMsgData::WareHouse_Is_Full);
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"购买商城道具(%u,%u)",itemid,num);
    if(!m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,confBase->itemInfo->shopprice() * num,temp,false))
    {
        return opErrorReturn(HelloKittyMsgData::Gem_Not_Enough);
    }
    bzero(temp,sizeof(temp));
    snprintf(temp,sizeof(temp),"商城购买");
    return m_store_house.addOrConsumeItem(itemid,num,temp,true);
}


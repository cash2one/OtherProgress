#include "TradeCmdDispatcher.h"
#include "SceneUser.h"
#include "SceneUserManager.h"
#include "TradeCommand.h"
#include "serialize.pb.h"
#include "extractProtoMsg.h"
#include "CharBase.h"
#include "SceneToOtherManager.h"
#include "SceneTaskManager.h"

bool TradeCmdHandle::addItemInWareHouse(SceneUser* u, const HelloKittyMsgData::ReqAddItem* cmd)
{
	if (!u || !cmd) 
    {
        return false;
    }
    
    HelloKittyMsgData::AckAddItemReturn message;
    bool flg = u->m_store_house.addOrConsumeItem(cmd->item().itemid(),cmd->item().itemcount(),"客户端请求给予",true);
    message.set_ret(flg);
    
    std::string ret;
    encodeMessage(&message,ret);
    return u->sendCmdToMe(ret.c_str(),ret.size());
}

bool TradeCmdHandle::requireStoreInfo(SceneUser* u, const HelloKittyMsgData::ReqStoreItem* cmd) 
{
	if (!u || !cmd)
    {
        return false;
    }
    SceneUser *temp = NULL;
    if(cmd->charid() == u->charid || cmd->charid() == 0)
    {
        temp = u;
    }
    else
    {
        temp = SceneUserManager::getMe().getUserByID(cmd->charid());
        if(!temp)
        {
            CMD::SCENE::t_UserReqSall reqSall;
            reqSall.reqcharid = u->charid;
            reqSall.ackcharid = cmd->charid();
            reqSall.reqGatewayID = u->getGate() ? u->getGate()->getID() : 0;
            return SceneClientToOtherManager::getMe().SendMsgToOtherSceneCharID(cmd->charid(),&reqSall,sizeof(reqSall));
        }
    }
    if(!temp)
    {
        return false;
    }
    if(cmd->type() == HelloKittyMsgData::Store_Type_Ware_House)
    {
        return	temp->m_store_house.flushWareHouse();
    }
    else if(cmd->type() == HelloKittyMsgData::Store_Type_Build)
    {
        return temp->m_buildManager.flushAllWareHouseBuild();
    }
    else if(cmd->type() == HelloKittyMsgData::Store_Type_Sale)
    {
        if(temp == u)
        {
            return temp->m_trade.flushSaleBooth();
        }
        HelloKittyMsgData::AckFlushSaleBooth ackFlush;
        ackFlush.set_charid(cmd->charid());
        temp->m_trade.flushSaleBooth(ackFlush);
        std::string ret;
        encodeMessage(&ackFlush,ret);
        return SceneTaskManager::getMe().broadcastUserCmdToGateway(u->charid,ret.c_str(),ret.size());
    }
    return false;
}

bool TradeCmdHandle::reqPayGrid(SceneUser* u, const HelloKittyMsgData::ReqPayGrid* cmd)
{
    if(!u || !cmd)
    {
        return false;
    }
    if(!u->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,20,"购买格子",false))
    {
        u->opErrorReturn(HelloKittyMsgData::Gem_Not_Enough);
        return false;
    }
    u->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Ware_Grid_Val,cmd->grid(),"开放格子",true);
    return true;
}

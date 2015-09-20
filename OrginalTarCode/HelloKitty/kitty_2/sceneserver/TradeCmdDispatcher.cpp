#include "TradeCmdDispatcher.h"
#include "SceneUser.h"
#include "SceneUserManager.h"
#include "TradeCommand.h"
#include "AllZoneCommand.h"
#include "serialize.pb.h"
#include "extractProtoMsg.h"

bool TradeCmdHandle::useItem(SceneUser* u, const HelloKittyMsgData::UseItem* cmd)
{
	if (!u || !cmd) 
    {
        return false;
    }
    return u->_store_house.useItem(cmd->itemid(),cmd->num());
}

bool TradeCmdHandle::addItemInWareHouse(SceneUser* u, const HelloKittyMsgData::RequireAddItem* cmd)
{
	if (!u || !cmd) 
    {
        return false;
    }
    
    HelloKittyMsgData::AddItemReturn message;
    bool flg = u->_store_house.addItem(cmd->item());
    message.set_ret(flg);
    
    std::string ret;
    if(encodeMessage(&message,ret))
    {
        return u->sendCmdToMe(ret.c_str(),ret.size());
    }
    return false;
}

bool TradeCmdHandle::requireStoreInfo(SceneUser* u, const HelloKittyMsgData::RequireStoreItem* cmd) 
{
	if (!u || !cmd)
    {
        return false;
    }
    if(cmd->type() == HelloKittyMsgData::Store_Type_Ware_House)
    {
        return	u->_store_house.flushWareHouse();
    }
    else if(cmd->type() == HelloKittyMsgData::Store_Type_Sale)
    {
        return u->_trade.flushSaleBooth();
    }
    return false;
}

bool TradeCmdHandle::requireSallAddItem(SceneUser* u, const HelloKittyMsgData::RequireSallPutItem *cmd)
{
	if (!u || !cmd)
    {
        return false;
    }
	return u->_trade.addSallItem(cmd);
}

#if 0
bool TradeCmdHandle::requireSellPaper(SceneUser* u, const HelloKittyMsgData::RequirSellPaper *cmd)
{
	if (!u || !cmd)
    {
        return false;
    }
	return u->_trade.addSallItem(cmd);
}
#endif

bool TradeCmdHandle::returnSellPaper(SceneUser* u, const HelloKittyMsgData::ReturnSellPaper *cmd)
{
	if (!u || !cmd)
    {
        return false;
    }
	return u->_trade.returnSellPaper(cmd);
}

#if 0
bool TradeCmdHandle::req_other_player_salecells(SceneUser* u, const CMD::stReqOtherPlayerSaleCells_CS* cmd, DWORD nCmdLen)
{
	if (!u || !cmd) return false;

	CMD::ALLZONE::t_Super2AllZone_ReqSomePlayerSaleCells sendallzone;
	sendallzone.sceneid = SceneService::getMe().getZoneID();
	sendallzone.charid = u->charbase.charid;
	SceneService::getMe().sendCmdToAllZone(&sendallzone, sizeof(sendallzone));
	return true;	
}
#endif

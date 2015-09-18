#include "TradeCmdDispatcher.h"
#include "SceneUser.h"
#include "SceneUserManager.h"
#include "TradeCommand.h"
#include "AllZoneCommand.h"

bool TradeCmdHandle::req_itemconfig(SceneUser* u, const CMD::stReqItemconfig_CS* cmd, DWORD nCmdLen)
{
	if (!u) return false;

        return u->_trade.req_itemconfig();	
}

bool TradeCmdHandle::test_add_items(SceneUser* u, const CMD::stTestAddItems_CS* cmd, DWORD nCmdLen)
{
	if (!u || !cmd) return false;

	if(!u->_store_house.hasEnoughSpace(cmd->itemcount))
	{
		CMD::stTestAddItems_SC send;	
		u->sendCmdToMe(&send, sizeof(send));	
		return true;
	}
	
	u->_store_house.addItem(cmd->itemid,cmd->itemcount);

	CMD::stTestAddItems_SC send;
	u->sendCmdToMe(&send, sizeof(send));
	return true;
}

bool TradeCmdHandle::req_item_list(SceneUser* u, const CMD::stReqItemList_CS* cmd, DWORD nCmdLen)
{
	if (!u || !cmd) return false;

	return	u->_store_house.req_item_list();
}

bool TradeCmdHandle::req_massive_info(SceneUser* u, const CMD::stReqMassiveInfo_CS* cmd, DWORD nCmdLen)
{
	if (!u || !cmd) return false;

	CMD::stRetMassiveInfo_SC send;
	send.store_limit = u->charbase.store_limit;
	send.sale_grid_count = u->charbase.sale_grid_count;	
	u->sendCmdToMe(&send, sizeof(send));
	
	return true;
}

bool TradeCmdHandle::req_sale_cells(SceneUser* u, const CMD::stReqSaleCells_CS* cmd, DWORD nCmdLen)
{
	if (!u || !cmd) return false;

	return u->_trade.req_sale_cells();
}

bool TradeCmdHandle::req_salecell_putitem(SceneUser* u, const CMD::stReqSaleCellPutItem_CS* cmd, DWORD nCmdLen)
{
	if (!u || !cmd) return false;

	return u->_trade.req_salecell_putitem(cmd->cellid,cmd->itemid,cmd->itemcount);
}

bool TradeCmdHandle::req_other_player_salecells(SceneUser* u, const CMD::stReqOtherPlayerSaleCells_CS* cmd, DWORD nCmdLen)
{
	if (!u || !cmd) return false;

	CMD::ALLZONE::t_Super2AllZone_ReqSomePlayerSaleCells sendallzone;
	sendallzone.sceneid = SceneService::getMe().getZoneID();
	sendallzone.charid = u->charbase.charid;
	SceneService::getMe().sendCmdToAllZone(&sendallzone, sizeof(sendallzone));
	return true;	
}

#ifndef _TRADE_CMD_DISPATCHER
#define _TRADE_CMD_DISPATCHER

#include <string.h>
#include "Fir.h"
#include "Command.h"
#include "SceneServer.h"
#include "dispatcher.h"
#include "zCmdHandle.h"
#include "TradeCommand.h"
#include "SceneTask.h"

class SceneUser;

class TradeCmdHandle : public zCmdHandle
{
    public:
        TradeCmdHandle()
        {
        }
        
        void init()
        {
            USER_DISPATCHER_REG(CMD::stReqItemconfig_CS,TradeCmdHandle::req_itemconfig);
			USER_DISPATCHER_REG(CMD::stTestAddItems_CS,TradeCmdHandle::test_add_items);
			USER_DISPATCHER_REG(CMD::stReqItemList_CS,TradeCmdHandle::req_item_list);
			USER_DISPATCHER_REG(CMD::stReqMassiveInfo_CS,TradeCmdHandle::req_massive_info);
			USER_DISPATCHER_REG(CMD::stReqSaleCells_CS,TradeCmdHandle::req_sale_cells);
			USER_DISPATCHER_REG(CMD::stReqSaleCellPutItem_CS,TradeCmdHandle::req_salecell_putitem);
			USER_DISPATCHER_REG(CMD::stReqOtherPlayerSaleCells_CS,TradeCmdHandle::req_other_player_salecells);
        }
        
        bool req_itemconfig(SceneUser* u, const CMD::stReqItemconfig_CS* cmd, DWORD nCmdLen);
		bool test_add_items(SceneUser* u, const CMD::stTestAddItems_CS* cmd, DWORD nCmdLen);
		bool req_item_list(SceneUser* u, const CMD::stReqItemList_CS* cmd, DWORD nCmdLen);
		bool req_massive_info(SceneUser* u, const CMD::stReqMassiveInfo_CS* cmd, DWORD nCmdLen);
		bool req_sale_cells(SceneUser* u, const CMD::stReqSaleCells_CS* cmd, DWORD nCmdLen);
		bool req_salecell_putitem(SceneUser* u, const CMD::stReqSaleCellPutItem_CS* cmd, DWORD nCmdLen);
		bool req_other_player_salecells(SceneUser* u, const CMD::stReqOtherPlayerSaleCells_CS* cmd, DWORD nCmdLen);
};

#endif


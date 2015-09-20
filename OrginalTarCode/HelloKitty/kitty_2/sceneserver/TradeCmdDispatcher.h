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
#include "serialize.pb.h"
#include "item.pb.h"

class SceneUser;

class TradeCmdHandle : public zCmdHandle
{
    public:
        TradeCmdHandle()
        {
        }
        
        void init()
        {
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::RequireAddItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::RequireAddItem>::ProtoFunction(this,&TradeCmdHandle::addItemInWareHouse));
            
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::RequireStoreItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::RequireStoreItem>::ProtoFunction(this,&TradeCmdHandle::requireStoreInfo));
            
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::RequireSallPutItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::RequireSallPutItem>::ProtoFunction(this,&TradeCmdHandle::requireSallAddItem));
           
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReturnSellPaper>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReturnSellPaper>::ProtoFunction(this,&TradeCmdHandle::returnSellPaper));
        
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::UseItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::UseItem>::ProtoFunction(this,&TradeCmdHandle::useItem));
       
        }
        
        //使用道具
        bool useItem(SceneUser* u, const HelloKittyMsgData::UseItem* cmd);
        //请求仓库添加道具
        bool addItemInWareHouse(SceneUser* u, const HelloKittyMsgData::RequireAddItem* cmd);
        //请求道具容器信息
        bool requireStoreInfo(SceneUser* u, const HelloKittyMsgData::RequireStoreItem* cmd);
        //请求摊位添加道具
        bool requireSallAddItem(SceneUser* u, const HelloKittyMsgData::RequireSallPutItem *cmd);
        //请求寄售报纸信息
        bool requireSellPaper(SceneUser* u, const HelloKittyMsgData::RequirSellPaper *cmd);
        //全服区返回寄售报纸信息(一天只会一次)
        bool returnSellPaper(SceneUser* u, const HelloKittyMsgData::ReturnSellPaper *cmd);
#if 0
		bool req_other_player_salecells(SceneUser* u, const CMD::stReqOtherPlayerSaleCells_CS* cmd, DWORD nCmdLen);
#endif
};

#endif


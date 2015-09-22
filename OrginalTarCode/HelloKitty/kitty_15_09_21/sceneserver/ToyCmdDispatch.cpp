#include "TradeCmdDispatcher.h"
#include "SceneUser.h"

bool TradeCmdHandle::reqToy(SceneUser* u, const HelloKittyMsgData::ReqOpToy* cmd)
{
	if (!u || !cmd) 
    {
        return false;
    }
    if(cmd->optype() == HelloKittyMsgData::OTT_Req)
    {
        return u->flushToy();
    }
    else if(cmd->optype() == HelloKittyMsgData::OTT_Rand)
    {
        return u->randToy();
    }
    return false;
}

#include "sceneCmdDispatch.h"
#include "TradeMgr.h"

bool ZoneSceneCmdHandle::flushCeil(ZoneTask* task,const HelloKittyMsgData::PbSaleCeilFlushZone *meaasge)
{
    TradeMgr::getMe().flushCeil(task->getID(),meaasge);
    return true;
}

bool ZoneSceneCmdHandle::requirePaper(ZoneTask* task,const HelloKittyMsgData::RequirSellPaper *meaasge)
{
    TradeMgr::getMe().flushCellPaper(task->getID(),meaasge->sceneid(),meaasge->charid());
    return true;
}

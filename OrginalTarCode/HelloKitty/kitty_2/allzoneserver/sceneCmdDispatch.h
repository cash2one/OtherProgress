#ifndef SCENE_CMD_DISPATCH_H
#define SCENE_CMD_DISPATCH_H

//所有场景发过来的proto消息处理中心


#include "dispatcher.h"
#include "trade.pb.h"
#include "zCmdHandle.h"
#include "ZoneTask.h"

class ZoneSceneCmdHandle : public zCmdHandle
{
    public:
        ZoneSceneCmdHandle()
        {
        }

        void init()
        {
            ZoneTask::s_zone_scene_cmd_dispatch.func_reg<HelloKittyMsgData::PbSaleCeilFlushZone>(ProtoCmdCallback<ZoneTask,HelloKittyMsgData::PbSaleCeilFlushZone>::ProtoFunction(this, &ZoneSceneCmdHandle::flushCeil));
           
            ZoneTask::s_zone_scene_cmd_dispatch.func_reg<HelloKittyMsgData::RequirSellPaper>(ProtoCmdCallback<ZoneTask,HelloKittyMsgData::RequirSellPaper>::ProtoFunction(this,&ZoneSceneCmdHandle::requirePaper));
        }
        
        //刷新某个摊位cell
        bool flushCeil(ZoneTask* task,const HelloKittyMsgData::PbSaleCeilFlushZone *meaasge);
        //请求paper
        bool requirePaper(ZoneTask* task,const HelloKittyMsgData::RequirSellPaper *meaasge);
};

#endif

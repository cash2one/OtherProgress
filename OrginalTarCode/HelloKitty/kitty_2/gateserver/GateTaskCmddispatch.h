#ifndef GATE_TASK_CMD_DISPATCH_H
#define GATE_TASK_CMD_DISPATCH_H

#include <string.h>
#include "Fir.h"
#include "dispatcher.h"
#include "zCmdHandle.h"
#include "GatewayTask.h"
#include "login.pb.h"

class GateTaskCmdHandle : public zCmdHandle
{
    public:
        GateTaskCmdHandle()
        {
        }

        virtual void init()
        {
            GatewayTask::gate_task_cmd_dispatcher.func_reg<HelloKittyMsgData::ClientRequestVersion>(ProtoCmdCallback<GatewayTask,HelloKittyMsgData::ClientRequestVersion>::ProtoFunction(this, &GateTaskCmdHandle::vertifyVresion));
            
            GatewayTask::gate_task_cmd_dispatcher.func_reg<HelloKittyMsgData::LoginGateway>(ProtoCmdCallback<GatewayTask,HelloKittyMsgData::LoginGateway>::ProtoFunction(this, &GateTaskCmdHandle::verifyACCID));
        }
        //验证版本号
        bool vertifyVresion(GatewayTask *task,const HelloKittyMsgData::ClientRequestVersion *message);
        //验证accid
        bool verifyACCID(GatewayTask *task,const HelloKittyMsgData::LoginGateway *message);
};

#endif
          

#include "GateTaskCmddispatch.h"

bool GateTaskCmdHandle::vertifyVresion(GatewayTask *task,const HelloKittyMsgData::ClientRequestVersion *message)
{
    if(!task || !message)
    {
        return false;
    }

    return task->verifyVersion(message);
}

bool GateTaskCmdHandle::verifyACCID(GatewayTask *task,const HelloKittyMsgData::LoginGateway *message)
{
    if(!task || !message) 
    {
        return false;
    }

    return task->verifyACCID(message);
}


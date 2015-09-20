/**
 * \file
 * \version  $Id: LoginCmdDispatcher.cpp 64 2013-04-23 02:05:08Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义用户登录相关命令处理文件，注册给dispatcher
 *
 */

#include "LoginCmdDispatcher.h"

bool LoginCmdHandle::setVersion(LoginTask* task, const HelloKittyMsgData::ClientRequestVersion* message)
{
    if(task && message)
    {
        task->setClientVersion(message->clientversion());
        Fir::logger->debug("LoginCmdHandle::setVersion %u",message->clientversion());
        std::string ret;
        if(encodeMessage(message,ret))
        {
            task->sendCmd(ret.c_str(), ret.size());
        }   
		return true;
    }
    return false;

}

bool LoginCmdHandle::requireLogin(LoginTask* task,const HelloKittyMsgData::ClientRequestLogin *message)
{
    if(!task || !message)
    {
        return false;
    }
    
    task->requireLogin(message);
    return true;
}


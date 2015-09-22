#include "GmCmdDipatcher.h"
#include "SceneUser.h"
#include "dataManager.h"
#include "SuperCommand.h"
#include "SceneServer.h"
#include "TimeTick.h"
#include "TradeCmdDispatcher.h"

bool GMCmdHandle::s_initFlg = false;
std::map<std::string,GMCmdHandle::GmFun> GMCmdHandle::s_gmFunMap;

bool GMCmdHandle::reqGm(SceneUser* user,const HelloKittyMsgData::ReqGM *cmd)
{
    if(!user || !cmd)
    {
        return false;
    }

    std::vector<std::string> commandVec;
    pb::parseTagString(cmd->command()," ",commandVec);
    if(commandVec.empty())
    {
        return false;
    }

    auto iter = s_gmFunMap.find(commandVec[0]);
    if(iter == s_gmFunMap.end())
    {
        Fir::logger->debug("[GM命令] 命令没有注册(%lu,%s,%s)",user->charid,user->nickname,commandVec[0].c_str());
        return false;
    }

    bool ret = iter->second(user,commandVec);
    Fir::logger->debug("[GM命令] 执行命令%s(%lu,%s,%s)",ret ? "成功" : "失败",user->charid,user->nickname,commandVec[0].c_str());
    return ret;
}

void GMCmdHandle::initGmFunMap()
{
    if(s_initFlg)
    {
        return;
    }
    s_initFlg = true;
    s_gmFunMap.insert(std::pair<std::string,GmFun>("additem",GMCmdHandle::addItem));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("level",GMCmdHandle::changeLevel));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("pid",GMCmdHandle::getPid));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("buildlevel",GMCmdHandle::buildLevel));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("addatlas",GMCmdHandle::addAtlas));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("delatlas",GMCmdHandle::deleteAtlas));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("clearatlas",GMCmdHandle::clearAtlas));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("finishtask",GMCmdHandle::finishTask));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("opentask",GMCmdHandle::openTask));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("happyday",GMCmdHandle::changeHappyDay));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("finishachieve",GMCmdHandle::finishAchieve));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("time",GMCmdHandle::changeTime));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("now",GMCmdHandle::nowTime));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("clear",GMCmdHandle::clearUserData));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("paper",GMCmdHandle::randPaper));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("addvistor",GMCmdHandle::addVistor));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("addfriend",GMCmdHandle::addfriend));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("delfriend",GMCmdHandle::delfriend));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("getfriendlist",GMCmdHandle::getfriendlist)); 
    s_gmFunMap.insert(std::pair<std::string,GmFun>("getfanslist",GMCmdHandle::getfanslist));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("getotherlist",GMCmdHandle::getotherlist)); 
    s_gmFunMap.insert(std::pair<std::string,GmFun>("cleardress",GMCmdHandle::clearDress));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("reward",GMCmdHandle::rewardBuild));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("emailsys",GMCmdHandle::sendEmail));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("clearpaper",GMCmdHandle::clearPaper));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("god",GMCmdHandle::god));
    s_gmFunMap.insert(std::pair<std::string,GmFun>("clearday",GMCmdHandle::resetDailyData));
}

bool GMCmdHandle::addItem(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 3)
    {
        return false;
    }
    DWORD itemID = 0,value = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        itemID = atol(commandVec[1].c_str());
        command += commandVec[2];
        value = atol(commandVec[2].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"GM获得(%lu,%s)",user->charid,user->nickname);
    return user->m_store_house.addOrConsumeItem(itemID,value,temp,true);
}

bool GMCmdHandle::changeLevel(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    DWORD value = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        value = atol(commandVec[1].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }

    return user->changeLevel(value);
}

bool GMCmdHandle::getPid(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user)
    {
        return false;
    }
    DWORD pid = getpid();

    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"前服务器进程为:%u",pid);
    HelloKittyMsgData::AckGM ack;
    ack.set_ret(temp);

    std::string ret;
    encodeMessage(&ack,ret);
    user->sendCmdToMe(ret.c_str(),ret.size());
    Fir::logger->debug("[GM命令] 当前服务器进程为 %u(%lu,%s)",pid,user->charid,user->nickname);
    return true;
}

bool GMCmdHandle::buildLevel(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 3)
    {
        return false;
    }
    DWORD type = 0,value = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        type = atol(commandVec[1].c_str());
        command += commandVec[2];
        value = atol(commandVec[2].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    return user->m_buildManager.gmUpGrade(type,value);
}

bool GMCmdHandle::addAtlas(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    DWORD type = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        type = atol(commandVec[1].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    return user->m_atlasManager.addAtlas(type);
}

bool GMCmdHandle::deleteAtlas(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    DWORD type = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        type = atol(commandVec[1].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    return user->m_atlasManager.delAtlas(type);
}

bool GMCmdHandle::clearAtlas(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 1)
    {
        return false;
    }
    return user->m_atlasManager.clearAtlas();
}

bool GMCmdHandle::finishTask(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    DWORD taskID = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        taskID = atol(commandVec[1].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    return user->m_taskManager.finishTask(taskID);
}

bool GMCmdHandle::openTask(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    DWORD taskID = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        taskID = atol(commandVec[1].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    return user->m_taskManager.openTask(taskID,true);
}

bool GMCmdHandle::changeHappyDay(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 3)
    {
        return false;
    }
    DWORD happyTypeVal = 0,happyDay = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        happyTypeVal = atol(commandVec[1].c_str());
        command += commandVec[2];
        happyDay = atol(commandVec[2].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    return user->changeHappyDataGm(happyTypeVal,happyDay);
}

bool GMCmdHandle::finishAchieve(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    DWORD achieveID = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        achieveID = atol(commandVec[1].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    return user->m_achievementManager.finishAchieve(achieveID);
}

bool GMCmdHandle::changeTime(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    std::string timeStr; 
    std::string command;
    try
    {
        command = commandVec[1];
        timeStr = commandVec[1];
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }

    CMD::SUPER::t_ChangeGameTime changTime;
    strncpy(changTime.time,timeStr.c_str(),sizeof(changTime.time));
    std::string ret;
    encodeMessage(&changTime,sizeof(changTime),ret);
    return SceneService::getMe().sendCmdToSuperServer(ret.c_str(),ret.size());
}

bool GMCmdHandle::nowTime(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user)
    {
        return false;
    }

    std::string time = SceneTimeTick::currentTime.toString(); 
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"前服务器时间为:%s",time.c_str());
    HelloKittyMsgData::AckGM ack;
    ack.set_ret(temp);

    Fir::logger->debug("[GM命令] 当前服务器时间为 %s(%lu,%s)",time.c_str(),user->charid,user->nickname);
    std::string ret;
    encodeMessage(&ack,ret);
    return user->sendCmdToMe(ret.c_str(),ret.size());
}

bool GMCmdHandle::clearUserData(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user)
    {
        return false;
    }
    user->resetAllData(); 
    return true;
}

bool GMCmdHandle::randPaper(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    DWORD value = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        value = atol(commandVec[1].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    user->m_trade.requireCellPaper(value); 
    return true; 
}

bool GMCmdHandle::addVistor(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 2)
    {
        return false;
    }
    DWORD value = 0;
    std::string command;
    try
    {
        command = commandVec[1];
        value = atol(commandVec[1].c_str());
    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    user->addVertiseOther(value); 
    return true;
}

bool GMCmdHandle::addfriend(SceneUser* User,const std::vector<std::string> &commandVec)
{
    TradeCmdHandle handle;
    if(commandVec.size() < 2)
        return false;
    HelloKittyMsgData::ReqAddFriend req;
    req.set_playerid(atoll(commandVec[1].c_str()));
    handle.ReqAddFriend(User,&req);
    return false;

}

bool GMCmdHandle::delfriend(SceneUser* User,const std::vector<std::string> &commandVec)
{
    TradeCmdHandle handle;
    if(commandVec.size() < 2)
        return false;
    HelloKittyMsgData::ReqKickFriend req;
    req.set_playerid(atoll(commandVec[1].c_str()));
    handle.ReqKickFriend(User,&req);
    return true;

}

bool GMCmdHandle::getfriendlist(SceneUser* User,const std::vector<std::string> &commandVec)
{
    TradeCmdHandle handle;
    if(commandVec.size() != 3)
        return false;
    HelloKittyMsgData::ReqRelationList req;
    req.set_listtype(HelloKittyMsgData::FriendList);
    req.set_pagemax(atoi(commandVec[2].c_str()));
    req.set_pageno(atoi(commandVec[1].c_str()));
    handle.ReqRelationList(User,&req);
    return true;

}

bool GMCmdHandle::getfanslist(SceneUser* User,const std::vector<std::string> &commandVec)
{
    TradeCmdHandle handle;
    if(commandVec.size() != 3)
        return false;
    HelloKittyMsgData::ReqRelationList req;
    req.set_listtype(HelloKittyMsgData::FansList);
    req.set_pagemax(atoi(commandVec[2].c_str()));
    req.set_pageno(atoi(commandVec[1].c_str()));
    handle.ReqRelationList(User,&req);
    return true;

}

bool GMCmdHandle::getotherlist(SceneUser* User,const std::vector<std::string> &commandVec)
{
    TradeCmdHandle handle;
    if(commandVec.size() != 2)
        return false;
    HelloKittyMsgData::ReqRelationList req;
    req.set_listtype(HelloKittyMsgData::RadomList);
    req.set_pagemax(atoi(commandVec[1].c_str()));
    handle.ReqRelationList(User,&req);
    return true;

}

bool GMCmdHandle::rewardBuild(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 1)
    {
        return false;
    }
    //user->m_buildManager.getReward();
    return true;
}

bool GMCmdHandle::sendEmail(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 4)
    {
        return false;
    }
    const char *nickname = NULL,*title = NULL,*conten = NULL;
    std::map<DWORD,DWORD> itemMap;
    std::string command;
    try
    {
        command = commandVec[1];
        nickname = commandVec[1].c_str();

        command += commandVec[2];
        title = commandVec[2].c_str();
        
        command += commandVec[3];
        conten = commandVec[3].c_str();

        for(size_t index = 4;index < commandVec.size();)
        {
            command += commandVec[index];
            DWORD key = atol(commandVec[index].c_str());

            command += commandVec[index+1];
            DWORD value = atol(commandVec[index+1].c_str());

            if(itemMap.find(key) == itemMap.end())
            {
                itemMap.insert(std::pair<DWORD,DWORD>(key,value));
            }
            else
            {
                itemMap[key] += value;
            }
            index += 2;
        }

    }
    catch(...)
    {
        Fir::logger->debug("[GM命令] 命令格式错误%s(%lu,%s)",command.c_str(),user->charid,user->nickname);
        return false;
    }
    return EmailManager::sendEmailBySys(nickname,title,conten,itemMap);
}

bool GMCmdHandle::clearDress(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 1)
    {
        return false;
    }
    return user->m_dressManager.clearDress();
}

bool GMCmdHandle::clearPaper(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 1)
    {
        return false;
    }
    return user->m_paperManager.clearPaper();
}

bool GMCmdHandle::god(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 1)
    {
        return false;
    }
    user->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,100000000,"gm给予",true);
    user->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,100000000,"gm给予",true);
    user->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Exp,100000000,"gm给予",true);
    user->m_buildManager.gmUpGrade(10);
    return true;
}

bool GMCmdHandle::resetDailyData(SceneUser* user,const std::vector<std::string> &commandVec)
{
    if(!user || commandVec.size() < 1)
    {
        return false;
    }
    user->initDailyData();
    return true;
}

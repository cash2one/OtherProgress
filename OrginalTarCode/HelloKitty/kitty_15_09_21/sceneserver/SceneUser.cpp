//角色类一般函数实现

#include "SceneUser.h"
#include "zMetaData.h"
#include <stdarg.h>
#include "SceneServer.h"
#include "zMetaData.h"
#include "TimeTick.h"
#include "SceneUserManager.h"
#include <zlib.h>
#include <bitset>
#include "RecordClient.h"
#include "LoginUserCommand.h"
#include "xmlconfig.h"
#include <limits>
#include "ResType.h"
#include "RedisMgr.h"
#include "json/json.h"
#include "login.pb.h"
#include "extractProtoMsg.h"
#include "serialize.pb.h"
#include "dataManager.h"
#include "tbx.h"
#include "SceneTaskManager.h"
#include "SceneMail.h"
#include "SceneToOtherManager.h"
const DWORD DelCount = 30;

SceneUser::SceneUser(SceneTask *t) : m_trade(this),m_store_house(this),m_buildManager(this),m_taskManager(this),m_atlasManager(this),m_achievementManager(this),m_emailManager(this),m_dressManager(this),m_paperManager(this),m_burstEventManager(this),m_activeManger(*this),m_eventmanager(*this),m_friend(*this),m_kittyGarden(this),gate(t)
{
    accid = 0;
    charid = 0;
    bzero(nickname,sizeof(nickname));
    gate = t;
    needSave = false;
    _online = false;
    bzero(lastSaveCharBaseMD5,16);
    bzero(lastSaveMD5,16);
    VisitID = 0 ;
    m_LastCheckTimer = 0;
    initCarnivalShopData();
}

SceneUser::~SceneUser()
{
}

bool SceneUser::sendCmdToMe(const void *pstrCmd, const int nCmdLen) const
{
    if ((DWORD)nCmdLen > zSocket::MAX_DATASIZE)
    {
        Fir::logger->error("发送消息过大:%d",nCmdLen);
        return false;
    }
    if(gate)
    {
        return gate->sendCmdToUser(charid, pstrCmd, nCmdLen);
    }

    return false;
}

bool SceneUser::sendCmdToGateway(const void *pstrCmd, const int nCmdLen) const
{
    if ((DWORD)nCmdLen > zSocket::MAX_DATASIZE)
    {    
        Fir::logger->error("发送消息过大:%d",nCmdLen);
        return false;
    } 

    if(gate)
    {
        return gate->sendCmd(pstrCmd,nCmdLen);
    }

    return false;
}


DWORD SceneUser::getStoreLimit()
{
    return m_store_house.getAttr(HelloKittyMsgData::Attr_Ware_Grid_Val);
}

bool SceneUser::loop()
{
    bool candel = false;
    do{
        if(_online)
        {
            break ;
        }
        if(!vecVisit.empty())
        {
            break;
        }
        if(!m_eventmanager.canDel())
        {
            break;
        }
        candel = true;

    }while(0);
    if(candel)
    {
        m_LastCheckTimer++;
    }
    else
    {
        m_LastCheckTimer = 0;
    }
    if(m_LastCheckTimer < DelCount)
    {
        m_activeManger.timerCheck();
        m_eventmanager.timerCheck();   
        m_buildManager.loop();
        return true;
    }
    return false;
}

void SceneUser::AddVisit(QWORD PlayerID,DWORD GateId)
{
    auto iter = vecVisit.find(PlayerID);
    if (iter == vecVisit.end() || iter->second != GateId)
    {
        DoFirstVisit(PlayerID,GateId);
    }
    vecVisit.insert(std::pair<QWORD,DWORD>(PlayerID,GateId));
} 

bool SceneUser::isDailyData()
{
    DWORD now = SceneTimeTick::currentTime.sec();
    struct tm tm_old,tm_now;
    zRTime::getLocalTime(tm_now, now);
    zRTime::getLocalTime(tm_old, charbin.dailydata().dailydatatime());
    if(tm_old.tm_year != tm_now.tm_year || tm_old.tm_mon != tm_now.tm_mon || tm_old.tm_mday != tm_now.tm_mday)
    {
        return true;
    }
    return false;

}

bool SceneUser::flushGardenMsg(const DWORD GateId,const QWORD sendCharID)
{
    HelloKittyMsgData::AckEnterGarden ackEnterGarden;
    flushKittyGardenInfo(sendCharID,ackEnterGarden);

    std::string ret;
    encodeMessage(&ackEnterGarden,ret);
    return SceneTaskManager::getMe().broadcastUserCmdToGateway(GateId,sendCharID,ret.c_str(),ret.size());
}

void SceneUser::DelVisit(QWORD PlayerID)
{
    vecVisit.erase(PlayerID);
}

bool SceneUser::isVisit(QWORD PlayerID)
{
    return vecVisit.find(PlayerID) != vecVisit.end();
}

//第一次访问家园
void SceneUser::DoFirstVisit(QWORD PlayerID,DWORD GateId)
{
    flushGardenMsg(GateId,PlayerID);
}

//回到自己的家园
void SceneUser::UserReturn()
{
#if 0
    flushGardenMsg(gate->getID(),charid);
#endif
}
//建筑操作
void SceneUser::opBuild(QWORD PlayerID,QWORD BuildId)//建筑操作
{
    //不是自己，也不是访问者，不可以操作
    if(charid != PlayerID && vecVisit.find(PlayerID) == vecVisit.end())
    {
        HelloKittyMsgData::AckopBuilding ack;
        ack.set_result(HelloKittyMsgData::PlayerOpEventResult_NOVisit);
        ack.set_charid(PlayerID);
        ack.set_buildid(BuildId);
        std::string ret;
        encodeMessage(&ack,ret);
        SceneTaskManager::getMe().broadcastUserCmdToGateway(PlayerID,ret.c_str(),ret.size());

    }
    else
    {
        HelloKittyMsgData::AckopBuilding ack;
        ack.set_charid(charid);
        ack.set_buildid(BuildId);
        ack.set_result(HelloKittyMsgData::PlayerOpEventResult_Suc); 
        DWORD eventId = 0;
        //bool   needNotice = false;
        do{
            BuildBase* pBuild = m_buildManager.getBuild(BuildId);
            if(pBuild && pBuild->isTypeBuid(Build_Type_Road))
            {
                m_activeManger.OpRoad(PlayerID,BuildId,ack); 
                break;
            }
            m_eventmanager.OpRoad(PlayerID,BuildId,ack);

        }while(0);
        //发奖励
        if(ack.process() == HelloKittyMsgData::EventProcess_final && ack.result() == HelloKittyMsgData::PlayerOpEventResult_Suc)
        {

            if(ack.award_size() > 0)
            {
                HelloKittyMsgData::vecAward rvecaward;
                for(int i = 0 ;i < ack.award_size();i++)
                {
                    HelloKittyMsgData::Award* pawrd =  ack.mutable_award(i);
                    if(pawrd)
                    {
                        HelloKittyMsgData::Award* padd =  rvecaward.add_award();
                        if(padd)
                        {
                            *padd = *pawrd;
                        }


                    }
                }
                DoAward(PlayerID,rvecaward,eventId);//不发通知，因为返回里已经有通知

            }
        }
        std::string ret;
        encodeMessage(&ack,ret);
        returnMsgInMap(PlayerID,ret.c_str(),ret.size());

    }



}
void SceneUser::DoAward(QWORD PlayerID, const HelloKittyMsgData::vecAward& rvecAward,DWORD EventID,bool NeedNotice)
{
    do{

        if(PlayerID == charid)
        {
            DoBuildAward(rvecAward,EventID,charid,NeedNotice);
            break;

        }
        //查看本服玩家
        SceneUser* user = SceneUserManager::getMe().getUserByID(PlayerID);
        if(user)
        {
            user->DoBuildAward(rvecAward,EventID,charid,NeedNotice);
            break;
        }
        zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(PlayerID % MAX_MEM_DB+1);
        if(!handle2)
        {
            Fir::logger->error("找不到Mem,%lu",PlayerID % MAX_MEM_DB+1);
            break;

        }

        DWORD SenceId = handle2->getInt("playerscene",PlayerID,"sceneid");
        if(SenceId != 0)
        {
            Fir::logger->error("寻找其他server处理 ，id %d",SenceId);
            BYTE buf[zSocket::MAX_DATASIZE] = {0};
            CMD::SCENE::t_awardtoPlayer_scenescene *sendCmd = (CMD::SCENE::t_awardtoPlayer_scenescene *)buf;
            constructInPlace(sendCmd);
            sendCmd->charid = PlayerID;
            sendCmd->charowner = charid;
            sendCmd->eventid = EventID;
            sendCmd->bnotice = NeedNotice;
            sendCmd->size = rvecAward.ByteSize();
            rvecAward.SerializeToArray(sendCmd->data,sendCmd->size);
            std::string ret;
            encodeMessage(sendCmd,sizeof(*sendCmd) + sendCmd->size,ret);
            if(SceneClientToOtherManager::getMe().SendMsgToOtherScene(SenceId,ret.c_str(),ret.size()))
            {
                break;
            }

        }
        //玩家无实例，发邮件 
        SceneMailManager::getMe().sendSysMailToPlayerForEvent(PlayerID,EventID,charid,rvecAward,true);

    }while(0);

}

void SceneUser::sendhappenevent(const HelloKittyMsgData::PlayerEvent &event,bool bPush)
{
    zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(charid % MAX_MEM_DB+1);
    if(handle2)
    {
        DWORD size = event.ByteSize();
        char tepbuf[zSocket::MAX_DATASIZE] = {0};  
        event.SerializeToArray(tepbuf,size);  
        handle2->setBin("plyerevent", charid, tepbuf,size);

    }
    if(bPush)
    {
        if(event.eventid() != 0)
        {
            m_friend.eventhappen();
        }
        else
        {
            m_friend.eventclose();
        }

    }


}

bool SceneUser::brushDailyData()
{
    //日常临时数据
    initDailyData();
    //重置日常任务
    m_taskManager.resetDailyTask();
    return true;
}

void SceneUser::initDailyData()
{
    HelloKittyMsgData::DailyData *dailyData = charbin.mutable_dailydata();
    if(!dailyData)
    {
        return;
    }
    dailyData->set_dailydatatime(SceneTimeTick::currentTime.sec());     
    dailyData->set_addgold(0);
    dailyData->set_addgem(0);
    dailyData->set_addexp(0);
    dailyData->set_addhappy(0);
    dailyData->set_addfriend(0);
    dailyData->set_vistorother(0);
    dailyData->set_addatlas(0);
    dailyData->set_finishburstevent(0);
    dailyData->set_buildorlevel(0);
    dailyData->set_randtoy(0);
    HelloKittyMsgData::DivineData *divine = dailyData->mutable_divine();
    if(!divine)
    {
        return;
    }
    divine->set_answer(0);
    divine->set_lucklevel(0);
    divine->set_randorder("");
    divine->set_randtime(0);
    divine->set_firstkey(0);
    divine->set_status(HelloKittyMsgData::DS_Begin);
}

void SceneUser::resetAllData()
{
    charbase.onlinetime = 0;
    charbin.Clear();
    onlineInit();
}

bool SceneUser::changeTime()
{
    //工人cd
    m_buildManager.flushWorker();
    if(!isDailyData())
    {
        return false;
    }
    brushDailyData();
    return true;
}

bool   SceneUser::havePersonOnline()
{
    return  is_online() || !vecVisit.empty();
}

bool  SceneUser::checkPush(const HelloKittyMsgData::vecAward& rvecAward)
{
    std::map<DWORD,DWORD> itemMap;
    HelloKittyMsgData::vecAward rItem;
    for(int i = 0; i != rvecAward.award_size();i++)
    {
        const HelloKittyMsgData::Award& rcofig = rvecAward.award(i);
        if(rcofig.awardtype() < HelloKittyMsgData::Attr_Max)
        {
            continue;
        }
        HelloKittyMsgData::Award* pAward = rItem.add_award();
        if(pAward)
        {
            *pAward = rcofig;
        }
        if(itemMap.find(rcofig.awardtype()) == itemMap.end())
        {
            itemMap.insert(std::pair<DWORD,DWORD>(rcofig.awardtype(),rcofig.awardval()));
        }
        else
        {
            itemMap[rcofig.awardtype()] += rcofig.awardval();
        }
    }
    return m_store_house.hasEnoughSpace(itemMap);


}

bool  SceneUser::pushItem(const HelloKittyMsgData::vecAward& rvecAward,const char *reMark)
{
    HelloKittyMsgData::vecAward rItem;
    for(int i = 0; i != rvecAward.award_size();i++)
    {
        const HelloKittyMsgData::Award& rcofig = rvecAward.award(i);
        if(!m_store_house.addOrConsumeItem(rcofig.awardtype(),rcofig.awardval(),reMark,true))
        {
            break;
        }
    }
    return true;


}




void SceneUser::DoBuildAward(const HelloKittyMsgData::vecAward& rvecAward,DWORD EventID,QWORD owerid,bool NeedNotice)
{
    char buff[255];
    sprintf(buff,"BuildOp EventID :%u owerid :%lu",EventID,owerid);
    bool bCanPush  = checkPush(rvecAward);
    if(bCanPush)
    {
        pushItem(rvecAward,buff);
    }

    if(bCanPush)
    {
        if(NeedNotice)
        {
            if(is_online())//发通知
            {
                HelloKittyMsgData::returnEventAward ack;
                ack.set_charid(owerid);
                ack.set_eventid(EventID);
                ack.set_ismail(0);
                for(int i = 0; i != rvecAward.award_size();i++)
                {
                    const HelloKittyMsgData::Award& rcofig = rvecAward.award(i);
                    HelloKittyMsgData::Award* pAward = ack.add_award();
                    if(pAward)
                    {
                        *pAward = rcofig;
                    }
                }
                std::string ret;
                encodeMessage(&ack,ret);
                sendCmdToMe(ret.c_str(),ret.size());

            }
            else//发空白邮件
            {
                SceneMailManager::getMe().sendSysMailToPlayerForEvent(charid,EventID,owerid,rvecAward,false);

            }


        }
    }
    else
    {
        if(NeedNotice && is_online())
        {
            HelloKittyMsgData::returnEventAward ack;
            ack.set_charid(owerid);
            ack.set_eventid(EventID);
            ack.set_ismail(1);
            for(int i = 0; i != rvecAward.award_size();i++)
            {
                const HelloKittyMsgData::Award& rcofig = rvecAward.award(i);
                HelloKittyMsgData::Award* pAward = ack.add_award();
                if(pAward)
                {
                    *pAward = rcofig;
                }
            }
            std::string ret;
            encodeMessage(&ack,ret);
            sendCmdToMe(ret.c_str(),ret.size());


        }
        SceneMailManager::getMe().sendSysMailToPlayerForEvent(charid,EventID,owerid,rvecAward,true);
    }


}

bool SceneUser::sendOtherUserMsg(const void *pstrCmd, const int nCmdLen)
{
    for(auto iter = vecVisit.begin();iter != vecVisit.end();++iter)
    {
        SceneTaskManager::getMe().broadcastUserCmdToGateway(iter->second,iter->first,pstrCmd,nCmdLen);
    }
    return true;
}
//消息通知游客和自己,地图消息：比如说垃圾产生和清除,  
void SceneUser::broadcastMsgInMap(const void *pstrCmd, const int nCmdLen)
{
    if(is_online())
    {
        sendCmdToMe(pstrCmd, nCmdLen);
    }
    sendOtherUserMsg(pstrCmd,nCmdLen);
}

void SceneUser::returnMsgInMap(QWORD PlayerID,const void *pstrCmd, const int nCmdLen)
{
    if(PlayerID == charid && is_online()) 
    {
        sendCmdToMe(pstrCmd, nCmdLen);
        return ;

    }

    const map<QWORD,DWORD>& mapVist =  getVist();
    auto it = mapVist.find(PlayerID);
    if(it != mapVist.end())
    {
        SceneTaskManager::getMe().broadcastUserCmdToGateway(it->second,it->first,pstrCmd,nCmdLen);
    }
}

bool SceneUser::isOtherOnline(QWORD PlayerID)
{
    SceneUser* user = SceneUserManager::getMe().getUserByID(PlayerID);
    if(user)
    {
        return (user->is_online());
    }
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if(handle)
    {
        return  handle->checkSet("playerset",0 ,"online" , PlayerID);
    }
    return false;

}

void SceneUser::SendMsgToOher(QWORD PlayerID,const void *pstrCmd, const int nCmdLen)
{
    SceneUser* user = SceneUserManager::getMe().getUserByID(PlayerID);
    if(user)
    {
        user->sendCmdToMe(pstrCmd,nCmdLen);
        return ;
    }

    SceneTaskManager::getMe().broadcastUserCmdToGateway(PlayerID,pstrCmd,nCmdLen); 

}

QWORD SceneUser::getvisit()
{
    return VisitID;
}

void SceneUser::setVisit(QWORD PlayerId)
{
    bool bNeedDelLock =true;
    do{
        if(VisitID == PlayerId)
            break ;
        //原来在自己家
        //进自己家
        //0==0
        //到别人家
        if(VisitID == 0 && PlayerId != 0)
        {

            SceneUser* user = SceneUserManager::getMe().getUserByID(PlayerId);
            if(user)
            {
                user->AddVisit(charid,gate->getID());

            }
            else
            {
                zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(PlayerId % MAX_MEM_DB+1);
                if(!handle)
                    break ;
                DWORD SenceId = handle->getInt("playerscene",PlayerId,"sceneid");
                if(SenceId != 0)
                {
                    Fir::logger->info("寻找其他server处理 ，id %d",SenceId);
                    CMD::SCENE::t_SetVisit_scenescene sendCmd;
                    sendCmd.charid = charid;
                    sendCmd.ownerid = PlayerId;
                    sendCmd.chargateid = gate->getID();
                    std::string ret;
                    encodeMessage(&sendCmd,sizeof(sendCmd),ret);
                    if(!SceneClientToOtherManager::getMe().SendMsgToOtherScene(SenceId,ret.c_str(),ret.size()))
                    {
                        Fir::logger->error(" 找不到对应server，id %d",SenceId);

                    }
                    else
                    {
                        bNeedDelLock = false;
                    }


                }

            }

        }
        //原来在别人家 
        //回自己家
        if(VisitID != 0  && PlayerId == 0)
        {
            SceneUser* user = SceneUserManager::getMe().getUserByID(VisitID);
            if(user)
            {
                user->DelVisit(charid);
            }
            else
            {
                zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(VisitID % MAX_MEM_DB+1);
                if(!handle)
                    break ;
                DWORD SenceId = handle->getInt("playerscene",VisitID,"sceneid");
                if(SenceId != 0)
                {
                    Fir::logger->info("寻找其他server处理 ，id %d",SenceId);
                    CMD::SCENE::t_SetVisit_scenescene sendCmd;
                    sendCmd.charid = charid;
                    sendCmd.ownerid = VisitID;
                    std::string ret;
                    encodeMessage(&sendCmd,sizeof(sendCmd),ret);
                    if(!SceneClientToOtherManager::getMe().SendMsgToOtherScene(SenceId,ret.c_str(),ret.size()))
                    {
                        Fir::logger->error(" 找不到对应server，id %d",SenceId);

                    }

                }

            }
        }
        //到另外别人家
        if(VisitID != 0 && PlayerId != 0)
        {
            SceneUser* user1 = SceneUserManager::getMe().getUserByID(VisitID);
            if(user1)
            {
                user1->DelVisit(charid);
            }
            else
            {
                zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(VisitID % MAX_MEM_DB+1);
                if(!handle)
                    break ;

                DWORD SenceId = handle->getInt("playerscene",VisitID,"sceneid");
                if(SenceId != 0)
                {
                    Fir::logger->info("寻找其他server处理 ，id %d",SenceId);
                    CMD::SCENE::t_SetVisit_scenescene sendCmd;
                    sendCmd.charid = charid;
                    sendCmd.ownerid = VisitID;
                    std::string ret;
                    encodeMessage(&sendCmd,sizeof(sendCmd),ret);
                    if(!SceneClientToOtherManager::getMe().SendMsgToOtherScene(SenceId,ret.c_str(),ret.size()))
                    {
                        Fir::logger->error(" 找不到对应server，id %d",SenceId);

                    }

                }

            }
            SceneUser* user = SceneUserManager::getMe().getUserByID(PlayerId);
            if(user)
            {
                user->AddVisit(charid,gate->getID());

            }
            else
            {
                zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(PlayerId % MAX_MEM_DB+1);
                if(!handle)
                    break ;

                DWORD SenceId = handle->getInt("playerscene",PlayerId,"sceneid");
                if(SenceId != 0)
                {
                    Fir::logger->info("寻找其他server处理 ，id %d",SenceId);
                    CMD::SCENE::t_SetVisit_scenescene sendCmd;
                    sendCmd.charid = charid;
                    sendCmd.ownerid = PlayerId;
                    sendCmd.chargateid = gate->getID();
                    std::string ret;
                    encodeMessage(&sendCmd,sizeof(sendCmd),ret);
                    if(!SceneClientToOtherManager::getMe().SendMsgToOtherScene(SenceId,ret.c_str(),ret.size()))
                    {
                        Fir::logger->error(" 找不到对应server，id %d",SenceId);

                    }
                    else
                    {
                        bNeedDelLock = false;
                    }

                }

            }


        }
    }while(0);
    if(PlayerId > 0 && bNeedDelLock)
    { 
        zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(PlayerId % MAX_MEM_DB+1);
        if(handle)
            handle->delLock("playerlock",PlayerId,"newplayer");

    }

    VisitID = PlayerId;

}


bool SceneUser::checkMaterialMap(const std::map<DWORD,DWORD> &materialMap)
{
    for(auto iter = materialMap.begin();iter != materialMap.end();++iter)
    {
        if(!m_store_house.hasEnoughItem(iter->first,iter->second))
        {
            return false;
        }
    }
    return true;
}

bool SceneUser::reduceMaterialMap(const std::map<DWORD,DWORD> &materialMap,const char *reMark)
{
    for(auto iter = materialMap.begin();iter != materialMap.end();++iter)
    {
        if(!m_store_house.addOrConsumeItem(iter->first,iter->second,reMark,false))
        {   
            return false;
        }
    }
    return true;
}


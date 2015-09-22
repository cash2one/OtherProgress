#include "burstEventManager.h"
#include "SceneUser.h"
#include "tbx.h"
#include "TimeTick.h"

BurstEventManager::BurstEventManager(SceneUser *owner) : m_owner(owner)
{
}

BurstEventManager::~BurstEventManager()
{
}

bool BurstEventManager::save(HelloKittyMsgData::Serialize& binary)
{
    for(auto iter = m_eventMap.begin();iter != m_eventMap.end();++iter)
    {
        HelloKittyMsgData::BurstEvent *temp = binary.add_burstevent();
        if(temp)
        {
            *temp = iter->second;
        }
    }
    return true;
}

bool BurstEventManager::load(const HelloKittyMsgData::Serialize& binary)
{
    const std::map<QWORD,QWORD>& oldNewKeyMap = m_owner->m_buildManager.getOldNewKeyMap();
    for(int index = 0;index < binary.burstevent_size();++index)
    {
        HelloKittyMsgData::BurstEvent &temp = const_cast<HelloKittyMsgData::BurstEvent&>(binary.burstevent(index));
        auto iter = oldNewKeyMap.find(temp.tempid());
        if(iter != oldNewKeyMap.end())
        {
            temp.set_tempid(iter->second);
            m_eventMap.insert(std::pair<DWORD,HelloKittyMsgData::BurstEvent>(temp.tempid(),temp));
            m_owner->m_buildManager.opBurstEventMap(temp.tempid(),temp.npckey(),true);
        }
    }
    return true;
}

bool BurstEventManager::fullMessage(HelloKittyMsgData::UserBaseInfo &binary)
{
   for(auto iter = m_eventMap.begin();iter != m_eventMap.end();++iter)
   {
       HelloKittyMsgData::BurstEvent *temp = binary.add_burstevent();
       if(temp)
       {
           *temp = iter->second;
       }
   }
   return true;
}
 

bool BurstEventManager::flushEvent()
{
    HelloKittyMsgData::AckUpdateBurstEvent message;
    for(auto iter = m_eventMap.begin();iter != m_eventMap.end();++iter)
    {
        HelloKittyMsgData::BurstEvent *temp = message.add_eventlist();
        if(temp)
        {
            *temp = iter->second;
        }
    }

    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool BurstEventManager::updateBurstEvent(const QWORD eventID)
{
    HelloKittyMsgData::BurstEvent* event = getEvent(eventID);
    if(!event)
    {
        return false;
    }
    HelloKittyMsgData::AckUpdateBurstEvent message;
    HelloKittyMsgData::BurstEvent *temp = message.add_eventlist();
    if(temp)
    {
        *temp = *event;
    }
    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool BurstEventManager::loop()
{
    DWORD now = SceneTimeTick::currentTime.sec();
    std::vector<QWORD> delVec;
    std::set<DWORD> npcKeySet;
    std::set<DWORD> rewardKeySet;
    for(auto iter = m_eventMap.begin();iter != m_eventMap.end();++iter)
    {
        HelloKittyMsgData::BurstEvent &temp = const_cast<HelloKittyMsgData::BurstEvent&>(iter->second);
        if(now >= temp.begintime() + 2*60)
        {
            delVec.push_back(iter->first);
        }
        else
        {
            npcKeySet.insert(temp.npckey());
            rewardKeySet.insert(temp.rewardkey());
        }
    }
    for(auto iter = delVec.begin();iter != delVec.end();++iter)
    {
        delEvent(*iter,HelloKittyMsgData::BES_Del_Other);
    }

    for(int cnt = 0;m_eventMap.size() < 3 && cnt < 10;++cnt)
    {
        DWORD npcKey = pb::Conf_t_BurstEventNpc::randExceptNpc(m_owner->charbase.level,npcKeySet);
        DWORD rewardKey = pb::Conf_t_BurstEventReward::randExceptReward(m_owner->charbase.level,rewardKeySet);
        if(npcKey && rewardKey)
        {
            BuildBase* road = m_owner->m_buildManager.getEmptyRoad();
            if(!road)
            {
                break;
            }
            Fir::logger->debug("[刷出突发事件]:(%lu,%s,%lu,%u,%u)",m_owner->charid,m_owner->nickname,road->getID(),npcKey,rewardKey);
            HelloKittyMsgData::BurstEvent temp;
            temp.set_tempid(road->getID());
            temp.set_npckey(npcKey);
            temp.set_rewardkey(rewardKey);
            temp.set_status(HelloKittyMsgData::BES_Accept);
            temp.set_begintime(now);
            m_eventMap.insert(std::pair<DWORD,HelloKittyMsgData::BurstEvent>(temp.tempid(),temp));
            updateBurstEvent(temp.tempid());
            npcKeySet.insert(npcKey);
            rewardKeySet.insert(rewardKey);
            m_owner->m_buildManager.opBurstEventMap(temp.tempid(),npcKey,true);
        }
    }
    return true;
}

bool BurstEventManager::opEvent(const HelloKittyMsgData::ReqOpBurstEvent *cmd)
{
    HelloKittyMsgData::BurstEvent *event = getEvent(cmd->tempid());
    if(!event || event->status() != HelloKittyMsgData::BES_Accept)
    {
        return false;
    }
    if(cmd->optype() == HelloKittyMsgData::BEOT_Submit)
    {
        return checkTarget(cmd->tempid());
    }
    else
    {
        return delEvent(cmd->tempid(),HelloKittyMsgData::BES_Del_Other);
    }
    return false;
}

bool BurstEventManager::checkTarget(const QWORD tempid)
{
    HelloKittyMsgData::BurstEvent* temp = getEvent(tempid);
    if(!temp)
    {
        return false;
    }
    const pb::Conf_t_BurstEventReward *rewardConf = tbx::BurstEventReward().get_base(temp->rewardkey());
    if(!rewardConf || !m_owner->m_store_house.hasEnoughSpace(rewardConf->getRewardMap()))
    {
        m_owner->opErrorReturn(HelloKittyMsgData::WareHouse_Is_Full);
        return false;
    }
    const std::map<DWORD,DWORD>& randItemMap = rewardConf->getRandItemMap();
    char reMark[100] = {0};
    snprintf(reMark,sizeof(reMark),"突发事件扣除(%u,%u)",temp->npckey(),temp->rewardkey());
    if(!randItemMap.empty() && (!m_owner->checkMaterialMap(randItemMap) || !m_owner->reduceMaterialMap(randItemMap,reMark)))
    {
        m_owner->opErrorReturn(HelloKittyMsgData::Material_Not_Enough);
        return false;
    }
    bzero(reMark,sizeof(reMark));
    snprintf(reMark,sizeof(reMark),"突发事件奖励(%u,%u)",temp->npckey(),temp->rewardkey());
    m_owner->m_store_house.addOrConsumeItem(rewardConf->getRewardMap(),reMark,true);
#if 0
    if(m_owner->m_store_house.hasEnoughSpace(rewardConf->getRewardMap()))
    {
        m_owner->m_store_house.addOrConsumeItem(rewardConf->getRewardMap(),reMark,true);
    }
    else
    {
        EmailManager::sendEmailBySys(m_owner->nickname,"突发事件奖励",reMark,rewardConf->getRewardMap(),true);
    }
#endif
    delEvent(tempid,HelloKittyMsgData::BES_Del_Finish);
    return true;
}

HelloKittyMsgData::BurstEvent* BurstEventManager::getEvent(const QWORD tempid)
{
    auto iter = m_eventMap.find(tempid);
    if(iter == m_eventMap.end())
    {
        return NULL;
    }
    return const_cast<HelloKittyMsgData::BurstEvent*>(&(iter->second));
}

bool BurstEventManager::delEvent(const QWORD tempid,const HelloKittyMsgData::BurstEventStatus &delType)
{
    HelloKittyMsgData::BurstEvent* temp = getEvent(tempid);
    if(!temp)
    {
        return false;
    }
    Fir::logger->debug("[删除突发事件]:(%lu,%s,%lu,%u,%u)",m_owner->charid,m_owner->nickname,tempid,temp->npckey(),temp->rewardkey());
    m_owner->m_buildManager.opBurstEventMap(temp->tempid(),temp->npckey(),false);
    temp->set_status(delType);
    updateBurstEvent(temp->tempid());
    m_eventMap.erase(temp->tempid());
    return true;
}



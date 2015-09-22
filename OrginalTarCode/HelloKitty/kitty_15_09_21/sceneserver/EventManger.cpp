#include "EventManger.h"
#include "tbx.h"
#include "zMisc.h"
#include "TimeTick.h"
#include "buildManager.h"
#include "SceneUser.h"
#include "Misc.h"
bool EventBase::OpRoad(QWORD PlayerId,HelloKittyMsgData::AckopBuilding &ack)
{
    ack.set_eventid(m_Id);
    ack.set_buildid(m_InsId);
    ack.set_result(HelloKittyMsgData::PlayerOpEventResult_Suc);
    return false;
}

bool EventBase::init(DWORD bindBuild)
{
    return m_InsId != 0;
}

bool EventBase::init(const HelloKittyMsgData::SaveForEvent& rEvent)
{
    m_EndTimer = rEvent.endtimer();
    m_step = rEvent.value();
    if(rEvent.opplayer_size() == rEvent.optimer_size())
    {
        for(int i =0 ; i != rEvent.opplayer_size();i++)
        {
            m_otherOpTimer[rEvent.opplayer(i)] = rEvent.optimer(i);

        }

    }
    return init(rEvent.buildid());

}


EventBase::~EventBase()
{
    //DONothing 
}

bool EventBase::isOverTimer(DWORD nowTimer)
{
    if(m_EndTimer == 0)
    {
        return false;
    }
    return nowTimer >= m_EndTimer;
}

EventBase::EventBase(EventManager &rManager,DWORD Id ,HelloKittyMsgData::PlayerEventType type,DWORD intraltimer):m_rManager(rManager),m_Id(Id),m_type(type),m_InsId(0),m_step(0)    
{
    m_EndTimer  = intraltimer == 0 ? 0 :  SceneTimeTick::currentTime.sec() + intraltimer;
}

DWORD EventBase::getId()
{
    return m_Id;

}

HelloKittyMsgData::PlayerEventType EventBase::getType()
{
    return m_type;
}


DWORD EventBase::getEndTimer()
{
    return m_EndTimer;
}

void EventBase::NoticeBindBuild(bool add,QWORD PlayerId)//绑定建筑通知
{
    HelloKittyMsgData::EventBuildNotice ack;
    ack.set_charid(m_rManager.getUser().charid);
    ack.set_buildid(m_InsId);
    if(add)
    {
        ack.set_eventid(m_Id);
        ack.set_data(m_step);
        ack.set_timerover(m_EndTimer);
        LOG_ERR("Send add Build Messge Bulid :%lu event %d",m_InsId,m_Id);
    }
    else
    {
        ack.set_eventid(0);
        LOG_ERR("Send remove Build Messge Bulid :%lu event %d",m_InsId,m_Id);
    }
    const map<QWORD,DWORD>& mapVist =  m_rManager.getUser().getVist();
    for(auto iter = mapVist.begin(); iter != mapVist.end(); iter++)
    {
        if(PlayerId != 0 && iter->first != PlayerId)
        {
            continue;
        }
        if(add)
        {
            auto it = m_otherOpTimer.find(iter->first);
            if(it != m_otherOpTimer.end())
            {
                ack.set_lastoptimer(it->second);
            }
        }
        std::string ret;
        encodeMessage(&ack,ret);
        m_rManager.getUser().returnMsgInMap(iter->first,ret.c_str(),ret.size());


    }
    if(PlayerId != 0 && PlayerId != m_rManager.getUser().charid)
    {
        return ;
    }
    if(add)
    {
        auto it = m_otherOpTimer.find(m_rManager.getUser().charid);
        if(it == m_otherOpTimer.end())
        {
            ack.set_lastoptimer(m_rManager.getUser().charid);
        }
    }
    std::string ret;
    encodeMessage(&ack,ret);
    m_rManager.getUser().returnMsgInMap(m_rManager.getUser().charid,ret.c_str(),ret.size());

}

void EventBase::NoticeBindBuild(HelloKittyMsgData::Evententer *info)//绑定建筑通知
{
    LOG_ERR("Send load Build Messge Bulid :%lu event %d",m_InsId,m_Id);
    HelloKittyMsgData::EventBuildNotice * pAck = info->add_eventbuild();
    if(!pAck)
        return ;
    HelloKittyMsgData::EventBuildNotice &ack = *pAck;
    ack.set_charid(m_rManager.getUser().charid);
    ack.set_buildid(m_InsId);
    ack.set_eventid(m_Id);
    ack.set_data(m_step);
}
void EventBase::NoticeNewEvent(HelloKittyMsgData::Evententer *info)
{

    LOG_ERR("Send load  event %d",m_Id);
    HelloKittyMsgData::EventNotice *pAck = info->add_eventinfo(); 
    if(!pAck)
        return;
    HelloKittyMsgData::EventNotice& ack = *pAck;
    ack.set_charid(m_rManager.getUser().charid);
    ack.set_eventid(m_Id);
}
void EventBase::NoticeNewEvent(bool add,bool bClient,bool bsessionPush)//新事件通知
{
    //ToClient
    if(bClient)
    {

        HelloKittyMsgData::EventNotice ack;
        ack.set_charid(m_rManager.getUser().charid);
        if(add)
        {
            ack.set_eventid(m_Id);
            LOG_ERR("Send add  event %d",m_Id);
        }
        else
        {
            ack.set_eventid(0);
            LOG_ERR("Send del  event %d",m_Id);
        }
        std::string ret; 
        encodeMessage(&ack,ret);
        m_rManager.getUser().broadcastMsgInMap(ret.c_str(),ret.size());

    }
    //ToSession
    HelloKittyMsgData::PlayerEvent event;
    if(add)
    {
        event.set_eventid(m_Id);
    }
    else
    {
        event.set_eventid(0);

    }
    event.set_endtimer(m_EndTimer);
    m_rManager.getUser().sendhappenevent(event,bsessionPush);

}
bool EventBase::canDel()
{
    return false;
}

/***************************************EventLoseBoy*******************************************/
bool EventLoseBoy::OpRoad(QWORD PlayerId,HelloKittyMsgData::AckopBuilding &ack)
{
    if(EventBase::OpRoad(PlayerId,ack))
    {
        return true;
    }
    const pb::Conf_t_event *eventConf = tbx::event().get_base(m_Id); 
    if(!eventConf)
    {
        ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
        return true;
    }
    if(PlayerId == m_rManager.getUser().charid)
    {
        ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
        return true;
    }

    bool bfinish = false;
    BYTE rate = zMisc::randBetween(0,100);
    if(m_step < eventConf->target.size())
    {
        if(eventConf->target[m_step] <= rate)
        {
            bfinish = true;
        }

    }
    else
    {
        bfinish = true;
    }
    if(!bfinish)
    {
        m_step++;
        NoticeBindBuild(false,m_rManager.getUser().charid);
        m_InsId = m_rManager.getUser().m_buildManager.getAnyBuildBytype(eventConf->buildevent,false);
        NoticeBindBuild(true,m_rManager.getUser().charid);

    }
    if(bfinish)
    {
        ack.set_process(HelloKittyMsgData::EventProcess_final);
    }

    return true;

}


void EventLoseBoy::destroy()
{
    //清除建筑物上标记
    NoticeBindBuild(false,m_rManager.getUser().charid);
    NoticeNewEvent(false,true,true);

}

bool EventLoseBoy::init(DWORD bindBuild)
{
    const pb::Conf_t_event *eventConf = tbx::event().get_base(m_Id); 
    if(eventConf)
    {
        if(bindBuild != 0)
        {
            m_InsId = m_rManager.getUser().m_buildManager.getAnyBuildById(bindBuild);
        }
        if(m_InsId == 0)
        {
            m_InsId = m_rManager.getUser().m_buildManager.getAnyBuildBytype(eventConf->buildevent,false);

        }
    }
    if(bindBuild == 0)
    {
        NoticeBindBuild(true,m_rManager.getUser().charid);
    }
    NoticeNewEvent(true,bindBuild == 0,bindBuild == 0);

    return EventBase::init(bindBuild);

}

EventLoseBoy::EventLoseBoy(EventManager &rManager,DWORD Id,DWORD intraltimer):EventBase(rManager,Id,HelloKittyMsgData::PlayerEvent_LoseBoy,intraltimer)
{
}



void EventLoseBoy::OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer *info)
{
    if(PlayerId == m_rManager.getUser().charid)
    {
        NoticeBindBuild(info); 
    }
    NoticeNewEvent(info);
}
/************************************EventGoldHill************************************************/
bool EventGoldHill::OpRoad(QWORD PlayerId,HelloKittyMsgData::AckopBuilding &ack)//操作该建筑
{
    if(EventBase::OpRoad(PlayerId,ack))
    {
        return true;
    }
    const pb::Conf_t_event *eventConf = tbx::event().get_base(m_Id); 
    if(!eventConf)
    {
        ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
        return true;
    }
    DWORD nowTimer = SceneTimeTick::currentTime.sec();
    auto iter = m_otherOpTimer.find(PlayerId);
    if(iter != m_otherOpTimer.end())
    {
        DWORD nowTimer = SceneTimeTick::currentTime.sec();
        if(iter->second < nowTimer + eventConf->event->cooltimer()*60)
        {
            ack.set_result(HelloKittyMsgData::PlayerOpEventResult_Cool);
            return true;


        }


    }
    m_otherOpTimer[PlayerId] = nowTimer;


    bool bfinish = false;
    m_step++;
    if(m_step >= eventConf->target.size())
    {
        bfinish = true;
    }
    if(!bfinish)
    {
        NoticeBindBuild(true); 
    }
    if(bfinish)
    {
        ack.set_process(HelloKittyMsgData::EventProcess_final);
    }

    return true;



}

void EventGoldHill::destroy()//销毁时该做的的事情
{
    NoticeBindBuild(false);
    NoticeNewEvent(false,true,true);
}

bool EventGoldHill::init(DWORD bindBuild)//初始化
{
    const pb::Conf_t_event *eventConf = tbx::event().get_base(m_Id); 
    if(!eventConf && eventConf->buildevent.size() > 0 && eventConf->target.size() > 0)
    {
        if(bindBuild != 0)
        {
            m_InsId = m_rManager.getUser().m_buildManager.createBuildAnySpace(bindBuild);

        }
        if(m_InsId == 0)
        {
            m_InsId = m_rManager.getUser().m_buildManager.createBuildAnySpace(eventConf->buildevent[0]);

        }
        if(bindBuild == 0)
        {
            NoticeBindBuild(true);
        }
        NoticeNewEvent(true,bindBuild==0,bindBuild==0); 

    }
    return EventBase::init(bindBuild);

}


EventGoldHill::~EventGoldHill()
{
}

EventGoldHill::EventGoldHill(EventManager &rManager,DWORD Id,DWORD intraltimer):EventBase(rManager,Id,HelloKittyMsgData::PlayerEvent_GoldHill,intraltimer)
{
}

void EventGoldHill::OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer *info)
{
    NoticeBindBuild(info);
    NoticeNewEvent(info);
}


/****************************************EventFixBuild*************************************************/
bool EventFixBuild::OpRoad(QWORD PlayerId,EventManager &rManager,HelloKittyMsgData::AckopBuilding &ack)//操作该建筑
{
    if(EventBase::OpRoad(PlayerId,ack))
    {
        return true;
    }
    const pb::Conf_t_event *eventConf = tbx::event().get_base(m_Id); 
    if(!eventConf)
    {
        ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
        return true;
    }
    DWORD nowTimer = SceneTimeTick::currentTime.sec();
    auto iter = m_otherOpTimer.find(PlayerId);
    if(iter != m_otherOpTimer.end())
    {
        DWORD nowTimer = SceneTimeTick::currentTime.sec();
        if(iter->second < nowTimer + eventConf->event->cooltimer())
        {
            ack.set_result(HelloKittyMsgData::PlayerOpEventResult_Cool);
            return true;


        }


    }
    m_otherOpTimer[PlayerId] = nowTimer;


    bool bfinish = false;
    BYTE rate = zMisc::randBetween(0,100);
    if(m_step < eventConf->target.size())
    {
        if(eventConf->target[m_step] <= rate)
        {
            bfinish = true;
        }

    }
    else
    {
        bfinish = true;
    }
    if(!bfinish)
    {
        m_step++;

    }
    if(bfinish)
    {
        ack.set_process(HelloKittyMsgData::EventProcess_final);
    }

    return true;


}

void EventFixBuild::destroy()//销毁时该做的的事情
{
    NoticeBindBuild(false);
    NoticeNewEvent(false,true,true);
}

bool EventFixBuild::init(DWORD bindBuild)//初始化
{
    const pb::Conf_t_event *eventConf = tbx::event().get_base(m_Id); 
    if(eventConf)
    {
        if(bindBuild != 0)
        {
            m_InsId = m_rManager.getUser().m_buildManager.getAnyBuildById(bindBuild);

        }
        if(m_InsId == 0)
        {
            m_InsId = m_rManager.getUser().m_buildManager.getAnyBuildById(eventConf->buildevent,false);

        }
        if(bindBuild == 0)
        {
            NoticeBindBuild(true);
        }
        NoticeNewEvent(false,bindBuild == 0 ,bindBuild == 0);

    }
    return EventBase::init(bindBuild);


}

EventFixBuild::~EventFixBuild()
{
}

EventFixBuild::EventFixBuild(EventManager &rManager,DWORD Id):EventBase(rManager,Id,HelloKittyMsgData::PlayerEvent_FixBuild,0)
{
} 

void EventFixBuild::OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer *info)
{
    NoticeBindBuild(info);
    NoticeNewEvent(info);
}

bool EventFixBuild::canDel()
{
    return true;
}
/******************************************************EventPlant**************************************/                
bool EventPlant::OpRoad(QWORD PlayerId,EventManager &rManager,HelloKittyMsgData::AckopBuilding &ack)//操作该建筑
{
    if(EventBase::OpRoad(PlayerId,ack))
    {
        return true;
    }
    const pb::Conf_t_event *eventConf = tbx::event().get_base(m_Id); 
    if(!eventConf)
    {
        ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
        return true;
    }
    bool bfinish = false;
    switch(m_step)
    {
        case 0: //主人种植
            {
                if(PlayerId != m_rManager.getUser().charid)
                {
                    ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
                    return true;
                }
                m_step++;
            }
            break;
        case 1://玩家加速
            {
                if(PlayerId == m_rManager.getUser().charid)
                {
                    ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
                    return true;
                }
                if(m_otherOpTimer.find(PlayerId) != m_otherOpTimer.end())
                {
                    ack.set_result(HelloKittyMsgData::PlayerOpEventResult_Cool);
                    return true;

                }
                if(eventConf->target.size() > 0)
                {
                    DWORD nowTimer = SceneTimeTick::currentTime.sec();
                    DWORD Rate = eventConf->target[0];
                    if(nowTimer < m_EndTimer && Rate >0 && Rate < 100)
                    {
                        m_EndTimer = nowTimer + (m_EndTimer - nowTimer)*(100 - Rate) / (float)(100);
                        m_otherOpTimer[PlayerId] = nowTimer;

                    }
                }

            }
            break;
        case 2://主人收割
            {
                if(PlayerId != m_rManager.getUser().charid)
                {
                    ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
                    return true;
                }
                bfinish = true; 


            }
            break;
    }

    if(bfinish)
    {
        ack.set_process(HelloKittyMsgData::EventProcess_final);
    }
    else
    {
        NoticeBindBuild(true);
    }

    return true;


}

void EventPlant::destroy()//销毁时该做的的事情
{
    NoticeBindBuild(false);
}

bool EventPlant::init(DWORD bindBuild)//初始化
{
    const pb::Conf_t_event *eventConf = tbx::event().get_base(m_Id); 
    if(eventConf && eventConf->buildevent.size() > 0 )
    {
        if(bindBuild != 0)
        {
            m_InsId = m_rManager.getUser().m_buildManager.getAnyBuildById(bindBuild);
        }
        if(m_InsId == 0)
        {
            m_InsId = m_rManager.getUser().m_buildManager.getAnyBuildById(eventConf->buildevent,false);
        }
        if(bindBuild == 0)
        {
            NoticeBindBuild(true);
        }
    }
    return EventBase::init(bindBuild);


}

EventPlant::~EventPlant()
{
}

EventPlant::EventPlant(EventManager &rManager,DWORD Id,DWORD intraltimer):EventBase(rManager,Id,HelloKittyMsgData::PlayerEvent_Plant,intraltimer)
{

}

bool EventPlant::isOverTimer(DWORD nowTimer)
{
    if(m_step == 1 && EventBase::isOverTimer(nowTimer))
    {
        m_step++;
        NoticeBindBuild(true);
    }
    return false;


}

void EventPlant::OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer *info)
{
    NoticeBindBuild(info);
}

bool EventPlant::canDel()
{
    return true;
}
/******************************************************EventManager************************************/
EventManager::EventManager(SceneUser& rUser):m_rUser(rUser)
{
}

SceneUser& EventManager::getUser()
{
    return m_rUser;
}

void EventManager::timerCheck()
{
    DWORD NowTimer = SceneTimeTick::currentTime.sec();  
    for(auto iter = m_vecEvent.begin(); iter != m_vecEvent.end();)
    {
        EventBase *pEvent = *iter;
        if(pEvent == NULL || pEvent->isOverTimer(NowTimer))
        {
            if(pEvent)
            {
                pEvent->destroy();
            }
            iter = m_vecEvent.erase(iter);
            SAFE_DELETE(pEvent);

        }
        else
        {
            ++iter;
        }

    }
    if(!m_rUser.is_online())
    {
        return ;
    }
    const std::unordered_map<unsigned int, const pb::Conf_t_event *> &tbxMap = tbx::event().getTbxMap();
    for(auto iter = tbxMap.begin();iter != tbxMap.end();++iter)
    {
        const pb::Conf_t_event* pconf = iter->second;
        if(!pconf)
        {
            continue;
        }
        //TODO:
        //先判定任务
        if(pconf->event->task() > 0) 
        {
            if(m_rUser.m_taskManager.checkTaskHasDone(pconf->event->task()))
            {
                continue;
            }
        }
        //然后等级
        if(!m_rUser.checkLevel(pconf->event->level()))
        {
            continue;
        }
        //建筑数
        if(m_rUser.m_buildManager.getBuildNum() < pconf->event->needbuild())
        {
            continue;
        }

        //其他事件
        //创建
        auto it = m_lastCreateTime.find(iter->first);
        if(it != m_lastCreateTime.end())
        {
            if(NowTimer < it->second)
            {
                continue;
            }
        }

        bool bSame = false;
        for(auto it = m_vecEvent.begin();it != m_vecEvent.end();++it)
        {
            EventBase * pbase = *it;
            if(pbase && pbase->getId() == iter->first)
            {
                bSame = true;
                break;
            }
            const pb::Conf_t_event *eventConf = tbx::event().get_base(pbase->getId()); 
            if(!eventConf)
            {
                continue;
            }

            if(pconf->event->send() == DOSNED && pconf->event->send() == eventConf->event->send())
            {
                bSame = true;
                break;
            }

        }
        if(bSame)
        {
            continue;
        }
        m_lastCreateTime[iter->first] = NowTimer + zMisc::randBetween(pconf->reflushtimemin*60,pconf->reflushtimemax*60);
        BYTE rate = zMisc::randBetween(0,100);
        if(rate > pconf->event->rate())
        {
            continue;
        }
        EventBase *pevent =NULL;
        HelloKittyMsgData::PlayerEventType EventType = static_cast<HelloKittyMsgData::PlayerEventType>(pconf->event->order());
        switch (EventType)
        {
            case  HelloKittyMsgData::PlayerEvent_LoseBoy :
                {
                    pevent = new EventLoseBoy(*this,iter->first,pconf->event->timer()*60);
                }
                break;
            case HelloKittyMsgData::PlayerEvent_GoldHill :
                {
                    pevent = new EventGoldHill(*this,iter->first,pconf->event->timer()*60);
                }
                break;
            case HelloKittyMsgData::PlayerEvent_FixBuild:
                {
                    pevent = new EventFixBuild(*this,iter->first); 
                }
                break;

            case HelloKittyMsgData::PlayerEvent_Plant:
                {
                    pevent = new EventPlant(*this,iter->first,pconf->event->timer()*60);
                }
                break;
            default:
                break;

        }
        if(pevent)
        {
            if(!pevent->init())
            {
                SAFE_DELETE(pevent);
            }
            else
            {
                m_vecEvent.push_back(pevent);

            }

        }




    }


}

void EventManager::OpRoad(QWORD PlayerId,QWORD InsId,HelloKittyMsgData::AckopBuilding &ack)
{
    bool find = false;
    for(auto iter = m_vecEvent.begin(); iter != m_vecEvent.end();)
    {
        EventBase *pEvent = *iter;
        if(pEvent == NULL )
        {
            ++iter;
            continue;

        }
        if(pEvent->getInsId() == InsId)
        {
            find = true;
            pEvent->OpRoad(PlayerId,ack);
            if(ack.result() ==HelloKittyMsgData::PlayerOpEventResult_Suc && ack.process() == HelloKittyMsgData::EventProcess_final)
            {
                DoAward(PlayerId,ack,pEvent);
                pEvent->destroy(); 
                SAFE_DELETE(pEvent);
                iter = m_vecEvent.erase(iter);
            }
            break;
        }
        ++iter;

    }

    if(!find)
    {
        ack.set_result(HelloKittyMsgData::PlayerOpEventResult_CaseNoExist);
        return ;
    }

}


void EventManager::DoAward(QWORD PlayerId,HelloKittyMsgData::AckopBuilding &ack,EventBase *pEvent)
{
    if(pEvent ==NULL)
        return;
    const pb::Conf_t_event *eventConf = tbx::event().get_base(pEvent->getId()); 
    if(!eventConf)
        return ;
    //Doself
    const HelloKittyMsgData::vecAward * pvec = NULL;
    if(PlayerId == m_rUser.charid)
    {
        pvec = &(eventConf->rewardower);
    }
    else
    {
        pvec = &(eventConf->rewardguess);
    }
    if(pvec)
    {
        for(int i = 0; i != pvec->award_size();i++)
        {
            const HelloKittyMsgData::Award& rcofig = pvec->award(i);
            HelloKittyMsgData::Award* pAward = ack.add_award();
            if(pAward)
            {
                *pAward = rcofig;

            }
        }


    }
    //Other
    for(auto it = pEvent->GetOpPlayer().begin(); it != pEvent->GetOpPlayer().end();it++)
    {
        QWORD opPlayer = it->first;

        if(PlayerId == opPlayer )
        {
            continue;
        }
        if(opPlayer == m_rUser.charid)
        {
            getUser().DoAward(opPlayer,eventConf->rewardower,pEvent->getId(),true);
        }
        else
        {
            getUser().DoAward(opPlayer,eventConf->rewardguess,pEvent->getId(),true);

        }

    }
    //self
    if(PlayerId != m_rUser.charid && pEvent->GetOpPlayer().find(m_rUser.charid) ==  pEvent->GetOpPlayer().end())
    {
        getUser().DoAward(m_rUser.charid,eventConf->rewardower,pEvent->getId(),true);  
    }

}

EventManager::~EventManager()
{
    for(auto it = m_vecEvent.begin(); it != m_vecEvent.end(); it++)
    {
        SAFE_DELETE(*it); 

    }
}


bool EventManager::load(const HelloKittyMsgData::Serialize& binary)
{
    for(int i = 0; i != binary.event_size();i++)
    {
        const HelloKittyMsgData::SaveForEvent& rEvent = binary.event(i);
        DWORD eventid =  rEvent.eventid();
        DWORD flushtimer = rEvent.flushtimer();
        m_lastCreateTime[eventid] = flushtimer;
        if(rEvent.isrun() > 0)
        {
            const pb::Conf_t_event *pConf = tbx::event().get_base(eventid); 
            if(!pConf)
            {
                continue;
            }
            EventBase *pevent =NULL;
            HelloKittyMsgData::PlayerEventType EventType = static_cast<HelloKittyMsgData::PlayerEventType>(pConf->event->order());
            switch (EventType)
            {
                case  HelloKittyMsgData::PlayerEvent_LoseBoy :
                    {
                        pevent = new EventLoseBoy(*this,eventid,0);
                    }
                    break;
                case HelloKittyMsgData::PlayerEvent_GoldHill :
                    {
                        pevent = new EventGoldHill(*this,eventid,0);
                    }
                    break;
                case HelloKittyMsgData::PlayerEvent_FixBuild:
                    {
                        pevent = new EventFixBuild(*this,eventid); 
                    }
                    break;
                case HelloKittyMsgData::PlayerEvent_Plant:
                    {
                        pevent = new EventPlant(*this,eventid,0);
                    }
                    break;
                default:
                    break;
            }
            if(pevent)
            {
                if(!pevent->init(rEvent))
                {
                    SAFE_DELETE(pevent);
                }
                else
                {
                    m_vecEvent.push_back(pevent);

                }

            }

        }



    }
    return true;

}

bool EventManager::save(HelloKittyMsgData::Serialize& binary)
{
    for(auto iter = m_lastCreateTime.begin();iter != m_lastCreateTime.end();iter++)
    {
        HelloKittyMsgData::SaveForEvent *pSaveEvent = binary.add_event();
        if(!pSaveEvent)
            continue;
        pSaveEvent->set_eventid(iter->first);
        pSaveEvent->set_flushtimer(iter->second);
        EventBase * pCurEvent = NULL;
        for(auto it = m_vecEvent.begin(); it != m_vecEvent.end(); it++)
        {
            if((*it) && (*it)->getId() == iter->first)
            {
                pCurEvent = *it;
                break;
            }
        }
        if(!pCurEvent)
        {
            pSaveEvent->set_isrun(0);
            continue;
        }
        else
        {
            pSaveEvent->set_isrun(1);
        }

        pSaveEvent->set_endtimer(pCurEvent->getEndTimer());
        pSaveEvent->set_value(pCurEvent->getStep());
        for(auto it =  pCurEvent->GetOpPlayer().begin();it != pCurEvent->GetOpPlayer().end();++it)
        {
            pSaveEvent->add_opplayer(it->first);
            pSaveEvent->add_optimer(it->second);

        }
        BuildBase* pbuildbase = getUser().m_buildManager.getBuild(pCurEvent->getInsId());  
        if(pbuildbase)
        {
            pSaveEvent->set_buildid(pbuildbase->getTypeID());
        }
    }
    return true;

}


bool EventManager::canDel()
{
    for(auto iter = m_vecEvent.begin(); iter != m_vecEvent.end(); iter++)
    {
        EventBase *pEvent = *iter;
        if(pEvent && !pEvent->canDel())
        {
            return false;
        }
    }
    return true;
}


void EventManager::fullMessage(QWORD PlayerId,HelloKittyMsgData::Evententer *info)
{
    for(auto iter = m_vecEvent.begin();iter != m_vecEvent.end(); iter++)
    {
        EventBase *pBase = *iter;
        if(pBase)
        {
            pBase->OnlineSend(PlayerId,info);
        }
    }
}


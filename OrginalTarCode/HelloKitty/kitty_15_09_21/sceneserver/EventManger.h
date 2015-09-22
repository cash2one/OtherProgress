#ifndef EVENTMANAGER_H__
#define EVENTMANAGER_H__
#include <set>
#include <vector> 
#include <map>
#include "zType.h"
#include "event.pb.h"
#include "serialize.pb.h"
class EventManager;
class EventBase
{
    public:
        virtual bool OpRoad(QWORD PlayerId,HelloKittyMsgData::AckopBuilding &ack);//操作该建筑
        virtual void destroy() = 0;//销毁时该做的的事情
        virtual bool init(DWORD bindBuild = 0);//初始化
        bool  init(const HelloKittyMsgData::SaveForEvent& rEvent);
        virtual ~EventBase();
        virtual bool isOverTimer(DWORD nowTimer);//是否超时
        virtual void OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer*info) = 0;//玩家进 ：上线，进入别人家
        virtual bool canDel();
        EventBase(EventManager &rManager,DWORD Id ,HelloKittyMsgData::PlayerEventType type,DWORD intraltimer);
        DWORD getId();
        HelloKittyMsgData::PlayerEventType getType();
        DWORD getEndTimer();
        DWORD getStep() {return m_step;}
        QWORD getInsId(){return m_InsId;}
        const std::map<QWORD,DWORD> & GetOpPlayer() { return m_otherOpTimer;}
        void  NoticeBindBuild(bool add,QWORD PlayerId =0 );//绑定建筑通知：事件发生时,或进入
        void  NoticeBindBuild(HelloKittyMsgData::Evententer* info);

        void  NoticeNewEvent(bool add,bool bClient,bool bsessionPush);//新事件通知：事件发生时
        void  NoticeNewEvent(HelloKittyMsgData::Evententer* info);//玩家进 ：上线，进入别人家
    protected:
        EventManager &m_rManager;
        DWORD m_Id;//当前事件id
        HelloKittyMsgData::PlayerEventType m_type;//事件类型
        QWORD m_InsId;//当前相关建筑
        DWORD m_EndTimer; //结束时间
        std::map<QWORD,DWORD> m_otherOpTimer;//最近操作玩家
        DWORD m_step;


};

class EventLoseBoy : public EventBase
{
    public:
        virtual bool OpRoad(QWORD PlayerId,HelloKittyMsgData::AckopBuilding &ack);//操作该建筑
        virtual void destroy();//销毁时该做的的事情
        virtual bool init(DWORD bindBuild = 0);//初始化
        virtual ~EventLoseBoy(){}
        virtual void OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer*info);//玩家进 ：上线，进入别人家

        EventLoseBoy(EventManager &rManager,DWORD Id,DWORD intraltimer);


};

class EventGoldHill : public EventBase
{
    public:
        virtual bool OpRoad(QWORD PlayerId,HelloKittyMsgData::AckopBuilding &ack);//操作该建筑
        virtual void destroy();//销毁时该做的的事情
        virtual bool init(DWORD bindBuild = 0);//初始化
        virtual ~EventGoldHill();
        virtual void OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer*info);//玩家进 ：上线，进入别人家
        EventGoldHill(EventManager &rManager,DWORD Id,DWORD intraltimer);

};

class EventFixBuild : public EventBase
{
    public:

        virtual bool OpRoad(QWORD PlayerId,EventManager &rManager,HelloKittyMsgData::AckopBuilding &ack);//操作该建筑
        virtual void destroy();//销毁时该做的的事情
        virtual bool init(DWORD bindBuild = 0);//初始化
        virtual ~EventFixBuild();
        virtual void OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer*info);//玩家进 ：上线，进入别人家
        EventFixBuild(EventManager &rManager,DWORD Id);
        virtual bool canDel();

};

class EventPlant : public EventBase
{
    public:
        virtual bool OpRoad(QWORD PlayerId,EventManager &rManager,HelloKittyMsgData::AckopBuilding &ack);//操作该建筑
        virtual void destroy();//销毁时该做的的事情
        virtual bool init(DWORD bindBuild = 0);//初始化
        virtual ~EventPlant();
        virtual void OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer*info);//玩家进 ：上线，进入别人家
        EventPlant(EventManager &rManager,DWORD Id,DWORD intraltimer);
        virtual bool isOverTimer(DWORD nowTimer);
        virtual bool canDel();
       


};


class SceneUser;
class EventManager
{
    public:
        enum SendType
        {
            DOSNEDNOne = 0,
            DOSNED = 1,
        };
        EventManager(SceneUser& rUser);
        SceneUser& getUser();
        void timerCheck();
        void OpRoad(QWORD PlayerId,QWORD InsId,HelloKittyMsgData::AckopBuilding &ack);
        void OnlineSend(QWORD PlayerId,HelloKittyMsgData::Evententer*info);
        bool load(const HelloKittyMsgData::Serialize& binary);
        bool save(HelloKittyMsgData::Serialize& binary);
        bool canDel();
        ~EventManager();
        void fullMessage(QWORD PlayerId,HelloKittyMsgData::Evententer *info);
    private:
        void DoAward(QWORD PlayerId,HelloKittyMsgData::AckopBuilding &ack,EventBase *pEvent);
    private:
        SceneUser& m_rUser;
        std::map<DWORD,DWORD> m_lastCreateTime;//上次创建时间
        std::vector<EventBase *> m_vecEvent;//
};



#endif// EVENTMANAGER_H__

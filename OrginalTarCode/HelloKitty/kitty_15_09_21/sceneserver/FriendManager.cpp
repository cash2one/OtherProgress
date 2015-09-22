#include "FriendManager.h"
#include "RedisMgr.h"
#include "SceneUserManager.h"
#include "zMemDBPool.h"
#include "SceneUser.h"
#include "RecordClient.h"
#include "SceneToOtherManager.h"
bool compare(QWORD a,QWORD b)
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if(!handle)
    {
        return true;
    }
    bool OnLineA = false;
    bool OnLineB = false;
    OnLineA = handle->checkSet("playerset",0 ,"online" , a);
    OnLineB = handle->checkSet("playerset",0 ,"online" , b);
    CharBase charbaseA; 
    zMemDB* handle1 = zMemDBPool::getMe().getMemDBHandle(a % MAX_MEM_DB+1);
    if (!handle1 || handle1->getBin("charbase",a,"charbase",(char*)&charbaseA) == 0)
    {
        return false;
    }
    zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(b % MAX_MEM_DB+1);
    CharBase charbaseB; 
    if (!handle2 || handle1->getBin("charbase",b,"charbase",(char*)&charbaseB) == 0)
    {
        return false;
    }

    if(OnLineA && OnLineB)
    {
        return charbaseA.onlinetime > charbaseB.onlinetime;
    }
    else if(OnLineA)
    {
        return true;
    }
    else if(OnLineB)
    {
        return false;
    }

    return charbaseA.offlinetime > charbaseB.offlinetime;

}

void doonline(vector<QWORD> &vecOnline)
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if(!handle)
    {
        return ;
    }
    for(auto iter = vecOnline.begin() ;iter != vecOnline.end();)
    {
        bool OnLineA  = handle->checkSet("playerset",0 ,"online" , *iter); 
        if(OnLineA)
        {
            ++iter;
        }
        else
        {
            iter = vecOnline.erase(iter);
        }


    }
}

void dosort(vector<QWORD> &vecOnline)
{
    sort(vecOnline.begin(),vecOnline.end(),compare);
}

ManagerFriend::ManagerFriend(SceneUser& rUser):m_rUser(rUser)
{

}

void  ManagerFriend::load()
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if(NULL != handle)
    {
        handle->getSet("rolerelation", m_rUser.charid, "friend", m_setFriendUsers);
        handle->getSet("rolerelation", m_rUser.charid, "fans", m_setFansUsers);
    }

}

bool ManagerFriend::IsFriend (QWORD PlayerB)//玩家B是玩家A的好友
{
    return m_setFriendUsers.find(PlayerB) != m_setFriendUsers.end();

}

bool ManagerFriend::IsFans(QWORD PlayerB)//玩家A是玩家B的好友
{
    return m_setFansUsers.find(PlayerB) != m_setFansUsers.end();

}

DWORD ManagerFriend::GetFriendList(DWORD pageno,DWORD pagenum,vector<QWORD> &vecFriend,bool bOnline,bool bsort)//返回值总页数
{

    vector<QWORD> total;
    total.assign(m_setFriendUsers.begin(),m_setFriendUsers.end());

    if(pagenum == 0 || !total.empty())
    {
        vecFriend.assign(total.begin(),total.end());
        if(bOnline)
        {
            doonline(vecFriend);
        }
        if(bsort)
        {
            dosort(vecFriend);
        }

        return 1;
    }
    if(bOnline)
    {
        doonline(total);
    }
    if(bsort)
    {
        dosort(total);
    }


    DWORD totalPage = total.size() % pagenum == 0 ? total.size() / pagenum : total.size() / pagenum + 1 ;

    DWORD start = pageno * pagenum;
    if(start >= total.size())
    {
        return totalPage;
    }
    DWORD distance = start + pagenum >= total.size() ? total.size() - start : pagenum ;
    vecFriend.assign(total.begin()+start,total.begin()+start+distance);
    return totalPage;

}

DWORD ManagerFriend::GetFansList(DWORD pageno,DWORD pagenum,vector<QWORD> &vecFans,bool bOnline,bool bsort)
    //玩家a的粉丝，页编号，每页数量，总页数，得到的玩家列表，如果 pagemax == 0 ,那么返回所有玩家
{
    //zRWLock_scope_rdlock lock(rwlock);
    vector<QWORD> total;
    total.assign(m_setFansUsers.begin(),m_setFansUsers.end());
    for(auto iter = total.begin();iter != total.end();)
    {
        if(IsFriend(*iter))
        {
            iter = total.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    if(pagenum == 0 || total.empty())
    {
        vecFans.assign(total.begin(),total.end());
        if(bOnline)
        {
            doonline(vecFans);
        }
        if(bsort)
        {
            dosort(vecFans);
        }

        return 1;
    }
    if(bOnline)
    {
        doonline(total);
    }
    if(bsort)
    {
        dosort(total);
    }
    DWORD totalPage = total.size() % pagenum == 0 ? total.size() / pagenum : total.size() / pagenum + 1 ;

    DWORD start = pageno * pagenum;
    if(start >= total.size())
    {
        return totalPage;
    }
    DWORD distance = start + pagenum >= total.size() ? total.size() - start : pagenum ;
    vecFans.assign(total.begin()+start,total.begin()+start+distance);
    return totalPage;

}

void ManagerFriend::GetOtherListOnline(DWORD pagenum,vector<QWORD> &vecFriend,bool bexpFriendAndFans ,bool bsort)//随机在线玩家
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if (handle==NULL) 
        return ;
    if(bexpFriendAndFans)
    {
        std::set<QWORD> rset;
        handle->getSet("playerset",0 ,"online" ,rset,pagenum * 1.5);
        vecFriend.assign(rset.begin(),rset.end());
        for(auto iter = vecFriend.begin(); iter != vecFriend.end();)
        {

            if(IsFriend(*iter) || IsFans(*iter) || *iter == m_rUser.charid)
            {
                iter = vecFriend.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
        if(vecFriend.size() > pagenum)
        {
            vecFriend.erase(vecFriend.begin() + pagenum,vecFriend.end());
        }

    }
    else
    {
        std::set<QWORD> rset;
        handle->getSet("playerset",0 ,"online" ,rset,pagenum );
        vecFriend.assign(rset.begin(),rset.end());
        for(auto iter = vecFriend.begin(); iter != vecFriend.end();)
        {
            if(*iter == m_rUser.charid)
            {
                iter = vecFriend.erase(iter);
            }
            else
            {
                ++iter;
            }
        }

    }
    if(bsort)
    {
        dosort(vecFriend);
    }

}

void  ManagerFriend::AddFriend(QWORD PlayerB)
{
    if(IsFriend(PlayerB))
        return ;
    m_setFriendUsers.insert(PlayerB);
    noticeOtherAboutMe(PlayerB,HelloKittyMsgData::FriendLineState_AddFriend);
    CMD::RECORD::t_userrelationchange_scenerecord cmd;
    cmd.charidA = m_rUser.charid;
    cmd.charidB = PlayerB;
    cmd.type = 0;
    std::string ret;
    encodeMessage(&cmd,sizeof(cmd),ret); 
    RecordClient *recordClient = MgrrecordClient.GetRecordByTableName("relation");
    if(recordClient)
        recordClient->sendCmd(ret.c_str(),ret.size());
    //通知相关玩家
    do{
        SceneUser* user = SceneUserManager::getMe().getUserByID(PlayerB);
        if(user)
        {
            user->getFriendManager().AddFans(m_rUser.charid);
            break;
        }
        zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(PlayerB % MAX_MEM_DB+1); 
        if(!handle2) 
        {
            Fir::logger->error("找不到Mem,%lu",PlayerB % MAX_MEM_DB+1);
            break;
        }
        DWORD SenceId = handle2->getInt("playerscene",PlayerB,"sceneid"); 
        if(SenceId != 0)
        {
            Fir::logger->error("寻找其他server处理 ，id %d",SenceId); 
            CMD::SCENE::t_setFans_scenescene cmd;
            cmd.charid = PlayerB;
            cmd.fansid = m_rUser.charid;
            cmd.type = 0;
            std::string ret;
            encodeMessage(&cmd,sizeof(cmd),ret);
            if(SceneClientToOtherManager::getMe().SendMsgToOtherScene(SenceId,ret.c_str(),ret.size()))
            {
                break;
            }
        }

    }while(0);




}

void ManagerFriend::KickFriend(QWORD PlayerB)
{
    if(!IsFriend(PlayerB))
    {
        return ;
    }
    m_setFriendUsers.erase(PlayerB);
    noticeOtherAboutMe(PlayerB, HelloKittyMsgData::FriendLineState_KickFriend);

    CMD::RECORD::t_userrelationchange_scenerecord cmd;
    cmd.charidA = m_rUser.charid;
    cmd.charidB = PlayerB;
    cmd.type = 1;
    std::string ret;
    encodeMessage(&cmd,sizeof(cmd),ret); 
    RecordClient *recordClient = MgrrecordClient.GetRecordByTableName("relation");
    if(recordClient)
        recordClient->sendCmd(ret.c_str(),ret.size());
    //通知相关玩家
    do{
        SceneUser* user = SceneUserManager::getMe().getUserByID(PlayerB);
        if(user)
        {
            user->getFriendManager().DelFans(m_rUser.charid);
            break;
        }
        zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(PlayerB % MAX_MEM_DB+1); 
        if(!handle2) 
        {
            Fir::logger->error("找不到Mem,%lu",PlayerB % MAX_MEM_DB+1);
            break;
        }
        DWORD SenceId = handle2->getInt("playerscene",PlayerB,"sceneid"); 
        if(SenceId != 0)
        {
            Fir::logger->error("寻找其他server处理 ，id %d",SenceId); 
            CMD::SCENE::t_setFans_scenescene cmd;
            cmd.charid = PlayerB;
            cmd.fansid = m_rUser.charid;
            cmd.type = 1;
            std::string ret;
            encodeMessage(&cmd,sizeof(cmd),ret);
            if(SceneClientToOtherManager::getMe().SendMsgToOtherScene(SenceId,ret.c_str(),ret.size()))
            {
                break;
            }
        }

    }while(0);

}

void ManagerFriend::AddFans(QWORD PlayerB)
{
    m_setFansUsers.insert(PlayerB);
}
void ManagerFriend::DelFans(QWORD PlayerB)
{
    m_setFansUsers.erase(PlayerB);
}


SWORD ManagerFriend::GetFriendSize()
{
    return m_setFriendUsers.size();


}

void ManagerFriend::GetShowInfoForMe(QWORD PlayerB,HelloKittyMsgData::MemberRelation & member)
{
    CharBase charbase; 
    zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(PlayerB % MAX_MEM_DB+1);
    if (!handle2 ||handle2->getBin("charbase",PlayerB,"charbase",(char*)&charbase) == 0)
    {
        Fir::logger->trace("账号不存在 %lu", PlayerB); 
        return ;
    }
    member.set_playerid(PlayerB);
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if(!handle)
    {
        return;
    }

    bool  OnLineA  = handle->checkSet("playerset",0 ,"online" , PlayerB); 
    DWORD size = 0;
    char tepbuf[zSocket::MAX_DATASIZE];
    size = handle2->getBin("plyerevent", PlayerB, tepbuf,size); 
    if(size > 0)
    {
        HelloKittyMsgData::PlayerEvent* pEvent =  member.mutable_event();
        if(pEvent)
        {
            pEvent->ParseFromArray(tepbuf,size);
        }
    }
    if(OnLineA)
    {
        member.set_loginouttimer(0);
    }
    else
    {
        member.set_loginouttimer(charbase.offlinetime);
    }

    member.set_playername(string(charbase.nickname));
    member.set_typeralation(getFriendForMe(PlayerB));
}

void ManagerFriend::GetShowInfoForOther(QWORD PlayerB,HelloKittyMsgData::MemberRelation & member)
{
    zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(m_rUser.charid % MAX_MEM_DB+1);
    if (!handle2)
    {
        Fir::logger->trace("账号不存在 %lu", m_rUser.charid); 
        return ;
    }
    member.set_playerid(m_rUser.charid);
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if(!handle)
    {
        return;
    }
    bool  OnLineA  = m_rUser.is_online();
    DWORD size = 0;
    char tepbuf[zSocket::MAX_DATASIZE];
    size = handle2->getBin("plyerevent", m_rUser.charid, tepbuf,size); 
    if(size > 0)
    {
        HelloKittyMsgData::PlayerEvent* pEvent =  member.mutable_event();
        if(pEvent)
        {
            pEvent->ParseFromArray(tepbuf,size);
        }
    }
    if(OnLineA)
    {
        member.set_loginouttimer(0);
    }
    else
    {
        member.set_loginouttimer(m_rUser.charbase.offlinetime);
    }

    member.set_playername(string(m_rUser.charbase.nickname));
    member.set_typeralation(getFriendForOther(PlayerB));



}

void ManagerFriend::online()
{
    //得到所有在线好友，通知粉丝上线
    vector<QWORD> vecFriend;
    GetFriendList(0,0,vecFriend,true);
    for(auto iter = vecFriend.begin(); iter != vecFriend.end();iter++)
    {
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_OnLine); 
    }

    //得到所有在线粉丝，好友上线
    vector<QWORD> vecFans;
    GetFansList(0,0,vecFans,true);
    for(auto iter = vecFans.begin(); iter != vecFans.end();iter++)
    {
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_OnLine); 
    }

}

void ManagerFriend::noticeOtherAboutMe(QWORD PlayerB,HelloKittyMsgData::FriendLineState state)
{
    if(!m_rUser.isOtherOnline(PlayerB))
        return ;
    HelloKittyMsgData::FriendFansChangeLine notice;
    notice.set_linestate(state);
    HelloKittyMsgData::MemberRelation* pmember = notice.mutable_member();
    GetShowInfoForOther(PlayerB,*pmember);
    std::string ret;
    encodeMessage(&notice,ret);
    m_rUser.SendMsgToOher(PlayerB,ret.c_str(),ret.size());
}

void ManagerFriend::offline()
{
    //得到所有在线好友，通知粉丝上线
    //得到所有在线粉丝，好友上线
    vector<QWORD> vecFriend;
    GetFriendList(0,0,vecFriend,true);
    for(auto iter = vecFriend.begin(); iter != vecFriend.end();iter++)
    {
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_OffLine);
    }

    vector<QWORD> vecFans;
    GetFansList(0,0,vecFans,true);
    for(auto iter = vecFans.begin(); iter != vecFans.end();iter++)
    {
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_OffLine);
    }

}

HelloKittyMsgData::RlationTypeClient ManagerFriend::getFriendForMe(QWORD PlayerB)
{
    HelloKittyMsgData::RlationTypeClient type = HelloKittyMsgData::RlationTypeClient_None;
    if(IsFriend(PlayerB))
    {
        type = HelloKittyMsgData::RlationTypeClient_IsFriend;

    }
    if(IsFans(PlayerB))
    {
        if(type == HelloKittyMsgData::RlationTypeClient_IsFriend)
        {
            type = HelloKittyMsgData::RlationTypeClient_IsFriend2;
        }
        else
        {
            type = HelloKittyMsgData::RlationTypeClient_IsFans;
        }
    }
    return type;

}

HelloKittyMsgData::RlationTypeClient ManagerFriend::getFriendForOther(QWORD PlayerB)
{
    HelloKittyMsgData::RlationTypeClient type = HelloKittyMsgData::RlationTypeClient_None;
    if(IsFans(PlayerB))
    {
        type = HelloKittyMsgData::RlationTypeClient_IsFriend;

    }
    if(IsFriend(PlayerB))
    {
        if(type == HelloKittyMsgData::RlationTypeClient_IsFriend)
        {
            type = HelloKittyMsgData::RlationTypeClient_IsFriend2;
        }
        else
        {
            type = HelloKittyMsgData::RlationTypeClient_IsFans;
        }
    }
    return type;

}

void ManagerFriend::eventhappen()
{
    vector<QWORD> vecFriend;
    GetFriendList(0,0,vecFriend,true);
    for(auto iter = vecFriend.begin(); iter != vecFriend.end();iter++)
    {
        if(m_rUser.isVisit(*iter))
            continue;
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_EventHappen);
    }

    vector<QWORD> vecFans;
    GetFansList(0,0,vecFans,true);
    for(auto iter = vecFans.begin(); iter != vecFans.end();iter++)
    {
        if(m_rUser.isVisit(*iter))
            continue;
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_EventHappen);
    }
    vector<QWORD> vecOthers;
    GetOtherListOnline(20,vecOthers,true);
    for(auto iter = vecOthers.begin(); iter != vecOthers.end();iter++)
    {
        if(m_rUser.isVisit(*iter))
            continue;
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_EventHappen);
    }

}

void ManagerFriend::eventclose()
{
    vector<QWORD> vecFriend;
    GetFriendList(0,0,vecFriend,true);
    for(auto iter = vecFriend.begin(); iter != vecFriend.end();iter++)
    {
        if(m_rUser.isVisit(*iter))
            continue;
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_EventClose);
    }

    vector<QWORD> vecFans;
    GetFansList(0,0,vecFans,true);
    for(auto iter = vecFans.begin(); iter != vecFans.end();iter++)
    {
        if(m_rUser.isVisit(*iter))
            continue;
        noticeOtherAboutMe(*iter,HelloKittyMsgData::FriendLineState_EventClose);
    }

}

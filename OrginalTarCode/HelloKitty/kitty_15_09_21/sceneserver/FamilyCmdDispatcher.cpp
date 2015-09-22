#include "FamilyCmdDispatcher.h"
#include "SceneUser.h"
#include "SceneUserManager.h"
#include "extractProtoMsg.h"
#include "SceneToOtherManager.h"
#include "SceneTaskManager.h"
#include "RecordFamily.h"
#include "RedisMgr.h"
#include "RecordClient.h"
#include "Misc.h"


bool FamilyCmdHandle::ReqGetFamilyList(SceneUser* User,const HelloKittyMsgData::ReqGetFamilyList *message)
{
    HelloKittyMsgData::AckReqGetFamilyList ack;
    QWORD serchFamilyID = message->familyid();
    ack.set_familyid(serchFamilyID);
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc); 
    if(serchFamilyID > 0)
    {
        if(!RecordFamily::getMe().checkHasfamily(serchFamilyID))
        {
            HelloKittyMsgData::BaseFamilyInfo* pInfo  = ack.add_vecfamily();
            RecordFamily::getMe().readFamily(serchFamilyID,*pInfo,User->charid);
        }
    }
    else
    {
        std::set<QWORD> setApply;
        RecordFamily::getMe().getSelfApplyList(setApply,User->charid);
        for(auto iter = setApply.begin();iter != setApply.end(); iter++)
        {
            HelloKittyMsgData::BaseFamilyInfo* pInfo  = ack.add_vecfamily(); 
            RecordFamily::getMe().readFamily(*iter,*pInfo,User->charid);
        }
        if(setApply.size() < ParamManager::getMe().GetSingleParam(eParam_Family_recommend))
        {
            std::set<QWORD> resApply; 
            RecordFamily::getMe().getFamilyList(resApply,ParamManager::getMe().GetSingleParam(eParam_Family_recommend));
            for(auto it = resApply.begin();(it != resApply.end()) && (setApply.size() < ParamManager::getMe().GetSingleParam(eParam_Family_recommend)) ; it++)
            {
                if(setApply.insert(*it).second)
                {
                    HelloKittyMsgData::BaseFamilyInfo* pInfo  = ack.add_vecfamily(); 
                    RecordFamily::getMe().readFamily(*it,*pInfo,User->charid);

                }

            }

        }
    }
    std::string ret;
    encodeMessage(&ack,ret);
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;

}

bool FamilyCmdHandle::ReqAddFamily(SceneUser* User,const HelloKittyMsgData::ReqAddFamily *message)
{
    HelloKittyMsgData::AckReqAddFamily ack;
    QWORD familyID = message->familyid();
    ack.set_familyid(familyID);
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    std::string strName; 
    do{
        if(!RecordFamily::getMe().checkHasfamily(familyID))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_FamilyNoExist);
            break;
        }
        if(RecordFamily::getMe().GetMemSize(familyID) >= ParamManager::getMe().GetSingleParam(eParam_Family_MemberMax))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_FamilyFull);
            break;
        }
        if(RecordFamily::getMe().getFamilyID(User->charid) > 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_HasFamily);
            break;
        }
        if(!checkFamilyBulid(User))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamilyBuild);
            break;
        }
        CMD::RECORD::FamilyBase base;
        if(!RecordFamily::getMe().readFamily(familyID,base))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_FamilyNoExist);
            break;

        }
        ack.set_familyname(base.m_strName);
        if(base.m_limmitType >= HelloKittyMsgData::MAXPublicType)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_OtherErr);
            break;

        }
        CharBase charbase;
        if(!RedisMgr::getMe().get_charbase(User->charid,charbase))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_OtherErr);
            break;

        }
        if(base.m_lowLevel != 0 && base.m_lowLevel > charbase.level)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_JoinLevelErr);
            break;
        }
        if(base.m_highLevel != 0 && base.m_highLevel < charbase.level)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_JoinLevelErr);
            break;
        }
        zMemDB* handlechar = zMemDBPool::getMe().getMemDBHandle(User->charid%MAX_MEM_DB+1);
        if(handlechar)
        {
            if(handlechar->isLock("playerlock",User->charid,"createfamily"))
            {
                ack.set_result(HelloKittyMsgData::FamilyOpResult_ServerBusy);
                break;
            }

        }
        HelloKittyMsgData::FamilyPublicType publicType = static_cast<HelloKittyMsgData::FamilyPublicType>(base.m_limmitType);
        switch(publicType)
        {
            case HelloKittyMsgData::PublicForAll:
                {
                    ack.set_result(RecordFamily::getMe().addMember(User->charid,familyID));

                }
                break;
            case HelloKittyMsgData::NoPublic:
                {
                    ack.set_result(HelloKittyMsgData::FamilyOpResult_NoPublic);

                }
                break;
            case HelloKittyMsgData::Needapply:
                {
                    if(RecordFamily::getMe().getSelfApplySize(User->charid) >= ParamManager::getMe().GetSingleParam(eParam_Family_ApplyMax))
                    {
                        ack.set_result(HelloKittyMsgData::FamilyOpResult_ApplyMax);
                        break;
                    }
                    ack.set_result(RecordFamily::getMe().addApply(User->charid,familyID));

                }
                break;
            default:
                ack.set_result(HelloKittyMsgData::FamilyOpResult_OtherErr);
                break;
        }

    }while(0);

    std::string ret;
    encodeMessage(&ack,ret);
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;

}

bool FamilyCmdHandle::ReqCancelApply(SceneUser* User,const HelloKittyMsgData::ReqCancelApply *message)
{
    HelloKittyMsgData::AckReqCancelApply ack;
    ack.set_familyid(message->familyid());
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    do{
        if(!RecordFamily::getMe().checkPlayerIsApply(User->charid,message->familyid()))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoApply);  
            break;
        }
        ack.set_result(RecordFamily::getMe().removeApply(User->charid,message->familyid()));
    }while(0);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;

}


HelloKittyMsgData::FamilyOpResult   FamilyCmdHandle::checkFamilyName(const string & strName)
{
    if(strName.size() > ParamManager::getMe().GetSingleParam(eParam_Family_NameMax))
    {
        return HelloKittyMsgData::FamilyOpResult_NameTooLong;
    }
    if(strName.size() < ParamManager::getMe().GetSingleParam(eParam_Family_NameMin))
    {
        return HelloKittyMsgData::FamilyOpResult_NameTooShort;
    }
    return HelloKittyMsgData::FamilyOpResult_Suc;
}

HelloKittyMsgData::FamilyOpResult   FamilyCmdHandle::FamilyCmdHandle::checkFamilyNotice(const string & strNotice)
{   
    if(strNotice.size() > ParamManager::getMe().GetSingleParam(eParam_Family_NameMax))
    {
        return HelloKittyMsgData::FamilyOpResult_NoticeToLong;
    }
    return HelloKittyMsgData::FamilyOpResult_Suc; 
}

bool FamilyCmdHandle::ReqCreateFamily(SceneUser* User,const HelloKittyMsgData::ReqCreateFamily *message)
{
    HelloKittyMsgData::FamilyOpResult result = HelloKittyMsgData::FamilyOpResult_Suc;
    RecordClient *recordClient = MgrrecordClient.GetRecordByTableName("t_family"); 

    do{
        if(NULL == recordClient)
        {
            result = HelloKittyMsgData::FamilyOpResult_OtherErr;
            break;
        }
        if(RecordFamily::getMe().getFamilyID(User->charid) > 0)
        {
            result = HelloKittyMsgData::FamilyOpResult_HasFamily;
            break;
        }
        if(!checkFamilyBulid(User))
        {
            result = HelloKittyMsgData::FamilyOpResult_NoFamilyBuild;
            break;
        }
        if(message->familyicon() == 0)
        {
            result = HelloKittyMsgData::FamilyOpResult_NoIcon;
            break;
        }
        if(message->pulictype() >= HelloKittyMsgData::MAXPublicType)
        {
            result = HelloKittyMsgData::FamilyOpResult_PublicSetErr;
            break;
        }
        if(message->lowlevel() != 0 && message->highlevel() != 0 && message->lowlevel() > message->highlevel())
        {
            result = HelloKittyMsgData::FamilyOpResult_LevelLimitErr;
            break;
        }
        result = checkFamilyName(message->familyname());
        if(result != HelloKittyMsgData::FamilyOpResult_Suc)
        {
            break;
        }
        zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(User->charid%MAX_MEM_DB+1);
        if(handle)
        {
            if(!handle->getLock("playerlock",User->charid,"createfamily",30))
            {
                result = HelloKittyMsgData::FamilyOpResult_ServerBusy;
                break;
            }

        }
        if(!delCreateSource(User))
        {
            result = HelloKittyMsgData::FamilyOpResult_SourceLimit;
            break;
        }

    }while(0);
    if(result != HelloKittyMsgData::FamilyOpResult_Suc)
    {
        HelloKittyMsgData::AckReqCreateFamily ack;
        ack.set_result(result);
        std::string ret;
        encodeMessage(&ack,ret);
        User->sendCmdToMe(ret.c_str(),ret.size());
    }
    else
    {
        CMD::RECORD::t_WriteFamily_SceneRecord cmd;
        cmd.m_base.m_charid =  User->charid;
        sprintf(cmd.m_base.m_strName,message->familyname().c_str(),message->familyname().size());
        cmd.m_base.m_icon = message->familyicon();
        cmd.m_base.m_limmitType = message->pulictype();
        cmd.m_base.m_lowLevel = message->lowlevel();
        cmd.m_base.m_highLevel =message->highlevel();
        std::string ret;
        encodeMessage(&cmd,sizeof(cmd),ret); 
        recordClient->sendCmd(ret.c_str(),ret.size());
    }
    return true;

}


void FamilyCmdHandle::DocreateReturn(const CMD::RECORD::t_WriteFamily_RecordScene_Create_Return *cmd)
{
    //释放创建锁
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(cmd->charid%MAX_MEM_DB+1);
    if(handle)
    {
        handle->delLock("playerlock",cmd->charid,"createfamily");
    }
    SceneUser* User = SceneUserManager::getMe().getUserByID(cmd->charid);
    if(!User)
    {
        LOG_ERR("Can not Find player for  create Family player :%lu ret :%d",cmd->charid,cmd->ret);
        return;

    }
    HelloKittyMsgData::AckReqCreateFamily ack; 
    ack.set_result(cmd->ret == 0 ? HelloKittyMsgData::FamilyOpResult_Suc:HelloKittyMsgData::FamilyOpResult_OtherErr);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());


    if(cmd->ret >0 )//返回资源
    {
        returnCreateSource(User);
    }
    else
    {
        RecordFamily::getMe().removeApply(cmd->charid);
    }

}

bool FamilyCmdHandle::delCreateSource(SceneUser* User)
{
    std::vector<DWORD> vecRes = ParamManager::getMe().GetVecParam(eParam_Family_CreateRes);
    if(vecRes.size() == 2)
    {
      return User->m_store_house.addOrConsumeItem(vecRes[0],vecRes[1],"新建家族扣除",false);
    }
    return true;
}

void FamilyCmdHandle::returnCreateSource(SceneUser* User)
{
    std::vector<DWORD> vecRes = ParamManager::getMe().GetVecParam(eParam_Family_CreateRes);
    if(vecRes.size() == 2)
    {
      User->m_store_house.addOrConsumeItem(vecRes[0],vecRes[1],"新建家族失败返还",true);
    }

}

bool FamilyCmdHandle::ReqAgreeJoin(SceneUser* User,const HelloKittyMsgData::ReqAgreeJoin *message)
{
    HelloKittyMsgData::AckReqAgreeJoin ack;
    ack.set_charid(message->charid());
    ack.set_isagree(message->isagree());
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    do{
        QWORD familyID = RecordFamily::getMe().getFamilyID(User->charid);
        if(familyID == 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoLeader);
            break;
        }
        if(RecordFamily::getMe().getFamilyLeader(familyID) != User->charid)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoLeader);
            break;
        }
        if(!RecordFamily::getMe().checkPlayerIsApply(message->charid(),familyID))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoApply);  
            break;
        }
        if(message->isagree() == 0)
        {
            ack.set_result(RecordFamily::getMe().removeApply(message->charid(),familyID));

        }
        else
        {
            ack.set_result(RecordFamily::getMe().addMember(message->charid(),familyID)); 
        }


    }while(0);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;

}

bool FamilyCmdHandle::ReqselfFamilyInfo(SceneUser* User,const HelloKittyMsgData::ReqselfFamilyInfo *message)
{

    HelloKittyMsgData::AckReqselfFamilyInfo ack;
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    do{
        QWORD familyID = RecordFamily::getMe().getFamilyID(User->charid);
        if(familyID == 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamily);
            break;
        }
        HelloKittyMsgData::FamilyInfo* pselfinfo = ack.mutable_selfinfo();
        if(!pselfinfo)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_OtherErr);
            break;
        }
        HelloKittyMsgData::BaseFamilyInfo* pBase = pselfinfo->mutable_baseinfo();
        if(!pBase)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_OtherErr);
            break;
        }
        if(!RecordFamily::getMe().readFamily(familyID,*pBase,User->charid))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_OtherErr);
            break;
        }
        std::set<QWORD> setMember;
        RecordFamily::getMe().getMember(setMember,familyID);
        for(auto iter = setMember.begin(); iter != setMember.end();iter++)
        {
            HelloKittyMsgData::FamilyMember* pMember = pselfinfo->add_vecmember();
            if(!pMember)
            {
                continue;
            }
            pMember->set_charid(*iter);
            CharBase charbase;
            if(!RedisMgr::getMe().get_charbase(*iter,charbase))
            {
                continue;

            }
            pMember->set_name(charbase.nickname);
            pMember->set_level(charbase.level);
            pMember->set_job(*iter == RecordFamily::getMe().getFamilyLeader(familyID) ? HelloKittyMsgData::Family_Leader : HelloKittyMsgData::Family_Member); 

        }

        std::set<QWORD> setApply;
        RecordFamily::getMe().getApplyPlayer(setApply,familyID);
        for(auto iter = setApply.begin(); iter != setApply.end();iter++)
        {
            HelloKittyMsgData::FamilyMember* pMember = pselfinfo->add_vecappy();
            if(!pMember)
            {
                continue;
            }
            pMember->set_charid(*iter);
            CharBase charbase;
            if(!RedisMgr::getMe().get_charbase(*iter,charbase))
            {
                continue;

            }
            pMember->set_name(charbase.nickname);
            pMember->set_level(charbase.level);

        }

    }while(0);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}


bool FamilyCmdHandle::ReqQuitFamily(SceneUser* User,const HelloKittyMsgData::ReqQuitFamily *message)
{
    HelloKittyMsgData::AckReqQuitFamily ack;
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    do{
        QWORD familyID = RecordFamily::getMe().getFamilyID(User->charid);
        if(familyID == 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamily);
            break;
        }
        if(RecordFamily::getMe().GetMemSize(familyID) > 1)//家族人数大于1，族长不能退
        {

            if(RecordFamily::getMe().getFamilyLeader(familyID) == User->charid)
            {
                ack.set_result(HelloKittyMsgData::FamilyOpResult_LeaderCanNotQuit);
            }
            else
            {
                ack.set_result(RecordFamily::getMe().removeMember(User->charid,familyID));
            }
        }
        else
        {
            ack.set_result(RecordFamily::getMe().removeMember(User->charid,familyID));
            if(RecordFamily::getMe().GetMemSize(familyID) == 0)
            {
                RecordFamily::getMe().doDel(familyID);
            }


        }

    }while(0);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;

}

bool FamilyCmdHandle::ReqUpdateOtherFamilyJob(SceneUser* User,const HelloKittyMsgData::ReqUpdateOtherFamilyJob *message)
{
    HelloKittyMsgData::AckUpdateOtherFamilyJob ack;
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    do{
        QWORD familyID = RecordFamily::getMe().getFamilyID(User->charid);
        if(familyID == 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamily);
            break;
        }
        if(RecordFamily::getMe().getFamilyLeader(familyID) != User->charid)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoLeader);
            break;
        }
        if(User->charid == message->charid())
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_OpSelf);
            break;

        }
        if(RecordFamily::getMe().getFamilyID(message->charid()) != familyID)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamily);
            break;
        }
        CMD::RECORD::FamilyBase base;
        if(!RecordFamily::getMe().readFamily(familyID,base))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_FamilyNoExist);
            break;

        }
        base.m_charid = message->charid();
        RecordFamily::getMe().update(base);

    }while(0);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());

    return true;
}

bool FamilyCmdHandle::ReqKickFamilyMember(SceneUser* User,const HelloKittyMsgData::ReqKickFamilyMember *message)
{
    HelloKittyMsgData::AckReqKickFamilyMember ack;
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    do{
        QWORD familyID = RecordFamily::getMe().getFamilyID(User->charid);
        if(familyID == 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamily);
            break;
        }
        if(RecordFamily::getMe().getFamilyLeader(familyID) != User->charid)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoLeader);
            break;
        }
        if(User->charid == message->charid())
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_OpSelf);
            break;

        }
        if(RecordFamily::getMe().getFamilyID(message->charid()) != familyID)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamily);
            break;
        }
        ack.set_result(RecordFamily::getMe().removeMember(message->charid(),familyID));

    }while(0);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;

}

bool FamilyCmdHandle::ReqSetFamilyBaseInfo(SceneUser* User,const HelloKittyMsgData::ReqSetFamilyBaseInfo *message)
{
    HelloKittyMsgData::AckReqSetFamilyBaseInfo ack;
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    do{
        QWORD familyID = RecordFamily::getMe().getFamilyID(User->charid);
        if(familyID == 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamily);
            break;
        }
        if(RecordFamily::getMe().getFamilyLeader(familyID) != User->charid)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoLeader);
            break;
        }
        if(message->familyicon() == 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoIcon);
            break;
        }
        if(message->pulictype() >= HelloKittyMsgData::MAXPublicType)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_PublicSetErr);
            break;
        }
        if(message->lowlevel() != 0 && message->highlevel() != 0 && message->lowlevel() > message->highlevel())
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_LevelLimitErr);
            break;
        }
        ack.set_result(checkFamilyNotice(message->familynotice()));
        if(ack.result() != HelloKittyMsgData::FamilyOpResult_Suc)
        {
            break;
        }
        CMD::RECORD::FamilyBase base;
        if(!RecordFamily::getMe().readFamily(familyID,base))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_FamilyNoExist);
            break;

        }
        base.m_icon = message->familyicon();
        base.m_limmitType = message->pulictype();
        base.m_lowLevel = message->lowlevel();
        base.m_highLevel =message->highlevel();
        sprintf(base.m_notice,message->familynotice().c_str(),message->familynotice().size());
        RecordFamily::getMe().update(base);

    }while(0);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;

}


bool FamilyCmdHandle::ReqFamilyRanking(SceneUser* User,const HelloKittyMsgData::ReqFamilyRanking *message)
{
    HelloKittyMsgData::AckReqFamilyRanking ack; 
    ack.set_result(HelloKittyMsgData::FamilyOpResult_Suc);
    do{//TODO:
        QWORD familyID = RecordFamily::getMe().getFamilyID(User->charid);
        if(familyID == 0)
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_NoFamily);
            break;
        }
        CMD::RECORD::FamilyBase base;
        if(!RecordFamily::getMe().readFamily(familyID,base))
        {
            ack.set_result(HelloKittyMsgData::FamilyOpResult_FamilyNoExist);
            break;

        }
        zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle();
        if(!handle2)
            break;
        //1- 10名
        for(int i = 1; i <= int(ParamManager::getMe().GetSingleParam(eParam_Family_TopLen)) ;i++)
        {
            QWORD  fID =  handle2->getInt("family",i,"Rank");
            if(fID > 0)
            {
                HelloKittyMsgData::BaseFamilyInfo* pInfo  = ack.add_vecfamily(); 
                RecordFamily::getMe().readFamily(fID,*pInfo,User->charid);
            }
        }
        //自己前两名
        if(base.m_ranking == 0)
        {
            HelloKittyMsgData::BaseFamilyInfo* pInfo  = ack.add_vecfamily(); 
            RecordFamily::getMe().readFamily(familyID,*pInfo,User->charid);

        }
        else 
        {
            int nowRank = base.m_ranking;
            for(int rank = nowRank -ParamManager::getMe().GetSingleParam(eParam_Family_NearRank); rank <= int(nowRank +ParamManager::getMe().GetSingleParam(eParam_Family_NearRank)) ;rank++)
            {
                if(rank <= int(ParamManager::getMe().GetSingleParam(eParam_Family_TopLen)))
                {
                    continue;
                }
                QWORD  fID =  handle2->getInt("family",rank,"Rank");
                if(fID > 0)
                {
                    HelloKittyMsgData::BaseFamilyInfo* pInfo  = ack.add_vecfamily(); 
                    RecordFamily::getMe().readFamily(fID,*pInfo,User->charid);
                }

            }
        }
        //自己后两名
    }while(0);
    std::string ret;    
    encodeMessage(&ack,ret);  
    User->sendCmdToMe(ret.c_str(),ret.size());
    return true;



}

bool FamilyCmdHandle::checkFamilyBulid(SceneUser* User)
{
    return User->m_buildManager.getAnyBuildById(ParamManager::getMe().GetSingleParam(eParam_Family_CreateNeedBulid)) > 0 ;

}



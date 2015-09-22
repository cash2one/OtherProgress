#include "buildBase.h"
#include "TimeTick.h"
#include "tbx.h"
#include "SceneUser.h"
#include "key.h"
#include "SceneMapData.h"
#include "buildLandMark.h"
#include "usecardbuild.pb.h"
#include "buffer.h"

QWORD BuildBase::generateID = 0;

BuildBase::BuildBase(SceneUser* owner,const DWORD typeID,const DWORD level,const Point &point,const bool active) : m_owner(owner),m_typeID(typeID),m_level(level),m_point(point)
{
    m_mark = HelloKittyMsgData::Build_Status_Normal;
    m_durTime = 0;
    m_produceTime = SceneTimeTick::currentTime.sec();
    m_rationMark = false;
    m_isActive = false;
    m_cardID = 0;
    m_useCardTime = 0;
    ++generateID;
    m_id = generateID;
    initConfBase();
}

BuildBase::BuildBase(SceneUser* owner,const pb::Conf_t_building *buildConf,const Point &point) : m_owner(owner),m_typeID(buildConf->buildInfo->dependid()),m_level(buildConf->buildInfo->level()),m_point(point)
{
    m_mark = HelloKittyMsgData::Build_Status_Normal;
    m_durTime = 0; 
    m_produceTime = SceneTimeTick::currentTime.sec();
    m_rationMark = false;
    m_isActive = false;
    m_cardID = 0;
    m_useCardTime = 0;
    ++generateID;
    m_id = generateID;
    confBase = buildConf;
}

BuildBase::BuildBase(SceneUser* owner,const HelloKittyMsgData::BuildBase &buildBase) : m_owner(owner),m_typeID(buildBase.type()),m_level(buildBase.level()),m_point(buildBase.point().x(),buildBase.point().y()),m_mark(buildBase.status()),m_rationMark(buildBase.rotationmark())
{
    m_durTime = buildBase.durtime();
    m_produceTime = buildBase.producetime();
    m_isActive = false;
    m_cardID = 0;
    m_useCardTime = 0;
    ++generateID;
    m_id = generateID;
    initConfBase();
}

BuildBase::~BuildBase()
{
}

void BuildBase::save(HelloKittyMsgData::BuildBase *buildBase)
{
    buildBase->set_tempid(m_id);
    buildBase->set_type(m_typeID);
    buildBase->set_level(m_level);
    buildBase->set_status(m_mark);
    buildBase->set_durtime(m_durTime);
    buildBase->set_producetime(m_produceTime);
    buildBase->set_rotationmark(m_rationMark);
    buildBase->set_active(m_isActive);
    HelloKittyMsgData::Point *point = buildBase->mutable_point();
    point->set_x(m_point.x);
    point->set_y(m_point.y);
}

bool BuildBase::flush()
{

    HelloKittyMsgData::AckFlushOneBuild flushBuild;
    flushBuild.set_updatecharid(m_owner->charid);
    HelloKittyMsgData::BuildBase *buildBase = flushBuild.mutable_buildinfo();
    save(buildBase);

    std::string ret;
    if(encodeMessage(&flushBuild,ret))
    {
         m_owner->sendCmdToMe(ret.c_str(),ret.size());
    }
    return true;
}


bool BuildBase::initConfBase()
{
    QWORD key = hashKey(m_typeID,m_level);
    confBase = tbx::building().get_base(key);
    if(!confBase)
    {
        Fir::logger->error("[初始化建筑错误]:在配表中找不到对应的建筑信息 %u,%u",m_typeID,m_level);
        return false;
    }
    return true;
}

bool BuildBase::checkDependBuildMap(const std::map<DWORD,DWORD> &dependBuildMap)
{
    const std::unordered_map<DWORD,std::set<QWORD> >&buildTypeMap = m_owner->m_buildManager.getBuildTypeMap();
    for(auto iter = dependBuildMap.begin();iter != dependBuildMap.end();++iter)
    {
        auto iterType = buildTypeMap.find(iter->first);
        if(iterType == buildTypeMap.end())
        {
            return false;
        }
        const std::set<QWORD> &tempIdSet = iterType->second;
        for(auto iterid = tempIdSet.begin();iterid != tempIdSet.end();++iterid)
        {
            BuildBase *depend = m_owner->m_buildManager.getBuild(*iterid);
            if(!depend || depend->getLevel() < iter->second)
            {
                return false;
            }
        }
    }
    return true;
}

bool BuildBase::build(const Point &buildPoint,const bool initFlg,const bool rationFlg)
{
    if(!m_owner->m_kittyGarden.checkPoint(this,buildPoint,rationFlg))
    {
        return false;
    }
    m_owner->m_kittyGarden.addBuildPoint(this,buildPoint,rationFlg);
    
    m_rationMark = rationFlg;
    //新建角色时，不发消息
    if(!initFlg)
    {
        opSuccessReturn(HelloKittyMsgData::Build_Building);
    }
    
    BuildTypeLandMark* temp = NULL;
    if(isTypeBuid(Build_Type_Land_Mark))
    {
        temp = dynamic_cast<BuildTypeLandMark*>(this);
        if(temp)
        {
            temp->checkBuffer(true);
        }
    }
    if(!initFlg)
    {
        HelloKittyMsgData::DailyData *dailyData = m_owner->charbin.mutable_dailydata();
        dailyData->set_buildorlevel(1 + dailyData->buildorlevel());
        TaskArgue arg(Target_Build,Attr_Add_Build_or_Level,Attr_Add_Build_or_Level,dailyData->buildorlevel());
        m_owner->m_taskManager.target(arg);
    }
    
    AchieveArg achieveArg(Achieve_Target_Have,Achieve_Sub_Buid_Level,m_typeID,m_level);
    m_owner->m_achievementManager.target(achieveArg);

    AchieveArg achieveArg1(Achieve_Target_Have,Achieve_Sub_Build_Num,m_typeID,m_level);
    m_owner->m_achievementManager.target(achieveArg1);
    return true;
}



bool BuildBase::upGrade(const bool gmFlg)
{
    QWORD key = hashKey(m_typeID,m_level+1);
    const pb::Conf_t_building *tempConf = tbx::building().get_base(key);
    if(!tempConf)
    {
        opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Build_Full_Level);
        return false;
    }
    if(!gmFlg && !checkDependBuildMap(confBase->getDependBuildMap()))
    {
        opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Build_Premise_Limit);
        return false;
    }
    if(!gmFlg && !m_owner->checkMaterialMap(confBase->getMaterialMap()))
    {
        opFailReturn(HelloKittyMsgData::Material_Not_Enough);
        return false;
    }
    if(!gmFlg && !m_owner->m_store_house.checkAttr(HelloKittyMsgData::Attr_Gold,confBase->buildInfo->requiregold()))
    {
        opFailReturn(HelloKittyMsgData::Gold_Not_Enough);
        return false;
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"建筑升级(%lu,%u,%u)",m_id,m_typeID,m_level);
    if(!gmFlg && !m_owner->reduceMaterialMap(confBase->getMaterialMap(),temp))
    {
        opFailReturn(HelloKittyMsgData::Material_Not_Enough);
        return false;
    }
    
    bzero(temp,sizeof(temp));
    snprintf(temp,sizeof(temp),"建筑(%lu,%u)升级消耗",m_id,m_typeID);
    if(!gmFlg && !m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,confBase->buildInfo->requiregold(),temp,false))
    {
        opFailReturn(HelloKittyMsgData::Gold_Not_Enough);
        return false;
    }
    m_level += 1;
    initConfBase();
    opSuccessReturn(HelloKittyMsgData::Build_Up_Grade); 
    
    HelloKittyMsgData::DailyData *dailyData = m_owner->charbin.mutable_dailydata();
    dailyData->set_buildorlevel(1 + dailyData->buildorlevel());

    TaskArgue arg(Target_Build,Attr_Add_Build_or_Level,Attr_Add_Build_or_Level,dailyData->buildorlevel());
    m_owner->m_taskManager.target(arg); 
    
    TaskArgue arg1(Target_Build,Attr_Build,m_typeID,m_level);
    m_owner->m_taskManager.target(arg1); 


    AchieveArg achieveArg(Achieve_Target_Have,Achieve_Sub_Buid_Level,m_typeID,m_level);
    m_owner->m_achievementManager.target(achieveArg);
    
    AchieveArg achieveArg1(Achieve_Target_Have,Achieve_Sub_Build_Num,m_typeID,m_level);
    m_owner->m_achievementManager.target(achieveArg1);
    return true;
}


bool BuildBase::changeStatus(const HelloKittyMsgData::BuildStatueType &status)
{
    m_mark = status;
    return true;
}

bool BuildBase::movePlace(const HelloKittyMsgData::ReqBuildMovePlace *message)
{
    Point buildPoint(message->point());
    Point oldPoint(m_point);
    if(!move(buildPoint,message->moveflg()))
    {
        return false;
    }
    m_rationMark = message->moveflg();
    opSuccessReturn(HelloKittyMsgData::Build_Move,oldPoint);
    return true;
}

bool BuildBase::move(const Point &buildPoint,const bool rationFlg)
{
    if(!m_owner->m_kittyGarden.checkPoint(this,buildPoint,rationFlg))
    {
        return false;
    }
    BuildTypeLandMark* temp = NULL;
    if(isTypeBuid(Build_Type_Land_Mark))
    {
        temp = dynamic_cast<BuildTypeLandMark*>(this);
        if(temp)
        {
            temp->checkBuffer(false);
        }
    }
    m_owner->m_kittyGarden.eraseBuildPoint(this);
    m_owner->m_kittyGarden.addBuildPoint(this,buildPoint,rationFlg);
    m_point = buildPoint;
    if(temp)
    {
        temp->checkBuffer(true);
    }
    return true;
}

bool BuildBase::loop()
{
    if(m_cardID)
    {
        return true;
    }
    const pb::Conf_t_itemInfo* base = tbx::itemInfo().get_base(m_cardID); 
    if(!base)
    {
        return true;
    }

    m_cardID = 0;
    m_useCardTime = 0;
    updateCard();
    return true;
}

bool BuildBase::opSuccessReturn(const HelloKittyMsgData::BuildSuccessCodeType &code,const Point &oldPoint)
{
    HelloKittyMsgData::AckBuildOpReturnSuccess opReturn;
    opReturn.set_updatecharid(m_owner->charid);
    opReturn.set_code(code);
    opReturn.set_tempid(m_id);
    HelloKittyMsgData::BuildBase *buildBase = opReturn.mutable_buildinfo();
    if(!buildBase)
    {
        return false;
    }
    save(buildBase);
    
    HelloKittyMsgData::Point *pt = opReturn.mutable_oldpoint();
    pt->set_x(oldPoint.x);
    pt->set_y(oldPoint.y);

    std::string ret;
    encodeMessage(&opReturn,ret);
    m_owner->broadcastMsgInMap(ret.c_str(),ret.size());
    return true;
}

bool BuildBase::opFailReturn(const HelloKittyMsgData::ErrorCodeType &commonError,const HelloKittyMsgData::BuildFailCodeType &code)
{
    HelloKittyMsgData::AckBuildOpReturnFail opReturn;
    opReturn.set_commoncode(commonError);
    opReturn.set_code(code);
    opReturn.set_tempid(m_id);
    HelloKittyMsgData::BuildBase *buildBase = opReturn.mutable_buildinfo();
    if(!buildBase)
    {
        return false;
    }
    save(buildBase);

    std::string ret;
    encodeMessage(&opReturn,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

void BuildBase::beginActive()
{
    m_mark ^= HelloKittyMsgData::Build_Status_Stop;
    m_produceTime = SceneTimeTick::currentTime.sec();
}

void BuildBase::countDurTime()
{
    DWORD nowTime = SceneTimeTick::currentTime.sec();
    if(m_mark & HelloKittyMsgData::Build_Status_Normal)
    {
        m_durTime += (nowTime - m_produceTime);
    }
    m_mark |= HelloKittyMsgData::Build_Status_Stop;
}

void BuildBase::saveAsWareHouseBuildBase(WareHouseBuildBase &info)
{
    info.typeID = m_typeID;
    info.level = m_level;
    info.produceTime = m_produceTime;
    info.mark = m_mark;
    info.durTime = m_durTime;
    info.num = 1;
}

bool BuildBase::recycle(const DWORD itemID,const DWORD itemNum)
{
    DWORD nowTime = SceneTimeTick::currentTime.sec();
    if((nowTime - m_produceTime + m_durTime) < confBase->buildInfo->selltime())
    {
        opFailReturn(HelloKittyMsgData::Build_In_CD);
        return false;
    }
    if(!m_owner->m_store_house.hasEnoughItem(itemID,itemNum) || !m_owner->m_store_house.sallSystem(itemID,itemNum))
    {
        m_owner->opErrorReturn(HelloKittyMsgData::Item_Not_Enough);
        return false;
    }
    m_durTime = 0;
    m_produceTime = nowTime;
    flush();
    return true;
}

bool BuildBase::updateBufferMsg()
{
    HelloKittyMsgData::AckUpdateBuffer update;
    HelloKittyMsgData::BufferInfo *buffer = update.mutable_bufferinfo();
    if(!buffer)
    {
        return false;
    }
    buffer->set_tempid(m_id);
    for(auto iter = m_bufferMap.begin();iter != m_bufferMap.end();++iter)
    {
        const std::map<DWORD,Buffer> &tempMap = iter->second;
        for(auto it = tempMap.begin();it != tempMap.end();++it)
        {
            HelloKittyMsgData::BufferData *temp = buffer->add_bufferdata();
            if(!temp)
            {
                continue;
            }
            const Buffer& bufferTemp = it->second;
            bufferTemp.save(*temp);
        }
    }

    std::string ret;
    encodeMessage(&update,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool BuildBase::fullUserInfoMsg(HelloKittyMsgData::UserBaseInfo &useInfo)
{
    if(m_bufferMap.empty() || isTypeBuid(Build_Type_Road) || isTypeBuid(Build_Type_Land_Mark))
    {
        return true;
    }
    HelloKittyMsgData::BufferInfo *buffer = useInfo.add_bufferinfo();
    if(!buffer)
    {
        return false;
    }
    buffer->set_tempid(m_id);
    for(auto iter = m_bufferMap.begin();iter != m_bufferMap.end();++iter)
    {
        const std::map<DWORD,Buffer> &tempMap = iter->second;
        for(auto it = tempMap.begin();it != tempMap.end();++it)
        {
            HelloKittyMsgData::BufferData *temp = buffer->add_bufferdata();
            if(!temp)
            {
                continue;
            }
            const Buffer& bufferTemp = it->second;
            bufferTemp.save(*temp);
        }
    }
    return true;
}

bool BuildBase::fullUserCard(HelloKittyMsgData::UserBaseInfo &useInfo)
{
    if(!m_cardID)
    {
        return false;
    }
    HelloKittyMsgData::UseCardInfo *temp = useInfo.add_usecard();
    if(!temp)
    {
        return false;
    }
    temp->set_tempid(m_id);
    temp->set_cardid(m_cardID);
    temp->set_usecardtime(m_useCardTime);
    return true;
}

bool BuildBase::saveCard(HelloKittyMsgData::Serialize& binary)
{
    if(!m_cardID)
    {
        return false;
    }
    HelloKittyMsgData::UseCardInfo *temp = binary.add_usecard();
    if(!temp)
    {
        return false;
    }
    temp->set_tempid(m_id);
    temp->set_cardid(m_cardID);
    temp->set_usecardtime(m_useCardTime);
    return true;
}

bool BuildBase::loadCard(const HelloKittyMsgData::UseCardInfo &temp)
{
    m_cardID = temp.cardid();
    m_useCardTime = temp.usecardtime();
    return true;
}

bool BuildBase::updateCard()
{
    HelloKittyMsgData::AckUpdateCard ackMessage;
    HelloKittyMsgData::UseCardInfo *temp = ackMessage.mutable_cardinfo();
    if(!temp)
    {
        return false;
    }
    temp->set_tempid(m_id);
    temp->set_cardid(m_cardID);
    temp->set_usecardtime(m_useCardTime);

    std::string ret;
    encodeMessage(&ackMessage,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool BuildBase::useCard(const DWORD card)
{
    const pb::Conf_t_itemInfo* base = tbx::itemInfo().get_base(card);
    if(m_cardID || !base)
    {
        return false;
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"建筑使用卡牌(%lu,%u,%u)",m_id,m_typeID,m_level);
    if(!m_owner->m_store_house.addOrConsumeItem(card,1,temp,false))
    {
        return m_owner->opErrorReturn(HelloKittyMsgData::Material_Not_Enough);
    }
    m_cardID = card;
    m_useCardTime = SceneTimeTick::currentTime.sec();
    m_owner->m_buildManager.opCardSet(m_cardID,m_id);
    updateCard();
    opBuffer(this,card,HelloKittyMsgData::BST_Item,base->getBufferMap(),true,true);
    return true;
}

bool BuildBase::clearCard()
{
    const pb::Conf_t_itemInfo* base = tbx::itemInfo().get_base(m_cardID);
    if(!m_cardID || !base)
    {
        return false;
    }
    m_owner->m_buildManager.opCardSet(m_cardID,m_id,false);
    opBuffer(this,m_cardID,HelloKittyMsgData::BST_Item,base->getBufferMap(),false,true);
    m_cardID = 0;
    m_useCardTime = 0; 
    updateCard();
    return true;
}

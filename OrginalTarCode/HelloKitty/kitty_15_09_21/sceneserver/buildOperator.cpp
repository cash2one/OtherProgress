#include "buildManager.h"
#include "SceneUser.h"
#include "tbx.h"
#include "key.h"
#include "warehouse.pb.h"
#include "taskAttr.h"
#include "TimeTick.h"
#include "SceneTaskManager.h"
#include "SceneUserManager.h"
#include "zMemDBPool.h"
#include "SceneToOtherManager.h"
#include "SceneMail.h"
#include "buildItemProduce.h"

//建筑一般性功能

bool BuildManager::gmUpGrade(const DWORD typeID,const DWORD level)
{
    auto iter = m_buildTypeMap.find(typeID);
    if(iter == m_buildTypeMap.end())
    {
        return false;
    }
    const std::set<QWORD> &tempSet = iter->second;
    for(auto temp = tempSet.begin();temp != tempSet.end();++temp)
    {
        BuildBase *build = getBuild(*temp);
        if(!build || build->getLevel() >= level)
        {
            continue;
        }
        for(int index = level - build->getLevel();index > 0;--index)
        {
            if(!build->upGrade(true))
            {
                break;
            }
        }
    }
    return true;
}

bool BuildManager::gmUpGrade(const DWORD level)
{
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        BuildBase *build = getBuild(iter->first);
        if(!build || build->getLevel() >= level)
        {
            continue;
        }
        for(int index = level - build->getLevel();index > 0;--index)
        {
            if(!build->upGrade(true))
            {
                break;
            }
        }
    }
    return true;
}


bool BuildManager::upGrade(const QWORD tempid)
{
    BuildBase *build = getBuild(tempid);
    if(!build)
    {
        return false;
    }

    if(findIdleWorkerNum() < BUILD_WORKER_NUM)
    {
        m_owner->opErrorReturn(HelloKittyMsgData::Worker_Not_Enough);
        return false;
    }

    QWORD key = hashKey(build->getTypeID(),build->getLevel()+1);
    const pb::Conf_t_building *tempConf = tbx::building().get_base(key);
    if(!key || !build->upGrade())
    {
        return false;
    }

    work(build->getID(),tempConf->buildInfo->time());
    const pb::Conf_t_CarnivalData *carnival = tbx::CarnivalData().get_base(1);
    if(carnival)
    {
        m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Carnival_Val,carnival->carnival->rewardpoint(),"升级增加",true);
    }
    return true;
}

bool BuildManager::move(const HelloKittyMsgData::ReqBuildMovePlace *message)
{
    BuildBase *build = getBuild(message->tempid());
    if(!build)
    {
        return false;
    }
    bool ret = build->movePlace(message);
    if(ret)
    {
        checkBuildActive();
    }
    return ret;
}

bool BuildManager::checkPreBuild(const DWORD typeID,const DWORD level,const bool needWorkerFlg)
{
    QWORD key = hashKey(typeID,level);
    const pb::Conf_t_building *buildConf = tbx::building().get_base(key);
    if(!buildConf || buildConf->buildInfo->buildkind() == Build_Type_Road)
    {
        Fir::logger->error("[建造建筑错误]:建筑类型id非法 %s,%lu,%u",m_owner->nickname,m_owner->charid,typeID);
        return false;
    }

    if(needWorkerFlg && findIdleWorkerNum() < BUILD_WORKER_NUM)
    {
        m_owner->opErrorReturn(HelloKittyMsgData::Worker_Not_Enough);
        return false;
    }
    
    DWORD sum = 0;
    if(m_wareHouseTypeMap.find(typeID) != m_wareHouseTypeMap.end())
    {
        sum += m_wareHouseTypeMap[typeID];
    }
    if(m_buildTypeMap.find(typeID) != m_buildTypeMap.end())
    {
        sum += m_buildTypeMap[typeID].size();
    }
    if(sum >= buildConf->buildInfo->maxcap())
    {
        BuildBase *build = NULL;
        if(m_buildTypeMap.find(typeID) != m_buildTypeMap.end())
        {
            std::set<QWORD> &tempSet = m_buildTypeMap[typeID];
            build = getBuild(*(tempSet.begin()));
        }
        else
        {
            build = (m_buildMap.begin())->second;
        }
        if(build)
        {
            build->opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Build_Type_Enough);
            return false;
        }
    }
    return true;
}

bool BuildManager::asistBuild(BuildBase *build,const DWORD workCD,const bool rationFlg,const HelloKittyMsgData::Point &point)
{
    if(!addBuild(build))
    {
        SAFE_DELETE(build);
        return false;
    }
    build->setPoint(point);
    if(!build->build(point,false,rationFlg))
    {
        deleteBuild(build->getID());
        return false;
    }
    checkBuildActive();
    work(build->getID(),workCD);
    initTypeBuild(build);
    TaskArgue arg(Target_Build,Attr_Build,build->getTypeID(),build->getLevel());
    m_owner->m_taskManager.target(arg);
    const pb::Conf_t_CarnivalData *carnival = tbx::CarnivalData().get_base(1);
    if(carnival)
    {
        m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Carnival_Val,carnival->carnival->rewardpoint(),"建造增加",true);
    }
    return true;
}



bool BuildManager::build(const DWORD typeID,const DWORD level,const bool rationFlg,const HelloKittyMsgData::Point &point)
{
    if(!checkPreBuild(typeID,level))
    {
        return false;
    }
    QWORD key = hashKey(typeID,level);
    const pb::Conf_t_building *buildConf = tbx::building().get_base(key);
    if(!buildConf)
    {
        return false;
    }
    BuildBase *build = newBuild(buildConf);
    if(!build)
    {
        return false;
    }
    return asistBuild(build,buildConf->buildInfo->time(),rationFlg,point);
}

bool BuildManager::buildRoad(const HelloKittyMsgData::ReqBuildRoad *cmd)
{
    DWORD typeID = cmd->type();
    QWORD key = hashKey(typeID,1);
    const pb::Conf_t_building *buildConf = tbx::building().get_base(key);
    if(!buildConf)
    {
        Fir::logger->error("[建造建筑错误]:建筑类型id非法 %s,%lu,%u",m_owner->nickname,m_owner->charid,typeID);
        return false;
    }
    bool ret = true;
    std::vector<QWORD> buildRoadVec;
    for(int index = 0;index < cmd->point_size();++index)
    {
        BuildBase *build = newBuild(buildConf);
        if(!build)
        {
            continue;
        }
        build->setActive(true);
        if(!addBuild(build))
        {
            SAFE_DELETE(build);
            ret = false;
            break;
        }
        buildRoadVec.push_back(build->getID());
        const HelloKittyMsgData::Point &point = cmd->point(index);
        build->setPoint(point);
        if(!build->build(point,false,false))
        {
            ret = false;
            break;
        }
        m_emptyRoadSet.insert(build->getID());
    }
    if(!ret)
    {
        for(auto iter = buildRoadVec.begin();iter != buildRoadVec.end();++iter)
        {
            deleteBuild(*iter);
            m_emptyRoadSet.erase(*iter);
        }
    }
    else
    {
        TaskArgue arg(Target_Build,Attr_Build,typeID,1);
        m_owner->m_taskManager.target(arg);
    }
    checkBuildActive();
    return true;
}

bool BuildManager::clearRoad(const HelloKittyMsgData::ReqClearRoad *cmd)
{
    for(int index = 0;index < cmd->tempid_size();++index)
    {
        if(m_rubbishMap.find(cmd->tempid(index)) != m_rubbishMap.end())
        {
            m_rubbishMap.erase(cmd->tempid(index));
        }
        if(m_burstEventMap.find(cmd->tempid(index)) != m_burstEventMap.end())
        {
            m_owner->m_burstEventManager.delEvent(cmd->tempid(index),HelloKittyMsgData::BES_Del_Road);
        }
        m_owner->m_activeManger.destroyRoad(cmd->tempid(index));
        deleteBuild(cmd->tempid(index));
        m_emptyRoadSet.erase(cmd->tempid(index));
    }
    checkBuildActive();
    return true;
}

bool BuildManager::build(const WareHouseBuildBase &buildBase,const bool rationFlg,const HelloKittyMsgData::Point &point)
{
    if(!checkPreBuild(buildBase.typeID,buildBase.level,false))
    {
        return false;
    }
    QWORD key = hashKey(buildBase.typeID,buildBase.level);
    const pb::Conf_t_building *buildConf = tbx::building().get_base(key);
    BuildBase *build = newBuild(buildConf);
    if(!buildConf || !build)
    {
        SAFE_DELETE(build);
        return false;
    }
    build->setMark(buildBase.mark ^ HelloKittyMsgData::Build_Status_Stop);
    build->setDurTime(buildBase.durTime);
    return asistBuild(build,buildConf->buildInfo->time(),rationFlg,point);
}



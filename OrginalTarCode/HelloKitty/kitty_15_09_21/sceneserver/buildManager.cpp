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
#include "buildTypeProduceGold.h"
#include "buildLandMark.h"
#include "buildItemComposite.h"

BuildManager::BuildManager(SceneUser *owner) : m_owner(owner)
{
    m_maxCellID = 0;
    m_wareHouseBuildMap.clear();
    m_cellSet.clear();
}

BuildManager::~BuildManager()
{
    m_owner = NULL;
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        BuildBase *build = iter->second;
        SAFE_DELETE(build);
    }
    m_buildMap.clear();
}

void BuildManager::reset()
{
    m_workerMap.clear();
    m_buildMap.clear();
    m_buildTypeMap.clear();
    m_wareHouseBuildMap.clear();
}

BuildBase* BuildManager::newBuild(const pb::Conf_t_building *argConf,const HelloKittyMsgData::BuildBase *buidBase)
{
    BuildBase *build = NULL;
    if(!((argConf && !buidBase) || (!argConf && buidBase)))
    {
        return build;
    }
    const pb::Conf_t_building *buildConf = argConf;
    if(!buildConf)
    {
        QWORD key = hashKey(buidBase->type(),buidBase->level());
        buildConf = tbx::building().get_base(key);
        if(!buildConf)
        {
            Fir::logger->error("[建筑错误]:新建建筑信息错误 %s,%lu,%u,%u",m_owner->nickname,m_owner->charid,buidBase->type(),buidBase->level());
            return build;
        }
    }
    switch(buildConf->buildInfo->buildkind())
    {
        case Build_Type_Item_Produce:
            {
                build = buidBase ? new BuildTypeProduceItem(m_owner,*buidBase) : new BuildTypeProduceItem(m_owner,buildConf);
            }
            break;
        case Build_Type_Gold_Produce:
            {
                build = buidBase ? new BuildTypeProduceGold(m_owner,*buidBase) : new BuildTypeProduceGold(m_owner,buildConf);
            }
            break;
        case Build_Type_Land_Mark:
            {
                build = buidBase ? new BuildTypeLandMark(m_owner,*buidBase) : new BuildTypeLandMark(m_owner,buildConf);
            }
            break;
        case Build_Type_Item_Composite:
            {
                build = buidBase ? new BuildTypeCompositeItem(m_owner,*buidBase) : new BuildTypeCompositeItem(m_owner,buildConf);
            }
            break;
        default:
            {
                build = buidBase ? new BuildBase(m_owner,*buidBase) : new BuildBase(m_owner,buildConf);
            }
            break;
    }
    return build;
}

bool BuildManager::init(const pb::Conf_t_newRoleAttr *confBase)
{
    reset();
    //初始化工人数据
    for(DWORD num = 0;num < m_owner->m_store_house.getAttr(HelloKittyMsgData::Attr_Worker);++num)
    {
        HelloKittyMsgData::Worker worker;
        worker.set_id(num+1);
        worker.set_starttime(0);
        worker.set_cd(0);
        worker.set_lastsec(0);
        worker.set_build(0);
        m_workerMap.insert(std::pair<DWORD,HelloKittyMsgData::Worker>(worker.id(),worker));
    }

    const std::set<pb::InitBuildInfo> buildLevelSet = confBase->getBuildLevelSet();
    for(auto iter = buildLevelSet.begin();iter != buildLevelSet.end();++iter)
    {
        const pb::InitBuildInfo &initBuildInfo = *iter;
        QWORD key = hashKey(initBuildInfo.buildID,initBuildInfo.buildLevel);
        const pb::Conf_t_building *buildConf = tbx::building().get_base(key);
        if(!buildConf)
        {
            Fir::logger->error("[建筑错误]:新建角色属性中建筑信息错误 %s,%lu,%u,%u",m_owner->nickname,m_owner->charid,initBuildInfo.buildID,initBuildInfo.buildLevel);
            return false;
        }
        BuildBase *build = newBuild(buildConf);
        if(!build)
        {
            return false;
        }
        build->setPoint(initBuildInfo.point);
        if(!addBuild(build))
        {
            SAFE_DELETE(build);
            return false;
        }
        if(!build->build(build->getPoint(),true))
        {
            deleteBuild(build->getID());
            return false;
        }
        initTypeBuild(build);
    }
    checkBuildActive();
    return true;
}

bool BuildManager::addBuild(BuildBase *build)
{
    if(!build)
    {
        return false;
    }

    auto iter = m_buildMap.find(build->getID());
    if(iter != m_buildMap.end())
    {
        Fir::logger->error("[建筑错误]:建筑id分配器重复 %s,%lu,%lu",m_owner->nickname,m_owner->charid,BuildBase::generateID);
        return false;
    }
    m_buildMap.insert(std::pair<QWORD,BuildBase*>(build->getID(),build));

    auto iter1 = m_buildTypeMap.find(build->getTypeID());
    if(iter1 == m_buildTypeMap.end())
    {
        std::set<QWORD> tempIdSet;
        m_buildTypeMap.insert(std::pair<DWORD,std::set<QWORD>>(build->getTypeID(),tempIdSet));
    }
    std::set<QWORD> &tempIdSet = m_buildTypeMap[build->getTypeID()];
    if(tempIdSet.find(build->getID()) != tempIdSet.end())
    {
        Fir::logger->error("[建筑错误]:建筑id分配器重复 %s,%lu,%lu",m_owner->nickname,m_owner->charid,BuildBase::generateID);
        return false;
    }
    tempIdSet.insert(build->getID());
    opKindType(build->getID());
    return true;
}

bool BuildManager::deleteBuild(const QWORD tempid)
{
    BuildBase *build = getBuild(tempid);
    if(!build)
    {
        return true;
    }
    if(build->isTypeBuid(Build_Type_Land_Mark))
    {
        BuildTypeLandMark *temp = dynamic_cast<BuildTypeLandMark*>(build);
        if(temp)
        {
            temp->checkBuffer(false);
        }
    }
    m_owner->m_kittyGarden.eraseBuildPoint(build);
    opKindType(tempid,false);
    eraseBuild(build);
    SAFE_DELETE(build);
    m_buildMap.erase(tempid);

    HelloKittyMsgData::AckRemoveBuid removeBuild;
    removeBuild.set_updatecharid(m_owner->charid);
    removeBuild.set_tempid(tempid);
    std::string ret;
    encodeMessage(&removeBuild,ret);
    m_owner->broadcastMsgInMap(ret.c_str(),ret.size());
    return true;
}

bool BuildManager::eraseBuild(BuildBase *build)
{
    auto iter = m_buildMap.find(build->getID());
    if(iter == m_buildMap.end())
    {
        return false;
    }

    auto iter1 = m_buildTypeMap.find(build->getTypeID());
    if(iter1 == m_buildTypeMap.end())
    {
        return false;
    }
    std::set<QWORD> &tempIdSet = m_buildTypeMap[build->getTypeID()];
    if(tempIdSet.find(build->getID()) == tempIdSet.end())
    {
        return false;
    }
    tempIdSet.erase(build->getID());
    return true;
}

bool BuildManager::load(const HelloKittyMsgData::Serialize& binary)
{
    for(int index = 0;index < binary.buildbase_size();++index)
    {
        const HelloKittyMsgData::BuildBase &buidBase = binary.buildbase(index);
        BuildBase *build = newBuild(NULL,&buidBase);
        if(!addBuild(build))
        {
            SAFE_DELETE(build);
            return false;
        }
        m_oldNewKey.insert(std::pair<QWORD,QWORD>(buidBase.tempid(),build->getID()));
        if(build->isTypeBuid(Build_Type_Road))
        {
            m_emptyRoadSet.insert(build->getID());
        }
    }
    for(int index = 0;index < binary.buildproduce_size();++index)
    {
        const HelloKittyMsgData::BuildProduce &temp = binary.buildproduce(index);
        auto iter = m_oldNewKey.find(temp.tempid());
        if(iter == m_oldNewKey.end())
        {
            continue;
        }
        BuildBase *build = getBuild(iter->second);
        if(build && build->isTypeBuid(Build_Type_Gold_Produce))
        {
            BuildTypeProduceGold *buildType = dynamic_cast<BuildTypeProduceGold*>(build);
            if(buildType)
            {
                buildType->load(temp);
            }
        }
    }
    for(int index = 0;index < binary.functioncell_size();++index)
    {
        const HelloKittyMsgData::StoreFunctionCell &temp = binary.functioncell(index);
        auto iter = m_oldNewKey.find(temp.tempid());
        if(iter == m_oldNewKey.end())
        {
            continue;
        }
        BuildBase *build = getBuild(iter->second);
        if(!build)
        {
            continue;
        }
        if(build->isTypeBuid(Build_Type_Item_Produce))
        {
            BuildTypeProduceItem *func = dynamic_cast<BuildTypeProduceItem*>(build);
            if(func)
            {
                func->load(temp);
            }
        }
        else if(build->isTypeBuid(Build_Type_Item_Composite))
        {
            BuildTypeCompositeItem *func = dynamic_cast<BuildTypeCompositeItem*>(build);
            if(func)
            {
                func->load(temp);
            }
        }
    }
    for(int index = 0;index < binary.usecard_size();++index)
    {
        const HelloKittyMsgData::UseCardInfo &temp = binary.usecard(index);
        auto iter = m_oldNewKey.find(temp.tempid());
        if(iter == m_oldNewKey.end())
        {
            continue;
        }
        BuildBase *build = getBuild(iter->second);
        if(build)
        {
            build->loadCard(temp);
            opCardSet(temp.cardid(),build->getID());
        }
    }
    for(int index = 0;index < binary.warebuild_size();++index)
    {
        const HelloKittyMsgData::WareHouseBuildBase &wareBuild = binary.warebuild(index);
        WareHouseBuildBase wareHouseBuild(m_maxCellID,wareBuild.type(),wareBuild.level(),wareBuild.producetime(),wareBuild.status(),wareBuild.durtime(),wareBuild.num());
        m_wareHouseBuildMap.insert(std::pair<DWORD,WareHouseBuildBase>(m_maxCellID,wareHouseBuild));
        m_cellSet.insert(m_maxCellID);
        ++m_maxCellID;
    }
    for(int index = 0;index < binary.worker_size();++index)
    {
        const HelloKittyMsgData::Worker &worker = binary.worker(index);
        m_workerMap.insert(std::pair<DWORD,HelloKittyMsgData::Worker>(worker.id(),worker));
    }
    loadBuildInMap();
    return true;
}

bool BuildManager::save(HelloKittyMsgData::Serialize& binary)
{
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        BuildBase *build = iter->second;
        if(build)
        {
            HelloKittyMsgData::BuildBase *buildBase = binary.add_buildbase();
            if(buildBase)
            {
                build->save(buildBase);
                build->saveProduce(binary);
                build->saveCard(binary);
            }
        }
    }

    for(auto iter = m_workerMap.begin();iter != m_workerMap.end();++iter)
    {
        HelloKittyMsgData::Worker *worker = binary.add_worker();
        *worker = iter->second;
    }
    for(auto iter = m_wareHouseBuildMap.begin();iter != m_wareHouseBuildMap.end();++iter)
    {
        HelloKittyMsgData::WareHouseBuildBase *wareBuild = binary.add_warebuild();
        if(wareBuild)
        {
            const WareHouseBuildBase& wareBuildInfo = iter->second;
            wareBuild->set_type(wareBuildInfo.typeID);
            wareBuild->set_level(wareBuildInfo.level);
            wareBuild->set_num(wareBuildInfo.num);
            wareBuild->set_cellid(wareBuildInfo.cellID);
            wareBuild->set_status(wareBuildInfo.mark);
            wareBuild->set_producetime(wareBuildInfo.produceTime);
            wareBuild->set_durtime(wareBuildInfo.durTime);
        }
    }
    for(auto iter = m_workerMap.begin();iter != m_workerMap.end();++iter)
    {
        HelloKittyMsgData::Worker *worker = binary.add_worker();
        *worker = iter->second;
    }
    return true;
}

bool BuildManager::flushAllBuild()
{
    HelloKittyMsgData::AckFlushAllBuild flushAllBuild;
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        HelloKittyMsgData::BuildBase *buildBase = flushAllBuild.add_buildinfo();
        BuildBase *build = iter->second;
        if(buildBase && build)
        {
            build->save(buildBase);
        }
    }

    std::string ret;
    if(encodeMessage(&flushAllBuild,ret))
    {
        m_owner->sendCmdToMe(ret.c_str(),ret.size());
    }
    return true;
}

bool BuildManager::fullMessage(HelloKittyMsgData::UserBaseInfo& userInfo)
{
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        HelloKittyMsgData::BuildBase *buildBase = userInfo.add_buildinfo();
        BuildBase *build = iter->second;
        if(buildBase && build)
        {
            build->save(buildBase);
        }
    }
    for(auto iter = m_rubbishMap.begin();iter != m_rubbishMap.end();++iter)
    {
        HelloKittyMsgData::RubbishData *temp = userInfo.add_rubbish();
        if(temp)
        {
            temp->set_roadid(iter->first);
            temp->set_rubbish(iter->second);
        }
    }
    return true;
}

bool BuildManager::fullMessage(HelloKittyMsgData::EnterGardenInfo& kittyInfo)
{
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        HelloKittyMsgData::BuildBase *buildBase = kittyInfo.add_buildinfo();
        BuildBase *build = iter->second;
        if(buildBase && build)
        {
            build->save(buildBase);
        }
    }
    for(auto iter = m_rubbishMap.begin();iter != m_rubbishMap.end();++iter)
    {
        HelloKittyMsgData::RubbishData *temp = kittyInfo.add_rubbish();
        if(temp)
        {
            temp->set_roadid(iter->first);
            temp->set_rubbish(iter->second);
        }
    }
    return true;
}

bool BuildManager::flushOneBuild(const DWORD tempid)
{
    auto iter = m_buildMap.find(tempid);
    if(iter == m_buildMap.end())
    {
        Fir::logger->debug("[刷新建筑错误]:建筑找不到tempid %u",tempid);
        return false;
    }
    return iter->second->flush();
}

BuildBase* BuildManager::getBuild(const QWORD tempid)
{
    auto iter = m_buildMap.find(tempid);
    if(iter == m_buildMap.end())
    {
        Fir::logger->debug("[建筑查找实例错误]:建筑找不到tempid %lu",tempid);
        return NULL;
    }
    return iter->second;
}

bool BuildManager::loop()
{
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        BuildBase *build = iter->second;
        if(!build || build->isTypeBuid(Build_Type_Road) || !build->isActive())
        {
            continue;
        }
        build->loop();
    }
    return true;
}

bool BuildManager::loadBuildInMap()
{
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        BuildBase *build = iter->second;
        if(!build)
        {
            continue;
        }
        m_owner->m_kittyGarden.addBuildPoint(build,build->getPoint(),!build->getRationMask());
    }
    //判断是否激活
    checkBuildActive();
    //判断是否有地标建筑给予buffer
    checkBuildBuffer(false);
    return true;
}

bool BuildManager::checkBuildLevel(const DWORD typeID,const DWORD level,const DWORD num)
{
    return getBuildLevelNum(typeID,level) >= num;
}

DWORD BuildManager::getBuildLevelNum(const DWORD typeID,const DWORD level)
{
    DWORD size = 0;
    auto iter = m_buildTypeMap.find(typeID);
    if(iter == m_buildTypeMap.end())
    {
        return size;
    }

    const std::set<QWORD> &tempSet = iter->second;
    for(auto temp = tempSet.begin();temp != tempSet.end();++temp)
    {
        BuildBase *build = getBuild(*temp);
        if(build)
        {
            if(build->getLevel() >= level)
            {
                size += 1;
            }
        }
    }
    return size;
}   

DWORD BuildManager::getBuildLevel(const DWORD typeID)
{
    DWORD level = 0;
    auto iter = m_buildTypeMap.find(typeID);
    if(iter == m_buildTypeMap.end())
    {
        return level;
    }

    const std::set<QWORD> &tempSet = iter->second;
    for(auto temp = tempSet.begin();temp != tempSet.end();++temp)
    {
        BuildBase *build = getBuild(*temp);
        if(build)
        {
            if(build->getLevel() >= level)
            {
                level = build->getLevel();
            }
        }
    }
    return level;
}   

DWORD BuildManager::getBuildLevelNum(const DWORD level)
{
    DWORD num = 0;
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        const BuildBase *build = iter->second;
        if(build && build->getLevel() >= level)
        {
            num += 1;
        }
    }
    return num;

}

//获取所有者
SceneUser* BuildManager::getOwner()
{
    return  m_owner; 
}

bool BuildManager::checkBuildActive()
{
    //判断是否激活
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        BuildBase *build = iter->second;
        if(!build || build->isTypeBuid(Build_Type_Road))
        {
            continue;
        }
        bool isActiveFlg = build->isActive();
        bool flg = m_owner->m_kittyGarden.checkActive(build,build->getPoint(),build->getRationMask());
        if(flg != isActiveFlg)
        {
            build->setActive(flg);
            //激活
            if(flg)
            {
                build->beginActive();
            }
            build->flush();
        }
    }
    return true;
}

bool BuildManager::checkBuildBuffer(const bool notify)
{
    //判断是否有buffer
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();++iter)
    {
        BuildBase *build = iter->second;
        if(!build || !build->isTypeBuid(Build_Type_Land_Mark))
        {
            continue;
        }
        BuildTypeLandMark *temp = dynamic_cast<BuildTypeLandMark*>(build);
        if(temp)
        {
            temp->checkBuffer(true,notify);
        }
    }
    return true;
}

QWORD BuildManager::getAnyBuildBytype(const std::vector<DWORD> &vecId,bool bExp )
{
    std::set<DWORD> setId(vecId.begin(),vecId.end());
    std::vector<QWORD> rSel;
    for(auto iter = m_buildMap.begin();iter != m_buildMap.end();iter++)
    {
        BuildBase* pBase = iter->second;
        bool bFind = setId.find(pBase->getTypeBuild()) != setId.end();
        if(bFind && !bExp)
        {
            rSel.push_back(iter->first);

        }
        if(!bFind && bExp)
        {
            rSel.push_back(iter->first);
        }

    }

    if(rSel.empty())
        return 0;
    DWORD rate = zMisc::randBetween(0,rSel.size()-1);
    return rSel[rate];
}

QWORD BuildManager::getAnyBuildById(DWORD buildid)
{
    auto iter = m_buildTypeMap.find(buildid);
    if(iter == m_buildTypeMap.end())
        return 0;
    if(iter->second.empty())
        return 0;
    std::vector<QWORD> rSel(iter->second.begin(),iter->second.end()); 
    DWORD rate = zMisc::randBetween(0,rSel.size()-1);
    return rSel[rate]; 
}

QWORD BuildManager::getAnyBuildById(const std::vector<DWORD> &vecId,bool bExp )
{
    std::set<DWORD> setId(vecId.begin(),vecId.end());
    std::vector<QWORD> rSel;       
    for(auto iter = m_buildTypeMap.begin(); iter != m_buildTypeMap.end(); iter++)
    {
        bool bFind = setId.find(iter->first) != setId.end(); 
        if(bFind && !bExp)
        {
            for(auto it = iter->second.begin(); it != iter->second.end(); it++)
            {
                rSel.push_back(*it);
            }

        }
        if(!bFind && bExp)
        { 
            for(auto it = iter->second.begin(); it != iter->second.end(); it++)
            {
                rSel.push_back(*it);
            }
            rSel.push_back(iter->first);
        }


    }
    if(rSel.empty())
        return 0;
    DWORD rate = zMisc::randBetween(0,rSel.size()-1);
    return rSel[rate];

}

QWORD  BuildManager::createBuildAnySpace(DWORD buildid)
{
    //TODO:

    return 0;
}

void   BuildManager::destroyBuild(QWORD BuildId)
{
    deleteBuild(BuildId);
}

DWORD  BuildManager::getBuildNum()
{
    return m_buildMap.size();
}

bool BuildManager::opKindType(const QWORD tempid,const bool opAdd)
{
    BuildBase *temp = getBuild(tempid);
    if(!temp)
    {
        return false;
    }
    DWORD kindType = temp->confBase->buildInfo->buildkind();
    auto iter = m_kindTypeMap.find(kindType);
    if(iter == m_kindTypeMap.end())
    {
        if(opAdd)
        {
            std::set<QWORD> tempSet;
            tempSet.insert(tempid);
            m_kindTypeMap.insert(std::pair<DWORD,std::set<QWORD>>(kindType,tempSet));
            return true;
        }
        return true;
    }
    std::set<QWORD> &tempSet = const_cast<std::set<QWORD>&>(iter->second);
    if(opAdd)
    {
        tempSet.insert(tempid);
        return true;
    }
    tempSet.erase(tempid);
    if(tempSet.empty())
    {
        m_kindTypeMap.erase(iter);
    }
    return true;
}

bool BuildManager::initTypeBuild(BuildBase *build)
{
    if(!build)
    {
        return false;
    }
    //生产道具建筑
    if(build->isTypeBuid(Build_Type_Item_Produce))
    {
        BuildTypeProduceItem* temp = dynamic_cast<BuildTypeProduceItem*>(build);
        if(temp)
        {
            temp->init();
            temp->sendInfoMeg();
        }
    }
    //合成道具建筑
    else if(build->isTypeBuid(Build_Type_Item_Composite))
    {
        BuildTypeCompositeItem* temp = dynamic_cast<BuildTypeCompositeItem*>(build);
        if(temp)
        {
            temp->init();
            temp->sendInfoMeg();
        }
    }
    //生产金币建筑
    else if(build->isTypeBuid(Build_Type_Gold_Produce))
    {
        BuildTypeProduceGold* temp = dynamic_cast<BuildTypeProduceGold*>(build);
        if(temp)
        {
            temp->updateProduce();
        }
    }
    return true;
}

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
//建筑仓库相关的功能

DWORD BuildManager::getEmptyCell()
{
    for(DWORD cellid = 0;cellid < m_maxCellID;++cellid)
    {
        if(m_cellSet.find(cellid) == m_cellSet.end())
        {
            return cellid;
        }
    }
    DWORD cellid = m_maxCellID;
    ++m_maxCellID;
    return cellid;
}


bool BuildManager::pickBuildInWare(const QWORD tempid)
{
    BuildBase *build = getBuild(tempid);
    //路不可以收起来
    if(!build || build->isTypeBuid(Build_Type_Road))
    {
        return false;
    }
    build->countDurTime(); 
    WareHouseBuildBase wareBuild(getEmptyCell());
    build->saveAsWareHouseBuildBase(wareBuild);
    m_wareHouseBuildMap.insert(std::pair<DWORD,WareHouseBuildBase>(wareBuild.cellID,wareBuild));
    if(m_wareHouseTypeMap.find(wareBuild.typeID) == m_wareHouseTypeMap.end())
    {
        m_wareHouseTypeMap.insert(std::pair<DWORD,DWORD>(wareBuild.typeID,wareBuild.num));
    }
    else
    {
        m_wareHouseTypeMap[wareBuild.typeID] += wareBuild.num;
    }
    m_cellSet.insert(wareBuild.cellID);
    m_owner->m_kittyGarden.eraseBuildPoint(build);
    deleteBuild(tempid);
    checkBuildActive();
    updateWareBuild(wareBuild.cellID);
    return true;
}

bool BuildManager::pickoutBuild(const HelloKittyMsgData::ReqPickOutBuid *message)
{
    auto iter = m_wareHouseBuildMap.find(message->cellid());
    if(iter == m_wareHouseBuildMap.end())
    {
        return false;
    }
    WareHouseBuildBase &temp = const_cast<WareHouseBuildBase&>(iter->second); 
    if(!build(temp,message->moveflg(),message->point()))
    {
        return false;
    }
    if(m_wareHouseTypeMap.find(temp.typeID) != m_wareHouseTypeMap.end())
    {
        if(m_wareHouseTypeMap[temp.typeID] >= temp.num)
        {
            m_wareHouseTypeMap[temp.typeID] -= temp.num;
        }
        else
        {
            m_wareHouseTypeMap.erase(temp.typeID);
        }
    }
    checkBuildActive();
    temp.num = 0;
    updateWareBuild(temp.cellID);
    m_wareHouseBuildMap.erase(iter);
    m_cellSet.erase(message->cellid());
    return true;
}

bool BuildManager::flushAllWareHouseBuild()
{
    HelloKittyMsgData::AckFlushWareBuild message;
    for(auto iter = m_wareHouseBuildMap.begin();iter != m_wareHouseBuildMap.end();++iter)
    {
        const WareHouseBuildBase &wareBuildInfo = iter->second;
        HelloKittyMsgData::WareHouseBuildBase *wareBuild = message.add_warebuild();
        wareBuild->set_type(wareBuildInfo.typeID);
        wareBuild->set_level(wareBuildInfo.level);
        wareBuild->set_num(wareBuildInfo.num);
        wareBuild->set_cellid(wareBuildInfo.cellID);

    }

    std::string ret;
    if(encodeMessage(&message,ret))
    {
        m_owner->sendCmdToMe(ret.c_str(),ret.size());
    }
    return true;
}

bool BuildManager::updateWareBuild(const DWORD cellID)
{
    auto iter = m_wareHouseBuildMap.find(cellID);
    if(iter == m_wareHouseBuildMap.end())
    {
        return false;
    }

    const WareHouseBuildBase &wareBuildInfo = iter->second; 
    HelloKittyMsgData::AckUpdateWareBuid update;
    HelloKittyMsgData::WareHouseBuildBase *temp = update.mutable_warebuild();
    if(!temp)
    {
        return false;
    }
    temp->set_type(wareBuildInfo.typeID);
    temp->set_level(wareBuildInfo.level);
    temp->set_num(wareBuildInfo.num);
    temp->set_cellid(wareBuildInfo.cellID);

    std::string ret;
    if(encodeMessage(&update,ret))
    {
        m_owner->sendCmdToMe(ret.c_str(),ret.size());
    }
    return true;
}



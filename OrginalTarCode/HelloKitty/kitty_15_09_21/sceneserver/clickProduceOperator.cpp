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
#include "buildTypeProduceGold.h"
#include "buildItemProduce.h"
#include "buildItemComposite.h"

//建筑产物相关功能

bool BuildManager::flushBuildProduce(const HelloKittyMsgData::ReqBuildProduce *cmd)
{
    HelloKittyMsgData::AckBuildProduce ackBuild;
    for(int index = 0;index < cmd->tempid_size();++index)
    {
        BuildBase *build = getBuild(cmd->tempid(index));
        if(!build || !build->isTypeBuid(Build_Type_Gold_Produce))
        {
            continue;
        }
        BuildTypeProduceGold *buildType = dynamic_cast<BuildTypeProduceGold*>(build);
        if(buildType)
        {
            HelloKittyMsgData::BuildProduce *temp = ackBuild.add_produce();
            buildType->fullProduceMsg(temp);
        }
    }
   
    std::string ret;
    encodeMessage(&ackBuild,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool BuildManager::fullBuildProduce(HelloKittyMsgData::UserBaseInfo *useInfo)
{
    auto iter = m_kindTypeMap.find(Build_Type_Gold_Produce);
    if(iter == m_kindTypeMap.end())
    {
        return false;
    }
    const std::set<QWORD> &tempSet = iter->second;
    for(auto tempIter = tempSet.begin();tempIter != tempSet.end();++tempIter)
    {
        BuildBase *build = getBuild(*tempIter);
        if(!build)
        {
            continue;
        }
        build->fullUserInfoMsg(*useInfo);
        if(!build || !build->isTypeBuid(Build_Type_Gold_Produce))
        {
            continue;
        }
        BuildTypeProduceGold *buildType = dynamic_cast<BuildTypeProduceGold*>(build);
        if(buildType)
        {
            HelloKittyMsgData::BuildProduce *temp = useInfo->add_produce();
            if(temp)
            {
                buildType->fullProduceMsg(temp);
            }
        }
    }

    iter = m_kindTypeMap.find(Build_Type_Item_Produce);
    if(iter == m_kindTypeMap.end())
    {
        iter = m_kindTypeMap.find(Build_Type_Item_Composite);
        if(iter == m_kindTypeMap.end())
        {
            return false;
        }
    }
    const std::set<QWORD> &tempSet1 = iter->second;
    for(auto tempIter = tempSet1.begin();tempIter != tempSet1.end();++tempIter)
    {
        BuildBase *build = getBuild(*tempIter);
        if(!build)
        {
            continue;
        }
        BuildTypeProduceItem *buildType = dynamic_cast<BuildTypeProduceItem*>(build);
        if(buildType)
        {
            buildType->fullUserInfo(*useInfo);
        }
    }
    
    iter = m_kindTypeMap.find(Build_Type_Item_Composite);
    if(iter == m_kindTypeMap.end())
    {
        iter = m_kindTypeMap.find(Build_Type_Item_Composite);
        if(iter == m_kindTypeMap.end())
        {
            return false;
        }
    }
    const std::set<QWORD> &tempSet2 = iter->second;
    for(auto tempIter = tempSet2.begin();tempIter != tempSet2.end();++tempIter)
    {
        BuildBase *build = getBuild(*tempIter);
        if(!build)
        {
            continue;
        }
        BuildTypeCompositeItem *buildType = dynamic_cast<BuildTypeCompositeItem*>(build);
        if(buildType)
        {
            buildType->fullUserInfo(*useInfo);
        }

    }
    for(auto iter = m_cardMap.begin();iter != m_cardMap.end();++iter)
    {
        BuildBase *build = getBuild(iter->second);
        if(build)
        {
            build->fullUserCard(*useInfo);
        }
    }
    return true;
}



#include "atlasManager.h"
#include "SceneUser.h"
#include "tbx.h"
#include "atlas.pb.h"

AtlasManager::AtlasManager(SceneUser *owner) : m_owner(owner)
{
}

AtlasManager::~AtlasManager()
{
}

bool AtlasManager::save(HelloKittyMsgData::Serialize& binary)
{
    for(auto iter = m_atlasSet.begin();iter != m_atlasSet.end();++iter)
    {
        binary.add_atlas(*iter);
    }
    return true;
}

bool AtlasManager::load(const HelloKittyMsgData::Serialize& binary)
{
    for(int index = 0;index < binary.atlas_size();++index)
    {
        m_atlasSet.insert(binary.atlas(index));
    }
    return true;
}

bool AtlasManager::flushAtlas()
{
    HelloKittyMsgData::AckAtlas message;
    for(auto iter = m_atlasSet.begin();iter != m_atlasSet.end();++iter)
    {
        message.add_atlas(*iter);
    }

    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool AtlasManager::updateAtlas(const DWORD atlas)
{
    HelloKittyMsgData::AckAddAtlas message;
    auto iter = m_atlasSet.find(atlas);
    if(iter == m_atlasSet.end())
    {
        return false;
    }
    message.set_atlas(atlas);

    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool AtlasManager::checkAtlas(const DWORD atlas)
{
    auto iter = m_atlasSet.find(atlas);
    if(iter == m_atlasSet.end())
    {
        return false;
    }
    return true;
}

bool AtlasManager::addAtlas(const DWORD atlas)
{
    if(checkAtlas(atlas))
    {
        const pb::Conf_t_Handbook *atlasTemp = tbx::Handbook().get_base(atlas);
        if(!atlasTemp)
        {
            return false;
        }
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"多余图鉴兑换(%u)",atlas);
        m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,atlasTemp->handBook->glod(),temp,true);
        return false;
    }

    m_atlasSet.insert(atlas);
    updateAtlas(atlas);
    
    HelloKittyMsgData::DailyData *dailyData = m_owner->charbin.mutable_dailydata();
    dailyData->set_addatlas(dailyData->addatlas() + 1);

    TaskArgue arg(Target_Atlas,Attr_Avartar,Attr_Avartar,getAtlasNum());
    m_owner->m_taskManager.target(arg);
    
    TaskArgue arg1(Target_Atlas,Attr_Avartar,Attr_Add_Atlas,dailyData->addatlas());
    m_owner->m_taskManager.target(arg1);


    AchieveArg achieveArg(Achieve_Target_Have,Achieve_Sub_Sorce_Num,Attr_Avartar,m_atlasSet.size());
    m_owner->m_achievementManager.target(achieveArg);
    return true;
}

bool AtlasManager::delAtlas(const DWORD atlas)
{
    if(!checkAtlas(atlas))
    {
        return false;
    }
    m_atlasSet.erase(atlas);
    flushAtlas();
    return true;
}

bool AtlasManager::clearAtlas()
{
    m_atlasSet.clear();
    flushAtlas();
    return true;
}


bool AtlasManager::addAtlasByItem(const DWORD itemID)
{
    const pb::Conf_t_Handbook *atlas = tbx::Handbook().get_base(itemID);
    if(!atlas)
    {
        return false;
    }
    return addAtlas(itemID);
}

DWORD AtlasManager::getAtlasNum()
{
    return m_atlasSet.size();
}

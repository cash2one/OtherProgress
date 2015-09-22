#include "dressManager.h"
#include "SceneUser.h"
#include "tbx.h"
#include "dress.pb.h"
#include "key.h"
#include "taskAttr.h"
#include "buffer.h"

DressManager::DressManager(SceneUser *owner) : m_owner(owner)
{
}

DressManager::~DressManager()
{
}

bool DressManager::save(HelloKittyMsgData::Serialize& binary)
{
    for(auto iter = m_dressMap.begin();iter != m_dressMap.end();++iter)
    {
        HelloKittyMsgData::DressData *dressData = binary.add_dress();
        if(dressData)
        {
            dressData->set_id(iter->first);
            dressData->set_level(iter->second);
        }
    }
    return true;
}

bool DressManager::load(const HelloKittyMsgData::Serialize& binary)
{
    for(int index = 0;index < binary.dress_size();++index)
    {
        const HelloKittyMsgData::DressData &dressData = binary.dress(index);
        m_dressMap.insert(std::pair<DWORD,DWORD>(dressData.id(),dressData.level()));
    }
    return true;
}

bool DressManager::flushDress()
{
    HelloKittyMsgData::AckDress message;
    for(auto iter = m_dressMap.begin();iter != m_dressMap.end();++iter)
    {
        HelloKittyMsgData::DressData *dressData = message.add_dress();
        if(dressData)
        {
            dressData->set_id(iter->first);
            dressData->set_level(iter->second);
        }
    }

    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool DressManager::updateDress(const DWORD dressID)
{
    HelloKittyMsgData::AckUpdateDress message;
    auto iter = m_dressMap.find(dressID);
    if(iter == m_dressMap.end())
    {
        return false;
    }
    HelloKittyMsgData::DressData *dressData = message.mutable_dress();
    if(dressData)
    {
        dressData->set_id(iter->first);
        dressData->set_level(iter->second);
    }

    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool DressManager::checkDress(const DWORD dressID)
{
    auto iter = m_dressMap.find(dressID);
    if(iter == m_dressMap.end())
    {
        return false;
    }
    return true;
}

bool DressManager::addDress(const DWORD dressID)
{
    if(checkDress(dressID))
    {
        QWORD key = hashKey(dressID,1);
        const pb::Conf_t_Dress *dress = tbx::Dress().get_base(key);
        if(!dress)
        {
            return false;
        }
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"多余时装兑换(%u)",dressID);
        m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,dress->dress->price(),temp,true);
        return false;
    }
    m_dressMap.insert(std::pair<DWORD,DWORD>(dressID,1));
    updateDress(dressID);
    
    TaskArgue arg(Target_Atlas,Attr_Fashion_Get,Attr_Fashion_Get,getDressNum());
    m_owner->m_taskManager.target(arg);
    
    HelloKittyMsgData::DressData *dressData = m_owner->charbin.mutable_dress();
    if(!dressData)
    {
        return false;
    }
    if(!(dressData->id() || dressData->level()))
    {
        putUpDress(dressID,1);
    }
    return true;
}

bool DressManager::delDress(const DWORD dressID) 
{
    if(!checkDress(dressID))
    {
        return false;
    }
    m_dressMap.erase(dressID);
    flushDress();
    return true;
}

bool DressManager::clearDress()
{
    m_dressMap.clear();
    flushDress();
    return true;
}

bool DressManager::addDressByItem(const DWORD itemID)
{
    QWORD key = hashKey(itemID,1);
    const pb::Conf_t_Dress *dress = tbx::Dress().get_base(key);
    if(!dress)
    {
        return false;
    }
    return addDress(itemID);
}

DWORD DressManager::getDressNum()
{
    return m_dressMap.size();
}

DWORD DressManager::findLevel(const DWORD level)
{
    DWORD num = 0;
    for(auto iter = m_dressMap.begin();iter != m_dressMap.end();++iter)
    {
        if(iter->second >= level)
        {
            num += 1;
        }
    }
    return num;
}

bool DressManager::upLevel(const DWORD dressID)
{
    if(!checkDress(dressID))
    {
        return false;
    }
    DWORD oldLevel = m_dressMap[dressID];
    QWORD key = hashKey(dressID,oldLevel+1);
    const pb::Conf_t_Dress *dress = tbx::Dress().get_base(key);
    if(!dress)
    {
        return false;
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"时装升级(%u,%u,%u)",dressID,oldLevel,oldLevel+1);
    if(!(m_owner->checkMaterialMap(dress->getMaterialMap()) && m_owner->reduceMaterialMap(dress->getMaterialMap(),temp)))
    {
        return m_owner->opErrorReturn(HelloKittyMsgData::Material_Not_Enough);
    }
    m_dressMap[dressID] += 1;
    
    TaskArgue arg(Target_Atlas,Attr_Fashion_Level,Attr_Fashion_Level,dressID);
    m_owner->m_taskManager.target(arg);
    
    TaskArgue arg1(Target_Atlas,Attr_Fashion_Has,Attr_Fashion_Has,dressID);
    m_owner->m_taskManager.target(arg1);
    return updateDress(dressID);
}

bool DressManager::putDownDress()
{
    HelloKittyMsgData::DressData *dressData = m_owner->charbin.mutable_dress();
    if(!dressData)
    {
        return false;
    }
    QWORD key = hashKey(dressData->id(),dressData->level());
    const pb::Conf_t_Dress *dress = tbx::Dress().get_base(key);
    if(!dress)
    {
        return false;
    }
    opBuffer(m_owner,dressData->id(),HelloKittyMsgData::BST_Item,dress->getBufferMap(),false,true);
    dressData->set_id(0);
    dressData->set_level(0);
    return true;
}

bool DressManager::putUpDress(const DWORD dressID,const DWORD level)
{
    HelloKittyMsgData::DressData *dressData = m_owner->charbin.mutable_dress();
    if(!dressData || !checkDress(dressID))
    {
        return false;
    }
    QWORD key = hashKey(dressID,level);
    const pb::Conf_t_Dress *dress = tbx::Dress().get_base(key);
    if(!dress)
    {
        return false;
    }
    opBuffer(m_owner,dressID,HelloKittyMsgData::BST_Item,dress->getBufferMap(),true,true);
    dressData->set_id(dressID);
    dressData->set_level(level);
    
    TaskArgue arg(Target_Atlas,Attr_Fashion_Dress,Attr_Fashion_Dress,dressID);
    m_owner->m_taskManager.target(arg);
    return true;
}

bool DressManager::changeDress(const DWORD dressID)
{
    if(!checkDress(dressID))
    {
        return false;
    }
    putDownDress();
    putUpDress(dressID,m_dressMap[dressID]);
    updateBodyDress();
    return true;
}

bool DressManager::updateBodyDress()
{
    HelloKittyMsgData::DressData *dressData = m_owner->charbin.mutable_dress();
    if(!dressData)
    {
        return false;
    }
    
    HelloKittyMsgData::AckBodyDress ackMessage;
    HelloKittyMsgData::DressData *temp = ackMessage.mutable_dress();
    if(!temp)
    {
        return false;
    }
    *temp = *dressData;
    std::string ret;
    encodeMessage(&ackMessage,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool DressManager::putUpDressInit()
{
    HelloKittyMsgData::DressData *dressData = m_owner->charbin.mutable_dress();
    if(!dressData || !checkDress(dressData->id()))
    {
        return false;
    }
    QWORD key = hashKey(dressData->id(),dressData->level());
    const pb::Conf_t_Dress *dress = tbx::Dress().get_base(key);
    if(!dress)
    {
        return false;
    }
    opBuffer(m_owner,dressData->id(),HelloKittyMsgData::BST_Item,dress->getBufferMap(),true,false);
    return true;
}



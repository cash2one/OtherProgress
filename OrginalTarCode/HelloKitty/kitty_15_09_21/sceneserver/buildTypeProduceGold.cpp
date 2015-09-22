#include "buildTypeProduceGold.h"
#include "SceneUser.h"
#include "TimeTick.h"
#include "dataManager.h"
#include "tbx.h"
#include "buffer.h"

BuildTypeProduceGold::BuildTypeProduceGold(SceneUser* owner,const DWORD typeID,const DWORD level,const Point &point,const bool active) : BuildBase(owner,typeID,level,point,active)
{
}

BuildTypeProduceGold::BuildTypeProduceGold(SceneUser* owner,const pb::Conf_t_building *buildConf,const Point &point) : BuildBase(owner,buildConf,point)
{
}

BuildTypeProduceGold::BuildTypeProduceGold(SceneUser* owner,const HelloKittyMsgData::BuildBase &buildBase) : BuildBase(owner,buildBase)
{
}

bool BuildTypeProduceGold::load(const HelloKittyMsgData::BuildProduce& binary)
{
    for(int index = 0;index < binary.produce_size();++index)
    {
        const HelloKittyMsgData::ProduceBase &temp = binary.produce(index); 
        auto iter = m_produceMap.find(temp.itemid());
        if(iter == m_produceMap.end())
        {
            m_produceMap.insert(std::pair<DWORD,DWORD>(temp.itemid(),temp.value()));
        }
        else
        {
            m_produceMap[temp.itemid()] += temp.value();
        }
                    
    }
    return true;
}

bool BuildTypeProduceGold::saveProduce(HelloKittyMsgData::Serialize& binary)
{
    HelloKittyMsgData::BuildProduce *temp = binary.add_buildproduce();
    if(!temp)
    {
        return false;
    }
    temp->set_tempid(m_id);
    for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
    {
        HelloKittyMsgData::ProduceBase *produceBase = temp->add_produce();
        if(produceBase)
        {
            produceBase->set_itemid(iter->first);
            produceBase->set_value(iter->second);
        }
    }
    return true;
}

void BuildTypeProduceGold::fullProduceMsg(HelloKittyMsgData::BuildProduce *buildProduce)
{
    buildProduce->set_tempid(m_id);
    for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
    {
        HelloKittyMsgData::ProduceBase *temp = buildProduce->add_produce();
        if(!temp)
        {
            continue;
        }
        temp->set_itemid(iter->first);
        temp->set_value(iter->second);
    }
}

bool BuildTypeProduceGold::updateProduce()
{
    HelloKittyMsgData::AckBuildProduce ackProduce;
    HelloKittyMsgData::BuildProduce *buildProduce = ackProduce.add_produce();
    if(!buildProduce)
    {
        return false;
    }
    fullProduceMsg(buildProduce);
    
    std::string ret;
    encodeMessage(&ackProduce,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool BuildTypeProduceGold::clickReward()
{
    for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
    {
        char temp[100] = {0};
        if(iter->first == HelloKittyMsgData::Attr_Happy_Val)
        {
            snprintf(temp,sizeof(temp),"建筑(%lu,%u)产出增加",m_id,m_typeID);
            m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Happy_Val,iter->second,temp,true);
        }
        else if(iter->first == HelloKittyMsgData::Attr_Gold)
        {
            snprintf(temp,sizeof(temp),"建筑(%lu,%u)产出增加",m_id,m_typeID);
            m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,iter->second,temp,true);
        }
        m_produceMap[iter->first] = 0;
    }
    return true;
}

bool BuildTypeProduceGold::produce()
{
    DWORD key = HelloKittyMsgData::Attr_Gold;
    auto iter = m_produceMap.find(key);
    if(iter == m_produceMap.end())
    {
        m_produceMap.insert(std::pair<DWORD,DWORD>(key,confBase->buildInfo->goldoutput()));
    }
    else
    {
        m_produceMap[key] += (confBase->buildInfo->goldoutput()) / 3600;
    }

    m_produceMap[key] += getBufferVal(this,HelloKittyMsgData::Buffer_Type_Gold);
    m_produceMap[key] += getBufferVal(m_owner,HelloKittyMsgData::Buffer_Type_Gold);
    //金币生成上限
    if(m_produceMap[key] >= confBase->buildInfo->goldoutputmax())
    {
        m_produceMap[key] = confBase->buildInfo->goldoutputmax();
    }

    return true;
}

bool BuildTypeProduceGold::loop()
{
    DWORD nowTime = SceneTimeTick::currentTime.sec();
    if(m_mark & HelloKittyMsgData::Build_Status_Normal)
    {
        loopBuffer(this);
        if((nowTime - m_produceTime + m_durTime) >= 1)
        {
            produce();
            m_durTime = 0;
            m_produceTime = SceneTimeTick::currentTime.sec();
        }
    }
    return true;
}


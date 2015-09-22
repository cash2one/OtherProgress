#include "SceneUser.h"
#include "divine.pb.h"
#include "tbx.h"
#include "key.h"
#include "buffer.h"
#include "common.pb.h"

const pb::Conf_t_Divine* SceneUser::randDivine(const DWORD answer)
{
    if(pb::Conf_t_Divine::retWeightMap.find(answer) == pb::Conf_t_Divine::retWeightMap.end())
    {
        return NULL;
    }
    
    DWORD randVal = zMisc::randBetween(0,pb::Conf_t_Divine::retWeightMap[answer]); 
    const std::unordered_map<unsigned int, const pb::Conf_t_Divine*>& tbxMap = tbx::Divine().getTbxMap();
    for(auto iter = tbxMap.begin();iter != tbxMap.end();++iter)
    {
        const pb::Conf_t_Divine* temp = iter->second;
        if(temp->divine->id() == answer && randVal <= temp->getWeight())
        {
            return temp;
        }
    }
    return NULL;
}

bool SceneUser::randDivineAnswer(std::string &ret,DWORD &firstKey)
{
    std::set<DWORD> keySet;
    for(DWORD key = DIVINE_BEGIN;key <= DIVINE_END;++key)
    {
        keySet.insert(key);
    }
    std::vector<DWORD> keyVec;
    while(!keySet.empty())
    {
        DWORD key = 0;
        if(!randKey(keySet,key))
        {
            return false;
        }
        keySet.erase(key);
        keyVec.push_back(key);
        if(!firstKey)
        {
            firstKey = key;
        }
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"%u%u%u%u",keyVec[0],keyVec[1],keyVec[2],keyVec[3]);
    ret = temp;
    return true;
}

bool SceneUser::divineNotice()
{
    HelloKittyMsgData::DailyData *dailyData = charbin.mutable_dailydata();
    if(!dailyData)
    {
        return false;
    }
    HelloKittyMsgData::DivineData *divine = dailyData->mutable_divine();
    if(!divine || divine->status() == HelloKittyMsgData::DS_Vertify)
    {
        return false;
    }
    DWORD firstKey = 0;
    std::string ret;
    if(!randDivineAnswer(ret,firstKey))
    {
        return false;
    }
    divine->set_randtime(divine->randtime()+1);
    divine->set_randorder(ret);
    divine->set_status(HelloKittyMsgData::DS_Vertify);
    divine->set_firstkey(firstKey);

    HelloKittyMsgData::DivineData temp;
    temp = *divine;
    temp.set_randorder("");
    return flushDivine(&temp);
}

bool SceneUser::divine(const bool notify)
{
    HelloKittyMsgData::DivineData *divine = charbin.mutable_dailydata()->mutable_divine();
    if(!divine || divine->status() != HelloKittyMsgData::DS_Vertify)
    {
        return false;
    }
    if(notify)
    {
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"占卜(%u)",divine->randtime());
        DWORD money = RAND_DIVINE_GEM * divine->randtime();
        if(!money)
        {
            if(!m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,money,temp,false))
            {
                return opErrorReturn(HelloKittyMsgData::Gem_Not_Enough);
            }
        }
    }
    if(notify)
    {
        return flushDivine();
    }
    HelloKittyMsgData::DivineData temp;
    temp = *divine;
    temp.set_randorder("");
    return flushDivine(&temp);
}

bool SceneUser::divineVerify(const std::string &answer)
{
    HelloKittyMsgData::DailyData *dailyData = charbin.mutable_dailydata();
    if(!dailyData)
    {
        return false;
    }
    HelloKittyMsgData::DivineData *divine = dailyData->mutable_divine();
    if(!divine || divine->status() != HelloKittyMsgData::DS_Vertify)
    {
        return false;
    }

    DWORD answerType = divine->randorder() == answer ? 2 : 1;
    const pb::Conf_t_Divine* divineConf = randDivine(answerType);
    if(!divineConf)
    {
        return false;
    }
    divine->set_status(HelloKittyMsgData::DS_End);
    divine->set_answer(divineConf->divine->id());
    divine->set_lucklevel(divineConf->divine->lucklevel());
    
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"占卜(%u)",divine->randtime());
    const std::map<DWORD,DWORD> recordMap = divineConf->getRewardMap();
    if(m_store_house.hasEnoughSpace(recordMap))
    {
        for(auto iter = recordMap.begin();iter != recordMap.end();++iter)
        {
            if(!m_store_house.addOrConsumeItem(iter->first,iter->second,temp,true))
            {
                break;
            }
        }
    }
    else
    {
        EmailManager::sendEmailBySys(nickname,"占卜所得","占卜所得",recordMap);
    }
    opBuffer(this,divine->randtime(),HelloKittyMsgData::BST_Divine,divineConf->getBufferMap(),true,true);
    return flushDivine();
}

bool SceneUser::flushDivine(const HelloKittyMsgData::DivineData *divine)
{
    HelloKittyMsgData::AckDivine ackMessage;
    HelloKittyMsgData::DivineData* temp = ackMessage.mutable_divine();
    if(!temp)
    {
        return false;
    }
    if(divine)
    {
        *temp = *divine;
    }
    else
    {
        *temp = charbin.dailydata().divine();
    }

    std::string ret;
    encodeMessage(&ackMessage,ret);
    sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

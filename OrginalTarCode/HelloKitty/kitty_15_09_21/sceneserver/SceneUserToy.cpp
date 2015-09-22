#include "SceneUser.h"
#include "dataManager.h"
#include "toy.pb.h"
#include "tbx.h"

bool SceneUser::flushToy()
{
    HelloKittyMsgData::AckToy ackToy;
    for(auto iter = pb::Conf_t_Toy::idToWeightMap.begin();iter != pb::Conf_t_Toy::idToWeightMap.end();++iter)
    {
        ackToy.add_toyid(iter->first);
    }

    std::string ret;
    encodeMessage(&ackToy,ret);
    return sendCmdToMe(ret.c_str(),ret.size());
}

bool SceneUser::randToy()
{
    DWORD randTime = charbin.dailydata().randtoy();
    DWORD money = RAND_TOY_GEM * randTime;
    if(money)
    {
        if(!m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,money,"扭蛋扣除",false))
        {
            return opErrorReturn(HelloKittyMsgData::Gem_Not_Enough);
        }
    }
   
    DWORD toyID = pb::Conf_t_Toy::randToyKey();
    const pb::Conf_t_Toy *base = tbx::Toy().get_base(toyID);
    if(!base)
    {
        Fir::logger->debug("[扭蛋] 找不到配置id(%lu,%s,%u)",charid,nickname,toyID);
        return false;
    }
    HelloKittyMsgData::DailyData *temp = charbin.mutable_dailydata();
    if(temp)
    {
        temp->set_randtoy(randTime+1);
        m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_RandToy_Val,temp->randtoy(),"扭蛋",true);
        updateAttrVal(HelloKittyMsgData::Attr_RandToy_Val,temp->randtoy());
    }

    HelloKittyMsgData::AckRandToy ackRandToy;
    ackRandToy.set_randtoyid(toyID);
    std::string ret;
    encodeMessage(&ackRandToy,ret);
    sendCmdToMe(ret.c_str(),ret.size());
    
    if(!m_store_house.addOrConsumeItem(base->toy->itemid(),base->toy->num(),"扭蛋获得道具",true))
    {
        std::map<DWORD,DWORD> itemMap;
        itemMap.insert(std::pair<DWORD,DWORD>(base->toy->itemid(),base->toy->num()));
        EmailManager::sendEmailBySys(nickname,"扭蛋获得道具","扭蛋获得道具",itemMap);
    }
    return true;
}





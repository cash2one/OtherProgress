#include "SceneUser.h"
#include "zMetaData.h"
#include <stdarg.h>
#include "SceneServer.h"
#include "zMetaData.h"
#include "TimeTick.h"
#include "SceneUserManager.h"
#include <zlib.h>
#include <bitset>
#include "RecordClient.h"
#include "LoginUserCommand.h"
#include "xmlconfig.h"
#include <limits>
#include "ResType.h"
#include "RedisMgr.h"
#include "json/json.h"
#include "login.pb.h"
#include "extractProtoMsg.h"
#include "dataManager.h"
#include "tbx.h"
#include "taskAttr.h"
#include "Misc.h"

bool SceneUser::checkOpenCarnival()
{
    const pb::Conf_t_CarnivalData *carnival = tbx::CarnivalData().get_base(1);
    return carnival && m_store_house.getAttr(HelloKittyMsgData::Attr_Carnival_Val) >= carnival->carnival->state1uplimit();
}

bool SceneUser::openCarnival()
{
    const pb::Conf_t_CarnivalData *carnival = tbx::CarnivalData().get_base(1);
    if(!carnival || !checkOpenCarnival())
    {
        return false;
    }
    DWORD num = m_store_house.getAttr(HelloKittyMsgData::Attr_Carnival_Val);
    m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Carnival_Val,num,"开启嘉年华",false);
    Fir::logger->debug("[开启嘉年华嘉数值清空]:%s,%lu,%u,%u,%u",nickname,charid,num,num,m_store_house.getAttr(HelloKittyMsgData::Attr_Carnival_Val));

    DWORD rewardMoney = carnival->carnival->rewardpoint() + num * carnival->carnival->rewardgold();
    m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,rewardMoney,"嘉年华奖励",true);
    randCarnivalBox();
    return true;
}

void SceneUser::initCarnivalShopData()
{
    m_carnivalShopData.Clear();
    m_carnivalShopData.set_begintime(0);
    m_carnivalShopData.set_item(0);
    m_carnivalShopData.set_price(0);
}

bool SceneUser::randCarnivalShop()
{
    const pb::Conf_t_CarnivalShop *carnivalShop = tbx::CarnivalShop().get_base(1);
    if(!carnivalShop || !m_carnivalShopData.begintime())
    {
        return false;
    }

    DWORD randStarLevel = zMisc::randBetween(0,100) <= 50 ? 1 : 2;
    m_carnivalShopData.add_randitem(pb::Conf_t_itemInfo::randStarItem(randStarLevel));
    randStarLevel = zMisc::randBetween(0,100) < 50 ? 3 : 4;
    m_carnivalShopData.add_randitem(pb::Conf_t_itemInfo::randStarItem(randStarLevel));
    m_carnivalShopData.add_randitem(pb::Conf_t_itemInfo::randStarItem(5));

    randStarLevel = zMisc::randBetween(0,carnivalShop->getWeight()); 
    const std::vector<DWORD> &weightVec = carnivalShop->getWeightVec();
    int index = 0;
    for(auto iter = weightVec.begin();iter != weightVec.end() && index < m_carnivalShopData.randitem_size();++iter,++index)
    {
        if(randStarLevel <= *iter)
        {
            m_carnivalShopData.set_item(m_carnivalShopData.randitem(index));
            break;
        }
    }
        
    DWORD sumPrice = 0;
    for(int index = 0;index < m_carnivalShopData.randitem_size();++index)
    {
        const pb::Conf_t_itemInfo *itemInfo = tbx::itemInfo().get_base(m_carnivalShopData.randitem(index));
        if(itemInfo)
        {
            sumPrice += itemInfo->itemInfo->shopprice();
        }
    }
    m_carnivalShopData.set_price(carnivalShop->carnivalShop->discount() * 1.0 / 100 * sumPrice);

    HelloKittyMsgData::AckClickCarnicalBox ackMessage;
    ackMessage.set_price(m_carnivalShopData.price());
    for(int index = 0;index < m_carnivalShopData.randitem_size();++index)
    {
        ackMessage.add_randitem(m_carnivalShopData.randitem(index));
    }

    std::string ret; 
    encodeMessage(&ackMessage,ret);
    return sendCmdToMe(ret.c_str(),ret.size());
        
}
    
bool SceneUser::buyCarnivalBox()
{
    if(!m_carnivalShopData.item() || !m_carnivalShopData.price())
    {
        return false;
    }

    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"购买嘉年华商店物品(%u)",m_carnivalShopData.item());
    if(!m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,m_carnivalShopData.price(),temp,false))
    {
        return opErrorReturn(HelloKittyMsgData::Gem_Not_Enough);
    }
    if(!m_store_house.addOrConsumeItem(m_carnivalShopData.item(),1,"嘉年华购买",true))
    {
        std::map<DWORD,DWORD> itemMap;
        itemMap.insert(std::pair<DWORD,DWORD>(m_carnivalShopData.item(),1));
        EmailManager::sendEmailBySys(nickname,"购买嘉年华商店物品",temp,itemMap);
    }
    initCarnivalShopData();
    return true;
}

bool SceneUser::randCarnivalBox()
{
    initCarnivalShopData();
    m_carnivalShopData.set_begintime(SceneTimeTick::currentTime.sec());
    HelloKittyMsgData::AckUpdateCarnicalBox ackBox;
    ackBox.set_disapper(false);
    ackBox.set_begintime(m_carnivalShopData.begintime());

    std::string ret;
    encodeMessage(&ackBox,ret);
    return sendCmdToMe(ret.c_str(),ret.size());
}




    





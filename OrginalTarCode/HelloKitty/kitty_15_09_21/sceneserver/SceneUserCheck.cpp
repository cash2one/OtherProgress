//此文件主要放user的一些检测函数

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
#include "serialize.pb.h"
#include "dataManager.h"
#include "tbx.h"
#include "taskAttr.h"
#include "Misc.h"

bool SceneUser::checkLevel(const DWORD num)
{
    return charbase.level >= num;
}

void SceneUser::changeHappyData(HelloKittyMsgData::HappyData *happyData,const DWORD value,const DWORD judegeVal,const DWORD sec,const DWORD days,const bool gmFlg)
{
    if(value >= judegeVal && happyData)
    {
        if(happyData && (gmFlg || (!happyData->time() || sec - happyData->time() >= 24 * 36000)))
        {
            happyData->set_time(sec);
            happyData->set_frequency(happyData->frequency() + days);

            AchieveArg arg(Achieve_Target_Have,Achieve_Sub_Sorce_Day,happyData->grade(),happyData->frequency());
            m_achievementManager.target(arg);
        }
    }
}

void SceneUser::changeHappyData()
{
    DWORD happyVal = m_store_house.getAttr(HelloKittyMsgData::Attr_Happy_Val);
    if(happyVal < HAPPY_LOW)
    {
        return;
    }
    DWORD nowSec = SceneTimeTick::currentTime.sec();
    HelloKittyMsgData::HappyData *happyData = charbin.mutable_happy_hight();
    changeHappyData(happyData,happyVal,HAPPY_HIGHT,nowSec);

    happyData = charbin.mutable_happy_mid();
    changeHappyData(happyData,happyVal,HAPPY_MID,nowSec);

    happyData = charbin.mutable_happy_low();
    changeHappyData(happyData,happyVal,HAPPY_LOW,nowSec);
}

bool SceneUser::changeHappyDataGm(const DWORD happyVal,const DWORD day)
{
    if(happyVal < HAPPY_LOW)
    {
        return false;
    }
    DWORD nowSec = SceneTimeTick::currentTime.sec();
    HelloKittyMsgData::HappyData *happyData = charbin.mutable_happy_hight();
    changeHappyData(happyData,happyVal,HAPPY_HIGHT,nowSec,day,true);

    happyData = charbin.mutable_happy_mid();
    changeHappyData(happyData,happyVal,HAPPY_MID,nowSec,day,true);

    happyData = charbin.mutable_happy_low();
    changeHappyData(happyData,happyVal,HAPPY_LOW,nowSec,day,true);
    return true;
}

DWORD SceneUser::getHappyFequence(const DWORD happyVal)
{
    if(happyVal < HAPPY_LOW)
    {
        return 0;
    }
    HelloKittyMsgData::HappyData *happyData  = NULL;
    if(happyVal >= HAPPY_HIGHT)
    {
        happyData = charbin.mutable_happy_hight();
    }
    else if(happyVal >= HAPPY_MID)
    {
        happyData = charbin.mutable_happy_mid();
    }
    else if(happyVal >= HAPPY_LOW)
    {
        happyData = charbin.mutable_happy_low();
    }
    return happyData ? happyData->frequency() : 0;
}

bool SceneUser::upgrade()
{
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"升级%u扣除",charbase.level);
    const pb::Conf_t_upgrade* levelConf = tbx::upgrade().get_base(charbase.level);
    if(!levelConf || !m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Exp,levelConf->upgrade->exp(),temp,false)) 
    {
        return false;
    }
    charbase.level += 1;
    updateAttrVal(HelloKittyMsgData::Attr_Level,charbase.level);

    m_taskManager.upLevel();
    TaskArgue arg(Target_Role_Level,Attr_Role_Level,Attr_Role_Level,charbase.level);
    m_taskManager.target(arg); 
    return true;
}

bool SceneUser::changeLevel(const DWORD level)
{
    const pb::Conf_t_upgrade* levelConf = tbx::upgrade().get_base(level);
    if(!levelConf) 
    {
        return false;
    }
    charbase.level = level;
    updateAttrVal(HelloKittyMsgData::Attr_Level,charbase.level);
    m_taskManager.upLevel();
    TaskArgue arg(Target_Role_Level,Attr_Role_Level,Attr_Role_Level,charbase.level);
    m_taskManager.target(arg); 
    return true;

}

bool SceneUser::opErrorReturn(const HelloKittyMsgData::ErrorCodeType &errorCode)
{
    HelloKittyMsgData::AckReturnError error;
    error.set_reason(errorCode);

    std::string ret;
    encodeMessage(&error,ret);
    return sendCmdToMe(ret.c_str(),ret.size());
}

bool SceneUser::opSuccessReturn(const HelloKittyMsgData::SuccessCodeType &code)
{
    HelloKittyMsgData::AckReturnSuccess success;
    success.set_code(code);

    std::string ret;
    encodeMessage(&success,ret);
    return sendCmdToMe(ret.c_str(),ret.size());
}

bool SceneUser::updateAttrVal(const HelloKittyMsgData::AttrType &attrType,const DWORD value)
{
    HelloKittyMsgData::AckUpdateAttrVal updateAttr;
    updateAttr.set_attrtype(attrType);
    updateAttr.set_attrval(value);
    updateAttr.set_updatechar(charid);
    std::string ret;
    encodeMessage(&updateAttr,ret);
    broadcastMsgInMap(ret.c_str(),ret.size());
    return true;
}

bool SceneUser::addVertiseOther(const DWORD num)
{
    HelloKittyMsgData::DailyData *dailyData = charbin.mutable_dailydata();
    if(!dailyData)
    {
        return false;
    }
    dailyData->set_vistorother(dailyData->vistorother() + num);
    
    TaskArgue arg(Target_InterActive,Attr_Enter_Garden,Attr_Enter_Garden,dailyData->vistorother());
    m_taskManager.target(arg); 
    return true;
}

bool SceneUser::addFriendNum(const DWORD num)
{
    HelloKittyMsgData::DailyData *dailyData = charbin.mutable_dailydata();
    if(!dailyData)
    {
        return false;
    }
    dailyData->set_addfriend(dailyData->addfriend() + num);
    
    TaskArgue arg(Target_InterActive,Attr_Frined,Attr_Frined,0);
    m_taskManager.target(arg); 

    TaskArgue arg1(Target_InterActive,Attr_Add_Friend,Attr_Add_Friend,dailyData->addfriend());
    m_taskManager.target(arg1); 
    
    AchieveArg arg2(Achieve_Target_Have,Achieve_Sub_Sorce_Num,Attr_Frined,0);
    m_achievementManager.target(arg2);
    return true;
}


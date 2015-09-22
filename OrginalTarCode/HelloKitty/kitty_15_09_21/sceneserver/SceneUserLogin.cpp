//此文件为user登录下线的一些逻辑操作

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
#include "SceneMapDataManager.h"
#include "enterkitty.pb.h"
#include "RecordFamily.h"

bool SceneUser::reg(CMD::SCENE::t_regUser_Gatescene* cmd)
{
	this->charid = cmd->charid;
	this->accid = cmd->accid;
	strncpy(this->nickname, cmd->name, sizeof(this->nickname));

	if(!RedisMgr::getMe().get_charbase(this->charid,this->charbase))
	{
        Fir::logger->debug("[客户端登录_3]:角色注册场景失败(charbase数据异常,%lu)",this->charid);
		return false;
	}
	HelloKittyMsgData::Serialize binary;
	if(!RedisMgr::getMe().get_binary(this->charid,binary))
	{
        Fir::logger->debug("[客户端登录_3]:角色注册场景失败(binary数据异常,%lu)",this->charid);
		return false;
	}

	if(!RedisMgr::getMe().is_login_first(this->charid))
	{
		setupBinaryArchive(binary);
	}
	changeTime();
	bool ret = SceneUserManager::getMe().addUser(this);
    Fir::logger->debug("[客户端登录_3]:角色注册场景%s(注册场景,%lu)",ret ? "成功" : "失败",this->charid);
    return ret;

}


void SceneUser::offline()
{
	Fir::logger->error("[下线]:%u,%lu,%s 角色下线成功", this->accid, this->charid, this->nickname);
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if(handle)
		handle->delSet("playerset",0 ,"online" , this->charid);
	_online = false;
	charbase.offlinetime = SceneTimeTick::currentTime.sec();
	getFriendManager().offline();
	setVisit(0);
	save();
	gate = NULL;
}

bool SceneUser::online(std::string phone_uuid,SceneTask* _gate)
{
	if (_online) 
	{
        Fir::logger->debug("[客户端登录_3]:角色注册场景失败(角色已在线,%lu)",this->charid);
		return false;
	}
	gate = _gate;
	_online = true;
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if(handle)
    {
		handle->setSet("playerset",0 ,"online" , this->charid);
    }
    Fir::logger->debug("[客户端登录_3]:角色注册场景成功(角色在线成功,%lu)",this->charid);


	//----所有上线初始化，放在该行以上------
	//通知会话，场景上线成功

	CMD::SCENE::t_Refresh_LoginScene ret_gate;
	ret_gate.charid = this->charid;
	std::string ret;
	encodeMessage(&ret_gate,sizeof(ret_gate),ret);
	if (gate)
	{
		gate->sendCmd(ret.c_str(),ret.size());
	}

	//----上线初始化完成后的处理 都放在onlineInit这个函数里------
	this->onlineInit();
	getFriendManager().online();

	return true;
}

bool SceneUser::unreg()
{
	//玩家处于离线状态，除了登录消息，不接收任何其它用户指令
	this->offline();
	return true;
}

bool SceneUser::initNewRole()
{
	const pb::Conf_t_newRoleAttr *confBase = tbx::newRoleAttr().get_base(1);
	if(!confBase)
	{
		Fir::logger->debug("错误:SceneUser::initNewRole找不到对应的初始数据表");
		return false;
	}

    //等级
    charbase.level = confBase->roleAttr->level();
    //性别
    charbase.sex = 0;
    //嘉年华数值
    m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Carnival_Val,120,"新建角色",true);
    //所穿时装
    HelloKittyMsgData::DressData *temp = charbin.mutable_dress();
    if(temp)
    {
        temp->set_id(0);
        temp->set_level(0);
    }
    //愉悦值的3个档次数据
    HelloKittyMsgData::HappyData *happData = charbin.mutable_happy_low();
    if(happData)
    {
        happData->set_grade(HAPPY_LOW);
        happData->set_frequency(0);
        happData->set_time(0);
    }
    happData = charbin.mutable_happy_mid();
    if(happData)
    {
        happData->set_grade(HAPPY_MID);
        happData->set_frequency(0);
        happData->set_time(0);
    }
    happData = charbin.mutable_happy_hight();
    if(happData)
    {
        happData->set_grade(HAPPY_HIGHT);
        happData->set_frequency(0);
        happData->set_time(0);
    }

    //初始仓库和角色属性
    m_store_house.init(confBase->getItemMap());

	//嘉年华商城
	initCarnivalShopData();

	//初始化日常数据刷新时间
	initDailyData();

	//初始化kitty乐园地图
	const MapData *mapConf = SceneMapDataManager::getMe().getMapData(KittyGardenMapID);
	m_kittyGarden.fullMapData(mapConf);

	//初始化建筑管理器
	m_buildManager.init(confBase);

	//初始化交易模块
	m_trade.initTradeInfo();

	//初始化任务列表
	m_taskManager.init();

	//初始化成就信息
	m_achievementManager.init();

	return true;
}

bool SceneUser::flushUserInfo()
{   
	HelloKittyMsgData::AckFlushUserInfo send;
	HelloKittyMsgData::UserBaseInfo *userBaseInfo = send.mutable_userbase();
	userBaseInfo->set_name(nickname);
	userBaseInfo->set_charid(this->charid);
	HelloKittyMsgData::SexType sexType = charbase.sex ? HelloKittyMsgData::Female : HelloKittyMsgData::Male;
	userBaseInfo->set_sex(sexType);
	userBaseInfo->set_level(charbase.level);
	userBaseInfo->set_gold(m_store_house.getAttr(HelloKittyMsgData::Attr_Gold));
	userBaseInfo->set_gem(m_store_house.getAttr(HelloKittyMsgData::Attr_Gem));
	userBaseInfo->set_exp(m_store_house.getAttr(HelloKittyMsgData::Attr_Exp));
	userBaseInfo->set_workernum(m_store_house.getAttr(HelloKittyMsgData::Attr_Worker));
	userBaseInfo->set_friendval(m_store_house.getAttr(HelloKittyMsgData::Attr_Friend_Val));
	userBaseInfo->set_happyval(m_store_house.getAttr(HelloKittyMsgData::Attr_Happy_Val));
	userBaseInfo->set_itemwarehousecap(m_store_house.getAttr(HelloKittyMsgData::Attr_Ware_Grid_Val));
	userBaseInfo->set_carnival(m_store_house.getAttr(HelloKittyMsgData::Attr_Carnival_Val));
	userBaseInfo->set_randtoy(m_store_house.getAttr(HelloKittyMsgData::Attr_RandToy_Val));
	userBaseInfo->set_sweetval(m_store_house.getAttr(HelloKittyMsgData::Attr_Sweet_Val));
	HelloKittyMsgData::DressData *dressData = userBaseInfo->mutable_dress();
	if(dressData)
	{
		*dressData = charbin.dress();
	}

	//填充全局buffer
	fullUserInfoBuffer(*userBaseInfo);
	//填充建筑信息
	m_buildManager.fullMessage(*userBaseInfo);
	//填充地图信息
	m_kittyGarden.fullMessage(*userBaseInfo);
	//填充建筑的产出 
	m_buildManager.fullBuildProduce(userBaseInfo);
	//填充事件信息
	m_eventmanager.fullMessage(this->charid,userBaseInfo->mutable_eventinit());
	userBaseInfo->set_familyid(RecordFamily::getMe().getFamilyID(this->charid));
    //突发事件
    m_burstEventManager.fullMessage(*userBaseInfo);
    

	//刷新角色面板消息
	std::string ret;
	if(encodeMessage(&send,ret))
	{
		this->sendCmdToMe(ret.c_str(),ret.size());
	}
	return true;
}

bool SceneUser::flushUserInfo(HelloKittyMsgData::AckFlushUserInfo &send)
{   
	HelloKittyMsgData::UserBaseInfo *userBaseInfo = send.mutable_userbase();
	userBaseInfo->set_name(nickname);
	userBaseInfo->set_charid(this->charid);
	HelloKittyMsgData::SexType sexType = charbase.sex ? HelloKittyMsgData::Female : HelloKittyMsgData::Male;
	userBaseInfo->set_sex(sexType);

	userBaseInfo->set_level(charbase.level);
	userBaseInfo->set_gold(m_store_house.getAttr(HelloKittyMsgData::Attr_Gold));
	userBaseInfo->set_gem(m_store_house.getAttr(HelloKittyMsgData::Attr_Gem));
	userBaseInfo->set_exp(m_store_house.getAttr(HelloKittyMsgData::Attr_Exp));
	userBaseInfo->set_workernum(m_store_house.getAttr(HelloKittyMsgData::Attr_Worker));
	userBaseInfo->set_friendval(m_store_house.getAttr(HelloKittyMsgData::Attr_Friend_Val));
	userBaseInfo->set_happyval(m_store_house.getAttr(HelloKittyMsgData::Attr_Happy_Val));
	userBaseInfo->set_itemwarehousecap(m_store_house.getAttr(HelloKittyMsgData::Attr_Ware_Grid_Val));
	//填充建筑信息
	m_buildManager.fullMessage(*userBaseInfo);
	//填充地图信息
	m_kittyGarden.fullMessage(*userBaseInfo);

	return true;
}

bool SceneUser::flushKittyGardenInfo(QWORD sendCharID, HelloKittyMsgData::AckEnterGarden &send)
{   
	HelloKittyMsgData::EnterGardenInfo *gardenInfo = send.mutable_gardeninfo();
	gardenInfo->set_name(nickname);
	gardenInfo->set_charid(this->charid);
	gardenInfo->set_level(this->charbase.level);
	gardenInfo->set_exp(m_store_house.getAttr(HelloKittyMsgData::Attr_Exp));
	//填充建筑信息
	m_buildManager.fullMessage(*gardenInfo);
	//填充地图信息
	m_kittyGarden.fullMessage(*gardenInfo);
	//填充事件信息
	m_eventmanager.fullMessage(sendCharID,gardenInfo->mutable_eventinit());


	return true;
}

bool SceneUser::flushKittyGardenInfo()
{   
	HelloKittyMsgData::AckEnterGarden send;
	HelloKittyMsgData::EnterGardenInfo *gardenInfo = send.mutable_gardeninfo();
	gardenInfo->set_name(nickname);
	gardenInfo->set_charid(this->charid);
	gardenInfo->set_level(this->charbase.level);
	gardenInfo->set_exp(m_store_house.getAttr(HelloKittyMsgData::Attr_Exp));
	//填充建筑信息
	m_buildManager.fullMessage(*gardenInfo);
	//填充地图信息
	m_kittyGarden.fullMessage(*gardenInfo);

	std::string ret;
	if(encodeMessage(&send,ret))
	{
		this->sendCmdToMe(ret.c_str(),ret.size());
	}
	return true;
}

void SceneUser::onlineInit()
{
	if(!charbase.onlinetime)
	{
		initNewRole();
	}

	//重置日常数据
	if(isDailyData())
	{
		brushDailyData();
	}

	//初始化全局buffer
	initBuffer();

	//登录时间
	charbase.onlinetime = SceneTimeTick::currentTime.sec();     

	//保存数据
	save();

	//刷新角色面板消息
	flushUserInfo();

	//刷新摊位信息
	m_trade.flushSaleBooth();

	//刷新kitty乐园
	m_kittyGarden.flushMap();
}



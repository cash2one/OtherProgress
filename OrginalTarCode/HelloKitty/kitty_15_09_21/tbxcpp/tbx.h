#ifndef __TBX_H__
#define __TBX_H__
#include "Event.pb.h"
#include "Paper.pb.h"
#include "AchievementInfo.pb.h"
#include "TaskInfo.pb.h"
#include "BurstEventReward.pb.h"
#include "GardenActivetyItem.pb.h"
#include "Dress.pb.h"
#include "Role.pb.h"
#include "Building.pb.h"
#include "Production.pb.h"
#include "BurstEventNpc.pb.h"
#include "CarnivalShop.pb.h"
#include "Buffer.pb.h"
#include "ItemInfo.pb.h"
#include "HandBook.pb.h"
#include "Toy.pb.h"
#include "CarnivalData.pb.h"
#include "Divine.pb.h"
#include "Param.pb.h"
#include "tbxbase.h"

namespace tbx 
{
	const tbx::table< pb::BurstEventNpc,pb::Conf_t_BurstEventNpc,pb::BurstEventNpc::t_BurstEventNpc >& BurstEventNpc();
	const tbx::table< pb::rubbish,pb::Conf_t_rubbish,pb::rubbish::t_rubbish >& rubbish();
	const tbx::table< pb::Toy,pb::Conf_t_Toy,pb::Toy::t_Toy >& Toy();
	const tbx::table< pb::buffer,pb::Conf_t_buffer,pb::buffer::t_buffer >& buffer();
	const tbx::table< pb::CarnivalShop,pb::Conf_t_CarnivalShop,pb::CarnivalShop::t_CarnivalShop >& CarnivalShop();
	const tbx::table< pb::CarnivalData,pb::Conf_t_CarnivalData,pb::CarnivalData::t_CarnivalData >& CarnivalData();
	const tbx::table< pb::building,pb::Conf_t_building,pb::building::t_building >& building();
	const tbx::table< pb::newRoleAttr,pb::Conf_t_newRoleAttr,pb::newRoleAttr::t_newRoleAttr >& newRoleAttr();
	const tbx::table< pb::BurstEventReward,pb::Conf_t_BurstEventReward,pb::BurstEventReward::t_BurstEventReward >& BurstEventReward();
	const tbx::table< pb::upgrade,pb::Conf_t_upgrade,pb::upgrade::t_upgrade >& upgrade();
	const tbx::table< pb::event,pb::Conf_t_event,pb::event::t_event >& event();
	const tbx::table< pb::Task,pb::Conf_t_Task,pb::Task::t_Task >& Task();
	const tbx::table< pb::Dress,pb::Conf_t_Dress,pb::Dress::t_Dress >& Dress();
	const tbx::table< pb::produceItem,pb::Conf_t_produceItem,pb::produceItem::t_produceItem >& produceItem();
	const tbx::table< pb::Handbook,pb::Conf_t_Handbook,pb::Handbook::t_Handbook >& Handbook();
	const tbx::table< pb::Divine,pb::Conf_t_Divine,pb::Divine::t_Divine >& Divine();
	const tbx::table< pb::param,pb::Conf_t_param,pb::param::t_param >& param();
	const tbx::table< pb::Paper,pb::Conf_t_Paper,pb::Paper::t_Paper >& Paper();
	const tbx::table< pb::itemInfo,pb::Conf_t_itemInfo,pb::itemInfo::t_itemInfo >& itemInfo();
	const tbx::table< pb::Achievement,pb::Conf_t_Achievement,pb::Achievement::t_Achievement >& Achievement();

	const pb::Conf_t_BurstEventNpc& BurstEventNpc(unsigned int id);
	const pb::Conf_t_rubbish& rubbish(unsigned int id);
	const pb::Conf_t_Toy& Toy(unsigned int id);
	const pb::Conf_t_buffer& buffer(unsigned int id);
	const pb::Conf_t_CarnivalShop& CarnivalShop(unsigned int id);
	const pb::Conf_t_CarnivalData& CarnivalData(unsigned int id);
	const pb::Conf_t_building& building(unsigned int id);
	const pb::Conf_t_newRoleAttr& newRoleAttr(unsigned int id);
	const pb::Conf_t_BurstEventReward& BurstEventReward(unsigned int id);
	const pb::Conf_t_upgrade& upgrade(unsigned int id);
	const pb::Conf_t_event& event(unsigned int id);
	const pb::Conf_t_Task& Task(unsigned int id);
	const pb::Conf_t_Dress& Dress(unsigned int id);
	const pb::Conf_t_produceItem& produceItem(unsigned int id);
	const pb::Conf_t_Handbook& Handbook(unsigned int id);
	const pb::Conf_t_Divine& Divine(unsigned int id);
	const pb::Conf_t_param& param(unsigned int id);
	const pb::Conf_t_Paper& Paper(unsigned int id);
	const pb::Conf_t_itemInfo& itemInfo(unsigned int id);
	const pb::Conf_t_Achievement& Achievement(unsigned int id);
}

#endif
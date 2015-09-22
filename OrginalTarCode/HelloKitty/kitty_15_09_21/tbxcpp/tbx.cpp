#include "tbx.h"

namespace tbx 
{
	tbx::table<pb::BurstEventNpc,pb::Conf_t_BurstEventNpc,pb::BurstEventNpc::t_BurstEventNpc> _BurstEventNpc;
	tbx::table<pb::rubbish,pb::Conf_t_rubbish,pb::rubbish::t_rubbish> _rubbish;
	tbx::table<pb::Toy,pb::Conf_t_Toy,pb::Toy::t_Toy> _Toy;
	tbx::table<pb::buffer,pb::Conf_t_buffer,pb::buffer::t_buffer> _buffer;
	tbx::table<pb::CarnivalShop,pb::Conf_t_CarnivalShop,pb::CarnivalShop::t_CarnivalShop> _CarnivalShop;
	tbx::table<pb::CarnivalData,pb::Conf_t_CarnivalData,pb::CarnivalData::t_CarnivalData> _CarnivalData;
	tbx::table<pb::building,pb::Conf_t_building,pb::building::t_building> _building;
	tbx::table<pb::newRoleAttr,pb::Conf_t_newRoleAttr,pb::newRoleAttr::t_newRoleAttr> _newRoleAttr;
	tbx::table<pb::BurstEventReward,pb::Conf_t_BurstEventReward,pb::BurstEventReward::t_BurstEventReward> _BurstEventReward;
	tbx::table<pb::upgrade,pb::Conf_t_upgrade,pb::upgrade::t_upgrade> _upgrade;
	tbx::table<pb::event,pb::Conf_t_event,pb::event::t_event> _event;
	tbx::table<pb::Task,pb::Conf_t_Task,pb::Task::t_Task> _Task;
	tbx::table<pb::Dress,pb::Conf_t_Dress,pb::Dress::t_Dress> _Dress;
	tbx::table<pb::produceItem,pb::Conf_t_produceItem,pb::produceItem::t_produceItem> _produceItem;
	tbx::table<pb::Handbook,pb::Conf_t_Handbook,pb::Handbook::t_Handbook> _Handbook;
	tbx::table<pb::Divine,pb::Conf_t_Divine,pb::Divine::t_Divine> _Divine;
	tbx::table<pb::param,pb::Conf_t_param,pb::param::t_param> _param;
	tbx::table<pb::Paper,pb::Conf_t_Paper,pb::Paper::t_Paper> _Paper;
	tbx::table<pb::itemInfo,pb::Conf_t_itemInfo,pb::itemInfo::t_itemInfo> _itemInfo;
	tbx::table<pb::Achievement,pb::Conf_t_Achievement,pb::Achievement::t_Achievement> _Achievement;

	void mgr::init(Fir::XMLParser &xml, const tbx::ReadTbxBufFunc &func)
	{
		loadconfig(xml);
		load_table("pb.BurstEventNpc",_BurstEventNpc,func);
		load_table("pb.rubbish",_rubbish,func);
		load_table("pb.Toy",_Toy,func);
		load_table("pb.buffer",_buffer,func);
		load_table("pb.CarnivalShop",_CarnivalShop,func);
		load_table("pb.CarnivalData",_CarnivalData,func);
		load_table("pb.building",_building,func);
		load_table("pb.newRoleAttr",_newRoleAttr,func);
		load_table("pb.BurstEventReward",_BurstEventReward,func);
		load_table("pb.upgrade",_upgrade,func);
		load_table("pb.event",_event,func);
		load_table("pb.Task",_Task,func);
		load_table("pb.Dress",_Dress,func);
		load_table("pb.produceItem",_produceItem,func);
		load_table("pb.Handbook",_Handbook,func);
		load_table("pb.Divine",_Divine,func);
		load_table("pb.param",_param,func);
		load_table("pb.Paper",_Paper,func);
		load_table("pb.itemInfo",_itemInfo,func);
		load_table("pb.Achievement",_Achievement,func);
	}

	const tbx::table< pb::BurstEventNpc,pb::Conf_t_BurstEventNpc,pb::BurstEventNpc::t_BurstEventNpc >& BurstEventNpc()
	{
		 return _BurstEventNpc;
	}
	const tbx::table< pb::rubbish,pb::Conf_t_rubbish,pb::rubbish::t_rubbish >& rubbish()
	{
		 return _rubbish;
	}
	const tbx::table< pb::Toy,pb::Conf_t_Toy,pb::Toy::t_Toy >& Toy()
	{
		 return _Toy;
	}
	const tbx::table< pb::buffer,pb::Conf_t_buffer,pb::buffer::t_buffer >& buffer()
	{
		 return _buffer;
	}
	const tbx::table< pb::CarnivalShop,pb::Conf_t_CarnivalShop,pb::CarnivalShop::t_CarnivalShop >& CarnivalShop()
	{
		 return _CarnivalShop;
	}
	const tbx::table< pb::CarnivalData,pb::Conf_t_CarnivalData,pb::CarnivalData::t_CarnivalData >& CarnivalData()
	{
		 return _CarnivalData;
	}
	const tbx::table< pb::building,pb::Conf_t_building,pb::building::t_building >& building()
	{
		 return _building;
	}
	const tbx::table< pb::newRoleAttr,pb::Conf_t_newRoleAttr,pb::newRoleAttr::t_newRoleAttr >& newRoleAttr()
	{
		 return _newRoleAttr;
	}
	const tbx::table< pb::BurstEventReward,pb::Conf_t_BurstEventReward,pb::BurstEventReward::t_BurstEventReward >& BurstEventReward()
	{
		 return _BurstEventReward;
	}
	const tbx::table< pb::upgrade,pb::Conf_t_upgrade,pb::upgrade::t_upgrade >& upgrade()
	{
		 return _upgrade;
	}
	const tbx::table< pb::event,pb::Conf_t_event,pb::event::t_event >& event()
	{
		 return _event;
	}
	const tbx::table< pb::Task,pb::Conf_t_Task,pb::Task::t_Task >& Task()
	{
		 return _Task;
	}
	const tbx::table< pb::Dress,pb::Conf_t_Dress,pb::Dress::t_Dress >& Dress()
	{
		 return _Dress;
	}
	const tbx::table< pb::produceItem,pb::Conf_t_produceItem,pb::produceItem::t_produceItem >& produceItem()
	{
		 return _produceItem;
	}
	const tbx::table< pb::Handbook,pb::Conf_t_Handbook,pb::Handbook::t_Handbook >& Handbook()
	{
		 return _Handbook;
	}
	const tbx::table< pb::Divine,pb::Conf_t_Divine,pb::Divine::t_Divine >& Divine()
	{
		 return _Divine;
	}
	const tbx::table< pb::param,pb::Conf_t_param,pb::param::t_param >& param()
	{
		 return _param;
	}
	const tbx::table< pb::Paper,pb::Conf_t_Paper,pb::Paper::t_Paper >& Paper()
	{
		 return _Paper;
	}
	const tbx::table< pb::itemInfo,pb::Conf_t_itemInfo,pb::itemInfo::t_itemInfo >& itemInfo()
	{
		 return _itemInfo;
	}
	const tbx::table< pb::Achievement,pb::Conf_t_Achievement,pb::Achievement::t_Achievement >& Achievement()
	{
		 return _Achievement;
	}

	const pb::Conf_t_BurstEventNpc& BurstEventNpc(unsigned int id)
	{
		 return _BurstEventNpc.get(id);
	}
	const pb::Conf_t_rubbish& rubbish(unsigned int id)
	{
		 return _rubbish.get(id);
	}
	const pb::Conf_t_Toy& Toy(unsigned int id)
	{
		 return _Toy.get(id);
	}
	const pb::Conf_t_buffer& buffer(unsigned int id)
	{
		 return _buffer.get(id);
	}
	const pb::Conf_t_CarnivalShop& CarnivalShop(unsigned int id)
	{
		 return _CarnivalShop.get(id);
	}
	const pb::Conf_t_CarnivalData& CarnivalData(unsigned int id)
	{
		 return _CarnivalData.get(id);
	}
	const pb::Conf_t_building& building(unsigned int id)
	{
		 return _building.get(id);
	}
	const pb::Conf_t_newRoleAttr& newRoleAttr(unsigned int id)
	{
		 return _newRoleAttr.get(id);
	}
	const pb::Conf_t_BurstEventReward& BurstEventReward(unsigned int id)
	{
		 return _BurstEventReward.get(id);
	}
	const pb::Conf_t_upgrade& upgrade(unsigned int id)
	{
		 return _upgrade.get(id);
	}
	const pb::Conf_t_event& event(unsigned int id)
	{
		 return _event.get(id);
	}
	const pb::Conf_t_Task& Task(unsigned int id)
	{
		 return _Task.get(id);
	}
	const pb::Conf_t_Dress& Dress(unsigned int id)
	{
		 return _Dress.get(id);
	}
	const pb::Conf_t_produceItem& produceItem(unsigned int id)
	{
		 return _produceItem.get(id);
	}
	const pb::Conf_t_Handbook& Handbook(unsigned int id)
	{
		 return _Handbook.get(id);
	}
	const pb::Conf_t_Divine& Divine(unsigned int id)
	{
		 return _Divine.get(id);
	}
	const pb::Conf_t_param& param(unsigned int id)
	{
		 return _param.get(id);
	}
	const pb::Conf_t_Paper& Paper(unsigned int id)
	{
		 return _Paper.get(id);
	}
	const pb::Conf_t_itemInfo& itemInfo(unsigned int id)
	{
		 return _itemInfo.get(id);
	}
	const pb::Conf_t_Achievement& Achievement(unsigned int id)
	{
		 return _Achievement.get(id);
	}
}

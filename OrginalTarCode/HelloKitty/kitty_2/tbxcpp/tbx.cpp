#include "tbx.h"

namespace tbx 
{
	tbx::table<pb::building,pb::Conf_t_building,pb::building::t_building> _building;
	tbx::table<pb::newRoleAttr,pb::Conf_t_newRoleAttr,pb::newRoleAttr::t_newRoleAttr> _newRoleAttr;
	tbx::table<pb::itemInfo,pb::Conf_t_itemInfo,pb::itemInfo::t_itemInfo> _itemInfo;

	void mgr::init(Fir::XMLParser &xml, const tbx::ReadTbxBufFunc &func)
	{
		loadconfig(xml);
		load_table("pb.building",_building,func);
		load_table("pb.newRoleAttr",_newRoleAttr,func);
		load_table("pb.itemInfo",_itemInfo,func);
	}

	const tbx::table< pb::building,pb::Conf_t_building,pb::building::t_building >& building()
	{
		 return _building;
	}
	const tbx::table< pb::newRoleAttr,pb::Conf_t_newRoleAttr,pb::newRoleAttr::t_newRoleAttr >& newRoleAttr()
	{
		 return _newRoleAttr;
	}
	const tbx::table< pb::itemInfo,pb::Conf_t_itemInfo,pb::itemInfo::t_itemInfo >& itemInfo()
	{
		 return _itemInfo;
	}

	const pb::Conf_t_building& building(unsigned int id)
	{
		 return _building.get(id);
	}
	const pb::Conf_t_newRoleAttr& newRoleAttr(unsigned int id)
	{
		 return _newRoleAttr.get(id);
	}
	const pb::Conf_t_itemInfo& itemInfo(unsigned int id)
	{
		 return _itemInfo.get(id);
	}
}

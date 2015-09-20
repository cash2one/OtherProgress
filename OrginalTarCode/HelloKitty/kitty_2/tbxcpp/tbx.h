#ifndef __TBX_H__
#define __TBX_H__
#include "building.pb.h"
#include "itemInfo.pb.h"
#include "tbxbase.h"

namespace tbx 
{
	const tbx::table< pb::building,pb::Conf_t_building,pb::building::t_building >& building();
	const tbx::table< pb::newRoleAttr,pb::Conf_t_newRoleAttr,pb::newRoleAttr::t_newRoleAttr >& newRoleAttr();
	const tbx::table< pb::itemInfo,pb::Conf_t_itemInfo,pb::itemInfo::t_itemInfo >& itemInfo();

	const pb::Conf_t_building& building(unsigned int id);
	const pb::Conf_t_newRoleAttr& newRoleAttr(unsigned int id);
	const pb::Conf_t_itemInfo& itemInfo(unsigned int id);
}

#endif
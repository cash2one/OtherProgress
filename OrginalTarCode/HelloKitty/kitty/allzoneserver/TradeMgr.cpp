#include "TradeMgr.h"
#include "TimeTick.h"
#include "zSocket.h"
#include "zCmdBuffer.h"
#include "AllZoneCommand.h"
#include "ZoneManager.h"
#include "AllZoneServer.h"

TradeMgr::TradeMgr()
{
}

TradeMgr::~TradeMgr()
{
}

void TradeMgr::addSaleInfo(DWORD charid, const std::vector<CMD::stSaleCell>& vecCells)
{
#if 0
	auto itr=_mapSaleInfos.find(charid);
	if(itr == _mapSaleInfos.end())
	{
		stSaleInfo info;
		info.charid = charid;
		info.modify_time = AZTimeTick::currentTime.sec();
		info.vecCells.assign(vecCells.begin(),vecCells.end());
		_mapSaleInfos.insert(std::make_pair(charid,info));
		return;
	}

	stSaleInfo& info = itr->second;
	info.modify_time = AZTimeTick::currentTime.sec();
	info.vecCells.clear();
	info.vecCells.assign(vecCells.begin(),vecCells.end());
#endif
}

void TradeMgr::reqSomePlayersSaleCells(DWORD zoneid,DWORD sceneid,QWORD charid)
{
#if 0
	MsgAllRoleCell allrolecell;
	for(auto itr=_mapSaleInfos.begin(); itr!=_mapSaleInfos.end(); itr++)
	{
		stSaleInfo& info = itr->second;
		if(info.charid == charid) continue;

		MsgRoleCell* rolecell = allrolecell.add_rolecells();
		if(NULL == rolecell) break;
		rolecell->set_charid(info.charid);
		for(auto itr2=info.vecCells.begin(); itr2!=info.vecCells.end(); itr2++)
		{
			const CMD::stSaleCell& cell = *itr2;
			MsgSaleCell* pcell = rolecell->add_salecells();
			if(NULL == pcell) break;
			pcell->set_cellid(cell.cellid);
			pcell->set_itemid(cell.itemid);
			pcell->set_itemcount(cell.itemcount);
			pcell->set_status(cell.status);
			pcell->set_nickname(cell.nickname);
		}

		if(allrolecell.rolecells_size() >= 30)
			break;
	}

	if ((DWORD)allrolecell.ByteSize() > zSocket::MAX_DATASIZE)
    {
        Fir::logger->error("[贸易系统],charid=%lu,严重错误请求物品数据大于64K",charid);
        return;
    }

	zCmdBufferAdapterT<CMD::ALLZONE::t_AllZone2Super_RetSomePlayerSaleCells> send;	
	send->datasize = allrolecell.ByteSize();
    char buffer[zSocket::MAX_DATASIZE] = {0};
    *(BYTE*)buffer = PROTOBUF_TYPE;
    allrolecell.SerializeToArray(buffer+sizeof(BYTE),send->datasize);
	if (!send.write(&buffer, send->datasize))
	{
		Fir::logger->error("[贸易系统],charid=%lu,严重错误战斗数据大于64K",charid);
		return;
	}
        
	AllZoneService::getMe().sendCmdToScene(zoneid,sceneid,send.data(),send.size());	
	//ZoneManager::getMe().broadcastByID(zoneid,send.data(),send.size());
#endif
}

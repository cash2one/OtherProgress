#include "UTrade.h"
#include "TradeCommand.h"
#include "tbx.h"
#include "SceneUser.h"
#include "AllZoneCommand.h"
#include "SceneServer.h"

using namespace CMD;

UTrade::UTrade(SceneUser* u)
{
	owner = u;
}

UTrade::~UTrade()
{

}
#if 0
void UTrade::save(Serialize& binary)
{
	for(auto itr=_mapSaleCells.begin(); itr!=_mapSaleCells.end(); itr++)
	{
		const stSaleCell& cell = itr->second;
		PbSaleCell* pcell = binary.add_sale_cells();
		pcell->set_cellid(cell.cellid);
		pcell->set_itemid(cell.itemid);
		pcell->set_itemcount(cell.itemcount);
		pcell->set_status(cell.status);
		pcell->set_nickname(cell.nickname);
	}
}

void UTrade::load(const Serialize& binary)
{
	_mapSaleCells.clear();
	for(int i=0; i<binary.sale_cells_size(); i++)
	{
		const PbSaleCell& cell = binary.sale_cells(i);
		stSaleCell item;
		item.cellid = cell.cellid();
		item.itemid = cell.itemid();
		item.itemcount = cell.itemcount();	
		item.status = cell.status();
		strncpy(item.nickname,cell.nickname().c_str(),MAX_NAMESIZE);
		_mapSaleCells.insert(std::make_pair(item.cellid,item));	
	}
}
#endif
bool UTrade::initTradeInfo()
{
	for(DWORD i=0; i<owner->charbase.sale_grid_count; i++)
	{
		stSaleCell  cell;
		cell.cellid = i+1;
		addSaleCell(cell);	
	}	
	
	return true;
}

bool UTrade::addSaleCell(const stSaleCell& cell)
{
	auto itrfind = _mapSaleCells.find(cell.cellid);
	if(itrfind == _mapSaleCells.end())
	{
		_mapSaleCells.insert(std::make_pair(cell.cellid,cell));
		return true;
	}

	return false;
}

bool UTrade::req_itemconfig()
{
 #if 0
	zCmdBufferAdapterT<CMD::stRetItemconfig_SC> send;
        for (auto it = tbx::item_config().begin(); it != tbx::item_config().end(); ++it)
        {
                const pb::item_config::t_item_config *base = it->second;
                if(NULL == base)
                {
                        Fir::logger->error("[贸易系统],请求t_item_config配置出错");
                        return false;
                }
		
		CMD::stconfigItem *item = send.constructTail<CMD::stconfigItem>();
		if(NULL == item)
			break;
		
		item->itemid = base->id();
		strncpy(item->name, base->name().c_str(), 30);
		strncpy(item->desc, base->desc().c_str(), 50);
		item->price = base->price();
		
		send->count++;
	}        
	
        owner->sendCmdToMe(send.data(), send.size());
 #endif
	return true;
}

bool UTrade::req_sale_cells()
{
	zCmdBufferAdapterT<CMD::stRetSaleCells_SC> send;
	
	for(auto itr=_mapSaleCells.begin(); itr!=_mapSaleCells.end(); itr++)
	{
		CMD::stSaleCell *cell = send.constructTail<CMD::stSaleCell>();
                if(NULL == cell)
                        break;
		*cell = itr->second;
		send->count++;
	}
	
	owner->sendCmdToMe(send.data(), send.size());
	
	return true;
}

bool UTrade::hasCell(DWORD cellid)
{
	return _mapSaleCells.find(cellid) != _mapSaleCells.end();
}

CMD::stSaleCell& UTrade::getCell(DWORD cellid)
{
	auto itr=_mapSaleCells.find(cellid);
	if(itr != _mapSaleCells.end())	
	{
		return itr->second;
	}

	static CMD::stSaleCell s_cell;
	return s_cell;
}

bool UTrade::req_salecell_putitem(DWORD cellid, DWORD itemid, DWORD itemcount)
{
	if(!hasCell(cellid))
	{
		CMD::stRetSaleCellPutItem_SC send;
		send.errorcode = 1; // 失败
		owner->sendCmdToMe(&send,sizeof(send));
		return true;	
	}		

	CMD::stSaleCell& cell = getCell(cellid);
	if(cell.status != 0)
	{
		CMD::stRetSaleCellPutItem_SC send;
                send.errorcode = 1; // 失败
                owner->sendCmdToMe(&send,sizeof(send));
                return true;
	}
	
	if(!owner->_store_house.hasEnoughItem(itemid,itemcount))
	{
		CMD::stRetSaleCellPutItem_SC send;
                send.errorcode = 1; // 失败
                owner->sendCmdToMe(&send,sizeof(send));
                return true;
	}
	owner->_store_house.consumeItem(itemid,itemcount);

	cell.status = 1; // 放上物品
	cell.itemid = itemid;
	cell.itemcount = itemcount;

	CMD::stRetSaleCellPutItem_SC send;
	send.errorcode = 0; // 成功
	owner->sendCmdToMe(&send,sizeof(send));

	zCmdBufferAdapterT<CMD::ALLZONE::t_Super2AllZone_SaleCells> sendallzone;
	sendallzone->charid = owner->charid;
	for(auto itr=_mapSaleCells.begin(); itr!=_mapSaleCells.end(); itr++)
	{
		CMD::stSaleCell *cell = sendallzone.constructTail<CMD::stSaleCell>();
		if(NULL == cell)
			break;
		*cell = itr->second;
		sendallzone->count++;
	}
	SceneService::getMe().sendCmdToAllZone(sendallzone.data(), sendallzone.size());
		
	return true;
}

bool UTrade::ret_someplayer_salecells(const std::vector<char>& vecBinary)
{
	BYTE buf[zSocket::MAX_DATASIZE];
	stRetOtherPlayerSaleCells_SC *scmd=(stRetOtherPlayerSaleCells_SC *)buf;
	constructInPlace(scmd);

	scmd->datasize = vecBinary.size();
	bcopy(&vecBinary[0], scmd->data, scmd->datasize);
	owner->sendCmdToMe(&scmd,scmd->getSize());	
	
	return true;
}

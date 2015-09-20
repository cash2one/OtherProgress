#include "TradeMgr.h"
#include "TimeTick.h"
#include "zSocket.h"
#include "zCmdBuffer.h"
#include "AllZoneCommand.h"
#include "ZoneManager.h"
#include "AllZoneServer.h"
#include "login.pb.h"

TradeMgr::TradeMgr()
{
}

TradeMgr::~TradeMgr()
{
}

void TradeMgr::flushCeil(const DWORD zoneID,const HelloKittyMsgData::PbSaleCeilFlushZone *meaasge)
{
    auto zoneIter = m_zoneSellInfoMap.find(zoneID);
    if(zoneIter == m_zoneSellInfoMap.end())
    {
        SellInfoMap tempMap;
        m_zoneSellInfoMap[zoneID] = tempMap;
    }

    SellInfoMap& sellInfoMap = m_zoneSellInfoMap[zoneID];
	auto iter = sellInfoMap.find(meaasge->charid());
	if(iter == sellInfoMap.end())
	{
		SellInfo info;
        sellInfoMap.insert(std::make_pair(meaasge->charid(),info));
	}
    SellInfo& info = sellInfoMap[meaasge->charid()];
    *(&info.saleCell) = meaasge->salecell();
    info.modifyTime = AZTimeTick::currentTime.sec();
}

void TradeMgr::randSallPaper(const QWORD charid,const DWORD randNum)
{
    DWORD num = 0;
    SellPaperMap sellPaperMap;
    for(auto zoneIter = m_zoneSellInfoMap.begin();zoneIter != m_zoneSellInfoMap.end() && num <= randNum;++zoneIter)
    {
        SellInfoMap &sellInfoMap = zoneIter->second;
        for(auto iter = sellInfoMap.begin();iter != sellInfoMap.end();++iter)
        {
            SellInfo &sellInfo = iter->second;
            if(sellInfo.charid == charid)
            {
                continue;
            }
            HelloKittyMsgData::SellPaperCell sellPaperCell;
            sellPaperCell.set_charid(sellInfo.charid);
            sellPaperCell.set_name(sellInfo.name);
            HelloKittyMsgData::PbSaleCell *paperCell = sellPaperCell.mutable_salecell();
            *paperCell = sellInfo.saleCell;
            sellPaperMap[sellInfo.charid] = sellPaperCell;
            ++num; 
        }
    }
    if(num < randNum)
    {
        Fir::logger->debug("寄售人数不够,生成寄售报纸信息太少(%lu,%u,%u)",charid,randNum,num);
    }
    m_sellPaperMap[charid] = sellPaperMap;
}

void TradeMgr::resetSellPaper(const DWORD zoneID,const DWORD charid)
{
    auto iter = m_sellPaperMap.find(charid);
    if(iter == m_sellPaperMap.end())
    {
        return;
    }

    SellPaperMap cellPaperMap = iter->second;
    cellPaperMap.clear();
    m_sellPaperMap.erase(iter);
}

void TradeMgr::flushCellPaper(const DWORD zoneID,const DWORD sceneID,const QWORD charid)
{
    //清除原来的
    resetSellPaper(zoneID,charid);
    //随机生成新的
    randSallPaper(charid,30);
    
    //刷新给scene
    auto iter = m_sellPaperMap.find(charid);
    if(iter == m_sellPaperMap.end())
    {
        randSallPaper(charid);
    }
    SellPaperMap &sellPaperMap = m_sellPaperMap[charid];
    HelloKittyMsgData::ReturnSellPaper sellPaperMessage;
    sellPaperMessage.set_createtime(AZTimeTick::currentTime.sec());
    
    for(auto cellIter = sellPaperMap.begin();cellIter != sellPaperMap.end();++cellIter)
    {
        HelloKittyMsgData::SellPaperCell *sellPaperCell = sellPaperMessage.add_papercell();
        *sellPaperCell = cellIter->second;
    }

    std::string ret;
    encodeMessage(&sellPaperMessage,ret);
    AllZoneService::getMe().sendCmdToScene(zoneID,sceneID,ret.c_str(),ret.size());
}

void TradeMgr::reqSomePlayersSaleCells(const DWORD zoneid,const DWORD sceneid,const  QWORD charid)
{
#if 0
	MsgAllRoleCell allrolecell;
	for(auto itr=m_mapSaleInfo.begin(); itr!=m_mapSaleInfo.end(); itr++)
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

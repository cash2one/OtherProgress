#include "UTrade.h"
#include "TradeCommand.h"
#include "tbx.h"
#include "SceneUser.h"
#include "AllZoneCommand.h"
#include "SceneServer.h"
#include "extractProtoMsg.h"
#include "TimeTick.h"

using namespace CMD;

UTrade::UTrade(SceneUser* u)
{
	m_owner = u;
    m_wait = false;
}

UTrade::~UTrade()
{

}

void UTrade::save(HelloKittyMsgData::Serialize& binary)
{
    HelloKittyMsgData::PbSaleBooth *saleBooth = binary.mutable_salebooth();
    *saleBooth = m_saleBooth;
}

void UTrade::load(const HelloKittyMsgData::Serialize& binary)
{
    m_saleBooth = binary.salebooth();
}

bool UTrade::initTradeInfo()
{
	for(DWORD i=0; i<m_owner->charbase.sale_grid_count; i++)
	{
        addSaleCell(i);
	}	
	
	return true;
}

bool UTrade::addSaleCell(const DWORD cellId)
{
    if(hasCell(cellId))
    {
        return false;
    }
    HelloKittyMsgData::PbSaleCell *saleCell = m_saleBooth.add_salecell();
    saleCell->set_cellid(cellId);
	return true;
}

bool UTrade::flushSaleCeilClient(const DWORD cellID)
{
    HelloKittyMsgData::PbSaleCeilFlush flush;
    HelloKittyMsgData::PbSaleCell *saleBooth = m_saleBooth.mutable_salecell(cellID);
    HelloKittyMsgData::PbSaleCell *cellInfo = flush.mutable_salecell();
    *cellInfo = *saleBooth;

    std::string ret;
    if(encodeMessage(&flush,ret))
    {
        return m_owner->sendCmdToMe(ret.c_str(),ret.size());  
    }
    return false;
}

bool UTrade::flushSaleCeilZone(const DWORD cellID)
{
    HelloKittyMsgData::PbSaleCeilFlushZone flush;
    flush.set_sceneid(SceneService::getMe().getServerID());
    flush.set_charid(m_owner->charid);
    HelloKittyMsgData::PbSaleCell *saleBooth = m_saleBooth.mutable_salecell(cellID);
    HelloKittyMsgData::PbSaleCell *cellInfo = flush.mutable_salecell();
    *cellInfo = *saleBooth;

    std::string ret;
    if(encodeMessage(&flush,ret))
    {
        return SceneService::getMe().sendCmdToAllZone(ret.c_str(),ret.size());
    }
    return false;
}


bool UTrade::flushSaleBooth()
{
    HelloKittyMsgData::FlushSaleBooth flush;
    HelloKittyMsgData::PbSaleBooth *saleBooth = flush.mutable_salebooth();
    *saleBooth = m_saleBooth;
    std::string ret;
    if(encodeMessage(&flush,ret))
    {
        return m_owner->sendCmdToMe(ret.c_str(),ret.size());
    }
    return false;
}

bool UTrade::hasCell(const DWORD cellid)
{
    return (DWORD)(m_saleBooth.salecell_size()) < cellid;
}

HelloKittyMsgData::PbSaleCell* UTrade::getCell(const DWORD cellid)
{
    if(hasCell(cellid))
    {
        return m_saleBooth.mutable_salecell(cellid);
    }
    return NULL;
}

bool UTrade::addSallItem(const HelloKittyMsgData::RequireSallPutItem *cmd)
{
    HelloKittyMsgData::SaleCellOpItemReturn message;
    message.set_ret(true);
    if(!(hasCell(cmd->cellid()) && m_owner->_store_house.hasEnoughItem(cmd->itemid(),cmd->itemcount())))
    {
        message.set_ret(false);
        message.set_reason(HelloKittyMsgData::Sale_Op_Item_Not_Enough);
    }
    
    //格子上有东西
    HelloKittyMsgData::PbSaleCell *cell = getCell(cmd->cellid());

    if(message.ret() && cell->status() != HelloKittyMsgData::Sale_Status_Empty)
    {
        if(cell->status() == HelloKittyMsgData::Sale_Status_Close)
        {
            message.set_reason(HelloKittyMsgData::Sale_Op_Close);
        }
        else
        {
            message.set_reason(HelloKittyMsgData::Sale_Op_Not_Empty);
        }
        message.set_ret(false);
    }

    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    if(!message.ret())
    {
        return true;
    }

    m_owner->_store_house.consumeItem(cmd->itemid(),cmd->itemcount());
	cell->set_status(HelloKittyMsgData::Sale_Status_For_Sale); // 放上物品
	cell->set_itemid(cmd->itemid());
	cell->set_itemcount(cmd->itemcount());
    cell->set_price(cmd->price());
    
    flushSaleCeilClient(cmd->cellid());
    if(m_saleBooth.zonecellid() == 10000)
    {
        flushSaleCeilZone(cmd->cellid());
    }
    return true;
}

void UTrade::flushZoneNextSaleCell()
{
    HelloKittyMsgData::PbSaleCell* cell = NULL;
    for(int index = 0;index < m_saleBooth.salecell_size();++index)
    {
        HelloKittyMsgData::PbSaleCell* cell = getCell(index);
        if(!cell || cell->status() == HelloKittyMsgData::Sale_Status_For_Sale)
        {
            break;
        }
    }
    if(cell && cell->status() == HelloKittyMsgData::Sale_Status_For_Sale)
    {
        if(flushSaleCeilZone(cell->cellid()))
        {
            m_saleBooth.set_zonecellid(cell->cellid());
        }
    }
    m_saleBooth.set_zonecellid(10000);
    return;
}

bool UTrade::offSallItem(const HelloKittyMsgData::RequireSallDownItem *cmd)
{
    HelloKittyMsgData::SaleCellOpItemReturn message;
    message.set_ret(true);
   
    if(!hasCell(cmd->cellid()))
    {
        return false;
    }
    
    HelloKittyMsgData::PbSaleCell *cell = getCell(cmd->cellid());
    if(cell->status() != HelloKittyMsgData::Sale_Status_For_Sale)
    {
        if(cell->status() == HelloKittyMsgData::Sale_Status_Close)
        {
            message.set_reason(HelloKittyMsgData::Sale_Op_Close);
        }
        else
        {
            message.set_reason(HelloKittyMsgData::Sale_Op_Empty);
        }
        message.set_ret(false);
    }
    
    //空间不够
    if(message.ret() && !m_owner->_store_house.hasEnoughSpace(cell->itemcount()))
    {
        message.set_ret(false);
        message.set_reason(HelloKittyMsgData::Sale_Op_Full);
    }

    
    //钻石不够
    if(message.ret() && m_owner->charbase.gem < 10)
    {
        message.set_reason(HelloKittyMsgData::Sale_Op_Money);
        message.set_ret(false);
    }
        
    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    if(!message.ret())
    {
        return true;
    }
    
    m_owner->charbase.gem -= 10;
    Fir::logger->debug("%s,%lu 下架商品消耗钻石 %u",m_owner->nickname,m_owner->charid,10);
    
    HelloKittyMsgData::PbStoreItem item;
    item.set_itemid(cell->itemid());
    item.set_itemcount(cell->itemcount());

    m_owner->_store_house.addItem(item);
    cell->set_status(HelloKittyMsgData::Sale_Status_Empty);
    cell->set_itemcount(0);
    cell->set_price(0);
    cell->set_itemid(0);
    
    flushSaleCeilClient(cmd->cellid());
    if(m_saleBooth.zonecellid() == cmd->cellid())
    {
        flushSaleCeilZone(cmd->cellid());
        flushZoneNextSaleCell();
    }
    return true;
}

bool UTrade::openCeil(const HelloKittyMsgData::RequireOpenCell *cmd)
{
    HelloKittyMsgData::SaleCellOpItemReturn message;
    message.set_ret(true);
   
    if(!hasCell(cmd->cellid())) 
    {
        return false;
    }
    
    HelloKittyMsgData::PbSaleCell *cell = getCell(cmd->cellid());
    if(cell->status() != HelloKittyMsgData::Sale_Status_Close)
    {
        message.set_reason(HelloKittyMsgData::Sale_Op_Open);
        message.set_ret(false);
    }
    
    //钻石不够
    if(message.ret() && m_owner->charbase.gem < 10)
    {
        message.set_reason(HelloKittyMsgData::Sale_Op_Money);
        message.set_ret(false);
    }
        
    std::string ret;
    encodeMessage(&message,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    if(!message.ret())
    {
        return true;
    }
    
    m_owner->charbase.gem -= 10;
    Fir::logger->debug("%s,%lu 扩充摊位消耗钻石 %u",m_owner->nickname,m_owner->charid,10);
    cell->set_status(HelloKittyMsgData::Sale_Status_Empty);
    cell->set_itemcount(0);
    cell->set_price(0);
    cell->set_itemid(0);

    flushSaleCeilClient(cmd->cellid());
    return true;
}

bool UTrade::returnSellPaper(const HelloKittyMsgData::ReturnSellPaper *cmd)
{
    *(&m_sellPaper) = *cmd;
#if 0
    for(int index = 0;index < cmd->papercell_size();++index)
    {
        HelloKittyMsgData::SellPaperCell *paperCell = m_sellPaper.papercell_size() ? m_sellPaper.mutable_papercell(index) : m_sellPaper.add_papercell();
        *paperCell = *(cmd->mutable_papercell(index));
    }
#endif
    m_sellPaper.set_createtime(cmd->createtime());
    m_owner->charbase.createSellPaperTime = cmd->createtime();
    
    m_wait = false;
    std::string ret;
    encodeMessage(cmd,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool UTrade::requireCellPaper(const HelloKittyMsgData::RequirSellPaper *cmd)
{
    DWORD tick = SceneTimeTick::currentTime.sec();
    if(tick <= m_owner->charbase.createSellPaperTime)
    {
        Fir::logger->error("错误:请求paper时间错误%lu,%u,%u",m_owner->charid,m_owner->charbase.createSellPaperTime,tick);
        return false;
    }
    if(m_wait)
    {
        Fir::logger->debug("提示:等待zone生成paper消息返回%lu,%u,%u",m_owner->charid,m_owner->charbase.createSellPaperTime,tick);
        return true;
    }
    
    //请求刷新
    if(tick - m_owner->charbase.createSellPaperTime >= 2*3600)
    {
        std::string ret;
        if(encodeMessage(cmd,ret))
        {
            if(SceneService::getMe().sendCmdToAllZone(ret.c_str(),ret.size()))
            {
                m_wait = true;
                return true;
            }
        }
    }

    std::string ret;
    encodeMessage(&m_sellPaper,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool UTrade::ret_someplayer_salecells(const std::vector<char>& vecBinary)
{
#if 0
	BYTE buf[zSocket::MAX_DATASIZE];
	stRetOtherPlayerSaleCells_SC *scmd=(stRetOtherPlayerSaleCells_SC *)buf;
	constructInPlace(scmd);

	scmd->datasize = vecBinary.size();
	bcopy(&vecBinary[0], scmd->data, scmd->datasize);
    
    std::string ret;
    encodeMessage(scmd,scmd->getSize(),ret);
	owner->sendCmdToMe(ret.c_str(),ret.size());	
#endif
	return true;
}

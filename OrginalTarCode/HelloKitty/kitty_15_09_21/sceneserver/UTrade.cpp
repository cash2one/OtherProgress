#include "UTrade.h"
#include "TradeCommand.h"
#include "tbx.h"
#include "SceneUser.h"
#include "SceneServer.h"
#include "extractProtoMsg.h"
#include "TimeTick.h"
#include "warehouse.pb.h"
#include "common.pb.h"
#include "RecordClient.h"
#include "SceneUserManager.h"
#include "SceneToOtherManager.h"

using namespace CMD;

UTrade::UTrade(SceneUser* u)
{
    m_owner = u;
    m_status = Trade_status_Normal;
    m_advertiseFlg = false;
}

UTrade::~UTrade()
{

}

void UTrade::save(HelloKittyMsgData::Serialize& binary)
{
    HelloKittyMsgData::PbSaleBooth *saleBooth = binary.mutable_salebooth();
    if(!saleBooth)
    {
        return;
    }

    //保存摊位信息 
    for(int index = 0;index < m_saleBooth.salecell_size();++index)
    {
        HelloKittyMsgData::PbSaleCell *sallCell = saleBooth->add_salecell();
        if(sallCell)
        {
            *sallCell = m_saleBooth.salecell(index);
        }
    }

    //保存报纸信息
    for(auto iter = m_sellPaper.begin();iter != m_sellPaper.end();++iter)
    {
        HelloKittyMsgData::SellPaper *sellPaper = binary.add_sellpaper();
        if(!sellPaper)
        {
            continue;
        }
        *sellPaper = iter->second;
    }
}

void UTrade::load(const HelloKittyMsgData::Serialize& binary)
{   
    const HelloKittyMsgData::PbSaleBooth &saleBooth = binary.salebooth();
    for(int index = 0;index < saleBooth.salecell_size();++index)
    {
        HelloKittyMsgData::PbSaleCell *sallCell = m_saleBooth.add_salecell();
        if(sallCell)
        {
            *sallCell = saleBooth.salecell(index);
        }
    }

    for(int index = 0;index < binary.sellpaper_size();++index)
    {
        const HelloKittyMsgData::SellPaper &temp = binary.sellpaper(index);
        if(m_sellPaper.find((BYTE)(temp.randtype())) != m_sellPaper.end())
        {
            continue;
        }
        m_sellPaper.insert(std::pair<BYTE,HelloKittyMsgData::SellPaper>((BYTE)(temp.randtype()),temp));
    }
}

void UTrade::reset()
{
    m_sellPaper.clear();
    m_saleBooth.Clear();
    m_status = Trade_status_Normal;
    flushSaleCeilZone(0,false);    
}

bool UTrade::initTradeInfo()
{
    DWORD gridNum = m_owner->m_store_house.getAttr(HelloKittyMsgData::Attr_Sall_Grid_Val);
    for(DWORD index = 1; index <= OPEN_CELL_NUM && index <= gridNum; index++)
    {
        addSaleCell(index);
    }	
    return true;
}

bool UTrade::addSaleCell(const DWORD cellId)
{
    if(cellId > m_owner->m_store_house.getAttr(HelloKittyMsgData::Attr_Sall_Grid_Val))
    {
        return false;
    }
    HelloKittyMsgData::PbSaleCell *saleCell = m_saleBooth.add_salecell();
    saleCell->set_cellid(cellId);
    saleCell->set_status(HelloKittyMsgData::Sale_Status_Empty);
    saleCell->set_itemcount(0);
    saleCell->set_itemid(0);
    saleCell->set_price(0);
    saleCell->set_nickname("");
    saleCell->set_advertise(false);
    return true;
}

bool UTrade::flushSaleCeilClient(const DWORD cellID)
{
    if(!hasCell(cellID))
    {
        return false;
    }

    HelloKittyMsgData::AckPbSaleCeilFlush flush;
    flush.set_charid(m_owner->charid);
    HelloKittyMsgData::PbSaleCell *saleBooth = getCell(cellID);
    HelloKittyMsgData::PbSaleCell *cellInfo = flush.mutable_salecell();
    if(saleBooth && cellInfo)
    {
        *cellInfo = *saleBooth;
    }

    std::string ret;
    encodeMessage(&flush,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    //同步到所有进入自己乐园的其他人
    m_owner->sendOtherUserMsg(ret.c_str(),ret.size());
    return true;
}

bool UTrade::flushSaleCeilZone(const DWORD cellID,const bool addFlg)
{
    if(!hasCell(cellID))
    {
        return false;
    }

    char buffer[zSocket::MAX_DATASIZE] = {0};
    CMD::RECORD::t_AdvertiseUser_SceneRecord *advertiseCmd = (CMD::RECORD::t_AdvertiseUser_SceneRecord*)(buffer);
    constructInPlace(advertiseCmd);

    advertiseCmd->charid = m_owner->charid;
    advertiseCmd->addFlg = addFlg;
    if(advertiseCmd->addFlg)
    {
        HelloKittyMsgData::PbSaleCell *saleBooth = getCell(cellID);
        saleBooth->SerializeToArray(advertiseCmd->data,zSocket::MAX_DATASIZE);
        advertiseCmd->datasize = saleBooth->ByteSize();
    }

    std::string ret;
    encodeMessage(advertiseCmd,sizeof(CMD::RECORD::t_AdvertiseUser_SceneRecord) + advertiseCmd->datasize,ret);
    RecordClient* recordClient =  MgrrecordClient.GetRecordByTableName("t_recordbinary");
    if(recordClient)
        recordClient->sendCmd(ret.c_str(),ret.size());
    Fir::logger->debug("[广告位操作]: %s,%s,%lu,%u",addFlg ? "打广告" : "撤销广告",m_owner->nickname,m_owner->charid,cellID);
    m_advertiseFlg = advertiseCmd->addFlg;
    return true;
}


bool UTrade::flushSaleBooth()
{
    HelloKittyMsgData::AckFlushSaleBooth flush;
    flush.set_charid(m_owner->charid);
    flushSaleBooth(flush);
    std::string ret;
    encodeMessage(&flush,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

void UTrade::flushSaleBooth(HelloKittyMsgData::AckFlushSaleBooth &flush)
{
    HelloKittyMsgData::PbSaleBooth *saleBooth = flush.mutable_salebooth();
    *saleBooth = m_saleBooth;
}

bool UTrade::hasCell(const DWORD cellid)
{
    return cellid > 0 && m_owner->m_store_house.getAttr(HelloKittyMsgData::Attr_Sall_Grid_Val) >= cellid && DWORD(m_saleBooth.salecell_size()) >= cellid;
}

HelloKittyMsgData::PbSaleCell* UTrade::getCell(const DWORD cellid)
{
    if(hasCell(cellid))
    {
        return m_saleBooth.mutable_salecell(cellid-1);
    }
    return NULL;
}

bool UTrade::addSallItem(const HelloKittyMsgData::ReqSallPutItem *cmd)
{
    if(!hasCell(cmd->cellid()))
    {
        return false;
    }

    //格子上有东西
    HelloKittyMsgData::PbSaleCell *cell = getCell(cmd->cellid());
    if(cell->status() != HelloKittyMsgData::Sale_Status_Empty)
    {
        if(cell->status() == HelloKittyMsgData::Sale_Status_Close)
        {
            opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Op_Close);
        }
        else
        {
            opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Op_Not_Empty);
        }
        return false;
    }
    if(cmd->advertise() && m_advertiseFlg)
    {
        opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Advertise_Again);
        return false;
    }

    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"摆摊(%u)",cmd->cellid());
    if(!m_owner->m_store_house.addOrConsumeItem(cmd->itemid(),cmd->itemcount(),temp,false))
    {
        opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Op_Item_Not_Enough);
        return false;
    }
    cell->set_status(HelloKittyMsgData::Sale_Status_For_Sale); // 放上物品
    cell->set_itemid(cmd->itemid());
    cell->set_itemcount(cmd->itemcount());
    cell->set_price(cmd->price());
    if(cmd->advertise())
    {
        cell->set_advertise(true);
        flushSaleCeilZone(cmd->cellid());
    }
    flushSaleCeilClient(cmd->cellid());
    return true;
}

bool UTrade::advertise(const HelloKittyMsgData::ReqAdvertise *cmd)
{
    if(!(hasCell(cmd->cellid())))
    {
        return false;
    }

    //格子上有东西
    HelloKittyMsgData::PbSaleCell *cell = getCell(cmd->cellid());
    if(cell->status() != HelloKittyMsgData::Sale_Status_For_Sale)
    {
        if(cell->status() == HelloKittyMsgData::Sale_Status_Close)
        {
            opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Op_Close);
        }
        else
        {
            opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Op_Empty);
        }
        return false;
    }

    if(m_advertiseFlg || cell->advertise())
    {
        opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Advertise_Again);
        return false;
    }
    cell->set_advertise(true); 
    flushSaleCeilZone(cmd->cellid());
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
        flushSaleCeilZone(cell->cellid());
    }
    return;
}

bool UTrade::offSallItem(const DWORD cellID)
{
    if(!hasCell(cellID))
    {
        return false;
    }
    HelloKittyMsgData::PbSaleCell *cell = getCell(cellID);
    if(cell->status() != HelloKittyMsgData::Sale_Status_For_Sale)
    {
        if(cell->status() == HelloKittyMsgData::Sale_Status_Close)
        {
            opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Op_Close);
        }
        else
        {
            opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Op_Empty);
        }
        return false;
    }

    //空间不够
    if(!m_owner->m_store_house.hasEnoughSpace(cell->itemid(),cell->itemcount()))
    {
        opFailReturn(HelloKittyMsgData::Error_Common_Occupy,HelloKittyMsgData::Trade_Op_Full);
        return false;
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"下架商品消耗钻石 %u",cellID);
    if(!m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,DWON_GOOD_PAY,temp,false))
    {
        return opFailReturn(HelloKittyMsgData::Gem_Not_Enough);
    }
    bzero(temp,sizeof(temp));
    snprintf(temp,sizeof(temp),"下架商品(%u)",cellID);

    itemLock.wrlock();
    m_owner->m_store_house.addOrConsumeItem(cell->itemid(),cell->itemcount(),temp,true);
    cell->set_status(HelloKittyMsgData::Sale_Status_Empty);
    cell->set_itemcount(0);
    cell->set_price(0);
    cell->set_itemid(0);
    itemLock.unlock();

    if(cell->advertise())
    {
        flushSaleCeilZone(cellID,false);
        m_advertiseFlg = false;
    }
    cell->set_advertise(false);
    flushSaleCeilClient(cellID);
    return true;
}

bool UTrade::openCeil()
{
    DWORD cellID = m_saleBooth.salecell_size() + 1;
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"扩充摊位 %u",cellID);
    if(!m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,PURCHASE_SALL_CELL,temp,false))
    {
        return opFailReturn(HelloKittyMsgData::Gem_Not_Enough);
    }
    addSaleCell(cellID);
    flushSaleCeilClient(cellID);
    return true;
}

bool UTrade::returnSellPaper(const HelloKittyMsgData::SellPaper *cmd)
{
    auto iter = m_sellPaper.find((BYTE)(cmd->randtype()));
    if(iter == m_sellPaper.end())
    {
        m_sellPaper.insert(std::pair<BYTE,HelloKittyMsgData::SellPaper>((BYTE)(cmd->randtype()),*cmd));
    }
    else
    {
        HelloKittyMsgData::SellPaper &temp = const_cast<HelloKittyMsgData::SellPaper&>(iter->second);
        temp.Clear();
        temp = *cmd;
    }
    m_status ^= Trade_status_Wait_Paper; 
    HelloKittyMsgData::AckSellPaper ackSellPaper;
    HelloKittyMsgData::SellPaper *sellPaper = ackSellPaper.mutable_sellpaper();
    *sellPaper = *cmd;


    std::string ret;
    encodeMessage(&ackSellPaper,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool UTrade::requireCellPaper(const BYTE randType)
{
    //请求刷新
    CMD::RECORD::t_RequirePaperUser_SceneRecord requirePaper;
    requirePaper.charid = m_owner->charid;
    requirePaper.randType = randType > 0 ? CMD::RECORD::RAND_Friend : CMD::RECORD::RAND_PASSER_BY;

    std::string ret;
    encodeMessage(&requirePaper,sizeof(CMD::RECORD::t_RequirePaperUser_SceneRecord),ret);
    RecordClient* recordClient =  MgrrecordClient.GetRecordByTableName("t_recordbinary");
    if(recordClient)
        recordClient->sendCmd(ret.c_str(),ret.size());
    m_status |= Trade_status_Wait_Paper;
    return true;
}

bool UTrade::requireCellPaper(const HelloKittyMsgData::ReqSellPaper *cmd)
{
    if(cmd->randtype() > HelloKittyMsgData::Rand_Friend || cmd->randtype() < HelloKittyMsgData::Rand_Passer_By)
    {
        return false;
    }
    if(m_status & Trade_status_Wait_Paper)
    {
        Fir::logger->debug("[报纸请求等待]:等待zone生成paper消息返回%lu",m_owner->charid);
        return true;
    }
    auto iter = m_sellPaper.find((BYTE)(cmd->randtype()));
    if(iter != m_sellPaper.end())
    {
        HelloKittyMsgData::SellPaper &temp = const_cast<HelloKittyMsgData::SellPaper&>(iter->second);
        DWORD tick = SceneTimeTick::currentTime.sec();
        if(tick <= temp.createtime())
        {
            Fir::logger->error("[报纸请求时间错误]:%lu,%u,%u",m_owner->charid,temp.createtime(),tick);
            return false;
        }
        if(tick - temp.createtime() < RAND_PAPER_CD)
        {
            HelloKittyMsgData::AckSellPaper ackPaper;
            HelloKittyMsgData::SellPaper *ackTemp = ackPaper.mutable_sellpaper();
            *ackTemp = temp;

            std::string ret;
            encodeMessage(&ackPaper,ret);
            m_owner->sendCmdToMe(ret.c_str(),ret.size());
            return true;
        }
    }

    //请求刷新
    CMD::RECORD::t_RequirePaperUser_SceneRecord requirePaper;
    requirePaper.charid = m_owner->charid;
    requirePaper.randType = (BYTE)cmd->randtype();
    std::string ret;
    encodeMessage(&requirePaper,sizeof(CMD::RECORD::t_RequirePaperUser_SceneRecord),ret);
    RecordClient* recordClient =  MgrrecordClient.GetRecordByTableName("t_recordbinary");
    if(recordClient)
        recordClient->sendCmd(ret.c_str(),ret.size());
    m_status |= Trade_status_Wait_Paper;
    return true;
}

bool UTrade::ret_someplayer_salecells(const std::vector<char>& vecBinary)
{
    return true;
}

bool UTrade::opFailReturn(const HelloKittyMsgData::ErrorCodeType &commonError,const HelloKittyMsgData::TradeFailCodeType &code)
{
    HelloKittyMsgData::AckTradeOpFail fail;
    fail.set_code(code);
    fail.set_commoncode(commonError);

    std::string ret;
    encodeMessage(&fail,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size()); 
    return true;
}
void UTrade::purchaseItemLock(const CMD::SCENE::t_UserPurchaseLockItem *cmd)
{
    const HelloKittyMsgData::PbSaleCell* cellTemp = getCell(cmd->cellID);
    if(!cellTemp || cellTemp->status() != HelloKittyMsgData::Sale_Status_For_Sale)
    {
        return;
    }
    CMD::SCENE::t_UserPurchasePrice itemPrice;
    itemPrice.reqcharid = cmd->reqcharid;
    itemPrice.ackcharid = cmd->ackcharid;
    itemPrice.price = cellTemp->price();
    itemPrice.item = cellTemp->itemid();
    itemPrice.num = cellTemp->itemcount();
    itemPrice.item = cellTemp->itemid();
    itemPrice.cellID = cmd->cellID; 
    std::string ret;
    encodeMessage(&itemPrice,sizeof(itemPrice),ret);
    SceneUser* user = SceneUserManager::getMe().getUserByID(cmd->reqcharid);
    if(user)
    {
        itemLock.wrlock();
        user->deductPrice(&itemPrice);
    }
    else
    {
        if(SceneClientToOtherManager::getMe().SendMsgToOtherSceneCharID(cmd->reqcharid,&itemPrice,sizeof(itemPrice)))
        {
            itemLock.wrlock();
        }
    }
    return;
}

void UTrade::purchaseUnLockItem(const CMD::SCENE::t_UserPurchaseUnlockeItem *cmd)
{
    HelloKittyMsgData::PbSaleCell* cellTemp = getCell(cmd->cellID);
    if(!cellTemp || !cmd->deductFlg)
    {
        itemLock.unlock();
        return;
    }

    CMD::SCENE::t_UserPurchaseShiftItem shiftItem; 
    shiftItem.reqcharid = cmd->reqcharid;
    shiftItem.itemID = cellTemp->itemid();
    shiftItem.itemNum = cellTemp->itemcount();

    cellTemp->set_status(HelloKittyMsgData::Sale_Status_Sale_End);
    cellTemp->set_nickname(cmd->name);
    flushSaleCeilClient(cmd->cellID);

    //如果打了广告，则删掉
    if(cellTemp->advertise())
    {
        flushSaleCeilZone(false);
        m_advertiseFlg = false;
    }
    itemLock.unlock();
    SceneUser* sceneUser = SceneUserManager::getMe().getUserByID(cmd->reqcharid);
    if(sceneUser)
    {
        sceneUser->purchaseAddItem(&shiftItem);
    }
    else
    {
        SceneClientToOtherManager::getMe().SendMsgToOtherSceneCharID(cmd->reqcharid,&shiftItem,sizeof(shiftItem));
    }
}

bool UTrade::reqGetCellMoney(const DWORD cellID)
{
    HelloKittyMsgData::PbSaleCell* cellTemp = getCell(cellID);
    if(!cellTemp || cellTemp->status() != HelloKittyMsgData::Sale_Status_Sale_End)
    {
        return false;
    }
    m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gold,cellTemp->price(),"出售道具",true);

    cellTemp->set_status(HelloKittyMsgData::Sale_Status_Empty);
    cellTemp->set_nickname("");
    cellTemp->set_price(0);
    cellTemp->set_itemid(0);
    cellTemp->set_itemcount(0);
    flushSaleCeilClient(cellID);
    return true;
}


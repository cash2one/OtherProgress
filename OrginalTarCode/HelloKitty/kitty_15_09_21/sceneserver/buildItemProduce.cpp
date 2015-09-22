#include "buildItemProduce.h"
#include "SceneUser.h"
#include "TimeTick.h"
#include "dataManager.h"
#include "tbx.h"

BuildTypeProduceItem::BuildTypeProduceItem(SceneUser* owner,const DWORD typeID,const DWORD level,const Point &point,const bool active) : BuildBase(owner,typeID,level,point,active)
{
}

BuildTypeProduceItem::BuildTypeProduceItem(SceneUser* owner,const pb::Conf_t_building *buildConf,const Point &point) : BuildBase(owner,buildConf,point)
{
}

BuildTypeProduceItem::BuildTypeProduceItem(SceneUser* owner,const HelloKittyMsgData::BuildBase &buildBase) : BuildBase(owner,buildBase)
{
}

bool BuildTypeProduceItem::init()
{
    for(DWORD index = 1;index <= OPEN_PRODUCE_NUM;++index)
    {
        HelloKittyMsgData::FunctionCell temp;
        temp.set_placeid(index);
        temp.set_produceid(0);
        temp.set_worktime(0);
        temp.set_lasttime(0);
        temp.set_status(HelloKittyMsgData::Place_Status_Empty);
        m_produceMap.insert(std::pair<DWORD,HelloKittyMsgData::FunctionCell>(temp.placeid(),temp));
    }
    return true;
}

bool BuildTypeProduceItem::load(const HelloKittyMsgData::StoreFunctionCell& binary)
{
    for(int index = 0;index < binary.functioncell_size();++index)
    {
        const HelloKittyMsgData::FunctionCell &temp = binary.functioncell(index); 
        m_produceMap.insert(std::pair<DWORD,HelloKittyMsgData::FunctionCell>(temp.placeid(),temp));
    }
    return true;
}

bool BuildTypeProduceItem::saveProduce(HelloKittyMsgData::Serialize& binary)
{
    HelloKittyMsgData::StoreFunctionCell *funcCell = binary.add_functioncell();
    if(!funcCell)
    {
        return false;
    }
    funcCell->set_tempid(m_id);
    funcCell->set_type(HelloKittyMsgData::Function_Type_Produce);
    for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
    {
        HelloKittyMsgData::FunctionCell *temp = funcCell->add_functioncell();
        if(temp)
        {
            *temp = iter->second;
        }
    }
    return true;
}

bool BuildTypeProduceItem::updateFuncType(const DWORD updateID)
{
    HelloKittyMsgData::AckFunctionCell ackMessage;
    ackMessage.set_tempid(m_id);
    ackMessage.set_type(HelloKittyMsgData::Function_Type_Produce);
    if(!updateID)
    {
        for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
        {
            HelloKittyMsgData::FunctionCell *temp = ackMessage.add_functioncell();
            if(temp)
            {
                *temp = iter->second;
            }
        }
    }
    else
    {
        HelloKittyMsgData::FunctionCell* cell = getFunctionCell(updateID);
        if(cell)
        {
            HelloKittyMsgData::FunctionCell *temp = ackMessage.add_functioncell();
            if(temp)
            {
                *temp = *cell;
            }
        }
    }

    std::string ret;
    encodeMessage(&ackMessage,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

HelloKittyMsgData::FunctionCell* BuildTypeProduceItem::getFunctionCell(const DWORD cellID)
{
    auto iter = m_produceMap.find(cellID);
    if(iter == m_produceMap.end())
    {
        return NULL;
    }
    return const_cast<HelloKittyMsgData::FunctionCell*>(&(iter->second));
}

bool BuildTypeProduceItem::workProduce(const DWORD cellID,const DWORD produceid)
{
    HelloKittyMsgData::FunctionCell* temp = getFunctionCell(cellID);
    if(!temp)
    {
        return false;
    }
    if(temp->status() == HelloKittyMsgData::Place_Status_Close)
    {
        return opBTPFailReturn(cellID,HelloKittyMsgData::BTP_Close);
    }
    if(temp->status() != HelloKittyMsgData::Place_Status_Empty)
    {
        return opBTPFailReturn(cellID,HelloKittyMsgData::BTP_Busy);
    }
    const pb::Conf_t_produceItem *base = tbx::produceItem().get_base(produceid);
    if(!base)
    {
        return opBTPFailReturn(cellID,HelloKittyMsgData::BTP_Not_Produce_Item);
    }
    if(!(base->produceItem->buildid() == m_typeID && m_level >= base->produceItem->level()))
    {
        return opBTPFailReturn(cellID,HelloKittyMsgData::BTP_Not_Produce_Item);
    }
    temp->set_produceid(produceid);
    temp->set_worktime(SceneTimeTick::currentTime.sec());
    temp->set_lasttime(base->produceItem->usetime());
    temp->set_status(HelloKittyMsgData::Place_Status_Work);
    return updateFuncType(cellID);
}

bool BuildTypeProduceItem::opBTPFailReturn(const DWORD cellID,const HelloKittyMsgData::BTPOpFailType &value,const HelloKittyMsgData::ErrorCodeType &commonError)
{
    HelloKittyMsgData::AckBTPOpReturnFail ackMessage;
    ackMessage.set_tempid(m_id);
    ackMessage.set_type(HelloKittyMsgData::Function_Type_Produce);
    ackMessage.set_placeid(cellID);
    ackMessage.set_commoncode(commonError);
    ackMessage.set_code(value);

    std::string ret;
    encodeMessage(&ackMessage,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

bool BuildTypeProduceItem::purchaseCell()
{
    DWORD num = m_produceMap.size();
    if(num >= MAX_PRODUCE_NUM)
    {
        return opBTPFailReturn(0,HelloKittyMsgData::BTP_Is_Max);
    }
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"购买生产格子(%lu,%u,%u,%u)",m_id,m_typeID,m_level,num+1);
    if(!m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,PURCHASE_CELL_PRICE,temp,false))
    {
        return m_owner->opErrorReturn(HelloKittyMsgData::Gem_Not_Enough);
    }
    HelloKittyMsgData::FunctionCell tempInst;
    tempInst.set_placeid(++num);
    tempInst.set_produceid(0);
    tempInst.set_worktime(0);
    tempInst.set_lasttime(0);
    tempInst.set_status(HelloKittyMsgData::Place_Status_Empty);
    m_produceMap.insert(std::pair<DWORD,HelloKittyMsgData::FunctionCell>(tempInst.placeid(),tempInst));
    return updateFuncType(tempInst.placeid());
}

bool BuildTypeProduceItem::purchaseCd(const DWORD cellID)
{
    HelloKittyMsgData::FunctionCell *temp = getFunctionCell(cellID);
    if(!temp)
    {
        return false;
    }
    if(temp->status() != HelloKittyMsgData::Place_Status_Work)
    {
        return opBTPFailReturn(cellID,HelloKittyMsgData::BTP_Is_Not_Busy);
    }
    const pb::Conf_t_produceItem *base = tbx::produceItem().get_base(temp->produceid());
    if(!base)
    {
        Fir::logger->debug("[生产道具] 生产配置错误(%lu,%u,%u,%u,%u)",m_id,m_typeID,m_level,cellID,temp->produceid());
        return false;
    }

    char reMark[100] = {0};
    snprintf(reMark,sizeof(reMark),"购买cd生产道具格子(%lu,%u,%u,%u)",m_id,m_typeID,m_level,cellID);
    DWORD gem = base->produceItem->clear();
    if(!m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,gem,reMark,false))
    {
        return m_owner->opErrorReturn(HelloKittyMsgData::Gem_Not_Enough);
    }
    temp->set_status(HelloKittyMsgData::Place_Status_Wait);
    return updateFuncType(cellID);
}

bool BuildTypeProduceItem::getItem(const DWORD cellID)
{
    HelloKittyMsgData::FunctionCell *temp = getFunctionCell(cellID);
    if(!temp)
    {
        return false;
    }
    if(temp->status() != HelloKittyMsgData::Place_Status_Wait)
    {
        return opBTPFailReturn(cellID,HelloKittyMsgData::BTP_Is_Not_Wait);
    }
    const pb::Conf_t_produceItem *base = tbx::produceItem().get_base(temp->produceid());
    if(!base)
    {
        return false;
    }
    
    char reMark[100] = {0};
    snprintf(reMark,sizeof(reMark),"生产道具 (%lu,%u,%u,%u,%u)",m_id,m_typeID,m_level,cellID,temp->produceid());
    if(!m_owner->m_store_house.addOrConsumeItem(base->produceItem->itemid(),1,reMark,true))
    {
        return m_owner->opErrorReturn(HelloKittyMsgData::WareHouse_Is_Full);
    }
    temp->set_status(HelloKittyMsgData::Place_Status_Empty);
    return updateFuncType(cellID);
}

bool BuildTypeProduceItem::OpBTPType(const HelloKittyMsgData::BTPOpType &opType,const DWORD placeID)
{
    switch(opType)
    {
        case HelloKittyMsgData::BTP_Op_Purchase:
            {
                return purchaseCell();
            }
            break;
        case HelloKittyMsgData::BTP_Op_Purchase_Cd:
            {
                return purchaseCd(placeID);
            }
            break;
        case HelloKittyMsgData::BTP_Op_Get_Item:
            {
                return getItem(placeID);
            }
            break;
        default:
            {
                break;
            }
    }
    return false;
}

bool BuildTypeProduceItem::checkCd()
{
    for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
    {
        HelloKittyMsgData::FunctionCell *temp = const_cast<HelloKittyMsgData::FunctionCell*>(&(iter->second));
        if(temp->status() != HelloKittyMsgData::Place_Status_Work)
        {
            continue;
        }
        const pb::Conf_t_produceItem *base = tbx::produceItem().get_base(temp->produceid());
        if(!base)
        {
            continue;
        }
        temp->set_lasttime(temp->lasttime() - 1);
        if(!temp->lasttime())
        {
            temp->set_status(HelloKittyMsgData::Place_Status_Wait);
            updateFuncType(iter->first);
        }
    }
    return true;
}

bool BuildTypeProduceItem::loop()
{
    checkCd();
    return true;
}

bool BuildTypeProduceItem::fullUserInfo(HelloKittyMsgData::UserBaseInfo& binary)
{
    HelloKittyMsgData::StoreFunctionCell *funcCell = binary.add_produceitem();
    if(!funcCell)
    {
        return false;
    }
    funcCell->set_tempid(m_id);
    funcCell->set_type(HelloKittyMsgData::Function_Type_Produce);
    for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
    {
        HelloKittyMsgData::FunctionCell *temp = funcCell->add_functioncell();
        if(temp)
        {
            *temp = iter->second;
        }
    }
    return true;
}

bool BuildTypeProduceItem::sendInfoMeg()
{
    HelloKittyMsgData::AckProduceItem ackMessage;
    HelloKittyMsgData::StoreFunctionCell *funcCell = ackMessage.mutable_produceitem();
    if(!funcCell)
    {
        return false;
    }
    funcCell->set_tempid(m_id);
    funcCell->set_type(HelloKittyMsgData::Function_Type_Produce);
    for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
    {
        HelloKittyMsgData::FunctionCell *temp = funcCell->add_functioncell();
        if(temp)
        {
            *temp = iter->second;
        }
    }
    std::string ret;
    encodeMessage(&ackMessage,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

void BuildTypeProduceItem::beginActive()
{
    BuildBase::beginActive();
    DWORD nowTime = SceneTimeTick::currentTime.sec();
    for(auto iter = m_produceMap.begin();iter != m_produceMap.end();++iter)
    {
        HelloKittyMsgData::FunctionCell* temp = getFunctionCell(iter->first);
        if(!temp)
        {
            continue;
        }
        if(temp->status() == HelloKittyMsgData::Place_Status_Work)
        {
            temp->set_worktime(nowTime);
            updateFuncType(iter->first);
        }
    }
}


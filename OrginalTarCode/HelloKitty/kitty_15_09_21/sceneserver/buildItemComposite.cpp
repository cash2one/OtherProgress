#include "buildItemComposite.h"
#include "SceneUser.h"
#include "TimeTick.h"
#include "dataManager.h"
#include "tbx.h"
#include "buildItemProduce.h"

BuildTypeCompositeItem::BuildTypeCompositeItem(SceneUser* owner,const DWORD typeID,const DWORD level,const Point &point,const bool active) : BuildBase(owner,typeID,level,point,active)
{
}

BuildTypeCompositeItem::BuildTypeCompositeItem(SceneUser* owner,const pb::Conf_t_building *buildConf,const Point &point) : BuildBase(owner,buildConf,point)
{
}

BuildTypeCompositeItem::BuildTypeCompositeItem(SceneUser* owner,const HelloKittyMsgData::BuildBase &buildBase) : BuildBase(owner,buildBase)
{
}

bool BuildTypeCompositeItem::init()
{
    for(DWORD index = 1;index < OPEN_COMPOSITE_NUM;++index)
    {
        HelloKittyMsgData::FunctionCell temp;
        temp.set_placeid(index);
        temp.set_produceid(0);
        temp.set_worktime(0);
        temp.set_lasttime(0);
        temp.set_status(HelloKittyMsgData::Place_Status_Empty);
        m_compositeList.push_back(temp);
    }
    return true;
}

bool BuildTypeCompositeItem::load(const HelloKittyMsgData::StoreFunctionCell& binary)
{
    for(int index = 0;index < binary.functioncell_size();++index)
    {
        const HelloKittyMsgData::FunctionCell &temp = binary.functioncell(index); 
        m_compositeList.push_back(temp);
    }
    return true;
}

bool BuildTypeCompositeItem::saveProduce(HelloKittyMsgData::Serialize& binary)
{
    HelloKittyMsgData::StoreFunctionCell *funcCell = binary.add_functioncell();
    if(!funcCell)
    {
        return false;
    }
    funcCell->set_tempid(m_id);
    funcCell->set_type(HelloKittyMsgData::Function_Type_Composite);
    for(auto iter = m_compositeList.begin();iter != m_compositeList.end();++iter)
    {
        HelloKittyMsgData::FunctionCell *temp = funcCell->add_functioncell();
        if(temp)
        {
            *temp = *iter;
        }
    }
    return true;
}

HelloKittyMsgData::FunctionCell* BuildTypeCompositeItem::findStatusCell(const HelloKittyMsgData::PlaceStatusType &status)
{
    HelloKittyMsgData::FunctionCell *ret = NULL;
    for(auto iter = m_compositeList.begin();iter != m_compositeList.end();++iter)
    {
        if((*iter).status() == status)
        {
            ret = const_cast<HelloKittyMsgData::FunctionCell*>(&(*iter));
            break;
        }
    }
    return ret;
}

HelloKittyMsgData::FunctionCell* BuildTypeCompositeItem::findIDCell(const DWORD placeID)
{
    HelloKittyMsgData::FunctionCell *ret = NULL;
    for(auto iter = m_compositeList.begin();iter != m_compositeList.end();++iter)
    {
        if((*iter).placeid() == placeID)
        {
            ret = const_cast<HelloKittyMsgData::FunctionCell*>(&(*iter));
            break;
        }
    }
    return ret;
}

void BuildTypeCompositeItem::eraseIDCell(const DWORD placeID)
{
    for(auto iter = m_compositeList.begin();iter != m_compositeList.end();++iter)
    {
        if((*iter).placeid() == placeID)
        {
            m_compositeList.erase(iter);
        }
    }
}

void BuildTypeCompositeItem::update(const DWORD cellID)
{
    HelloKittyMsgData::FunctionCell *temp = findIDCell(cellID);
    update(temp);
}

void BuildTypeCompositeItem::update(const HelloKittyMsgData::FunctionCell *cell)
{
    HelloKittyMsgData::AckFunctionCell ackMessage;
    ackMessage.set_tempid(m_id);
    ackMessage.set_type(HelloKittyMsgData::Function_Type_Composite);
    if(cell)
    {
        HelloKittyMsgData::FunctionCell *temp = ackMessage.add_functioncell();
        if(temp)
        {
            *temp = *cell;
        }
    }
    else
    {
        for(auto iter = m_compositeList.begin();iter != m_compositeList.end();++iter)
        {
            HelloKittyMsgData::FunctionCell *temp = ackMessage.add_functioncell();
            if(temp)
            {
                *temp = *iter;
            }
        }
    }
    std::string ret;
    encodeMessage(&ackMessage,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

bool BuildTypeCompositeItem::work()
{
    HelloKittyMsgData::FunctionCell *emptyCell = findStatusCell(HelloKittyMsgData::Place_Status_Work);
    if(emptyCell)
    {
        return true;
    }

    emptyCell = findStatusCell(HelloKittyMsgData::Place_Status_Suppend);
    if(!emptyCell || !emptyCell->produceid())
    {
        return true;
    }
    
    emptyCell->set_worktime(SceneTimeTick::currentTime.sec());
    emptyCell->set_status(HelloKittyMsgData::Place_Status_Work);
    update(emptyCell);
    return true;
}

bool BuildTypeCompositeItem::workComposite(const DWORD produceid)
{
    HelloKittyMsgData::FunctionCell *emptyCell = findStatusCell(HelloKittyMsgData::Place_Status_Empty);
    if(!emptyCell)
    {
        return opBTPFailReturn(0,HelloKittyMsgData::BTP_Busy);
    }
    const pb::Conf_t_produceItem *base = tbx::produceItem().get_base(produceid);
    if(!base)
    {
        return opBTPFailReturn(emptyCell->placeid(),HelloKittyMsgData::BTP_Not_Produce_Item);
    }
    if(!(base->produceItem->buildid() == m_typeID && m_level >= base->produceItem->level()))
    {
        return opBTPFailReturn(emptyCell->placeid(),HelloKittyMsgData::BTP_Not_Produce_Item);
    }
    char reMark[100] = {0};
    snprintf(reMark,sizeof(reMark),"合成道具扣除(%lu,%u,%u,%u,%u)",m_id,m_typeID,m_level,emptyCell->placeid(),produceid);
    if(!m_owner->checkMaterialMap(base->getMaterialMap()) || !m_owner->reduceMaterialMap(base->getMaterialMap(),reMark))
    {
        return opBTPFailReturn(emptyCell->placeid(),HelloKittyMsgData::BTP_Occcupy,HelloKittyMsgData::Material_Not_Enough);
    }
    emptyCell->set_produceid(produceid);
    emptyCell->set_lasttime(base->produceItem->usetime());
    emptyCell->set_status(HelloKittyMsgData::Place_Status_Suppend);
    update(emptyCell);
    work();
    return true;
}   
    
bool BuildTypeCompositeItem::opBTPFailReturn(const DWORD cellID,const HelloKittyMsgData::BTPOpFailType &value,const HelloKittyMsgData::ErrorCodeType &commonError)
{
    HelloKittyMsgData::AckBTPOpReturnFail ackMessage;
    ackMessage.set_tempid(m_id);
    ackMessage.set_type(HelloKittyMsgData::Function_Type_Composite);
    ackMessage.set_placeid(cellID);
    ackMessage.set_commoncode(commonError);
    ackMessage.set_code(value);

    std::string ret;
    encodeMessage(&ackMessage,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

bool BuildTypeCompositeItem::purchaseCell()
{
    DWORD num = m_compositeList.size();
    if(num >= MAX_COMPOSITE_NUM)
    {
        return opBTPFailReturn(0,HelloKittyMsgData::BTP_Is_Max);
    }    
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"购买合成格子(%lu,%u,%u,%u)",m_id,m_typeID,m_level,num+1);
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
    m_compositeList.push_back(tempInst);
    update(&tempInst);
    return true;
}

bool BuildTypeCompositeItem::purchaseCd()
{
    HelloKittyMsgData::FunctionCell *workCell = findStatusCell(HelloKittyMsgData::Place_Status_Work);
    if(!workCell)
    {
        return opBTPFailReturn(0,HelloKittyMsgData::BTP_Is_Not_Busy);
    }
    const pb::Conf_t_produceItem *base = tbx::produceItem().get_base(workCell->produceid());
    if(!base)
    {
        Fir::logger->debug("[道具合成] 找不到合成配置表(%lu,%s,%lu,%u,%u,%u)",m_owner->charid,m_owner->nickname,m_id,m_typeID,m_level,workCell->produceid());
        return false;
    }
    
    DWORD gem = base->produceItem->clear();
    char reMark[100] = {0};
    snprintf(reMark,sizeof(reMark),"购买合成格子(%lu,%u,%u,%u)",m_id,m_typeID,m_level,workCell->placeid());
    if(!m_owner->m_store_house.addOrConsumeItem(HelloKittyMsgData::Attr_Gem,gem,reMark,false))
    {
        return m_owner->opErrorReturn(HelloKittyMsgData::Gem_Not_Enough);
    }
    workCell->set_status(HelloKittyMsgData::Place_Status_Wait);
    update(workCell);
    work();
    return true;
}

bool BuildTypeCompositeItem::getItem(const DWORD cellID)
{
    HelloKittyMsgData::FunctionCell *temp = findIDCell(cellID);
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
    snprintf(reMark,sizeof(reMark),"道具合成(%lu,%u,%u,%u)获得",m_id,m_typeID,m_level,cellID);
    if(!m_owner->m_store_house.addOrConsumeItem(base->produceItem->itemid(),1,reMark,true))
    {
        return m_owner->opErrorReturn(HelloKittyMsgData::WareHouse_Is_Full);
    }

    HelloKittyMsgData::FunctionCell functionCell;
    functionCell.set_placeid(cellID);
    functionCell.set_produceid(0);
    functionCell.set_worktime(0);
    functionCell.set_lasttime(0);
    functionCell.set_status(HelloKittyMsgData::Place_Status_Empty);
    m_compositeList.push_back(functionCell);
    update(&functionCell);
    work();
    return true;
}

bool BuildTypeCompositeItem::OpBTPType(const HelloKittyMsgData::BTPOpType &opType,const DWORD placeID)
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
                return purchaseCd();
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

bool BuildTypeCompositeItem::checkCd()
{
    HelloKittyMsgData::FunctionCell *temp = findStatusCell(HelloKittyMsgData::Place_Status_Work);
    if(!temp)
    {
        return true;
    }
    const pb::Conf_t_produceItem *baseCom = tbx::produceItem().get_base(temp->produceid());
    if(!baseCom)
    {
        return true;
    }
    temp->set_lasttime(temp->lasttime() - 1);
    if(!temp->lasttime())
    {
        temp->set_status(HelloKittyMsgData::Place_Status_Wait);
        update(temp);
        work();
    }
    return true;
}

bool BuildTypeCompositeItem::loop()
{
    checkCd();
    return true;
}

bool BuildTypeCompositeItem::fullUserInfo(HelloKittyMsgData::UserBaseInfo& binary)
{
    HelloKittyMsgData::StoreFunctionCell *funcCell = binary.add_produceitem();
    if(!funcCell)
    {
        return false;
    }
    funcCell->set_tempid(m_id);
    funcCell->set_type(HelloKittyMsgData::Function_Type_Composite);
    for(auto iter = m_compositeList.begin();iter != m_compositeList.end();++iter)
    {
        HelloKittyMsgData::FunctionCell *temp = funcCell->add_functioncell();
        if(temp)
        {
            *temp = *iter;
        }
    }
    return true;
}

bool BuildTypeCompositeItem::sendInfoMeg()
{
    HelloKittyMsgData::AckProduceItem ackMessage;
    HelloKittyMsgData::StoreFunctionCell *funcCell = ackMessage.mutable_produceitem();
    if(!funcCell)
    {
        return false;
    }
    funcCell->set_tempid(m_id);
    funcCell->set_type(HelloKittyMsgData::Function_Type_Composite);
    for(auto iter = m_compositeList.begin();iter != m_compositeList.end();++iter)
    {
        HelloKittyMsgData::FunctionCell *temp = funcCell->add_functioncell();
        if(temp)
        {
            *temp = *iter;
        }
    }
    std::string ret;
    encodeMessage(&ackMessage,ret);
    return m_owner->sendCmdToMe(ret.c_str(),ret.size());
}

void BuildTypeCompositeItem::beginActive()
{
    BuildBase::beginActive();
    DWORD now = SceneTimeTick::currentTime.sec();
    HelloKittyMsgData::FunctionCell *temp = findStatusCell(HelloKittyMsgData::Place_Status_Work);
    if(temp)
    {
        temp->set_worktime(now);
        update(temp);
    }
}


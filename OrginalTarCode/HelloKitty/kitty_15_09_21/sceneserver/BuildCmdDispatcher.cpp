#include "TradeCmdDispatcher.h"
#include "SceneUser.h"
#include "SceneUserManager.h"
#include "TradeCommand.h"
#include "serialize.pb.h"
#include "extractProtoMsg.h"
#include "buildItemProduce.h"
#include "buildTypeProduceGold.h"
#include "buildItemComposite.h"

bool TradeCmdHandle::requireAllBuild(SceneUser* user, const HelloKittyMsgData::ReqAllBuild* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.flushAllBuild();
}

bool TradeCmdHandle::requireOneBuild(SceneUser* user, const HelloKittyMsgData::ReqOneBuild* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.flushOneBuild(cmd->tempid());
}

bool TradeCmdHandle::buildUpGrade(SceneUser* user, const HelloKittyMsgData::ReqBuildUpGrade* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.upGrade(cmd->tempid());
}

bool TradeCmdHandle::build(SceneUser* user, const HelloKittyMsgData::ReqBuildBuilding* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.build(cmd->type(),1,cmd->moveflg(),cmd->point());
}

bool TradeCmdHandle::move(SceneUser* user, const HelloKittyMsgData::ReqBuildMovePlace* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.move(cmd);
}

bool TradeCmdHandle::pickUpBuild(SceneUser* user, const HelloKittyMsgData::ReqPickUpBuid* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.pickBuildInWare(cmd->tempid());
}

bool TradeCmdHandle::pickoutBuild(SceneUser* user, const HelloKittyMsgData::ReqPickOutBuid* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.pickoutBuild(cmd);
}

bool TradeCmdHandle::reqWorker(SceneUser* user, const HelloKittyMsgData::ReqWorker* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.flushWorker();
}

bool TradeCmdHandle::reqResetWorker(SceneUser* user, const HelloKittyMsgData::ReqResetWorker* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.resetWorkerCD(cmd->workerid());
}

bool TradeCmdHandle::reqClickReward(SceneUser* user, const HelloKittyMsgData::ReqClickRewardBuid* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    BuildBase *temp = user->m_buildManager.getBuild(cmd->tempid());
    if(!temp || !temp->isTypeBuid(Build_Type_Gold_Produce))
    {
        return false;
    }
    BuildTypeProduceGold *buildType = dynamic_cast<BuildTypeProduceGold*>(temp);
    if(!buildType)
    {
        return false;
    }
    if(buildType->clickReward())
    {
        buildType->updateProduce();
    }
    return true;
}

bool TradeCmdHandle::reqRecycle(SceneUser* user, const HelloKittyMsgData::ReqRecycleItem* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.recycle(cmd);
}

bool TradeCmdHandle::reqFlushProduce(SceneUser* user, const HelloKittyMsgData::ReqBuildProduce* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.flushBuildProduce(cmd);
}

bool TradeCmdHandle::reqFuncCell(SceneUser* user, const HelloKittyMsgData::ReqFunctionCell* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    BuildBase *temp = user->m_buildManager.getBuild(cmd->tempid());
    if(!temp)
    {
        return false;
    }
    if(cmd->type() == HelloKittyMsgData::Function_Type_Produce)
    {
        BuildTypeProduceItem *buildType = dynamic_cast<BuildTypeProduceItem*>(temp);
        if(!buildType)
        {
            return false;
        }
        buildType->updateFuncType(cmd->placeid());
    }
    else if(cmd->type() == HelloKittyMsgData::Function_Type_Composite)
    {
        BuildTypeCompositeItem*buildType = dynamic_cast<BuildTypeCompositeItem*>(temp);
        if(!buildType)
        {
            return false;
        }
        buildType->update(cmd->placeid());
    }
    return true;
}

bool TradeCmdHandle::reqFuncWork(SceneUser* user, const HelloKittyMsgData::ReqFunctionCellWork* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    BuildBase *temp = user->m_buildManager.getBuild(cmd->tempid());
    if(!temp)
    {
        return false;
    }
    if(cmd->type() == HelloKittyMsgData::Function_Type_Produce)
    {
        BuildTypeProduceItem *buildType = dynamic_cast<BuildTypeProduceItem*>(temp);
        if(!buildType)
        {
            return false;
        }
        return buildType->workProduce(cmd->placeid(),cmd->produceid());
    }
    else if(cmd->type() == HelloKittyMsgData::Function_Type_Composite)
    {
        BuildTypeCompositeItem*buildType = dynamic_cast<BuildTypeCompositeItem*>(temp);
        if(!buildType)
        {
            return false;
        }
        return buildType->workComposite(cmd->produceid());
    }
    return false;
}

bool TradeCmdHandle::reqFuncOp(SceneUser* user, const HelloKittyMsgData::ReqFunctionOp* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    BuildBase *temp = user->m_buildManager.getBuild(cmd->tempid());
    if(!temp)
    {
        return false;
    }
    if(cmd->type() == HelloKittyMsgData::Function_Type_Produce)
    {
        BuildTypeProduceItem *buildType = dynamic_cast<BuildTypeProduceItem*>(temp);
        if(!buildType)
        {
            return false;
        }
        return buildType->OpBTPType(cmd->optype(),cmd->placeid());
    }
    else if(cmd->type() == HelloKittyMsgData::Function_Type_Composite)
    {
        BuildTypeCompositeItem*buildType = dynamic_cast<BuildTypeCompositeItem*>(temp);
        if(!buildType)
        {
            return false;
        }
        return buildType->OpBTPType(cmd->optype(),cmd->placeid());
    }
    return false;
}

bool TradeCmdHandle::reqOpCard(SceneUser* user, const HelloKittyMsgData::ReqOpCard* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    BuildBase *temp = user->m_buildManager.getBuild(cmd->tempid());
    if(!temp)
    {
        return false;
    }
    if(!(temp->isTypeBuid(Build_Type_Item_Produce) || temp->isTypeBuid(Build_Type_Gold_Produce) || temp->isTypeBuid(Build_Type_Item_Composite)))
    {
        return false;
    }
    if(cmd->optype() == HelloKittyMsgData::BCO_Req)
    {
        temp->updateCard();
    }
    else 
    {
        temp->clearCard();
    }
    return true;
}

bool TradeCmdHandle::reqUseCard(SceneUser* user, const HelloKittyMsgData::ReqUserCard* cmd) 
{
	if (!user || !cmd)
    {
        return false;
    }
    BuildBase *temp = user->m_buildManager.getBuild(cmd->tempid());
    if(!temp)
    {
        return false;
    }
    if(user->m_buildManager.findCard(cmd->item()))
    {
        return user->opErrorReturn(HelloKittyMsgData::Card_Is_Used);
    }
    if(!(temp->isTypeBuid(Build_Type_Item_Produce) || temp->isTypeBuid(Build_Type_Gold_Produce) || temp->isTypeBuid(Build_Type_Item_Composite)))
    {
        return user->opErrorReturn(HelloKittyMsgData::Card_Is_Not_Suit);
    }
    return temp->useCard(cmd->item());
}

bool TradeCmdHandle::reqBuildRoad(SceneUser* user,const HelloKittyMsgData::ReqBuildRoad *cmd)
{
    if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.buildRoad(cmd);
}

bool TradeCmdHandle::reqClearRoad(SceneUser* user,const HelloKittyMsgData::ReqClearRoad*cmd)
{
    if (!user || !cmd)
    {
        return false;
    }
    return user->m_buildManager.clearRoad(cmd);
}
 

 

#ifndef _TRADE_CMD_DISPATCHER
#define _TRADE_CMD_DISPATCHER

#include <string.h>
#include "Fir.h"
#include "Command.h"
#include "SceneServer.h"
#include "dispatcher.h"
#include "zCmdHandle.h"
#include "TradeCommand.h"
#include "SceneTask.h"
#include "serialize.pb.h"
#include "item.pb.h"
#include "build.pb.h"
#include "warehouse.pb.h"
#include "login.pb.h"
#include "task.pb.h"
#include "atlas.pb.h"
#include "enterkitty.pb.h"
#include "carnival.pb.h"
#include "event.pb.h"
#include "friend.pb.h"
#include "email.pb.h"
#include "produceitem.pb.h"
#include "usecardbuild.pb.h"
#include "toy.pb.h"
#include "paper.pb.h"
#include "divine.pb.h"
#include "burstevent.pb.h"

class SceneUser;

class TradeCmdHandle : public zCmdHandle
{
    public:
        TradeCmdHandle()
        {
        }

        void init()
        {
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqAddItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqAddItem>::ProtoFunction(this,&TradeCmdHandle::addItemInWareHouse));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqStoreItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqStoreItem>::ProtoFunction(this,&TradeCmdHandle::requireStoreInfo));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqSallPutItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqSallPutItem>::ProtoFunction(this,&TradeCmdHandle::requireSallAddItem));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqSellPaper>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqSellPaper>::ProtoFunction(this,&TradeCmdHandle::requireSellPaper));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqAdvertise>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqAdvertise>::ProtoFunction(this,&TradeCmdHandle::advertise));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqUseItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqUseItem>::ProtoFunction(this,&TradeCmdHandle::useItem));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqBuildUpGrade>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqBuildUpGrade>::ProtoFunction(this,&TradeCmdHandle::buildUpGrade));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqBuildMovePlace>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqBuildMovePlace>::ProtoFunction(this,&TradeCmdHandle::move));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqPickOutBuid>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqPickOutBuid>::ProtoFunction(this,&TradeCmdHandle::pickoutBuild));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqBuildBuilding>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqBuildBuilding>::ProtoFunction(this,&TradeCmdHandle::build));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqAtlas>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqAtlas>::ProtoFunction(this,&TradeCmdHandle::reqAtlas));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqAllAchieve>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqAllAchieve>::ProtoFunction(this,&TradeCmdHandle::reqAchieve));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqSubmitAchieve>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqSubmitAchieve>::ProtoFunction(this,&TradeCmdHandle::commitAchieve));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqWorker>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqWorker>::ProtoFunction(this,&TradeCmdHandle::reqWorker));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqSallSystem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqSallSystem>::ProtoFunction(this,&TradeCmdHandle::reqSallSystem));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqResetWorker>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqResetWorker>::ProtoFunction(this,&TradeCmdHandle::reqResetWorker));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqclearSweetBox>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqclearSweetBox>::ProtoFunction(this,&TradeCmdHandle::reqclearSweetBox));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqClickRewardBuid>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqClickRewardBuid>::ProtoFunction(this,&TradeCmdHandle::reqClickReward));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpCell>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpCell>::ProtoFunction(this,&TradeCmdHandle::reqOpCell));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqRecycleItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqRecycleItem>::ProtoFunction(this,&TradeCmdHandle::reqRecycle));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqBuildProduce>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqBuildProduce>::ProtoFunction(this,&TradeCmdHandle::reqFlushProduce));
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqAllBuild>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqAllBuild>::ProtoFunction(this,&TradeCmdHandle::requireAllBuild));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOneBuild>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOneBuild>::ProtoFunction(this,&TradeCmdHandle::requireOneBuild));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqPickUpBuid>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqPickUpBuid>::ProtoFunction(this,&TradeCmdHandle::pickUpBuild));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpenArea>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpenArea>::ProtoFunction(this,&TradeCmdHandle::reqOpenArea));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqPayGrid>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqPayGrid>::ProtoFunction(this,&TradeCmdHandle::reqPayGrid));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqAllTask>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqAllTask>::ProtoFunction(this,&TradeCmdHandle::reqTask));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqSubmitTask>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqSubmitTask>::ProtoFunction(this,&TradeCmdHandle::commitTask));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqAtlas>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqAtlas>::ProtoFunction(this,&TradeCmdHandle::reqAtlas));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqAllAchieve>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqAllAchieve>::ProtoFunction(this,&TradeCmdHandle::reqAchieve));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqSubmitAchieve>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqSubmitAchieve>::ProtoFunction(this,&TradeCmdHandle::commitAchieve));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqWorker>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqWorker>::ProtoFunction(this,&TradeCmdHandle::reqWorker));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpenCarnical>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpenCarnical>::ProtoFunction(this,&TradeCmdHandle::reqOpenCarnical));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqSallSystem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqSallSystem>::ProtoFunction(this,&TradeCmdHandle::reqSallSystem));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqResetWorker>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqResetWorker>::ProtoFunction(this,&TradeCmdHandle::reqResetWorker));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqclearSweetBox>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqclearSweetBox>::ProtoFunction(this,&TradeCmdHandle::reqclearSweetBox));

#define REGISTER(PROTOCFUN,SELFFUN) \
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::PROTOCFUN>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::PROTOCFUN>::ProtoFunction(this, &TradeCmdHandle::SELFFUN));
#define REGISTERSAME(PROTOCFUN) REGISTER(PROTOCFUN,PROTOCFUN) 
            REGISTERSAME(ReqAddFriend);
            REGISTERSAME(ReqKickFriend); 
            REGISTERSAME(ReqRelationList); 
            REGISTERSAME(ReqEnterGarden);
            REGISTERSAME(opBuilding);
            REGISTERSAME(ReqPurchase);


            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqEmail>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqEmail>::ProtoFunction(this,&TradeCmdHandle::reqEmail));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqSendEmail>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqSendEmail>::ProtoFunction(this,&TradeCmdHandle::reqSendEmail));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpEmail>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpEmail>::ProtoFunction(this,&TradeCmdHandle::reqOpEmail));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqFunctionCell>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqFunctionCell>::ProtoFunction(this,&TradeCmdHandle::reqFuncCell));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqFunctionCellWork>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqFunctionCellWork>::ProtoFunction(this,&TradeCmdHandle::reqFuncWork));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqFunctionOp>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqFunctionOp>::ProtoFunction(this,&TradeCmdHandle::reqFuncOp));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpCard>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpCard>::ProtoFunction(this,&TradeCmdHandle::reqOpCard));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqUserCard>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqUserCard>::ProtoFunction(this,&TradeCmdHandle::reqUseCard));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqBuildRoad>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqBuildRoad>::ProtoFunction(this,&TradeCmdHandle::reqBuildRoad));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqClearRoad>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqClearRoad>::ProtoFunction(this,&TradeCmdHandle::reqClearRoad));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpToy>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpToy>::ProtoFunction(this,&TradeCmdHandle::reqToy));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqDress>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqDress>::ProtoFunction(this,&TradeCmdHandle::reqDress));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpDress>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpDress>::ProtoFunction(this,&TradeCmdHandle::reqOpDress));
    
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqPaper>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqPaper>::ProtoFunction(this,&TradeCmdHandle::reqPaper));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpPaper>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpPaper>::ProtoFunction(this,&TradeCmdHandle::reqOpPaper));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqDivineInfo>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqDivineInfo>::ProtoFunction(this,&TradeCmdHandle::reqDivineInfo));
    
            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqDivine>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqDivine>::ProtoFunction(this,&TradeCmdHandle::reqDivine));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqDivineVerify>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqDivineVerify>::ProtoFunction(this,&TradeCmdHandle::reqDivineVerify));

            SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpenCarnical>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpenCarnical>::ProtoFunction(this,&TradeCmdHandle::reqOpenCarnical));
    
           SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqClickCarnicalBox>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqClickCarnicalBox>::ProtoFunction(this,&TradeCmdHandle::reqClickCarnival));

           SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqBuyCarnicalBox>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqBuyCarnicalBox>::ProtoFunction(this,&TradeCmdHandle::reqBuyCarnival));
        
           SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqPurchaseItem>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqPurchaseItem>::ProtoFunction(this,&TradeCmdHandle::reqPurchaseItem));
    
           SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqBurstEvent>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqBurstEvent>::ProtoFunction(this,&TradeCmdHandle::reqBurstEvent));
        
           SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqOpBurstEvent>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqOpBurstEvent>::ProtoFunction(this,&TradeCmdHandle::reqOpBurstEvent));
    
           SceneTask::scene_user_dispatcher.func_reg<HelloKittyMsgData::ReqDivineNotice>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqDivineNotice>::ProtoFunction(this,&TradeCmdHandle::reqDivineFristNotice));

        }



        //.......................道具解析函数开始......................

        //使用道具
        bool useItem(SceneUser* u, const HelloKittyMsgData::ReqUseItem* cmd);

        //.......................道具解析函数结束...................... 


        //.......................仓库解析函数开始...................... 

        //请求仓库添加道具
        bool addItemInWareHouse(SceneUser* u, const HelloKittyMsgData::ReqAddItem* cmd);
        //请求道具容器信息
        bool requireStoreInfo(SceneUser* u, const HelloKittyMsgData::ReqStoreItem* cmd);
        //购买仓库格子
        bool reqPayGrid(SceneUser* u, const HelloKittyMsgData::ReqPayGrid* cmd);
        //.......................仓库解析函数结束...................... 


        //.......................摊位解析函数开始...................... 

        //请求摊位添加道具
        bool requireSallAddItem(SceneUser* u, const HelloKittyMsgData::ReqSallPutItem *cmd);
        //请求寄售报纸信息
        bool requireSellPaper(SceneUser* u, const HelloKittyMsgData::ReqSellPaper *cmd);
        //打广告
        bool advertise(SceneUser* u, const HelloKittyMsgData::ReqAdvertise *cmd);
        //出售道具给系统
        bool reqSallSystem(SceneUser* u, const HelloKittyMsgData::ReqSallSystem *cmd);
        //点击摊位单元格操作
        bool reqOpCell(SceneUser* u, const HelloKittyMsgData::ReqOpCell *cmd);
        //.......................摊位解析函数结束...................... 


        //.......................建筑解析函数开始......................

        //升级
        bool buildUpGrade(SceneUser* user, const HelloKittyMsgData::ReqBuildUpGrade* cmd);
        //建筑
        bool build(SceneUser* user, const HelloKittyMsgData::ReqBuildBuilding* cmd);
        //移动
        bool move(SceneUser* user, const HelloKittyMsgData::ReqBuildMovePlace* cmd);
        //刷新所有建筑
        bool requireAllBuild(SceneUser* user, const HelloKittyMsgData::ReqAllBuild* cmd);
        //刷新单个建筑
        bool requireOneBuild(SceneUser* user, const HelloKittyMsgData::ReqOneBuild* cmd);
        //收起建筑
        bool pickUpBuild(SceneUser* user, const HelloKittyMsgData::ReqPickUpBuid* cmd);
        //拿出仓库建筑
        bool pickoutBuild(SceneUser* user, const HelloKittyMsgData::ReqPickOutBuid* cmd);
        //请求工人数据
        bool reqWorker(SceneUser* user, const HelloKittyMsgData::ReqWorker* cmd);
        //重置工人cd
        bool reqResetWorker(SceneUser* user, const HelloKittyMsgData::ReqResetWorker* cmd);
        //请求点击建筑产出
        bool reqClickReward(SceneUser* user, const HelloKittyMsgData::ReqClickRewardBuid* cmd);
        //请求回收站回收道具
        bool reqRecycle(SceneUser* user, const HelloKittyMsgData::ReqRecycleItem* cmd);
        //请求道具产出信息
        bool reqFlushProduce(SceneUser* user, const HelloKittyMsgData::ReqBuildProduce* cmd);
        //请求功能槽
        bool reqFuncCell(SceneUser* user, const HelloKittyMsgData::ReqFunctionCell* cmd);
        //请求工作槽开始工作
        bool reqFuncWork(SceneUser* user, const HelloKittyMsgData::ReqFunctionCellWork* cmd);
        //请求对工作槽操作
        bool reqFuncOp(SceneUser* user, const HelloKittyMsgData::ReqFunctionOp* cmd);
        //请求建筑卡牌操作
        bool reqOpCard(SceneUser* user, const HelloKittyMsgData::ReqOpCard* cmd);
        //使用建筑卡牌
        bool reqUseCard(SceneUser* user, const HelloKittyMsgData::ReqUserCard* cmd);
        //建筑道路
        bool reqBuildRoad(SceneUser* user,const HelloKittyMsgData::ReqBuildRoad *cmd);
        //清除道路
        bool reqClearRoad(SceneUser* user,const HelloKittyMsgData::ReqClearRoad *cmd);
        //.......................建筑解析函数结束......................


        //.......................乐园地图解析函数开始......................

        //请求开放区域
        bool reqOpenArea(SceneUser* user,const HelloKittyMsgData::ReqOpenArea *cmd);

        //.......................乐园解析函数结束......................

        //.......................任务解析函数开始......................

        //请求所有任务
        bool reqTask(SceneUser* u, const HelloKittyMsgData::ReqAllTask* cmd);
        //提交任务
        bool commitTask(SceneUser* u, const HelloKittyMsgData::ReqSubmitTask* cmd);

        //.......................任务解析函数结束......................


        //.......................图鉴解析函数开始......................

        //请求图鉴
        bool reqAtlas(SceneUser* user,const HelloKittyMsgData::ReqAtlas *cmd);
        //.......................图鉴解析函数结束......................


        //.......................成就解析函数开始......................
        //请求成就数据
        bool reqAchieve(SceneUser* u, const HelloKittyMsgData::ReqAllAchieve* cmd);
        //提交成就
        bool commitAchieve(SceneUser* u, const HelloKittyMsgData::ReqSubmitAchieve* cmd);
        //.......................成就解析函数开始......................

        //.......................邮件解析函数开始......................
        //请求邮件
        bool reqEmail(SceneUser* u, const HelloKittyMsgData::ReqEmail *cmd);
        //请求发送邮件
        bool reqSendEmail(SceneUser* u, const HelloKittyMsgData::ReqSendEmail *cmd);
        //请求操作邮件
        bool reqOpEmail(SceneUser* u, const HelloKittyMsgData::ReqOpEmail *cmd);
        //.......................邮件解析函数结束......................

        //.......................清空糖果罐......................
        bool reqclearSweetBox(SceneUser* user,const HelloKittyMsgData::ReqclearSweetBox *cmd);
        //.........................好友........................
        bool ReqAddFriend(SceneUser* User,const HelloKittyMsgData::ReqAddFriend *message);
        bool ReqKickFriend(SceneUser* User,const HelloKittyMsgData::ReqKickFriend *message);
        bool ReqRelationList(SceneUser* User,const HelloKittyMsgData::ReqRelationList *message);

        //.......................扭蛋解析函数开始......................
        //请求扭蛋
        bool reqToy(SceneUser* u, const HelloKittyMsgData::ReqOpToy* cmd);
        //.......................扭蛋解析函数开始......................
        //........................家园访问..........................

        bool ReqEnterGarden(SceneUser* User,const HelloKittyMsgData::ReqEnterGarden *message);
        bool opBuilding(SceneUser* User,const HelloKittyMsgData::opBuilding *message);
        //请求购买道具
        bool ReqPurchase(SceneUser* User,const HelloKittyMsgData::ReqPurchase *message);
        //商店购买道具
        bool reqPurchaseItem(SceneUser* user,const HelloKittyMsgData::ReqPurchaseItem *message);

        //.......................时装解析函数开始......................
        //请求时装
        bool reqDress(SceneUser* u, const HelloKittyMsgData::ReqDress* cmd);
        //时装操作
        bool reqOpDress(SceneUser* user,const HelloKittyMsgData::ReqOpDress*cmd);
        //.......................时装解析函数开始......................

        //.......................图纸解析函数开始......................
        //请求时装
        bool reqPaper(SceneUser* u, const HelloKittyMsgData::ReqPaper* cmd);
        //图纸操作
        bool reqOpPaper(SceneUser* user,const HelloKittyMsgData::ReqOpPaper *cmd);
        //.......................图纸解析函数开始......................

        //.......................占卜解析函数开始......................
        //请求占卜数据
        bool reqDivineInfo(SceneUser* u, const HelloKittyMsgData::ReqDivineInfo* cmd);
        //请求第一个提示
        bool reqDivineFristNotice(SceneUser* user,const HelloKittyMsgData::ReqDivineNotice *cmd);
        //占卜
        bool reqDivine(SceneUser* user,const HelloKittyMsgData::ReqDivine*cmd);
        //验证占卜
        bool reqDivineVerify(SceneUser* user,const HelloKittyMsgData::ReqDivineVerify *cmd);
        //.......................占卜解析函数开始......................

        //.......................嘉年华解析函数开始......................
        //开启嘉年华
        bool reqOpenCarnical(SceneUser* user,const HelloKittyMsgData::ReqOpenCarnical *cmd);
        //点击嘉年华宝盒
        bool reqClickCarnival(SceneUser* user,const HelloKittyMsgData::ReqClickCarnicalBox *cmd);
        //购买嘉年华宝盒中的道具
        bool reqBuyCarnival(SceneUser* user,const HelloKittyMsgData::ReqBuyCarnicalBox *cmd);
        //.......................嘉年华解析函数开始......................
    
        
        //.......................突发事件华解析函数开始......................
        //请求突发事件列表
        bool reqBurstEvent(SceneUser* user,const HelloKittyMsgData::ReqBurstEvent *cmd);
        //请求操作突发事件
        bool reqOpBurstEvent(SceneUser* user,const HelloKittyMsgData::ReqOpBurstEvent *cmd);
        //.......................突发事件解析函数开始......................




};

#endif


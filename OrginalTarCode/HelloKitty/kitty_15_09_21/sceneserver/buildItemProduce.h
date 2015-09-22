#ifndef BUILD_ITEM_PRODUCT_H
#define BUILD_ITEM_PRODUCT_H
#include "buildBase.h"
#include "produceitem.pb.h"
#include "serialize.pb.h"
#include "login.pb.h"

//产生道具类建筑

//默认开启的生产工作槽数量
const DWORD OPEN_PRODUCE_NUM = 4;
//最大开启的生产工作槽数量
const DWORD MAX_PRODUCE_NUM = 8;
//默认开启的合并工作槽数量
const DWORD OPEN_COMPOSITE_NUM = 4;
//最大开启的合并工作槽数量
const DWORD MAX_COMPOSITE_NUM = 8;
//购买一个工作槽的钻石
const DWORD PURCHASE_CELL_PRICE = 10;
//开通工作槽的价格
const DWORD OPEN_CELL_PRICE = 20;

class BuildTypeProduceItem : public BuildBase
{
    public:
        BuildTypeProduceItem(SceneUser *owner,const DWORD typeID,const DWORD level,const Point &point = Point(),const bool active = false);
        BuildTypeProduceItem(SceneUser *owner,const HelloKittyMsgData::BuildBase &buildBase);
        BuildTypeProduceItem(SceneUser *owner,const pb::Conf_t_building *buildConf,const Point &point = Point());
    public:
        //加载数据
        bool load(const HelloKittyMsgData::StoreFunctionCell& binary);
        //保存数据
        virtual bool saveProduce(HelloKittyMsgData::Serialize& binary);
        //更新工作槽
        bool updateFuncType(const DWORD updateID = 0);
        //初始化工作槽
        bool init();
        //工作槽的操作
        bool OpBTPType(const HelloKittyMsgData::BTPOpType &opType,const DWORD placeID);
        //loop
        virtual bool loop();
        //填充userinfo
        bool fullUserInfo(HelloKittyMsgData::UserBaseInfo& binary);
        //开通此类建筑刷新
        bool sendInfoMeg();
        //开始生产
        bool workProduce(const DWORD cellID,const DWORD produceid);
        //激活
        virtual void beginActive();
    private:
        //获得工作槽的实例
        HelloKittyMsgData::FunctionCell* getFunctionCell(const DWORD cellID);
        //操作错误返回
        bool opBTPFailReturn(const DWORD cellID,const HelloKittyMsgData::BTPOpFailType &value = HelloKittyMsgData::BTP_Occcupy,const HelloKittyMsgData::ErrorCodeType &commonError = HelloKittyMsgData::Error_Common_Occupy);
        //开通工作槽
        bool openCell(const DWORD cellID);
        //购买工作槽
        bool purchaseCell();
        //购买cd
        bool purchaseCd(const DWORD cellID);
        //领取道具
        bool getItem(const DWORD cellID);
        //检测cd
        bool checkCd();
    private:
        //产出功能槽
        std::map<DWORD,HelloKittyMsgData::FunctionCell> m_produceMap;
};

#endif

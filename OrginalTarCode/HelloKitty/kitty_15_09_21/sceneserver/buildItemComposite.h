#ifndef BUILD_ITEM_COMPOSITE_H
#define BUILD_ITEM_COMPOSITE_H
#include "buildBase.h"
#include "produceitem.pb.h"
#include "serialize.pb.h"
#include "login.pb.h"
#include <list>

//合成道具类建筑

class BuildTypeCompositeItem : public BuildBase
{
    public:
        BuildTypeCompositeItem(SceneUser *owner,const DWORD typeID,const DWORD level,const Point &point = Point(),const bool active = false);
        BuildTypeCompositeItem(SceneUser *owner,const HelloKittyMsgData::BuildBase &buildBase);
        BuildTypeCompositeItem(SceneUser *owner,const pb::Conf_t_building *buildConf,const Point &point = Point());
    public:
        //加载数据
        bool load(const HelloKittyMsgData::StoreFunctionCell& binary);
        //保存数据
        virtual bool saveProduce(HelloKittyMsgData::Serialize& binary);
        //开始合并
        bool workComposite(const DWORD produceid);
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
        //更新指定工作槽
        void update(const DWORD cellID = 0);
        //激活建筑
        virtual void beginActive();
    private:
        //查找处于指定状态下的工作槽
        HelloKittyMsgData::FunctionCell* findStatusCell(const HelloKittyMsgData::PlaceStatusType &status);
        //查找id对应的工作槽
        HelloKittyMsgData::FunctionCell* findIDCell(const DWORD placeID);
        //删掉某个id的工作槽
        void eraseIDCell(const DWORD placeID);
        //更新指定工作槽
        void update(const HelloKittyMsgData::FunctionCell *cell);
        //合成工作
        bool work();
        //操作错误返回
        bool opBTPFailReturn(const DWORD cellID,const HelloKittyMsgData::BTPOpFailType &value = HelloKittyMsgData::BTP_Occcupy,const HelloKittyMsgData::ErrorCodeType &commonError = HelloKittyMsgData::Error_Common_Occupy);
        //购买工作槽
        bool purchaseCell();
        //购买cd
        bool purchaseCd();
        //领取道具
        bool getItem(const DWORD cellID);
        //检测cd
        bool checkCd();
    private:
        //合并功能槽
        std::list<HelloKittyMsgData::FunctionCell> m_compositeList;
};

#endif

#ifndef BUILD_TYPE_PRODUCE_GOLD_H
#define BUILD_TYPE_PRODUCE_GOLD_H
#include "buildBase.h"
#include "serialize.pb.h"

//产生金币类建筑

class BuildTypeProduceGold : public BuildBase
{
    public:
        BuildTypeProduceGold(SceneUser *owner,const DWORD typeID,const DWORD level,const Point &point = Point(),const bool active = false);
        BuildTypeProduceGold(SceneUser *owner,const HelloKittyMsgData::BuildBase &buildBase);
        BuildTypeProduceGold(SceneUser *owner,const pb::Conf_t_building *buildConf,const Point &point = Point());
    public:
        //加载数据
        bool load(const HelloKittyMsgData::BuildProduce& binary);
        //保存数据
        virtual bool saveProduce(HelloKittyMsgData::Serialize& binary);
        //填充产出信息
        void fullProduceMsg(HelloKittyMsgData::BuildProduce *buildProduce);
        //更新产出
        bool updateProduce();
        //点击结算产出
        bool clickReward();
        //loop
        virtual bool loop();
    private:
        //产出
        bool produce();
    private:
        //生产列表(按照策划要求，此处应该只会产生金币，但是为了扩展，写成map
        std::map<DWORD,DWORD> m_produceMap;
};

#endif

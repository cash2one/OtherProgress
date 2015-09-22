#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

//此文件是进一步包装excel打出来protobuf的类，方便程序中读取,类的命名规则为Conf_+需要包装的类,一定要包含一个key，此处的key可以自由发挥

#include <map>
#include "zType.h"
#include "Fir.h"
#include "ItemInfo.pb.h"
#include "Building.pb.h"
#include "pos.h"
#include <set>
#include <vector>
#include "TaskInfo.pb.h"
#include "Role.pb.h"
#include "HandBook.pb.h"
#include "AchievementInfo.pb.h"
#include "CarnivalData.pb.h"
#include "GardenActivetyItem.pb.h"
#include "Event.pb.h"
#include "event.pb.h"
#include "Param.pb.h"
#include "Production.pb.h"
#include "Buffer.pb.h"
#include "Toy.pb.h"
#include "Dress.pb.h"
#include "Paper.pb.h"
#include "Divine.pb.h"
#include "CarnivalShop.pb.h"
#include "BurstEventNpc.pb.h"
#include "BurstEventReward.pb.h"

namespace pb
{
    //以tag来划开字符串
    void parseTagString(const std::string &src,const std::string &tag,std::vector<std::string> &retVec);
    //解析point
    void parsePoint(const std::string &src,Point &destPoint);
    //解析map
    void parseDWORDToDWORDMap(const std::string &src,std::map<DWORD,DWORD> &resultMap,const std::string &separatorTag = ",",const std::string &tag = "_");
    //解析vector
    void parseDWORDToVec(const std::string &src,std::vector<DWORD> &resultMap,const std::string &separatorTag = "_");
    //解析set
    void parseDWORDSet(const std::string &src,std::set<DWORD> &resultSet,const std::string &separatorTag = ",",const std::string &tag = "_");
    //解析map
    void parseStringToStringMap(const std::string &src,std::map<std::string,std::string> &resultMap,const std::string &separatorTag,const std::string &tag);
    //buffer结构体
    struct BufferMsg
    {
        //id
        DWORD id;
        //值
        DWORD val;
        //持续时间
        DWORD time;
    };
    //解析buffer
    void parseBuffer(const std::string &src,std::map<DWORD,pb::BufferMsg>& bufferMap);

    //道具表
    class Conf_t_itemInfo
    {
        private:
            QWORD key;
            std::map<DWORD,pb::BufferMsg> bufferMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::map<DWORD,pb::BufferMsg>& getBufferMap() const
            {
                return bufferMap;
            }
            static void initStarMap(const DWORD starLevel,const DWORD itemID);
            //随机出某个星级道具
            static DWORD randStarItem(const DWORD starLevel);
        public:
            Conf_t_itemInfo(const pb::itemInfo::t_itemInfo *_itemInfo) : itemInfo(_itemInfo) {};
            Conf_t_itemInfo() : itemInfo(NULL) {};
            bool init();
        public:
            const pb::itemInfo::t_itemInfo *itemInfo;
            static std::map<DWORD,std::vector<DWORD>> starMap;
    };

    //建筑表
    class Conf_t_building
    {
        private:
            QWORD key;
            //升级材料列表
            std::map<DWORD,DWORD> materialMap;
            //依赖建筑列表
            std::map<DWORD,DWORD> dependBuildMap;
            //合并列表
            std::map<DWORD,std::map<DWORD,DWORD>> compositeMap;
            //长和宽网格数
            Point gridPoint;
            //影响范围
            Point effectPoint;
            //buffer影响表
            std::map<DWORD,pb::BufferMsg> effectMap;
            //是否施加buffer
            bool bufferFlg;
        private:
            //初始化各种表
            void initAttrMap();
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::map<DWORD,DWORD>& getMaterialMap() const
            {
                return materialMap;
            }
            inline const std::map<DWORD,DWORD>& getDependBuildMap() const
            {
                return dependBuildMap;
            }
            inline const Point& getGridPoint() const
            {
                return gridPoint;
            }
            inline const std::map<DWORD,std::map<DWORD,DWORD>>& getCompositeMap() const
            {
                return compositeMap;
            }
            inline const Point& getEffectPoint() const
            {
                return effectPoint;
            }
            inline const std::map<DWORD,pb::BufferMsg>& getEffectMap() const
            {
                return effectMap;
            }
            inline const bool getBufferFlg() const
            {
                return bufferFlg;
            }
        public:
            Conf_t_building(const pb::building::t_building *_buildInfo) : buildInfo(_buildInfo) {};
            Conf_t_building() : buildInfo(NULL) {};
            bool init();
        public:
            const pb::building::t_building *buildInfo;
    };

    struct InitBuildInfo
    {
        DWORD buildID;     //id 
        DWORD buildLevel;  //等级
        Point point;       //初始坐标
        InitBuildInfo(const DWORD _buildID = 0,const DWORD _buildLevel = 0,const Point &_point = Point()) : buildID(_buildID),buildLevel(_buildLevel),point(_point)
        {
        }

        InitBuildInfo(const InitBuildInfo &initBuildInfo)
        {
            buildID = initBuildInfo.buildID;
            buildLevel = initBuildInfo.buildLevel;
            point = initBuildInfo.point;
        }

        bool operator < (const InitBuildInfo &initBuildInfo) const
        {
            if(buildID < initBuildInfo.buildID)
            {
                return true;
            }
            return buildLevel < initBuildInfo.buildLevel;
        }

    };

    //新角色属性表
    class Conf_t_newRoleAttr
    {
        private:
            QWORD key;
            std::set<InitBuildInfo> buildLevelSet;
            std::map<DWORD,DWORD> itemMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::set<InitBuildInfo>& getBuildLevelSet() const
            {
                return buildLevelSet;
            }
            inline const std::map<DWORD,DWORD>& getItemMap() const
            {
                return itemMap;
            }
        public:
            Conf_t_newRoleAttr(const pb::newRoleAttr::t_newRoleAttr *_roleAttr) : roleAttr(_roleAttr) {};
            Conf_t_newRoleAttr() : roleAttr(NULL) {};
            bool init();
        private:
            //解析buildLevelMap
            void initBuildLevelSet();
            //解析itemMap
            void initItemMap();
        public:
            const pb::newRoleAttr::t_newRoleAttr *roleAttr;
    };

    struct TaskTarget
    {
        DWORD para1;
        DWORD para2;
        DWORD para3;
        DWORD para4;
        TaskTarget()
        {
            bzero(this,sizeof(*this));
        }
    };
    //任务表
    class Conf_t_Task
    {
        private:
            QWORD key;
            std::set<QWORD> preTaskSet;
            std::map<DWORD,DWORD> rewardMap;
            std::map<DWORD,TaskTarget> targetMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::set<QWORD>& getPreTaskSet() const
            {
                return preTaskSet;
            }
            inline const std::map<DWORD,DWORD>& getRewardMap() const
            {
                return rewardMap;
            }
            inline const std::map<DWORD,TaskTarget>& getTargetMap() const
            {
                return targetMap;
            }
        public:
            Conf_t_Task(const pb::Task::t_Task *_task) : task(_task) {};
            Conf_t_Task() : task(NULL) {};
            bool init();
        private:
            //初始化前置任务列表
            void initPreTaskSet();
            //初始化奖励列表
            void initRewardMap();
            //初始化目标列表
            void initTargetMap();
        public:
            const pb::Task::t_Task *task;
            //所有前置任务对应的任务列表
            static std::map<QWORD,std::set<QWORD>> s_allPreTaskMap;
    };

    //角色升级表
    class Conf_t_upgrade
    {
        private:
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
        public:
            Conf_t_upgrade(const pb::upgrade::t_upgrade *_upgrade) : upgrade(_upgrade) {};
            Conf_t_upgrade() : upgrade(NULL) {};
            bool init();
        public:
            const pb::upgrade::t_upgrade *upgrade;
    };

    //图鉴
    class Conf_t_Handbook
    {
        private:
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            //通过道具id来查图鉴id
            static DWORD getAtlatID(const DWORD itemID);
        public:
            Conf_t_Handbook(const pb::Handbook::t_Handbook *_handBook) : handBook(_handBook) {};
            Conf_t_Handbook() : handBook(NULL) {};
            bool init();
        private:
            //初始化道具表
            bool initItemMap();
        public:
            const pb::Handbook::t_Handbook *handBook;
            //道具对应的图鉴id
            static std::map<DWORD,DWORD> s_itemAtlasMap;
    };

    //成就
    class Conf_t_Achievement
    {
        private:
            QWORD key;
            std::map<DWORD,DWORD> rewardMap;
            std::map<DWORD,TaskTarget> targetMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::map<DWORD,DWORD>& getRewardMap() const
            {
                return rewardMap;
            }
            inline const std::map<DWORD,TaskTarget>& getTargetMap() const
            {
                return targetMap;
            }
        public:
            Conf_t_Achievement(const pb::Achievement::t_Achievement *_achievement) : achievement(_achievement) {};
            Conf_t_Achievement() : achievement(NULL) {};
            bool init();
        private:
            //初始化奖励列表
            void initRewardMap();
            //初始化目标列表
            void initTargetMap();
        public:
            const pb::Achievement::t_Achievement *achievement;
    };

    //嘉年华
    class Conf_t_CarnivalData
    {
        private:
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
        public:
            Conf_t_CarnivalData(const pb::CarnivalData::t_CarnivalData *_carnival) : carnival(_carnival) {};
            Conf_t_CarnivalData() : carnival(NULL) {};
            bool init();
        public:
            const pb::CarnivalData::t_CarnivalData *carnival;
    };
    class Conf_t_rubbish
    {
        private: 
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
        public:
            Conf_t_rubbish(const pb::rubbish::t_rubbish *_rubbish) : rubbish(_rubbish) {};
            Conf_t_rubbish() : rubbish(NULL) {};
            bool init();
        public:
            const pb::rubbish::t_rubbish *rubbish;
            HelloKittyMsgData::vecAward reward;

    };
    class Conf_t_event
    {
        private: 
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }

        public:
            Conf_t_event(const pb::event::t_event *_event) : event(_event) {};
            Conf_t_event() : event(NULL) {};
            bool init();
        public:
            const pb::event::t_event *event;
            DWORD reflushtimemin;
            DWORD reflushtimemax;
            std::vector<DWORD> buildevent;
            std::vector<DWORD> target;
            HelloKittyMsgData::vecAward rewardower;
            HelloKittyMsgData::vecAward rewardguess;

    };
    //参数表
    class Conf_t_param
    {
        private: 
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }

        public:
            Conf_t_param(const pb::param::t_param *_param) : param(_param) {};
            Conf_t_param() : param(NULL) {};
            bool init();
        public:
            const pb::param::t_param *param;
            std::vector<DWORD> vecParam;//数组参数

    };

    //产生
    class Conf_t_produceItem
    {
        private:
            QWORD key;
            std::map<DWORD,DWORD> materialMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::map<DWORD,DWORD>& getMaterialMap() const
            {
                return materialMap;
            }
        public:
            Conf_t_produceItem(const pb::produceItem::t_produceItem *_produceItem) : produceItem(_produceItem) {};
            Conf_t_produceItem() : produceItem(NULL) {};
            bool init();
        public:
            const pb::produceItem::t_produceItem *produceItem;
    };
    
    //buffer
    class Conf_t_buffer
    {
        private:
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
        public:
            Conf_t_buffer(const pb::buffer::t_buffer *_buffer) : buffer(_buffer) {};
            Conf_t_buffer() : buffer(NULL) {};
            bool init();
        public:
            const pb::buffer::t_buffer *buffer;
    };

    //扭蛋
    class Conf_t_Toy
    {
        private:
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            //随机某个扭蛋
            static DWORD randToyKey();
        public:
            Conf_t_Toy(const pb::Toy::t_Toy *_toy) : toy(_toy) {};
            Conf_t_Toy() : toy(NULL) {};
            bool init();
        public:
            const pb::Toy::t_Toy *toy;
            static DWORD sumWeight;
            static std::map<DWORD,DWORD> idToWeightMap;
    };
    
    //时装
    class Conf_t_Dress
    {
        private:
            QWORD key;
            std::map<DWORD,DWORD> materialMap;
            std::map<DWORD,pb::BufferMsg> bufferMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::map<DWORD,DWORD>& getMaterialMap() const
            {
                return materialMap;
            }
            inline const std::map<DWORD,pb::BufferMsg>& getBufferMap() const
            {
                return bufferMap;
            }
        public:
            Conf_t_Dress(const pb::Dress::t_Dress *_dress) : dress(_dress) {};
            Conf_t_Dress() : dress(NULL) {};
            bool init();
        public:
            const pb::Dress::t_Dress *dress;
    };
    
    //图纸
    class Conf_t_Paper
    {
        private:
            QWORD key;
            std::map<DWORD,DWORD> materialMap;
            std::map<DWORD,DWORD> produceMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::map<DWORD,DWORD>& getMaterialMap() const
            {
                return materialMap;
            }
            inline const std::map<DWORD,DWORD>& getProduceMap() const
            {
                return produceMap;
            }
        public:
            Conf_t_Paper(const pb::Paper::t_Paper *_paper) : paper(_paper) {};
            Conf_t_Paper() : paper(NULL) {};
            bool init();
        public:
            const pb::Paper::t_Paper *paper;
    };
    //占卜
    class Conf_t_Divine
    {
        private:
            QWORD key;
            DWORD weight;
            std::map<DWORD,DWORD> rewardMap;
            std::map<DWORD,pb::BufferMsg> bufferMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline DWORD getWeight() const
            {
                return weight;
            }
            inline const std::map<DWORD,DWORD> &getRewardMap() const
            {
                return rewardMap;
            }
            inline const std::map<DWORD,pb::BufferMsg>& getBufferMap() const
            {
                return bufferMap;
            }
        public:
            Conf_t_Divine(const pb::Divine::t_Divine *_divine) : divine(_divine) {};
            Conf_t_Divine() : divine(NULL) {};
            bool init();
        public:
            const pb::Divine::t_Divine *divine;
            static std::map<DWORD,DWORD> retWeightMap;
    };

    //嘉年华商店
    class Conf_t_CarnivalShop
    {
        private:
            QWORD key;
            std::vector<DWORD> weightVec;
            DWORD weight;
            Point  point;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline DWORD getWeight() const
            {
                return weight;
            }
            inline const std::vector<DWORD>& getWeightVec() const
            {
                return weightVec;
            }
            inline const  Point& getPoint() const
            {
                return point;
            }
        public:
            Conf_t_CarnivalShop(const pb::CarnivalShop::t_CarnivalShop* _carnivalShop) : carnivalShop(_carnivalShop) {};
            Conf_t_CarnivalShop() : carnivalShop(NULL) {};
            bool init();
        private:
            void initWeight();
        public:
            const pb::CarnivalShop::t_CarnivalShop *carnivalShop;
    };

    //突发事件奖励池
    class Conf_t_BurstEventReward
    {
        private:
            QWORD key;
            std::map<DWORD,DWORD> randItemMap;
            std::map<DWORD,DWORD> rewardMap;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            inline const std::map<DWORD,DWORD>& getRandItemMap() const
            {
                return randItemMap;
            }
            inline const std::map<DWORD,DWORD>& getRewardMap() const
            {
                return rewardMap;
            }
            static DWORD randExceptReward(const DWORD level,const std::set<DWORD>&exceptRewardSet);
        public:
            Conf_t_BurstEventReward(const pb::BurstEventReward::t_BurstEventReward* _burstEventReward) : burstEventReward(_burstEventReward) {};
            Conf_t_BurstEventReward() : burstEventReward(NULL) {};
            bool init();
        public:
            const pb::BurstEventReward::t_BurstEventReward *burstEventReward;
            static std::map<DWORD,std::vector<DWORD>> levelGradeRewardMap;
    };
    
    //突发事件npc池
    class Conf_t_BurstEventNpc
    {
        private:
            QWORD key;
        public:
            inline QWORD getKey() const
            {
                return key;
            }
            static DWORD randExceptNpc(const DWORD level,const std::set<DWORD>&exceptNpcSet);
        public:
            Conf_t_BurstEventNpc(const pb::BurstEventNpc::t_BurstEventNpc* _burstEventNpc) : burstEventNpc(_burstEventNpc) {};
            Conf_t_BurstEventNpc() : burstEventNpc(NULL) {};
            bool init();
        public:
            const pb::BurstEventNpc::t_BurstEventNpc *burstEventNpc;
            static std::map<DWORD,std::set<DWORD>> levelGradeNpcMap;
    };


}


#endif




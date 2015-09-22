#ifndef BUILD_MANAGER_H
#define BUILD_MANAGER_H

#include "buildBase.h"
#include "zSingleton.h"
#include "serialize.pb.h"
#include <set>
#include <map>
#include "login.pb.h"
#include "enterkitty.pb.h"
#include "gardenactivity.h"
#include "login.pb.h"

class SceneUser;

class BuildManager 
{
    public:
        BuildManager(SceneUser *owner);
        ~BuildManager();
        //反序列化建筑管理器
        bool load(const HelloKittyMsgData::Serialize& binary);
        //序列化建筑管理器
        bool save(HelloKittyMsgData::Serialize& binary);
        //兴建角色初始化建筑管理器
        bool init(const pb::Conf_t_newRoleAttr *confBase);
        //刷新所有建筑的信息
        bool flushAllBuild();
        //刷新某个建筑信息
        bool flushOneBuild(const DWORD tempid);
        //升级
        bool upGrade(const QWORD tempid);
        //轮询
        bool loop();
        //获得建筑的实例
        BuildBase* getBuild(const QWORD tempid);
        //建筑移动位置
        bool move(const HelloKittyMsgData::ReqBuildMovePlace *message);
        //建造
        bool build(const DWORD typeID,const DWORD level,const bool rationFlg,const HelloKittyMsgData::Point &point);
        //获得m_buildTypeMap的引用
        inline const std::unordered_map<DWORD,std::set<QWORD> >& getBuildTypeMap() const 
        {
            return m_buildTypeMap;
        }
        //填充消息
        bool fullMessage(HelloKittyMsgData::UserBaseInfo& userInfo);
        //刷新所有仓库建筑信息
        bool flushAllWareHouseBuild();
        //收起建筑
        bool pickBuildInWare(const QWORD tempid);
        //拿出仓库建筑
        bool pickoutBuild(const HelloKittyMsgData::ReqPickOutBuid *message);
        //判断某个建筑达到某个等级的数量是否足够num个(此处不包含收起来的建筑)
        bool checkBuildLevel(const DWORD typeID,const DWORD level,const DWORD num = 1);
        //获得某个类型某个等级建筑的数量
        DWORD getBuildLevelNum(const DWORD typeID,const DWORD level);
        //建筑升级(gm)
        bool gmUpGrade(const DWORD typeID,const DWORD level);
        //获得某种类型的建筑最高等级
        DWORD getBuildLevel(const DWORD typeID);
        //获得等级不低于level的所有建筑的数量
        DWORD getBuildLevelNum(const DWORD level);
        //填充信息
        bool fullMessage(HelloKittyMsgData::EnterGardenInfo& kittyInfo);
        //刷新工人数据
        bool flushWorker();
        //购买工人cd
        bool resetWorkerCD(const DWORD workerID);
        //获取所有者
        SceneUser* getOwner();
        //随机找个位置放下垃圾，参数垃圾id,返回道路id
        QWORD createItemInRoad(DWORD Id);
        //删除某条道路的垃圾
        void destroyItemInRoad(QWORD Id,const BYTE delType);
        //是否有空道路可放垃圾
        bool isHaveFreeRoad();
        QWORD getAnyBuildBytype(const std::vector<DWORD> &vecId,bool bExp );//随机获得一个建筑，bExp为反选
        QWORD getAnyBuildById(DWORD buildid);
        QWORD getAnyBuildById(const std::vector<DWORD> &vecId,bool bExp );
        QWORD  createBuildAnySpace(DWORD buildid);
        void   destroyBuild(QWORD BuildId);
        DWORD  getBuildNum();

        //判断是否为道路
        bool isRoad(const QWORD tempid);
        //检测所有建筑是否可激活
        bool checkBuildActive();
        //从包裹中创建建筑
        bool build(const WareHouseBuildBase &buildBase,const bool rationFlg,const HelloKittyMsgData::Point &point);
        //回收站回收道具
        bool recycle(const HelloKittyMsgData::ReqRecycleItem *recycle);
        //gm获取建筑产出
        bool getReward();
        //刷新建筑产出
        bool flushBuildProduce(const HelloKittyMsgData::ReqBuildProduce *cmd);
        //填充建筑的产出信息
        bool fullBuildProduce(HelloKittyMsgData::UserBaseInfo *useInfo);
        //建造道路
        bool buildRoad(const HelloKittyMsgData::ReqBuildRoad *cmd);
        //清除道路
        bool clearRoad(const HelloKittyMsgData::ReqClearRoad *cmd);
        //对卡牌进行操作
        inline void opCardSet(const DWORD cardID,const QWORD tempid,const bool opAdd = true)
        {
            if(opAdd)
            {
                m_cardMap.insert(std::pair<DWORD,QWORD>(cardID,tempid));
            }
            else
            {
                m_cardMap.erase(cardID);
            }
        }
        //查找卡牌
        inline bool findCard(const DWORD cardID)
        {
            return m_cardMap.find(cardID) != m_cardMap.end();
        }
        //获得旧id，新id的map
        inline const std::map<QWORD,QWORD>& getOldNewKeyMap()
        {
            return m_oldNewKey;
        }
        //所有建筑升到某个等级
        bool gmUpGrade(const DWORD level);
        //操作突发事件容器(提供外部接口)
        bool opBurstEventMap(const QWORD roadID,const DWORD npcID,const bool opAdd = true);
        //获得一个空闲的道路
        BuildBase* getEmptyRoad();
    private:
        //向容器中添加建筑
        bool addBuild(BuildBase *build);
        //删除建筑(从内存中干掉)
        bool deleteBuild(const QWORD tempid);
        //erase建筑
        bool eraseBuild(BuildBase *build);
        //建筑填充到map中
        bool loadBuildInMap();
        //更新仓库建筑
        bool updateWareBuild(const DWORD cellID);
        //获得空闲格子
        DWORD getEmptyCell();
        //查找闲置工人数量
        DWORD findIdleWorkerNum();
        //重置工人数据
        bool workerReset(const DWORD id);
        //工人工作
        bool work(const QWORD buildID,const DWORD cd,const DWORD num = 1);
        //更新工人数据
        bool updateWork(const DWORD id);
        //重置数据
        void reset();
        //新建一个建筑
        BuildBase* newBuild(const pb::Conf_t_building *buildConf,const HelloKittyMsgData::BuildBase *buidBase = NULL);
        //判断路上是否有垃圾
        bool rubbishInRoad(const QWORD roadID);
        //更新路上的垃圾
        bool updateRoadRubbish(const QWORD roadID,const DWORD rubbishType,const BYTE opType = 1);
        //刷新资源
        bool flushBuildProduce(const QWORD tempid);
        //操作m_kindTypeMap表
        bool opKindType(const QWORD tempid,const bool opAdd = true);
        //检测所有地标建筑给予的buffer
        bool checkBuildBuffer(const bool notify = true);
        //建造建筑时初始化各类建筑
        bool initTypeBuild(BuildBase *build);
        //建造建筑条件检测
        bool checkPreBuild(const DWORD typeID,const DWORD level,const bool needWorkerFlg = true);
        //建造建筑后的数据初始化
        bool asistBuild(BuildBase *build,const DWORD workCD,const bool rationFlg,const HelloKittyMsgData::Point &point);
    private:
        //旧id对应新id
        std::map<QWORD,QWORD> m_oldNewKey;
        //所有建筑的实例id和实例
        std::unordered_map<QWORD,BuildBase*> m_buildMap;
        //所有建筑的类型id和实例id
        std::unordered_map<DWORD,std::set<QWORD> > m_buildTypeMap;
        //建筑仓库cellid
        std::set<DWORD> m_cellSet;
        //建筑仓库cellid对应建筑的属性
        std::map<DWORD,WareHouseBuildBase> m_wareHouseBuildMap;
        //建筑仓库typeid对应数量
        std::map<DWORD,DWORD> m_wareHouseTypeMap;
        //垃圾数据(道路id，垃圾类型id)
        std::map<QWORD,DWORD> m_rubbishMap;
        //突发事件
        std::map<QWORD,DWORD> m_burstEventMap;
        //维护一个空道路列表
        std::set<QWORD> m_emptyRoadSet;
        //工人数据
        std::map<DWORD,HelloKittyMsgData::Worker> m_workerMap;
        //kindtype对应的set
        std::map<DWORD,std::set<QWORD>> m_kindTypeMap;
        //所使用卡牌
        std::map<DWORD,QWORD> m_cardMap;
        //所属主人
        SceneUser* m_owner;
        DWORD m_maxCellID;
};

#endif


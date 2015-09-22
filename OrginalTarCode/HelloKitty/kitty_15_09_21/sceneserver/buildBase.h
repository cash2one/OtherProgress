#ifndef BUILD_BASE_H
#define BUILD_BASE_H

#include "zType.h"
#include "build.pb.h"
#include "dataManager.h"
#include "pos.h"
#include "common.pb.h"
#include "serialize.pb.h"
#include "login.pb.h"
#include "usecardbuild.pb.h"
#include "bufferData.h"

class BuildManager;
class SceneUser;
class WareHouseBuildBase;

//策划说所有建筑的产出cd都是一样的，10秒
const DWORD PRODUCE_CD_TIME = 10;
//所有建筑需要一个工人
const DWORD BUILD_WORKER_NUM = 1;
//重置工人cd所需钻石
const DWORD BUY_WORKER_CD = 2;

enum BUILD_TYPE
{
    Build_Type_Gold_Produce = 2, //金币产出建筑
    Build_Type_Item_Produce = 3, //生产道具类
    Build_Type_Recycle = 4,//回收站
    Build_Type_Land_Mark = 5, //地标建筑
    Build_Type_Road = 7,  //道路
    Build_Type_Item_Composite = 8, //合成道具
};
const DWORD ROad_ID = 10010041;
class BuildBase
{
    public:
        BuildBase(SceneUser *owner,const DWORD typeID,const DWORD level,const Point &point = Point(),const bool active = false);
        BuildBase(SceneUser *owner,const HelloKittyMsgData::BuildBase &buildBase);
        BuildBase(SceneUser *owner,const pb::Conf_t_building *buildConf,const Point &point = Point());
        virtual ~BuildBase();

        inline QWORD getID() const 
        {
            return m_id;
        }
        inline DWORD getTypeID() const
        {
            return m_typeID;
        }
        inline DWORD getLevel() const
        {
            return m_level;
        }
        inline DWORD getProduceTime() const
        {
            return m_produceTime;
        }
        inline DWORD getMark() const
        {
            return m_mark;
        }
        inline void setMark(const DWORD value)
        {
            m_mark = value;
        }
        inline void setDurTime(const DWORD value)
        {
            m_durTime = value;
        }
        inline Point getPoint() const
        {
            return m_point;
        }
        inline void setPoint(const Point &point)
        {
            m_point.x = point.x;
            m_point.y = point.y;
        }
        inline bool getRationMask() const
        {
            return m_rationMark;
        }
        inline bool isActive() const
        {
            return m_isActive;
        }
        inline void setActive(const bool activeFlg)
        {
            m_isActive = activeFlg;
        }
        //判断是否为某种类型的建筑
        inline bool isTypeBuid(const DWORD type) const
        {
            return confBase ? confBase->buildInfo->buildkind() == type : false;
        }

        DWORD getTypeBuild()
        {
          return confBase ? confBase->buildInfo->buildkind()  : 0;

        }
        void save(HelloKittyMsgData::BuildBase *buildBase);
        //存档一些建筑上的倍的信息
        virtual bool saveProduce(HelloKittyMsgData::Serialize& binary)
        {
            return true;
        }
        //loop轮询
        virtual bool loop();
        //升级
        bool upGrade(const bool gmFlg = false);
        //刷新建筑
        bool flush();
        //挪位置
        bool movePlace(const HelloKittyMsgData::ReqBuildMovePlace *message);
        //建造
        bool build(const Point &point,const bool initFlg = false,const bool rationFlg = false);
        //建筑操作成功返回
        bool opSuccessReturn(const HelloKittyMsgData::BuildSuccessCodeType &code,const Point &oldPoint = Point());
        //建筑操作失败原因
        bool opFailReturn(const HelloKittyMsgData::ErrorCodeType &commonError = HelloKittyMsgData::Error_Common_Occupy,const HelloKittyMsgData::BuildFailCodeType &code = HelloKittyMsgData::Build_Occcupy);
        //计算前面累积的cd
        void countDurTime();
        //把数据考到WareHouseBuildBase对象中
        void saveAsWareHouseBuildBase(WareHouseBuildBase &info);
        //回收道具
        bool recycle(const DWORD itemID,const DWORD itemNum);
        //向客户端更新buffer信息
        bool updateBufferMsg();
        //填充user中的buffer数据
        bool fullUserInfoMsg(HelloKittyMsgData::UserBaseInfo &useInfo);
        //激活
        virtual void beginActive();
        //保存卡牌信息
        bool saveCard(HelloKittyMsgData::Serialize& binary);
        //加载卡牌信息
        bool loadCard(const HelloKittyMsgData::UseCardInfo &temp);
        //使用卡牌
        bool useCard(const DWORD card);
        //清除卡牌
        bool clearCard();
        //更新卡牌
        bool updateCard();
        //填充user卡牌信息
        bool fullUserCard(HelloKittyMsgData::UserBaseInfo &useInfo);
    protected:
        //初始化配置表指针
        bool initConfBase();
        //检测依赖建筑
        bool checkDependBuildMap(const std::map<DWORD,DWORD> &dependBuildMap);
        //更改建筑状态
        bool changeStatus(const HelloKittyMsgData::BuildStatueType &status);
        //建筑移位接口(是否翻转)
        bool move(const Point &buildPoint,const bool rationFlg = false);
    protected:
        //拥有者
        SceneUser* m_owner;
        //实例id
        QWORD m_id;
        //类型id
        DWORD m_typeID;
        //等级
        DWORD m_level;
        //坐标
        Point m_point;
        //标志位
        DWORD m_mark;
        //升级cd时间
        DWORD m_durTime;
        //产出时间
        DWORD m_produceTime;
        //翻转标志(是否翻转)
        bool m_rationMark;
        //是否激活
        bool m_isActive;
        //使用明星id
        DWORD m_cardID;
        //使用明星时间
        DWORD m_useCardTime;
    public:
        //bufferMap(来源,buffer列表);
        std::map<QWORD,std::map<DWORD,Buffer>> m_bufferMap;
        //id生成器
        static QWORD generateID;
        //配置表指针
        const pb::Conf_t_building *confBase;
};

struct WareHouseBuildBase
{
    public:
        DWORD cellID;
        DWORD typeID;
        DWORD level;
        DWORD produceTime;
        DWORD durTime;
        DWORD mark;
        DWORD num;
        WareHouseBuildBase(const DWORD cellID = 0,const DWORD typeID = 0,const DWORD level = 0,const DWORD produceTime = 0,const DWORD mark = HelloKittyMsgData::Build_Status_Stop,const DWORD durTime = 0,const DWORD num = 0) : cellID(cellID),typeID(typeID),level(level),produceTime(produceTime),durTime(durTime),mark(mark),num(num)
        {
        }
        WareHouseBuildBase(const WareHouseBuildBase &info)
        {
            cellID = info.cellID;
            typeID = info.typeID;
            level = info.level;
            produceTime = info.produceTime;
            mark = info.mark;
            num = info.num;
        }
        bool operator< (const WareHouseBuildBase &info) const
        {
            if(typeID < info.typeID)
            {
                return true;
            }
            if(typeID == info.typeID)
            {
                return level < info.level;
            }
            return false;
        }
};



#endif


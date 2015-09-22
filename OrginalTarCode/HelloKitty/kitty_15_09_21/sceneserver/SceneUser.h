/**
 * \file	SceneUser.h
 * \version  	$Id: SceneUser.h 67 2013-04-23 09:44:20Z  $
 * \author  	,
 * \date 	2013年04月07日 15时48分31秒 CST
 * \brief 	场景用户定义
 *
 * 
 */

#ifndef _SCENEUSER_H_
#define _SCENEUSER_H_

#include <map>
#include "Fir.h"
#include "SceneTask.h"
#include "CharBase.h"
#include "zTime.h"
#include "RecordCommand.h"
#include "zSerialize.h"
#include "zCmdBuffer.h"
#include "common.h"
#include "UTrade.h"
#include "UStoreHouse.h"
#include "buildManager.h"
#include "common.pb.h"
#include "SceneMapData.h"
#include "taskManager.h"
#include "atlasManager.h"
#include "achievementManager.h"
#include "friend.pb.h" 
#include "EventManger.h"
#include "gardenactivity.h"
#include "FriendManager.h"
#include "emailManager.h"
#include "dressManager.h"
#include "paperManager.h"
#include "dataManager.h"
#include "carnival.pb.h"
#include "burstEventManager.h"

//愉悦值的3个档次
const DWORD HAPPY_LOW = 60;
const DWORD HAPPY_MID = 80;
const DWORD HAPPY_HIGHT = 100;
//每次随机扭蛋需要钻石
const DWORD RAND_TOY_GEM = 10;
//每次随机占卜需要钻石
const DWORD RAND_DIVINE_GEM = 10;
//占卜开始和结束
const DWORD DIVINE_BEGIN = 1;
const DWORD DIVINE_END = 4;
class RecordClient;

class SceneUser 
{
    public:
        friend class SceneUserManager;
        //accid(暂时没用)		
        DWORD accid;
        //角色id，全服唯一
        QWORD charid;
        //昵称
        char nickname[MAX_NAMESIZE+1];
        //charbase,不要在这儿添加字段，很不方便,要改数据库
        CharBase charbase;
        //charbin,后面角色需要存档的零散数据，放这里
        HelloKittyMsgData::CharBin charbin;
        // 贸易
        UTrade m_trade; 
        //仓库
        UStoreHouse m_store_house;
        //建筑管理器
        BuildManager m_buildManager;
        //任务管理器
        TaskManager m_taskManager;
        //图鉴管理
        AtlasManager m_atlasManager;
        //成就管理器
        AchievementManager m_achievementManager;
        //邮件管理器
        EmailManager m_emailManager;
        //时装管理器
        DressManager m_dressManager;
        //图纸管理器
        PaperManager m_paperManager;
        //突发事件管理器
        BurstEventManager m_burstEventManager;
        //垃圾产生器
        ActiveManager m_activeManger;
        //事件产生器
        EventManager m_eventmanager;
        //好友
        ManagerFriend m_friend;
        //存档md5	
        char lastSaveMD5[16];
        //kitty乐园
        SceneMapData m_kittyGarden;
            public:
        SceneUser(SceneTask *gate);
        virtual ~SceneUser();
        //发送数据到客户端
        bool sendCmdToMe(const void *pstrCmd, const int nCmdLen) const;
        //发送数据到网关
        bool sendCmdToGateway(const void *pstrCmd, const int nCmdLen) const;
        //是否在线标志
        inline bool is_online()
        {
            return _online;
        }
        //获得仓库当前最大容量
        DWORD getStoreLimit();
        //轮询
        bool loop();

        //上线函数
        bool online(std::string phone_uuid,SceneTask* _gate);
        bool offlineload();
        //从session注册到场景函数
        bool reg(CMD::SCENE::t_regUser_Gatescene *Cmd);
        //注销
        bool unreg();
        // 从charbase和二进制数据克隆一个玩家
        bool clone(CharBase charbase,std::string allbinary);


        //压缩角色数据
        DWORD saveBinaryArchive(unsigned char *out , const int maxsize);
        //保存角色数据
        bool save();

        //检查等级
        bool checkLevel(const DWORD num);
        //操作错误代码返回
        bool opErrorReturn(const HelloKittyMsgData::ErrorCodeType &errorCode);
        //操作成功返回
        bool opSuccessReturn(const HelloKittyMsgData::SuccessCodeType &code);
        //刷新角色基本信息
        bool flushUserInfo();
        //刷新角色单个属性
        bool updateAttrVal(const HelloKittyMsgData::AttrType &attrType,const DWORD value);
        //填充刷新角色乐园所有信息
        bool flushUserInfo(HelloKittyMsgData::AckFlushUserInfo &send);
        //升级
        bool upgrade();
        //gm升级(不扣经验)
        bool changeLevel(const DWORD level);
        void AddVisit(QWORD PlayerID,DWORD GateId);//加入一个访问者
        void DelVisit(QWORD PlayerID);//删除一个访问者
        bool isVisit(QWORD PlayerID);
        QWORD getvisit();
        void setVisit(QWORD PlayerId);

        void UserReturn();//回到自己的家园
        const map<QWORD,DWORD>& getVist(){return vecVisit;}
        bool  havePersonOnline();//是否有玩家在线
        DWORD getHappyFequence(const DWORD happyVal);
        void  DoBuildAward(const HelloKittyMsgData::vecAward& rvecAward,DWORD EventID,QWORD owerid,bool NeedNotice);//给玩家发奖励

        //刷新别人家乐园
        bool flushKittyGardenInfo();
        bool flushKittyGardenInfo(QWORD sendCharID,HelloKittyMsgData::AckEnterGarden &send);
        //gm修改愉悦值天数
        bool changeHappyDataGm(const DWORD happyValType,const DWORD day);
        //判断是否需要刷新日常数据
        bool isDailyData();
        //刷新日常数据
        bool brushDailyData();
        //初始化日常数据
        void initDailyData();
        //增加访问别人次数
        bool addVertiseOther(const DWORD num);
        //增加好友
        bool addFriendNum(const DWORD num);
        //开启嘉年华
        bool openCarnival();
        //重置玩家所有数据
        void resetAllData();
        //更改系统时间刷新有关时间的数据
        bool changeTime();
        //建筑操作
        void opBuild(QWORD PlayerID,QWORD BulidId);
        bool  checkPush(const HelloKittyMsgData::vecAward& rvecAward);
        bool  pushItem(const HelloKittyMsgData::vecAward& rvecAward,const char *reMark);
        //扣除道具价格
        bool deductPrice(const CMD::SCENE::t_UserPurchasePrice *cmd);
        //购买道具，增加道具
        bool purchaseAddItem(const CMD::SCENE::t_UserPurchaseShiftItem *cmd);
        //向在自己乐园家发送消息
        bool sendOtherUserMsg(const void *pstrCmd, const int nCmdLen);
        //发送时间
        void sendhappenevent(const HelloKittyMsgData::PlayerEvent &event,bool bSendOther);
        void broadcastMsgInMap(const void *pstrCmd, const int nCmdLen);  
        void returnMsgInMap(QWORD PlayerID,const void *pstrCmd, const int nCmdLen);
        //给玩家发操作建筑奖励
        void DoAward(QWORD PlayerID, const HelloKittyMsgData::vecAward &vecAward,DWORD EventID = 0,bool NeedNotice = false);
        void SendMsgToOher(QWORD PlayerID,const void *pstrCmd, const int nCmdLen); 
        bool isOtherOnline(QWORD PlayerID);
        ManagerFriend & getFriendManager(){return m_friend;}
        RecordClient  *getSelfRecord();
        //刷新扭蛋数据
        bool flushToy();
        //随机扭蛋数据
        bool randToy();
        //检查材料
        bool checkMaterialMap(const std::map<DWORD,DWORD> &materialMap);
        //扣除材料
        bool reduceMaterialMap(const std::map<DWORD,DWORD> &materialMap,const char *reMark);
        //更新全局buffer
        bool updateBufferMsg();
        const std::map<QWORD,std::map<DWORD,Buffer>>& getBufferMap();
        //初始化全局buffer
        void initBuffer();
        //上线辅助函数
        void onlineInit();
        //获得gate
        inline SceneTask* getGate()
        {
            return gate;
        }
        //刷新占卜信息
        bool flushDivine(const HelloKittyMsgData::DivineData *divine = NULL);
        //占卜第一个提示
        bool divineNotice();
        //占卜
        bool divine(const bool notify);
        //验证占卜顺序
        bool divineVerify(const std::string &answer);
        //购买嘉年华宝盒
        bool buyCarnivalBox();
        //刷出嘉年华宝盒内容
        bool randCarnivalShop();
        //购买商城道具
        bool purchaseItem(const DWORD itemid,const DWORD num);
        //更改愉悦值数据
        void changeHappyData();
    private:
        //下线辅助函数
        void offline();
        //新建角色初始化信息
        bool initNewRole();

        // 获取该角色的二进制信息
        std::string getAllBinary();
        // 获取该角色二进制数据
        std::string getBinaryArchive();
        //反序列化二进制数据
        void setupBinaryArchive(HelloKittyMsgData::Serialize& binary);
        //第一次访问家园
        void DoFirstVisit(QWORD PlayerID,DWORD GateId);
        //更改愉悦值数据
        void changeHappyData(HelloKittyMsgData::HappyData *happyData,const DWORD value,const DWORD judegeVal,const DWORD sec,const DWORD days = 1,const bool gmFlg = false);
        //检测开启嘉年华
        bool checkOpenCarnival();
        //进入乐园(进入别人家乐园或者返回自己家乐园)
        bool flushGardenMsg(const DWORD gatewayID,const QWORD sendCharID);
        //填充全局buffer
        bool fullUserInfoBuffer(HelloKittyMsgData::UserBaseInfo &userInfo);
        //占卜随机蜡烛顺序
        bool randDivineAnswer(std::string &ret,DWORD &firstKey);
        //占卜随机出运势
        const pb::Conf_t_Divine* randDivine(const DWORD answer);
        //刷出嘉年华宝盒
        bool randCarnivalBox();
        //重置嘉年华数据
        void initCarnivalShopData();
    public:
        //角色所带来的全局buffer
        std::map<QWORD,std::map<DWORD,Buffer>> m_bufferMap;
    private:
        SceneTask *gate;
        //玩家在线状态
        bool _online; 
        bool needSave;
        char lastSaveCharBaseMD5[16];
        map<QWORD,DWORD> vecVisit;
        QWORD VisitID;
        DWORD m_LastCheckTimer;
        //嘉年华商店数据(不用存档)
        HelloKittyMsgData::CarnivalShopData m_carnivalShopData;
};
#endif

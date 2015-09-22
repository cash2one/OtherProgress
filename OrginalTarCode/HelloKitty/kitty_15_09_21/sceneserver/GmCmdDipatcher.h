#ifndef GM_CMD_DISPATCHER_H
#define GM_CMD_DISPATCHER_H
#include "zCmdHandle.h"
#include "SceneTask.h"
#include "dispatcher.h"
#include "gm.pb.h"
#include "Fir.h"
#include "zType.h"
#include <map>
#include <vector>

class SceneUser;
class GMCmdHandle : public zCmdHandle
{
    public:
        GMCmdHandle()
        {
        }

        void init()
        {
            SceneTask::scene_user_gm_dispatcher.func_reg<HelloKittyMsgData::ReqGM>(ProtoCmdCallback<SceneUser,HelloKittyMsgData::ReqGM>::ProtoFunction(this,&GMCmdHandle::reqGm));
            initGmFunMap();
        }
        //gm函数
        typedef bool (*GmFun)(SceneUser* user,const std::vector<std::string> &commandVec); 
        //gm命令
        bool reqGm(SceneUser* user,const HelloKittyMsgData::ReqGM *cmd);
    private:
        //是否已经注册函数
        static bool s_initFlg;
        //注册函数容器
        static std::map<std::string,GmFun> s_gmFunMap;
        //注册函数
        void initGmFunMap();
        //给道具
        static bool addItem(SceneUser* user,const std::vector<std::string> &commandVec);
        //更改等级
        static bool changeLevel(SceneUser* user,const std::vector<std::string> &commandVec);
        //获得pid
        static bool getPid(SceneUser* user,const std::vector<std::string> &commandVec);
        //建筑升级
        static bool buildLevel(SceneUser* user,const std::vector<std::string> &commandVec);
        //增加图鉴
        static bool addAtlas(SceneUser* user,const std::vector<std::string> &commandVec);
        //删除某个图鉴
        static bool deleteAtlas(SceneUser* user,const std::vector<std::string> &commandVec);
        //删除所有图鉴
        static bool clearAtlas(SceneUser* user,const std::vector<std::string> &commandVec);
        //完成任务
        static bool finishTask(SceneUser* user,const std::vector<std::string> &commandVec);
        //开启一个任务
        static bool openTask(SceneUser* user,const std::vector<std::string> &commandVec);
        //更改愉悦值维持天数
        static bool changeHappyDay(SceneUser* user,const std::vector<std::string> &commandVec);
        //完成成就
        static bool finishAchieve(SceneUser* user,const std::vector<std::string> &commandVec);
        //更改系统时间
        static bool changeTime(SceneUser* user,const std::vector<std::string> &commandVec);
        //打印现在时间
        static bool nowTime(SceneUser* user,const std::vector<std::string> &commandVec);
        //清空角色所用数据
        static bool clearUserData(SceneUser* user,const std::vector<std::string> &commandVec);
        //随机刷新报纸
        static bool randPaper(SceneUser* user,const std::vector<std::string> &commandVec);
        //增加访问家园人数
        static bool addVistor(SceneUser* user,const std::vector<std::string> &commandVec);
        static bool addfriend(SceneUser* User,const std::vector<std::string> &commandVec);
        static bool delfriend(SceneUser* User,const std::vector<std::string> &commandVec);
        static bool getfriendlist(SceneUser* User,const std::vector<std::string> &commandVec);
        static bool getfanslist(SceneUser* User,const std::vector<std::string> &commandVec);
        static bool getotherlist(SceneUser* User,const std::vector<std::string> &commandVec);

        //领取建筑产出
        static bool rewardBuild(SceneUser* user,const std::vector<std::string> &commandVec);
        //发送系统邮件
        static bool sendEmail(SceneUser* user,const std::vector<std::string> &commandVec);
        //清空时装
        static bool clearDress(SceneUser* user,const std::vector<std::string> &commandVec);
        //清空图纸
        static bool clearPaper(SceneUser* user,const std::vector<std::string> &commandVec);
        //god指令
        static bool god(SceneUser* user,const std::vector<std::string> &commandVec);
        //重置每天数据
        static bool resetDailyData(SceneUser* user,const std::vector<std::string> &commandVec);
};

#endif

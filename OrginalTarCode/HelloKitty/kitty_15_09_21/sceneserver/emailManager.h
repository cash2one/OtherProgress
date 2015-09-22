#ifndef E_MAIL_MANAGER_H
#define E_MAIL_MANAGER_H
#include "email.pb.h"
#include "zType.h"
#include <map>
#include "serialize.pb.h"

//最大100封邮件
const DWORD MAX_EMAIL_NUM = 100;
class SceneUser;
class EmailManager
{
    public:
        EmailManager(SceneUser *owner);
    public:
        //刷新所有邮件
        bool flushEmail();
        //更新邮件
        bool updateEmail(const QWORD id);
        //邮件操作
        bool opEmail(const HelloKittyMsgData::ReqOpEmail *message);
        //存档
        bool save(HelloKittyMsgData::Serialize& binary);
        //加载
        bool load(const HelloKittyMsgData::Serialize& binary);
        //接收邮件
        bool acceptEmail(HelloKittyMsgData::EmailInfo &emailInfo);
        //发送邮件
        bool sendEmail(const HelloKittyMsgData::EmailBase *emailBase);
        //删除超时邮件
        bool delTimeOut(const bool notify = true);
        //系统发送道具邮件(默认不需要弹窗)
        static bool sendEmailBySys(const QWORD accepter,const char *title,const char *conten,const std::map<DWORD,DWORD> &itemMap,const bool popup = false);
        //发送邮件
        static bool sendEmail(HelloKittyMsgData::EmailInfo &emailInfo);
        //插入数据库
        static bool insertDB(const HelloKittyMsgData::EmailInfo &emailInfo);
        //系统发送道具邮件(默认不需要弹窗)
        static bool sendEmailBySys(const char *nickname,const char *title,const char *conten,const std::map<DWORD,DWORD> &itemMap,const bool popup = false);
        //请求刷新邮件
        bool reqEmail(const HelloKittyMsgData::ReqEmail *cmd);
    private:
        //获得邮件
        HelloKittyMsgData::EmailInfo* getEmail(const QWORD id);
        //删除邮件
        bool delEmail(const QWORD id,const bool notify = true,const bool system = true);
        //提取附件
        bool getItem(const QWORD id);
        //从数据库中加载邮件
        bool loadDB();
    private:
        SceneUser *m_owner;
        //邮件id对应邮件
        std::map<QWORD,HelloKittyMsgData::EmailInfo> m_emailMap;
        //邮件id
        static QWORD mailID;
        //true表示邮箱已满
        bool m_full;
};

#endif

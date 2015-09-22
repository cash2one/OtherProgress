/**
 * \file
 * \version  $Id: SceneMailManager.h 42 2013-04-10 07:33:59Z  $
 * \author  王海军, wanghaijun@ztgame.com 
 * \date 2006年01月04日 16时55分37秒 CST
 * \brief 网关到场景数据缓冲发送
 *
 * 
 */


#ifndef _SceneMailMANAGER_H_
#define _SceneMailMANAGER_H_

#include <vector>
#include <string>
#include "zSingleton.h"
#include "event.pb.h"
enum eMailID
{


};

/**
 ** \brief 定义服务器信息采集连接的客户端管理容器
 **/
class SceneMailManager : public Singleton<SceneMailManager>
{
    friend class Singleton<SceneMailManager>;
    public:
    ~SceneMailManager(){};
    void sendSysMailToPlayer(QWORD PlayerId,DWORD TitleID ,DWORD TextId ,const std::vector<std::string>* vecPara = NULL,const HelloKittyMsgData::vecAward* rvecAward = NULL);
    void sendSysMailToPlayerForEvent(QWORD PlayerId,DWORD eventId,QWORD OwerId,const HelloKittyMsgData::vecAward& rvecAward,bool bAddItem = false );

    private:
    SceneMailManager(){};

};

#endif


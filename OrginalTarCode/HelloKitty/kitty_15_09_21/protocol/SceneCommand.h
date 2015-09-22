#ifndef _SceneCommand_h_
#define _SceneCommand_h_

#include "zNullCmd.h"
#include "messageType.h"

#pragma pack(1)

namespace CMD
{

    namespace SCENE
    {
        struct SceneNull : t_NullCmd
        {
            SceneNull()
            {
                cmd = SCENECMD;
            }
        };

        const BYTE PARA_LOGIN = 1;
        struct t_LoginScene : SceneNull 
        {
            WORD wdServerID;
            WORD wdServerType;
            t_LoginScene()
            {
                para = PARA_LOGIN;
                wdServerID = 0;
                wdServerType = 0;
            }
        };

        const BYTE PARA_REFRESH_LOGIN_SCENE = 2;
        struct t_Refresh_LoginScene : SceneNull 
        {
            QWORD charid;
            DWORD dwSceneTempID;
            t_Refresh_LoginScene()
            {
                para = PARA_REFRESH_LOGIN_SCENE;
                charid = 0;
                dwSceneTempID = 0;
            }
        };

        const BYTE PARA_FORWARD_SCENE = 3;
        struct t_Scene_ForwardScene : SceneNull
        {
            QWORD charid;
            DWORD accid;
            DWORD size;
            char data[0];

            t_Scene_ForwardScene()
            {
                para = PARA_FORWARD_SCENE;
                charid = 0;
                accid = 0;
                size = 0;
            }
        };

        const BYTE PARA_SCENE_USER = 4;
        struct t_User_FromScene : SceneNull
        {
            QWORD charid;
            DWORD size;
            char data[0];

            t_User_FromScene()
            {
                para = PARA_SCENE_USER;
                charid = 0;
                size = 0;
            }
        };

        const BYTE PARA_START_OK_SCENE_GATE = 5;
        struct t_StartOKSceneGate : SceneNull
        {
            t_StartOKSceneGate()
            {
                para = PARA_START_OK_SCENE_GATE;
            }
        };
        //scene->scene
        const BYTE PARA_PLAYERAWARD = 6;
        struct t_awardtoPlayer_scenescene : SceneNull
        {
            QWORD charid;
            QWORD charowner;
            DWORD eventid;
            DWORD size;
            bool  bnotice;
            BYTE  data[0];
            t_awardtoPlayer_scenescene()
            {
                charid = 0;
                para =  PARA_PLAYERAWARD;
                charowner  = 0;
                eventid= 0;
                size =0;
                bnotice = false;

            }
        };
        //scene->scene
        const BYTE PARA_SETFANS = 7;
        struct t_setFans_scenescene : SceneNull
        {
            QWORD charid;
            QWORD fansid;
            BYTE  type;
            t_setFans_scenescene()
            {
                charid = 0;
                para =  PARA_SETFANS;
                fansid  = 0;
                type = 0;//0表示增加，1表示删除


            }
        };

        //scene->scene(发送邮件)
        const BYTE PARA_EMAIL_SEND = 8;
        struct t_EmailSendPlayer_scenescene : SceneNull
        {
            QWORD charid;
            DWORD size;
            BYTE  data[0];
            t_EmailSendPlayer_scenescene()
            {
                charid = 0;
                para =  PARA_EMAIL_SEND;
                size =0;
            }
        };
       //gate->secscene
        const BYTE PARA_REG_USER_GATE_SCENE = 9; 
        struct t_regUser_Gatescene : SceneNull
        {
            DWORD accid;
            QWORD charid;
            char  name[MAX_NAMESIZE+1];
            char  flat[MAX_FLAT_LENGTH];
            char phone_uuid[100];
            BYTE byCreate; // 0正常登陆 1创建登陆
            DWORD heroid; // 选择英雄 id
            WORD acctype;//登陆类型
            char account[MAX_ACCNAMESIZE+1];
            t_regUser_Gatescene()
            {
                para = PARA_REG_USER_GATE_SCENE; 
                accid = 0;
                charid = 0;
                bzero(name,sizeof(name));
                bzero(flat, sizeof(flat));
                bzero(phone_uuid,sizeof(phone_uuid));
                byCreate = 0;
                heroid = 0;
                acctype = 0;
                bzero(account, sizeof(account));
            };
        };

        const BYTE PARA_UNREG_USER_GATE_SCENE = 10;
        enum {
               UNREGUSER_RET_LOGOUT = 0,
        };
        struct t_unregUser_gatescene : SceneNull
        {
            QWORD charid;
            BYTE retcode;
            t_unregUser_gatescene()
            {
                para = PARA_UNREG_USER_GATE_SCENE;
                charid = 0;
                retcode = 0;
            }
        };

        //scen--scen

        const BYTE PARA_SetVisit = 11;
        struct t_SetVisit_scenescene : SceneNull
        {
            QWORD charid;
            QWORD ownerid;
            DWORD chargateid;

            t_SetVisit_scenescene()
            {
                charid = 0;
                para =  PARA_SetVisit;
                ownerid  = 0;
                chargateid = 0;//非0表示增加，0表示删除
            }
        };
        //scen--scen
        const BYTE PARA_DoBuliding = 12;
        struct t_DoBulid_scenescene : SceneNull
        {
            QWORD charid;
            QWORD ownerid;
            QWORD buildid;

            t_DoBulid_scenescene()
            {
                charid = 0;
                para =  PARA_DoBuliding;
                ownerid  = 0;
                buildid = 0;//非0表示增加，0表示删除
            }
        };
        
        //请求别人的摊位数据 
        const BYTE PARA_REQSALL = 13;
        struct t_UserReqSall : SceneNull 
        {
            QWORD reqcharid;
            QWORD ackcharid;
            DWORD reqGatewayID;
            t_UserReqSall()
            {
                para = PARA_REQSALL;
                reqcharid = 0;
                ackcharid = 0;
                reqGatewayID = 0;
            }
        };
        
        //锁定物品
        const BYTE PARA_PURCHASE_LOCK_ITEM = 14;
        struct t_UserPurchaseLockItem : SceneNull 
        {
            //请求购买者id
            QWORD reqcharid;
            //被购买者id
            QWORD ackcharid;
            //摊位id
            DWORD cellID;
            t_UserPurchaseLockItem()
            {
                para = PARA_PURCHASE_LOCK_ITEM;
                reqcharid = 0;
                ackcharid = 0;
                cellID = 0;
            }
        };
         
        //扣除价格
        const BYTE PARA_PURCHASE_PRICE = 15;
        struct t_UserPurchasePrice : SceneNull 
        {
            //请求购买者id
            QWORD reqcharid;
            //被购买者id
            QWORD ackcharid;
            //价格(总的)
            DWORD price;
            //道具id
            DWORD item;
            //数量(暂时用来判断包裹)
            DWORD num;
            //摊位格子id
            DWORD cellID;
            t_UserPurchasePrice()
            {
                para = PARA_PURCHASE_PRICE;
                reqcharid = 0;
                ackcharid = 0;
                price = 0;
                item = 0;
                num = 0;
                cellID = 0;
            }
        };
         
        //解锁道具
        const BYTE PARA_PURCHASE_UNLOCK_ITEM = 16;
        struct t_UserPurchaseUnlockeItem : SceneNull
        {
            //请求购买者id
            QWORD reqcharid;
            //被购买者id
            QWORD ackcharid;
            //购买者昵称
            char name[MAX_NAMESIZE+1]; 
            //摊位格子id
            DWORD  cellID;
            //是否扣除钱成功
            bool deductFlg;
            t_UserPurchaseUnlockeItem()
            {
                para = PARA_PURCHASE_UNLOCK_ITEM;
                reqcharid = 0;
                ackcharid = 0;
                bzero(name,sizeof(name));
                cellID = 0;
                deductFlg = false;
            }
        };
        
        //转移道具
        const BYTE PARA_PURCHASE_SHIFT_ITEM = 17;
        struct t_UserPurchaseShiftItem : SceneNull 
        {
            //请求购买者id
            QWORD reqcharid;
            //道具id
            DWORD itemID;
            //道具数量
            DWORD itemNum;
            t_UserPurchaseShiftItem()
            {
                para = PARA_PURCHASE_SHIFT_ITEM;
                reqcharid = 0;
                itemID = 0;
                itemNum = 0;
            }
        };
        

    };
};

#pragma pack()

#endif

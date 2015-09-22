#ifndef _RecordCommand_h_
#define _RecordCommand_h_

#include "zNullCmd.h"
#include "Command.h"
#include "CharBase.h"
#include "common.h"
#include "messageType.h"

#pragma pack(1)

namespace CMD
{

    namespace RECORD
    {

        struct FamilyBase
        {
            QWORD m_familyID;
            QWORD m_charid;
            char m_strName[50];
            DWORD m_icon;
            DWORD  m_limmitType;
            DWORD m_lowLevel;
            DWORD m_highLevel;
            DWORD m_level;
            DWORD m_ranking;
            DWORD m_lastranking;
            char m_notice[500];
            DWORD m_createtime;

            FamilyBase()
            {
                m_familyID = 0;
                m_charid = 0;
                m_icon = 0;
                m_limmitType = 0;
                m_lowLevel = 0;
                m_highLevel = 0;
                m_level = 1;
                m_ranking =0;
                m_lastranking = 0;
                m_createtime = 0;
                memset(m_strName,0,sizeof(m_strName));
                memset(m_notice,0,sizeof(m_notice));
            }

        }__attribute__ ((packed));
        struct FamilyApplyData
        {

            QWORD m_ID;
            DWORD m_timer;
            FamilyApplyData()
            {
                m_ID = 0;
                m_timer =0;
            }
            
        }__attribute__ ((packed));


#if 0
        const BYTE CMD_LOGIN = 1;
        const BYTE CMD_GATE = 2;
        const BYTE CMD_SCENE = 3;
        const BYTE CMD_SESSION = 4;
        const BYTE CMD_SUPER = 5;
#endif      
        struct RecordNull : t_NullCmd
        {
            RecordNull()
            {
                cmd = RECORDCMD;
            }
        };

        //////////////////////////////////////////////////////////////
        /// 登陆档案服务器指令
        //////////////////////////////////////////////////////////////
        const BYTE PARA_LOGIN = 1;
        struct t_LoginRecord : RecordNull 
        {
            WORD wdServerID;
            WORD wdServerType;
            t_LoginRecord()	
            {
                para = PARA_LOGIN;
                wdServerID = 0;
                wdServerType = 0;
            }
        };
        //////////////////////////////////////////////////////////////
        /// 登陆档案服务器指令
        //////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////
        /// 档案服务器和网关交互的指令
        //////////////////////////////////////////////////////////////
        const BYTE PARA_GATE_CREATECHAR  = 2;
        struct t_CreateChar_GateRecord : public RecordNull 
        {
            DWORD accid;
            char  name[MAX_NAMESIZE];		/// 角色名称
            DWORD createip;				/// 创建角色时的ip
            char  password[MAX_PASSWORD];
            BYTE  bySex;  // 性别 0未定义 1男 2女
            DWORD flatid; // 平台id
            char  phone_uuid[100]; // 设备uuid
            WORD  type;//帐号登陆
            char  account[MAX_ACCNAMESIZE];//数字帐号
            t_CreateChar_GateRecord()  
            {
                para = PARA_GATE_CREATECHAR;
                bzero(name, sizeof(name));
                bzero(password, sizeof(password));
                createip = 0;
                accid = 0;
                bySex = 0;
                flatid = 0;
                bzero(phone_uuid,sizeof(phone_uuid));
                type = 0;
                bzero(account, sizeof(account));
            };
        };

        const BYTE PARA_GATE_CREATECHAR_RETURN = 3;
        struct t_CreateChar_Return_GateRecord : public RecordNull 
        {
            DWORD accid;						/// 账号
            QWORD charid;
            WORD acctype;	                  //平台类型
            char account[MAX_ACCNAMESIZE+1];  //玩家账号
            BYTE retcode;						/// 返回代码，0成功 1失败 2账号已有角色 3角色名称重复

            t_CreateChar_Return_GateRecord() 
            {
                para = PARA_GATE_CREATECHAR_RETURN;
                accid = 0;
                charid = 0;
                acctype = 0;
                bzero(account, sizeof(account));
                retcode = 0;
            };
        };		

        const BYTE PARA_GATE_PLAYERNUM = 4;
        struct t_SynPlayerNum_GateRecord : public RecordNull 
        {
            DWORD playerNum;
            t_SynPlayerNum_GateRecord() 
            {
                para = PARA_GATE_PLAYERNUM;
                playerNum = 0;
            };
        };		


        //////////////////////////////////////////////////////////////
        /// 档案服务器和网关交互的指令
        //////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////
        /// 档案服务器和场景交互的指令
        //////////////////////////////////////////////////////////////

        const BYTE PARA_SCENE_FRESHUSER = 5; 
        struct t_freshUser_SceneRecord : RecordNull 
        {   
            QWORD charid;
            DWORD accid;
            DWORD scene_id;

            t_freshUser_SceneRecord()
            {
                para = PARA_SCENE_FRESHUSER;
                charid = 0;
                accid = 0;
                scene_id = 0;
            }
        };

        // 克隆角色，向数据库插入记录
        const BYTE PARA_CLONE_USER_WRITE = 6; 
        struct t_Clone_WriteUser_SceneRecord : RecordNull 
        {   
            DWORD accid;
            QWORD charid;/// 角色
            char prefix[MAX_NAMESIZE];
            DWORD start_index;
            DWORD finish_index;
            CharBase    charbase;               /// 存档的基本信息
            DWORD      dataSize;                ///存档二进制的大小
            char        data[0];                ///存档的二进制数据
            t_Clone_WriteUser_SceneRecord() 
            {   
                para = PARA_CLONE_USER_WRITE;
                bzero(&charbase , sizeof(charbase));
                dataSize = 0;
                accid = 0;
                charid = 0;
                bzero(prefix,MAX_NAMESIZE);
                start_index = 0;
                finish_index = 0;
            }
            DWORD getSize() {return sizeof(*this) + dataSize;}
        };

        // 保存角色数据
        const BYTE PARA_SCENE_USER_WRITE = 7;
        struct t_WriteUser_SceneRecord : RecordNull 
        {
            QWORD charid;
            DWORD dwMapTempID;					/// 地图临时ID
            CharBase    charbase;				/// 存档的基本信息
            DWORD      dataSize;				///存档二进制的大小
            char        data[0];				///存档的二进制数据
            t_WriteUser_SceneRecord()
            {
                para = PARA_SCENE_USER_WRITE;
                charid = 0;
                dwMapTempID = 0;
                bzero(&charbase , sizeof(charbase));
                dataSize = 0;
            }
        };

        // 刷新广告位数据
        const BYTE PARA_SCENE_USER_ADVERTISE = 8;
        struct t_AdvertiseUser_SceneRecord : RecordNull 
        {
            QWORD charid;
            bool  addFlg;
            DWORD      datasize;				///摊位数据大小
            char        data[0];				///摊位数据
            t_AdvertiseUser_SceneRecord()
            {
                para = PARA_SCENE_USER_ADVERTISE;
                charid = 0;
                addFlg = true;
                datasize = 0;
            }
        };

        //随机路人
        const BYTE RAND_PASSER_BY = 0;
        //随机好友
        const BYTE RAND_Friend = 1;
        // 请求报纸数据
        const BYTE PARA_SCENE_USER_REQUIRE_PAPER = 9;
        struct t_RequirePaperUser_SceneRecord : RecordNull 
        {
            QWORD charid;
            BYTE randType;
            t_RequirePaperUser_SceneRecord()
            {
                para = PARA_SCENE_USER_REQUIRE_PAPER;
                charid = 0;
                randType = RAND_PASSER_BY;
            }
        };


        // 刷新报纸数据
        const BYTE PARA_SCENE_USER_PAPER = 10;
        struct t_PaperUser_SceneRecord : RecordNull 
        {
            QWORD charid;
            DWORD      datasize;				///报纸数据大小
            char        data[0];				///报纸数据
            t_PaperUser_SceneRecord()
            {
                para = PARA_SCENE_USER_PAPER;
                charid = 0;
                datasize = 0;
            }
        };
        //scene->record 维护好友关系
        const BYTE PARA_SET_RELATION = 11;
        struct t_userrelationchange_scenerecord : RecordNull
        {
            QWORD charidA;
            QWORD charidB;
            BYTE  type;//0,加好友；1，删除好友
            t_userrelationchange_scenerecord()
            {
                para =  PARA_SET_RELATION;


                charidA = 0;
                charidB = 0;
                type = 0;
            }
        };
        const BYTE   PARA_FAMILYBASE = 12;
        struct t_WriteFamily_SceneRecord : RecordNull
        {
            t_WriteFamily_SceneRecord()
            {
                para =  PARA_FAMILYBASE;

            }
            FamilyBase m_base;
        };

        const BYTE   PARA_FAMILYBASE_CREATE_RETURN = 13;
        struct t_WriteFamily_RecordScene_Create_Return : RecordNull
        {
            t_WriteFamily_RecordScene_Create_Return()
            {
                para =  PARA_FAMILYBASE_CREATE_RETURN;
                ret = 0;
                charid = 0;

            }
            QWORD charid;
            BYTE  ret;

        };







#if 0

#ifdef _TEST_DATA_LOG
        enum enumWriteBackTest_Type
        {
            NEWCHAR_WRITEBACK,//新角色插入
            LEVELUP_WRITEBACK,//升级
            DEATH_WRITEBACK,//死亡
            HP_WRITEBACK,//HP
            MP_WRITEBACK,//MP
            SP_WRITEBACK,//SP
        };
        const BYTE PARA_SCENE_INSERT_CHARTEST = 4;
        struct t_Insert_CharTest_SceneRecord : t_NullCmd
        {
            char name[MAX_NAMESIZE];				/// 角色名称
            DWORD level;							/// 角色等级
            CharTest    chartest;				///存档数据
            t_Insert_CharTest_SceneRecord() : t_NullCmd(CMD_SCENE, PARA_SCENE_INSERT_CHARTEST)
            {
                bzero(&chartest , sizeof(chartest));
                bzero(name, sizeof(name));
            }
        };
        const BYTE PARA_SCENE_UPDATE_CHARTEST = 5;
        struct t_Update_CharTest_SceneRecord : t_NullCmd
        {
            char name[MAX_NAMESIZE];				/// 角色名称
            DWORD level;							/// 角色等级
            CharTest    chartest;				///存档数据
            t_Update_CharTest_SceneRecord() : t_NullCmd(CMD_SCENE, PARA_SCENE_UPDATE_CHARTEST)
            {
                bzero(&chartest , sizeof(chartest));
                bzero(name, sizeof(name));
            }
        };
        const BYTE PARA_SCENE_DELETE_CHARTEST = 6;
        struct t_Delete_CharTest_SceneRecord : t_NullCmd
        {
            char name[MAX_NAMESIZE];				/// 角色名称
            DWORD level;							/// 角色等级
            t_Delete_CharTest_SceneRecord()	: t_NullCmd(CMD_SCENE, PARA_SCENE_DELETE_CHARTEST)
            {
                bzero(name, sizeof(name));
                level = 0;
            }
        };
        const BYTE PARA_SCENE_READ_CHARTEST = 7;
        struct t_Read_CharTest_SceneRecord : t_NullCmd
        {
            char name[MAX_NAMESIZE];				/// 角色名称
            DWORD level;							/// 角色等级
            CharTest    chartest;				///存档数据
            t_Read_CharTest_SceneRecord() : t_NullCmd(CMD_SCENE, PARA_SCENE_READ_CHARTEST)
            {
                bzero(&chartest , sizeof(chartest));
                bzero(name, sizeof(name));
            }
        };
#endif
#endif
        //////////////////////////////////////////////////////////////
        /// 档案服务器和场景交互的指令
        //////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////
        /// 档案服务器和Super服务器交互的指令开始
        //////////////////////////////////////////////////////////////


    };

};

#pragma pack()

#endif


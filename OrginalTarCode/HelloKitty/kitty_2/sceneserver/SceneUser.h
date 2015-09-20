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
#include "SessionCommand.h"
#include "CharBase.h"
#include "CounterManager.h"
#include "zTime.h"
#include "RecordCommand.h"
#include "zSerialize.h"
#include "zCmdBuffer.h"
#include "common.h"
#include "UTrade.h"
#include "UStoreHouse.h"

class SceneUser 
{
	public:
		friend class SceneUserManager;
		
		DWORD accid;
		QWORD charid;
		char  nickname[MAX_NAMESIZE+1];
		CharBase charbase;
		CounterManager cm; // 角色相关计数管理器
		UTrade _trade;  // 贸易
		UStoreHouse _store_house; //仓库
		char lastSaveMD5[16];

		DWORD   dwLastSaveTime; //上次存档时间
		DWORD	dwOnlineTime;	//在线时长
		
		SceneUser(SceneTask *gate);

		virtual ~SceneUser();

		bool reg(const CMD::SESSION::t_regUser_SceneSession* cmd);
		bool unreg();//注销
		// 从charbase和二进制数据克隆一个玩家
		bool clone(CharBase charbase,std::string allbinary);
		// 获取该角色的二进制信息
		std::string getAllBinary();

		// 登录注销,scene -> session
		bool reg_unreg(const BYTE retcode);

		std::string getBinaryArchive();
		void setupBinaryArchive(const HelloKittyMsgData::Serialize& binary);
		DWORD saveBinaryArchive(unsigned char *out , const int maxsize);
		bool sendCmdToMe(const void *pstrCmd, const int nCmdLen) const;
		bool save();
		bool sendCmdToGateway(const void *pstrCmd, const int nCmdLen) const;

		bool online(std::string phone_uuid,SceneTask* _gate);
		void offline();
		void onlineInit();

		//存档在线时长
		void saveOnlineTime();

		bool is_online(){return _online;}

		DWORD getStoreLimit();
	private:
		SceneTask *gate;

		bool _online; //玩家在线状态
		bool needSave;
		char lastSaveCharBaseMD5[16];
};
#endif

/**
 * \file	RecordUserManager.h
 * \version  	$Id: RecordUserManager.h 64 2013-04-23 02:05:08Z  $
 * \author  	, @ztgame.com 
 * \date 	2007年01月30日 08时15分17秒 CST
 * \brief 	档案用户管理器定义
 *
 * 
 */


#ifndef RECORDUSER_MANAGER_H
#define RECORDUSER_MANAGER_H

#include <unordered_map>
#include <unordered_set>
#include "zSingleton.h"
#include "zMisc.h"
#include "zRWLock.h"
#include "RecordCommand.h"
#include "common.h"

#define MAX_CHAR_ID 9999999

class RecordUser;

class RecordUserM : public Fir::Singleton<RecordUserM>
{
	public:

		/**
		 * \brief 默认构造函数
		 *
		 */
		RecordUserM() 
		{
			maxCharId = 0;
		};

		~RecordUserM();

		bool init();
		bool add(RecordUser* u);
		RecordUser* getUserByCharid(QWORD charid);
		// 加载最大的角色id
		bool loadMaxCharId();

		bool cloneSaveChars(const CMD::RECORD::t_Clone_WriteUser_SceneRecord *rev);
        bool loadrelation();
        void synPlayerNum();

	private:
        
		typedef std::unordered_map<QWORD, RecordUser*> RecordUserHashmap;
		typedef RecordUserHashmap::iterator RecordUserHashmap_iterator;
		typedef RecordUserHashmap::value_type RecordUserHashmap_pair;
		RecordUserHashmap userMap;
		QWORD maxCharId; // 本区最大的charid;
		zRWLock rwlock_maxcharid; // maxCharId的读写锁
		/**
		 * \brief 互斥变量
		 *
		 */
		zMutex mlock;

	public:
		QWORD generateCharId()
		{  
			zRWLock_scope_wrlock lock(rwlock_maxcharid); // 获取写锁
			maxCharId++;
            return maxCharId;
		}   
};

#endif

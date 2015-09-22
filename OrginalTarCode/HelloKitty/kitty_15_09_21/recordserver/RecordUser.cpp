/**
 * \file: RecordUser.cpp
 * \version  $Id: RecordUser.cpp 64 2013-04-23 02:05:08Z  $
 * \author  , @ztgame.com 
 * \date 2007年01月30日 06时37分12秒 CST
 * \brief 档案对象
 *
 * 
 */


#include "Fir.h"
#include "zDBConnPool.h"
#include "RecordServer.h"
#include "RecordUser.h"
#include "RecordTask.h"
#include "zMemDB.h"

RecordUser::RecordUser()
{
	charid = 0;
	bzero(nickname,sizeof(nickname));
	
	acctype = 0;
	bzero(account,sizeof(account));
	level = 0;
}

RecordUser::~RecordUser()
{
}

bool RecordUser::readCharBase()
{
	using namespace CMD::RECORD;

	connHandleID handle = RecordService::dbConnPool->getHandle();
	if ((connHandleID)-1 == handle)
	{
		Fir::logger->error("[DB]不能获取数据库句柄");
		return false;
	}

	struct ReadData
	{
		ReadData()
		{
			role_size = 0;
			bzero(role, sizeof(role));
		}
		CharBase charbase;
		DWORD role_size;//角色档案数据大小
		unsigned char role[zSocket::MAX_DATASIZE];//角色档案数据,二进制数据
		
	}__attribute__ ((packed)) read_data;

	char where[128]={0};
	snprintf(where, sizeof(where) - 1, "f_charid=%lu", this->charid);
	unsigned int retcode = RecordService::dbConnPool->exeSelectLimit(handle, "t_charbase", record_charbase, where, "f_charid DESC", 1, (BYTE *)(&read_data));

	RecordService::dbConnPool->putHandle(handle);//释放handler
	if (1 != retcode)
	{
		Fir::logger->error("[角色读写]:0,charid=%lu,读取档案失败，没有找到记录",this->charid);
		return false;
	}

	this->charid = read_data.charbase.charid;
	strncpy(this->nickname, read_data.charbase.nickname, MAX_NAMESIZE+1);
	this->acctype = read_data.charbase.acctype;
	strncpy(this->account, read_data.charbase.account, MAX_ACCNAMESIZE+1);
	this->level = read_data.charbase.level;

	zMemDB* redishandle = zMemDBPool::getMe().getMemDBHandle(read_data.charbase.charid%MAX_MEM_DB+1);
	if (redishandle==NULL)
	{
		CharBase& tmp = read_data.charbase;
		Fir::logger->error("[读取角色],获取内存数据库失败，acctype=%u,account=%s,charid=%lu,nickname=%s",tmp.acctype,tmp.account,tmp.charid,tmp.nickname);
		return false;
	}

	// 同步
	if (!redishandle->setBin("charbase", read_data.charbase.charid, "charbase", (const char*)&read_data.charbase, sizeof(read_data.charbase)))
	{
		CharBase& tmp = read_data.charbase;
		Fir::logger->error("[读取角色],同步内存数据库charbase失败,in readCharBase，acctype=%u,account=%s,charid=%lu,nickname=%s",tmp.acctype,tmp.account,tmp.charid,tmp.nickname);
		return false;
	}

	if (!redishandle->setBin("charbase", read_data.charbase.charid, "allbinary", (const char*)read_data.role, read_data.role_size))
	{
		CharBase& tmp = read_data.charbase;
		Fir::logger->error("[读取角色],同步内存数据库allbinary失败，acctype=%u,account=%s,charid=%lu,nickname=%s",tmp.acctype,tmp.account,tmp.charid,tmp.nickname);
		return false;
	}
    syncBaseMemDB();
	Fir::logger->trace("[角色读写],charid=%lu,%s, 找到合格的角色记录", read_data.charbase.charid, read_data.charbase.nickname);
	Fir::logger->debug("读取档案服务器数据,压缩数据大小(size = %u)" , read_data.role_size);
	return true;
}

bool RecordUser::syncBaseMemDB()
{
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if (handle==NULL) 
	{
		return false;
	}

	if (!handle->setInt("rolebaseinfo",acctype, account, charid)) return false;

	if(!handle->set("rolebaseinfo", this->charid, "nickname",nickname)) return false;

	if (!handle->setInt("rolebaseinfo", this->charid, "state", 0)) return false;

	if(!handle->setInt("rolebaseinfo", this->nickname, "charid", charid)) return false;
	
	if(!handle->setInt("rolebaseinfo", this->charid, "charid", charid)) return false;
    
	if(!handle->setInt("rolebaseinfo", this->charid, "dbserver", RecordService::getMe().getServerID())) return false;

	return true;
}

bool RecordUser::refreshSaveBase(const CMD::RECORD::t_WriteUser_SceneRecord *rev)
{
	connHandleID handle = RecordService::dbConnPool->getHandle();
	if ((connHandleID)-1 == handle)
	{
		Fir::logger->error("不能获取数据库句柄");
		return false;
	}
    
    struct SaveData
	{   
		SaveData()
		{   
			role_size = 0;
			bzero(role, sizeof(role));
			bzero(&charbase,sizeof(charbase));
		}   
		CharBase charbase;
		DWORD role_size;//角色档案数据大小
		unsigned char role[zSocket::MAX_DATASIZE];//角色档案数据,二进制数据
	}__attribute__ ((packed)) save_data;

	save_data.role_size = rev->dataSize;
	bcopy(&rev->charbase, &save_data.charbase, sizeof(CharBase));
	bcopy(&rev->data[0], &save_data.role[0], rev->dataSize);


	char where[128]={0};
	snprintf(where, sizeof(where) - 1, "f_charid=%lu", rev->charid);
	unsigned int retcode = RecordService::dbConnPool->exeUpdate(handle, "t_charbase", record_charbase, (BYTE *)(&save_data), where);
	RecordService::dbConnPool->putHandle(handle);

	if (1 == retcode)
	{
		Fir::logger->trace("[角色读写],charid=%lu,保存档案成功 retcode=%u,role_size=%u", rev->charid, retcode,save_data.role_size);
	}
	else if (((unsigned int)-1) == retcode)
	{
		Fir::logger->error("[角色读写],charid=%lu,0, 保存档案失败 retcode=%u,role_size=%u", rev->charid, retcode,save_data.role_size);
		return false;
	}
    
	zMemDB* redishandle = zMemDBPool::getMe().getMemDBHandle(rev->charbase.charid%MAX_MEM_DB+1);
	if (redishandle==NULL)
	{
		const CharBase& tmp = rev->charbase;
		Fir::logger->error("[读取角色],获取内存数据库失败，acctype=%u,account=%s,charid=%lu,nickname=%s",tmp.acctype,tmp.account,tmp.charid,tmp.nickname);
		return false;
	}

	// 同步
	if (!redishandle->setBin("charbase", rev->charbase.charid, "charbase", (const char*)&rev->charbase, sizeof(rev->charbase)))
	{
		const CharBase& tmp = rev->charbase;
		Fir::logger->error("[读取角色],同步内存数据库charbase失败，in refreshSaveBase, acctype=%u,account=%s,charid=%lu,nickname=%s",tmp.acctype,tmp.account,tmp.charid,tmp.nickname);
		return false;
	}

	if (!redishandle->setBin("charbase", rev->charbase.charid, "allbinary", (const char*)rev->data, rev->dataSize))
	{
		const CharBase& tmp = rev->charbase;
		Fir::logger->error("[读取角色],同步内存数据库allbinary失败，acctype=%u,account=%s,charid=%lu,nickname=%s",tmp.acctype,tmp.account,tmp.charid,tmp.nickname);
		return false;
	}

	return true;
}

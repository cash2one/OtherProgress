#include "RedisMgr.h"

#include <zlib.h>

#include "zMemDBPool.h"
#include "zSocket.h"
#include "common.h"


bool RedisMgr::get_charbase(QWORD charid,CharBase& charbase)
{
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(charid%MAX_MEM_DB+1);
	if (!handle) 
	{    
		Fir::logger->error("[获得charbase失败],找不到内存数据库，charid=%lu",charid);
		return false;
	}    

	if (handle->getBin("charbase",charid,"charbase",(char*)&charbase) == 0)
	{
		Fir::logger->error("[获得charbase失败]，charid=%lu",charid);
		return false;
	}

	return true;
}

DWORD RedisMgr::get_charidbyName(const std::string nickname)
{
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if(NULL == handle) return 0;

	return handle->getInt("rolebaseinfo", nickname.c_str(), "charid");
}

DWORD RedisMgr::get_charid(const QWORD charid)
{
	zMemDB *handle = zMemDBPool::getMe().getMemDBHandle();
	if (!handle)
		return 0;

	return handle->getInt("rolebaseinfo", charid, "charid");
}

bool RedisMgr::get_binary(const QWORD charid, HelloKittyMsgData::Serialize& binary)
{
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(charid%MAX_MEM_DB+1);
	if (!handle) 
	{    
		Fir::logger->error("[获得charbase失败],找不到内存数据库，charid=%lu到",charid);
		return false;
	}  
	
	char input_buf[zSocket::MAX_DATASIZE]={0};
	DWORD input_size = handle->getBin("charbase", charid, "allbinary", (char*)input_buf);
	if(input_size == 0)
		return false;

	return get_binary(charid,input_buf,input_size,binary);
}

bool RedisMgr::get_binary(const QWORD charid,const char* input_buf, DWORD input_size,  HelloKittyMsgData::Serialize& binary)
{
	unsigned char output_buf[MAX_UZLIB_CHAR];
	bzero(output_buf, sizeof(output_buf));
	uLongf output_size = MAX_UZLIB_CHAR;

	int retcode = uncompress(output_buf, &output_size , (Bytef *)input_buf, input_size);
	switch(retcode)
	{   
		case Z_OK:
			Fir::logger->debug("解压缩档案成功(charid=%lu), size = %u, usize = %lu", charid, input_size, output_size);
			break;
		case Z_MEM_ERROR:
		case Z_BUF_ERROR:
		case Z_DATA_ERROR:
			{   
				Fir::logger->error("解压档案失败(charid=%lu), size = %u, uszie = %lu, 错误码 = %d",charid, input_size, output_size, retcode);
				return false;
			}   
			break;
		default:
			{   
				Fir::logger->error("解压档案未知错误(charid=%lu))", charid);
				return false;
			}   
			break;
	}   

	if(!binary.ParseFromArray(output_buf, output_size))
	{   
		Fir::logger->error("解压档案解析失败(charid=%lu))", charid);
		return false;
	}   

	return true;
}

bool RedisMgr::get_puppet(QWORD charid, stPuppet& puppet)
{
	if(!get_charbase(charid,puppet.charbase))
		return false;
	if(!get_binary(charid,puppet.binary))
		return false;
	return true;
}

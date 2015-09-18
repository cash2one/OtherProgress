#include "RedisMgr.h"

#include <zlib.h>

#include "zMemDBPool.h"
#include "zSocket.h"

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
#if 0
bool RedisMgr::get_binary(QWORD charid, Serialize& binary)
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
		return true;

	return get_binary(charid,input_buf,input_size,binary);
}
#endif
#if 0
bool RedisMgr::get_binary(QWORD charid,const char* input_buf, DWORD input_size,  Serialize& binary)
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
#endif
bool RedisMgr::get_puppet(QWORD charid, stPuppet& puppet)
{
	if(!get_charbase(charid,puppet.charbase))
		return false;
#if 0
	if(!get_binary(charid,puppet.binary))
		return false;
#endif
	return true;
}


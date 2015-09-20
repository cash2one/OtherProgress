/**
 * \file	zMemDB.cpp
 * \version  	$Id: zMemDB.cpp 74 2013-04-25 02:28:02Z  $
 * \author  	,
 * \date 	2013年03月19日 17时06分46秒
 * \brief  内存缓存数据库实现文件	
 *
 * 
 */

#include <string.h>
#include "Fir.h"
#include "zFirNew.h"
#include "zMetaData.h"
#include "zMemDB.h"
#include "hiredis.h"

zMemDB::zMemDB(const std::string& server, DWORD port, DWORD dbNum, DWORD hashcode):host(server),port(port),dbNum(dbNum),hashcode(hashcode)
{
	c = NULL;
	reply = NULL;
}

zMemDB::~zMemDB()
{
	this->disconn();
}

bool zMemDB::init()
{
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	this->disconn();

	this->c = redisConnectWithTimeout(this->host.c_str(), this->port, timeout);
	if (c->err) {
		Fir::logger->warn("初始化MemDB失败:%s,%d,errno:%s",this->host.c_str(), this->port, c->errstr);
		redisFree(c);
		c = NULL;
		return false;
	} 

	return true;
}

bool zMemDB::disconn()
{
	if (c)
	{
		if (reply) {freeReplyObject(reply); reply = NULL;}
		redisFree(c);c = NULL;
		Fir::logger->debug("[zMemDB]断开MemDB:%s,%d,hashcode:%u",this->host.c_str(), this->port,this->hashcode);
	}
	return true;
}

void zMemDB::debug(const char* func, const char* table, QWORD id,const char* col)
{
	if (col)
		Fir::logger->debug("[MEMDB]:%s  %s:[%lu]:%s",func, table,id,col);
	else if (id)
		Fir::logger->debug("[MEMDB]:%s %s:[%lu]",func, table,id);
	else if (table)
		Fir::logger->debug("[MEMDB]:%s table: %s",func, table);
}

void zMemDB::debug(const char* func, const char* table, const char* key,const char* col)
{
	if (col)
		Fir::logger->debug("[MEMDB]:%s  %s:[%s]:%s",func, table,key,col);
	else if (key)
		Fir::logger->debug("[MEMDB]:%s %s:[%s]",func, table, key);
	else if (table)
		Fir::logger->debug("[MEMDB]:%s table: %s",func, table);
}

DBVarType zMemDB::getInt(const char* table, QWORD id)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id);
#endif

	if (getHandle())
	{
		if (id)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]",table,id);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}
	}

	return getValue(GET_INTEGER);
}

DBVarType zMemDB::getInt(const char* table, const char* key)
{
#ifdef _ZJW_DEBUG
	//this->debug(__FUNCTION__, table, id);
#endif

	if (getHandle())
	{
		if (key)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%s]",table,key);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}
	}

	return getValue(GET_INTEGER);
}

DBVarType zMemDB::getInt(const char* table,QWORD id,const char* col)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:%s",table, id, col);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]",table,id);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}
	}

	return getValue(GET_INTEGER);
}

DBVarType zMemDB::getInt(const char* table,const char* key, const char* col)
{
#ifdef _ZJW_DEBUG
	Fir::logger->debug("%s %s:%s:%s", __FUNCTION__, table, key, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%s]:%s",table, key, col);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%s]",table,key);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}
	}

	return getValue(GET_INTEGER);
}

DBVarType zMemDB::getInt(const char* table, QWORD id, const char* key, const char* col)
{
#ifdef _ZJW_DEBUG
	Fir::logger->debug("%s %s:%s:%s", __FUNCTION__, table, key, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:[%s]:%s",table, id, key, col);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:[%s]",table,id,key);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}
	}

	return getValue(GET_INTEGER);
}

DBVarType zMemDB::get(const char* table, QWORD id)
{

#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id);
#endif

	if (getHandle())
	{
		if (id)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]",table,id);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}
	}

	return getValue(GET_STRING);
}

DBVarType zMemDB::get(const char* table, QWORD id, const char* col)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:%s",table, id, col);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]",table,id);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}
	}

	return getValue(GET_STRING);
}

DWORD zMemDB::getBin(const char* table, QWORD id, char* buf, DWORD len)
{
	DWORD real_len=0;

#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__,table, id);
#endif

	if (getHandle())
	{
		if (id)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]",table,id);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}

		if (!isReplyOK())
		{
			disconn();
			return 0;
		}

		if (reply && reply->type == REDIS_REPLY_STRING)
		{
			if (len == 0)
				memcpy(buf, reply->str, reply->len);
			else
				memcpy(buf, reply->str, len);

			real_len = reply->len;
		}
	}


	return real_len;
}

DWORD zMemDB::getBin(const char* table, QWORD id1, QWORD id2,  const char* col, char* buf, DWORD len)
{
	DWORD real_len=0;

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:[%lu]:%s",table, id1, id2, col);
		}
		else if (id1 && id2)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:%lu",table,id1, id2);
		}
		else if (id1)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]",table,id1);
		}
		else if (id2)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]",table,id2);
		}

		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}

		if (!isReplyOK())
		{
			disconn();
			return 0;
		}

		if (reply && reply->type == REDIS_REPLY_STRING)
		{
			if (len == 0)
				memcpy(buf, reply->str, reply->len);
			else
				memcpy(buf, reply->str, len);

			real_len = reply->len;
		}
	}


	return real_len;
}

DWORD zMemDB::getBin(const char* table, const char* key, char* buf, DWORD len)
{
	DWORD real_len=0;

	if (getHandle())
	{
		if (key)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%s]",table,key);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}

		if (!isReplyOK())
		{
			disconn();
			return 0;
		}

		if (reply && reply->type == REDIS_REPLY_STRING)
		{
			if (len == 0)
				memcpy(buf, reply->str, reply->len);
			else
				memcpy(buf, reply->str, len);

			real_len = reply->len;
		}
	}


	return real_len;
}

DWORD zMemDB::getBin(const char* table, QWORD id, const char* col, char* buf, DWORD len)
{
	DWORD real_len = 0;

#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__,table, id,col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:%s",table, id, col);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]",table,id);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}

		if (!isReplyOK())
		{
			disconn();
			return 0;
		}

		if (reply && reply->type == REDIS_REPLY_STRING)
		{
			if (len == 0)
				memcpy(buf, reply->str, reply->len);
			else
				memcpy(buf, reply->str, len);

			real_len = reply->len;
		}
		else if (reply && reply->type == REDIS_REPLY_NIL)
		{
			return 0;
		}
	}

	return real_len;
}

DWORD zMemDB::getBin(const char* table, const char* key, const char* col, char* buf, DWORD len)
{
	DWORD real_len = 0;

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%s]:%s",table, key, col);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%s]",table,key);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}

		if (!isReplyOK())
		{
			disconn();
			return 0;
		}

		if (reply && reply->type == REDIS_REPLY_STRING)
		{
			if (len == 0)
				memcpy(buf, reply->str, reply->len);
			else
				memcpy(buf, reply->str, len);

			real_len = reply->len;
		}
		else if (reply && reply->type == REDIS_REPLY_NIL)
		{
			return 0;
		}
	}

	return real_len;
}

DWORD zMemDB::getBin(const char* table, QWORD id, const char* key, const char* col, char* buf, DWORD len)
{
	DWORD real_len = 0;

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:[%s]:%s",table, id, key, col);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "GET %s:[%lu]:[%s]",table,id,key);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "GET %s",table);
		}

		if (!isReplyOK())
		{
			disconn();
			return 0;
		}

		if (reply && reply->type == REDIS_REPLY_STRING)
		{
			if (len == 0)
				memcpy(buf, reply->str, reply->len);
			else
				memcpy(buf, reply->str, len);

			real_len = reply->len;
		}
		else if (reply && reply->type == REDIS_REPLY_NIL)
		{
			return 0;
		}
	}

	return real_len;
}

bool zMemDB::setInt(const char* table, QWORD id,long long value)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id);
#endif

	if (getHandle())
	{
		if (id)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu] %lld",table,id, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %lld",table, value);
		}


		PROCESS_REPLY_ERROR
	}

	return false;
}

bool zMemDB::setInt(const char* table, QWORD id, const char* col, long long value)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu]:%s %lld",table,id, col,value);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu] %lld",table,id, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %lld",table, value);
		}

		PROCESS_REPLY_ERROR
	}

	return false;
}

bool zMemDB::setInt(const char* table, const char* key, const char* col, long long value)
{
#ifdef _ZJW_DEBUG
//	this->debug(__FUNCTION__, table, id, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%s]:%s %lld",table,key,col,value);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%s] %lld",table,key, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %lld",table, value);
		}

		PROCESS_REPLY_ERROR
	}

	return false;
}

bool zMemDB::setInt(const char* table, QWORD id, const char* key, const char* col, long long value)
{
#ifdef _ZJW_DEBUG
//	this->debug(__FUNCTION__, table, id, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu]:[%s]:%s %lld",table,id,key,col,value);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu]:[%s] %lld",table,id,key, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %lld",table, value);
		}

		PROCESS_REPLY_ERROR
	}

	return false;
}

bool zMemDB::set(const char* table, QWORD id, const char* value)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id);
#endif


	if (getHandle())
	{
		if (id)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu] %s",table,id, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %s",table, value);
		}

		PROCESS_REPLY_ERROR
	}

	return false;
}

bool zMemDB::set(const char* table, QWORD id, const char* col, const char* value)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id,col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu]:%s %s",table, id, col, value);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu] %s",table,id, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %s",table, value);
		}

		PROCESS_REPLY_ERROR
	}

	return false;
}

bool zMemDB::setBin(const char* table, QWORD id, const char* col, const char* value, int len)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id,col);
#endif

	char tmp[1024]={0};
	if (getHandle())
	{
		if (col)
		{
			//此处米深入研究，直接传参，会导致命令执行不成功，只能先临时这样处理下
			snprintf(tmp, 1024, "%s:[%lu]:%s", table, id, col);		
			reply = (redisReply*)redisCommand(c, "SET %s %b",tmp,value, len);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu] %b",table,id, value,len);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %b",table, value,len);
		}

		PROCESS_REPLY_ERROR	
	}

	return false;
}

bool zMemDB::setBin(const char* table, const char* key, const char* col, const char* value, int len)
{
#ifdef _ZJW_DEBUG
	//this->debug(__FUNCTION__, table, id,col);
#endif

	char tmp[1024]={0};
	if (getHandle())
	{
		if (col)
		{
			//此处米深入研究，直接传参，会导致命令执行不成功，只能先临时这样处理下
			snprintf(tmp, 1024, "%s:[%s]:%s", table, key, col);		
			reply = (redisReply*)redisCommand(c, "SET %s %b",tmp,value, len);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%s] %b",table,key, value,len);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %b",table, value,len);
		}

		PROCESS_REPLY_ERROR	
	}

	return false;
}

bool zMemDB::setBin(const char* table, QWORD id, const char* value, int len)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id);
#endif

	if (getHandle())
	{
		if (id)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu] %b",table,id, value, len);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %b",table, value,len);
		}

		PROCESS_REPLY_ERROR	
	}

	return false;
}

bool zMemDB::setBin(const char* table, QWORD id1, QWORD id2, const char* col, const char* value, int len)
{

	if (getHandle())
	{
		char tmp[1024]={0};
		if (col)
		{
			snprintf(tmp, 1024, "%s:[%lu]:[%lu]:%s", table, id1, id2, col);		
			reply = (redisReply*)redisCommand(c, "SET %s %b",tmp,value, len);
		}
		else if (id1 && id2)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu]:%lu %b",table,id1, id2, value, len);
		}
		else if (id1)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu] %b",table,id1, value, len);
		}
		else if (id2)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu] %b",table,id2, value, len);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %b",table, value,len);
		}

		PROCESS_REPLY_ERROR	
	}

	return false;
}
bool zMemDB::setBin(const char* table, const char* key, const char* value, int len)
{
#ifdef _ZJW_DEBUG
	//this->debug(__FUNCTION__, table, id);
#endif

	if (getHandle())
	{
		if (key)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%s] %b",table,key, value, len);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %b",table, value,len);
		}

		PROCESS_REPLY_ERROR	
	}

	return false;
}
bool zMemDB::setBin(const char* table, QWORD id, const char* key, const char* col, const char* value, int len)
{

	if (getHandle())
	{
		char tmp[1024]={0};
		if (col)
		{
			snprintf(tmp, 1024, "%s:[%lu]:[%s]:%s", table, id, key, col);		
			reply = (redisReply*)redisCommand(c, "SET %s %b",tmp,value, len);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "SET %s:[%lu]:[%s] %b",table,id,key, value,len);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SET %s %b",table, value,len);
		}

		PROCESS_REPLY_ERROR	
	}

	return false;
}
bool zMemDB::getSet(const char* table, QWORD id, const char* myset, std::set<std::string>& valueset, DWORD num)
{
	if (!num)
		return false;
#ifdef _PQQ_DEBUG
	this->debug(__FUNCTION__,table, id,myset);
#endif

	char tmp[1024]={0};
	if (getHandle())
	{
		if (myset)
		{
			snprintf(tmp, 1024, "%s:[%lu]:%s", table, id, myset);
			reply = (redisReply*)redisCommand(c, "SRANDMEMBER %s %u",tmp, num);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SRANDMEMBER %s:[%lu] %u",table,id,num);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SRANDMEMBER %s %u",table,num);
		}

		if (!isReplyOK())
		{
			disconn();
			return false;
		}

		if (reply && reply->type == REDIS_REPLY_ARRAY)
		{
			for (DWORD j = 0; j < reply->elements; j++) 
			{
				valueset.insert(reply->element[j]->str);
			}

			if (valueset.empty())
			{
				return false;
			}

			return true;

		}
		else if (reply && reply->type == REDIS_REPLY_NIL)
		{
			return false;
		}
	}

	return true;

}

bool zMemDB::getSet(const char* table, QWORD id, const char* myset, std::set<QWORD>& valueset, DWORD num)
{
	if (!num)
		return false;
#ifdef _PQQ_DEBUG
	this->debug(__FUNCTION__,table, id,myset);
#endif

	char tmp[1024]={0};
	if (getHandle())
	{
		if (myset)
		{
			snprintf(tmp, 1024, "%s:[%lu]:%s", table, id, myset);
			reply = (redisReply*)redisCommand(c, "SRANDMEMBER %s %u",tmp, num);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SRANDMEMBER %s:[%lu] %u",table,id,num);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SRANDMEMBER %s %u",table,num);
		}

		if (!isReplyOK())
		{
			disconn();
			return false;
		}

		if (reply && reply->type == REDIS_REPLY_ARRAY)
		{
			for (DWORD j = 0; j < reply->elements; j++) 
			{
				valueset.insert(strtoull(reply->element[j]->str, NULL, 10));
			}

			if (valueset.empty())
			{
				return false;
			}

			return true;

		}
		else if (reply && reply->type == REDIS_REPLY_NIL)
		{
			return false;
		}
	}

	return true;


}


bool zMemDB::setSet(const char* table, QWORD id, const char* myset, const char* value)
{
#ifdef _PQQ_DEBUG
	this->debug(__FUNCTION__, table, id, myset);
#endif

	char tmp[1024]={0};
	if (getHandle())
	{
		if (myset)
		{
			snprintf(tmp, 1024, "%s:[%lu]:%s", table, id, myset);	
			reply = (redisReply*)redisCommand(c, "SADD %s %s",tmp,value);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SADD %s:[%lu] %s",table,id, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SADD %s %s",table, value);
		}

		PROCESS_REPLY_ERROR	
	}

	return false;
	
}

bool zMemDB::setSet(const char* table, QWORD id, const char* myset, const QWORD value)
{
#ifdef _PQQ_DEBUG
	this->debug(__FUNCTION__, table, id, myset);
#endif

	char tmp[1024]={0};
	if (getHandle())
	{
		if (myset)
		{
			snprintf(tmp, 1024, "%s:[%lu]:%s", table, id, myset);	
			reply = (redisReply*)redisCommand(c, "SADD %s %lu",tmp,value);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SADD %s:[%lu] %lu",table,id, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SADD %s %lu",table, value);
		}

		PROCESS_REPLY_ERROR	
	}

	return false;
	
}

template <class T>
bool zMemDB::setSet(const char* table, QWORD id, const char* myset, const std::set<T>& srcset)
{
	if (srcset.empty())
	{
		return false;
	}
	std::ostringstream oss, os1;
	oss<<"SADD"<<" ";
	typename std::set<T>::iterator it = srcset.begin();
	for ( ;it != srcset.end();)
	{
		os1<<*it;
		if (++it != srcset.end())
		{
			os1<<" ";
		}
	}
	char tmp[1024]={0};
	if (getHandle())
	{
		if (myset)
		{
			snprintf(tmp, 1024, "%s:[%lu]:%s", table, id, myset);
			oss<<tmp<<" "<<os1.str().c_str();
			reply = (redisReply*)redisCommand(c, oss.str().c_str());
		}
		else if (id)
		{
			oss<<table<<":"<<"["<<id<<"]"<<" "<<os1.str().c_str();
			reply = (redisReply*)redisCommand(c, oss.str().c_str());
		}
		else
		{
			oss<<table<<" "<<os1.str().c_str();
			reply = (redisReply*)redisCommand(c, oss.str().c_str());
		}

		PROCESS_REPLY_ERROR
	}

	return false;
}

bool zMemDB::isReplyOK()
{
	if (!reply) return false;
	return true;
}

DBVarType zMemDB::getValue(int type)
{
	DBVarType ret;
	ret.setValid(false);

	if (!isReplyOK()) 
	{
		disconn();
		return ret;
	}

	switch (reply->type)
	{
		case REDIS_REPLY_STATUS:
			{
			}
			break;
		case REDIS_REPLY_ERROR:
			{
			}
			break;
		case REDIS_REPLY_INTEGER:
			{
				if (type == GET_INTEGER)
				{    
					ret.val_us = reply->integer;
					ret.val_short = reply->integer;
					ret.val_int = reply->integer;
					ret.val_dword = reply->integer;
					ret.val_ul = reply->integer;
					ret.val_qword = reply->integer;
					ret.val_sqword = reply->integer;
					ret.val_long = reply->integer;
					ret.val_byte = reply->integer;
				} 
			}
			break;
		case REDIS_REPLY_NIL:
			{
			}
			break;
		case REDIS_REPLY_STRING:
			{//只处理基本类型，INT,STRING,BIN
				if (type == GET_INTEGER)
				{
					ret.val_us = atoi(reply->str);
					ret.val_short = atoi(reply->str);
					ret.val_int = atoi(reply->str);
					ret.val_dword = atoi(reply->str);
					ret.val_ul = strtoul(reply->str, NULL, 10);
					ret.val_qword = strtoull(reply->str, NULL, 10);
					ret.val_sqword = strtoll(reply->str, NULL, 10);
					ret.val_long = atol(reply->str);
					ret.val_byte = atoi(reply->str);
				}
				else if (type == GET_STRING)
				{
					ret.val_bin.resize(reply->len+1);
					memset(&ret.val_bin[0], 0, reply->len+1);
					memcpy(&ret.val_bin[0], reply->str, reply->len);
					ret.val_pstr = &ret.val_bin[0];
				}
				else 
				{//default,暂时未用
					ret.val_bin.resize(reply->len);
					memcpy(&ret.val_bin[0], reply->str, reply->len);
				}
			}
			break;
		case REDIS_REPLY_ARRAY:
			{
				//set,vector,list,不在此处理
			}
		default:
			break;
	}

	// 由内部函数调用，暂不做安全性检查
	freeReplyObject(reply);
	reply = NULL;

	return ret;
}

bool zMemDB::getHandle()
{
	if (!c)
	{
		CHECK_CONNECT_VALID
		Fir::logger->debug("[zMemDB]重连MemDB:%s,%d,hashcode:%u",this->host.c_str(), this->port,this->hashcode);
	}

	if (!c)
	{
		Fir::logger->error("[zMemDB]重连不成功,断开MemDB:%s,%d,hashcode:%u",this->host.c_str(), this->port,this->hashcode);
		return false;
	}

	HANDLE_REPLY_FREE

	return true;
}

bool zMemDB::exec(const char* cmd)
{
	HANDLE_REPLY_FREE
	reply = (redisReply*)redisCommand(c, cmd);
	PROCESS_REPLY_ERROR
}

bool zMemDB::del(const char* table, const char* key, const char* col)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, key, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "DEL %s:[%s]:%s",table, key, col);
		}
		else if (key)
		{
			reply = (redisReply*)redisCommand(c, "DEL %s:[%s]",table,key);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "DEL %s",table);
		}
	}

	PROCESS_REPLY_ERROR
}

bool zMemDB::del(const char* table, QWORD id, const char* col)
{
#ifdef _ZJW_DEBUG
	this->debug(__FUNCTION__, table, id, col);
#endif

	if (getHandle())
	{
		if (col)
		{
			reply = (redisReply*)redisCommand(c, "DEL %s:[%lu]:%s",table, id, col);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "DEL %s:[%lu]",table,id);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "DEL %s",table);
		}
	}

	PROCESS_REPLY_ERROR
}

bool zMemDB::checkSet(const char* table, QWORD id, const char* myset, const QWORD value)
{
#ifdef _ALL_SUPER_GM
	this->debug(__FUNCTION__, table, id, myset);
#endif
	char tmp[1024]={0};
	if (getHandle())
	{
		if (myset)
		{
			snprintf(tmp, 1024, "%s:[%lu]:%s", table, id, myset);
			reply = (redisReply*)redisCommand(c, "SISMEMBER %s %lu",tmp,value);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SISMEMBER %s:[%lu] %lu",table,id, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SISMEMBER %s %lu",table, value);
		}
	}
	PROCESS_REPLY_ERROR
}

bool zMemDB::delSet(const char* table, QWORD id, const char* myset, const QWORD value)
{
#ifdef _ALL_SUPER_GM
	this->debug(__FUNCTION__, table, id, myset);
#endif
	char tmp[1024]={0};
	if (getHandle())
	{
		if (myset)
		{
			snprintf(tmp, 1024, "%s:[%lu]:%s", table, id, myset);
			reply = (redisReply*)redisCommand(c, "SREM %s %lu",tmp,value);
		}
		else if (id)
		{
			reply = (redisReply*)redisCommand(c, "SREM %s:[%lu] %lu",table,id, value);
		}
		else
		{
			reply = (redisReply*)redisCommand(c, "SREM %s %lu",table, value);
		}
	}
	PROCESS_REPLY_ERROR
}

DWORD zMemDB::mget(std::vector<DBVarType>& ret, const char* pattern,...)
{
	char buf[2*1024]={0};
	sprintf(buf, "mget %s", pattern);

	va_list ap;

	if (getHandle())
	{
		va_start(ap, pattern);
		reply = (redisReply*)redisvCommand(c, buf, ap);
		va_end(ap);
	}

	if (!isReplyOK())
	{
		disconn();
		return 0;
	}

	DWORD elements = 0;
	switch (reply->type)
	{
		case REDIS_REPLY_STATUS:
			{
			}
			break;
		case REDIS_REPLY_ERROR:
			{
			}
			break;
		case REDIS_REPLY_NIL:
			{
			}
			break;
		case REDIS_REPLY_STRING:
		case REDIS_REPLY_INTEGER:
			{
			}
			break;
		case REDIS_REPLY_ARRAY:
			{
				Fir::logger->debug("reply->elements:%lu", reply->elements);
				elements = reply->elements;
				for (unsigned int i=0; i<reply->elements; i++)
				{
					Fir::logger->debug("reply->elements%d:type:%d,value:%s", i, reply->element[i]->type, reply->element[i]->str);
					DBVarType vr;

					vr.val_us = atoi(reply->element[i]->str);
					vr.val_short = atoi(reply->element[i]->str);
					vr.val_int = atoi(reply->element[i]->str);
					vr.val_dword = atoi(reply->element[i]->str);
					vr.val_ul = strtoul(reply->element[i]->str, NULL, 10);
					vr.val_qword = strtoull(reply->element[i]->str, NULL, 10);
					vr.val_sqword = strtoll(reply->element[i]->str, NULL, 10);
					vr.val_long = atol(reply->element[i]->str);
					vr.val_byte = atoi(reply->element[i]->str);
					vr.val_pstr = &vr.val_bin[0];

					vr.val_bin.resize(reply->element[i]->len+1);
					memset(&vr.val_bin[0], 0, reply->element[i]->len+1);
					memcpy(&vr.val_bin[0], reply->element[i]->str, reply->element[i]->len);
					ret.push_back(vr);
				}
			}
		default:
			break;
	}

	// 由内部函数调用，暂不做安全性检查
	freeReplyObject(reply);
	reply=NULL;
	return elements;
}


DWORD zMemDB::mset(const char* pattern,...)
{
	char buf[2*1024]={0};
	sprintf(buf, "mset %s", pattern);

	va_list ap;

	if (getHandle())
	{
		va_start(ap, pattern);
		reply = (redisReply*)redisvCommand(c, buf, ap);
		va_end(ap);
	}

	PROCESS_REPLY_ERROR
}

DWORD zMemDB::hmset(const char* pattern,...)
{
	char buf[2*1024]={0};
	sprintf(buf, "hmset %s", pattern);

	va_list ap;

	if (getHandle())
	{    
		va_start(ap, pattern);
		reply = (redisReply*)redisvCommand(c, buf, ap); 
		va_end(ap);
	}    

	PROCESS_REPLY_ERROR
}

DWORD zMemDB::hmget(std::vector<DBVarType>& ret, const char* pattern,...)
{
	char buf[2*1024]={0};
	sprintf(buf, "hmget %s", pattern);

	va_list ap;

	if (getHandle())
	{
		va_start(ap, pattern);
		reply = (redisReply*)redisvCommand(c, buf, ap);
		va_end(ap);
	}

	if (!isReplyOK())
	{
		disconn();
		return 0;
	}

	DWORD elements = 0;

	switch (reply->type)
	{
		case REDIS_REPLY_STATUS:
			{
			}
			break;
		case REDIS_REPLY_ERROR:
			{
			}
			break;
		case REDIS_REPLY_NIL:
			{
			}
			break;
		case REDIS_REPLY_STRING:
		case REDIS_REPLY_INTEGER:
			{
			}
			break;
		case REDIS_REPLY_ARRAY:
			{
#ifdef _DEBUG_LBS            
				Fir::logger->debug("reply->elements:%lu", reply->elements);
#endif
				elements = reply->elements;

				for (unsigned int i=0; i<reply->elements; i++)
				{
#ifdef _DEBUG_LBS                   
					Fir::logger->debug("reply->elements%d:type:%d,value:%s", i, reply->element[i]->type, reply->element[i]->str);
#endif
					DBVarType vr;

					vr.val_us = atoi(reply->element[i]->str);
					vr.val_short = atoi(reply->element[i]->str);
					vr.val_int = atoi(reply->element[i]->str);
					vr.val_dword = atoi(reply->element[i]->str);
					vr.val_ul = strtoul(reply->element[i]->str, NULL, 10);
					vr.val_qword = strtoull(reply->element[i]->str, NULL, 10);
					vr.val_sqword = strtoll(reply->element[i]->str, NULL, 10);
					vr.val_long = atol(reply->element[i]->str);
					vr.val_byte = atoi(reply->element[i]->str);
					vr.val_pstr = &vr.val_bin[0];

					vr.val_bin.resize(reply->element[i]->len+1);
					memset(&vr.val_bin[0], 0, reply->element[i]->len+1);
					memcpy(&vr.val_bin[0], reply->element[i]->str, reply->element[i]->len);
					ret.push_back(vr);
				}

				//set,vector,list,不在此处理
			}
		default:
			break;
	}

	// 由内部函数调用，暂不做安全性检查
	freeReplyObject(reply);
	reply=NULL;

	return elements;
}

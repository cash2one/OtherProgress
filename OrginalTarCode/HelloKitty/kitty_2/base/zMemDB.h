/**
 * \file	zMemDB.h
 * \version  	$Id: zMemDB.h 75 2013-04-25 05:10:39Z  $
 * \author  	,
 * \date 	2013年03月19日 16时11分53秒
 * \brief 内存数据库的封装，包含连接，断开连接，发送命令，获取返回值等API的封装
 *
 * 
 */
#ifndef _ZMEMDB_H_
#define _ZMEMDB_H_

#include <string.h>
#include "hiredis.h"
#include "zMetaData.h"
#include <set>

const int GET_INTEGER = 1;
const int GET_STRING =  2; 
const int GET_BIN    =  3;

#define PROCESS_REPLY_ERROR if(reply == NULL) {this->disconn();return false;} \
							if (reply->type == REDIS_REPLY_ERROR) \
							{ \
								freeReplyObject(reply); \
								reply = NULL; \
								return false; \
							} \
							freeReplyObject(reply); \
							reply = NULL; \
							return true;


#define HANDLE_REPLY_FREE if(reply != NULL)  freeReplyObject(reply); \
                                                        reply = NULL; \

#define CHECK_CONNECT_VALID if (!c) init(); \
							
class zMemDB
{
	public:
		zMemDB(const std::string& host, DWORD port, DWORD dbNum, DWORD hashcode);
		~zMemDB();

		bool init();
		bool disconn();
		void debug(const char* func, const char* table=NULL, QWORD id=0,const char* col=NULL);
		void debug(const char* func, const char* table, const char* key=NULL,const char* col=NULL);
		//封装读取LIST,HASHMAP,SET,INT,STRING,BIN等类型数据

		//基础类型访问函数
		// 因redis没有整型，除了自增，自减型以外。所以，变量实际是按字符串保存，取出时由atoll转换
		// 不知道使用模板实现key和id，在内部使用stringstream来实现拼包性能如何，暂时使用参数类型重载
		DBVarType getInt(const char* table, QWORD id);
		DBVarType getInt(const char* table, const char* key);
		DBVarType getInt(const char* table, QWORD id, const char* col);
		DBVarType getInt(const char* table, const char* key, const char* col);
		DBVarType getInt(const char* table, QWORD id, const char* key, const char* col);
		bool setInt(const char* table, QWORD id,long long value);
		bool setInt(const char* table, const char* key,long long value);
		bool setInt(const char* table, QWORD id, const char* col, long long value);
		bool setInt(const char* table, const char* key, const char* col, long long value);
		bool setInt(const char* table, QWORD id, const char* key, const char* col, long long value);


		DBVarType get(const char* table, QWORD id);
		DBVarType get(const char* table, const char* key);
		DBVarType get(const char* table, QWORD id, const char* col);
		DBVarType get(const char* table, const char* key, const char* col);
		bool set(const char* table, QWORD id, const char* value);
		bool set(const char* table, QWORD id, const char* col, const char* value);
		bool set(const char* table, const char* key, const char* value);
		bool set(const char* table, const char* key, const char* col, const char* value);


		//len,为准备读取的大小，len==0时，按实际大小读取，返回值为实际读取大小
		DWORD getBin(const char* table, QWORD id, char* buf, DWORD len=0);
		DWORD getBin(const char* table, const char* key, char* buf, DWORD len=0);
		DWORD getBin(const char* table, QWORD id, const char* col, char* buf, DWORD len=0);
		DWORD getBin(const char* table, const char* key, const char* col, char* buf, DWORD len=0);
		DWORD getBin(const char* table, QWORD id, const char* key, const char* col, char* buf, DWORD len=0);
				
		bool setBin(const char* table, QWORD id, const char* value, int len);
		bool setBin(const char* table, const char* key, const char* value, int len);
		bool setBin(const char* table, QWORD id, const char* col, const char* value, int len);
		bool setBin(const char* table, const char* key, const char* col, const char* value, int len);
		bool setBin(const char* table, QWORD id, const char* key, const char* col, const char* value, int len);
		
		
		// set 操作
		bool getSet(const char* table, QWORD id, const char* myset, std::set<std::string>& valueset, DWORD num);
		bool getSet(const char* table, QWORD id, const char* myset, std::set<QWORD>& valueset, DWORD num);

		bool setSet(const char* table, QWORD id, const char* myset, const char* value);
		bool setSet(const char* table, QWORD id, const char* myset, QWORD value);	
		
		template <class T>
		bool setSet(const char* table, QWORD id, const char* myset, const std::set<T>& srcset);
		
		bool setBin(const char* table, QWORD id1, QWORD id2,  const char* col, const char* value, int len);
		DWORD getBin(const char* table, QWORD id1, QWORD id2,  const char* col, char* buf, DWORD len);

		// strings
		DWORD mset(const char* pattern,...);
		DWORD mget(std::vector<DBVarType>& ret, const char* pattern,...);
		
		// hash
		DWORD hmset(const char* pattern,...);
		DWORD hmget(std::vector<DBVarType>& ret, const char* pattern,...);

		bool del(const char* table, const char* key, const char* col);
		bool del(const char* table, QWORD id, const char* col);

		//查找指定set中的某值是否存在
		bool checkSet(const char* table, QWORD id, const char* myset, const QWORD value);

		//删除指定set中指定值
		bool delSet(const char* table, QWORD id, const char* myset, const QWORD value);

		DBVarType getValue(int type);
		bool getHandle();
		bool isReplyOK();
		bool is_valid()
		{
			if (!c) return false;
			return true;
		}

		bool exec(const char* cmd);
		
		redisContext* c;
	private:
		redisReply* reply;

		std::string host;
		DWORD port;
		DWORD dbNum;//redis default 1-15 database
		DWORD hashcode;
};
#endif

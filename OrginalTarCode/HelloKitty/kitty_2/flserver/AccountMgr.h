#ifndef _ACCOUNT_MGR_H_
#define _ACCOUNT_MGR_H_

#include <string>
#include <map>
#include <vector>
#include <set>
#include <unordered_map>

#include "zType.h"
#include "zMisc.h"
#include "Fir.h"
#include "zRWLock.h"
#include "zDBConnPool.h"
#include "zMetaData.h"

class AccountMgr : public Singleton<AccountMgr>
{
	private:
		friend class Singleton<AccountMgr>;
		AccountMgr();
		~AccountMgr();

	public:
		bool setDBConnPool(zDBConnPool *dbConnPool);

		bool init();

		bool initAccounts();

		DWORD getZoneidByAccount(std::string account);
	protected:
		void addAccountInner(const std::string& account, DWORD zoneid);
		bool dbInsert(const std::string& account, DWORD zoneid);
		bool dbUpdate(const std::string& account, DWORD zoneid);	
	private:
		zDBConnPool *dbConnPool;        //数据库连接池 
		MetaData* metaData;             //封装好的数据库操作对象
		unsigned int invitcode_mysql_hashcode;

		typedef std::unordered_map<std::string,DWORD> AccountMap;
		AccountMap m_mapAccounts;  // 所有玩家
		
		zRWLock rwlock;
};

#endif


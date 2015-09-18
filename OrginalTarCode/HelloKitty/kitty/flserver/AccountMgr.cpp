#include "FLCommand.h"
#include "zRWLock.h"
#include "zNoncopyable.h"
#include "AccountMgr.h"
#include "zXMLParser.h"
#include "FLCommand.h"
#include "ServerManager.h"
#include "ServerManager.h"

AccountMgr::AccountMgr() : dbConnPool(NULL), metaData(NULL), invitcode_mysql_hashcode(0)
{
}

AccountMgr::~AccountMgr()
{
}

bool AccountMgr::setDBConnPool(zDBConnPool *dbConnPool)
{
	invitcode_mysql_hashcode = atoi(Fir::global["invitcode_mysql_hashcode"].c_str());
	if (NULL == dbConnPool
			|| !dbConnPool->putURL(invitcode_mysql_hashcode, Fir::global["invitcode_mysql"].c_str(), false))
	{
		return false;
	}
	this->dbConnPool = dbConnPool;

	metaData = MetaData::newInstance("");
	if (!metaData ||
			!metaData->init(Fir::global["invitcode_mysql"].c_str()))
	{
		return false;
	}

	if(!init()) return false;

	return true;
}

bool AccountMgr::init()
{
	if (NULL == dbConnPool || NULL == metaData)
		return false;
	connHandleID handle = dbConnPool->getHandle((const void*)invitcode_mysql_hashcode);
	if ((connHandleID)-1 == handle)
		return false;
	FieldSet* fields = metaData->getFields("account_zone");
	if (NULL == fields)
	{   
		dbConnPool->putHandle(handle);
		return false;
	}   
	RecordSet* result=dbConnPool->exeSelect(handle, fields, NULL, NULL);
	if(result)
	{   
		unsigned int size = result->size();
		for(unsigned int i = 0; i < size; i++)
		{   
			Record* record = result->get(i);
			if (record)
			{
				std::string account;
				account.assign((const char*)record->get("account"));
				DWORD zoneid = record->get("zoneid");
				addAccountInner(account, zoneid);
			}
		}
		SAFE_DELETE(result);
	}
	dbConnPool->putHandle(handle);

	return true;
}

void AccountMgr::addAccountInner(const std::string& account, DWORD zoneid)
{
	AccountMap::const_iterator itr = m_mapAccounts.find(account);
	if(itr != m_mapAccounts.end())
		return;

	m_mapAccounts.insert(std::make_pair(account,zoneid));
}

DWORD AccountMgr::getZoneidByAccount(std::string account)
{
	zRWLock_scope_wrlock lock(rwlock);
	
	AccountMap::iterator itr = m_mapAccounts.find(account);
	if(itr == m_mapAccounts.end())
	{
		DWORD zoneid = ServerManager::getMe().getRegRoleMinZone();
		addAccountInner(account,zoneid);
		dbInsert(account,zoneid);
		return zoneid;	
	}	

	if(itr->second != 0) 
		return itr->second;

	DWORD zoneid = ServerManager::getMe().getRegRoleMinZone();
	itr->second = zoneid;
	dbUpdate(account,zoneid);
	return zoneid;
}

bool AccountMgr::dbInsert(const std::string& account, DWORD zoneid)
{
        if (NULL == dbConnPool || NULL == metaData)
                return false;

        connHandleID handle = dbConnPool->getHandle((const void*)invitcode_mysql_hashcode);
        if ((connHandleID)-1 == handle)
                return false;

        FieldSet* fields = metaData->getFields("account_zone");
        if (NULL == fields)
        {
                dbConnPool->putHandle(handle);
                return false;
        }

        Record record;
        record.put("account", account);
        record.put("zoneid",zoneid);
        unsigned int recode = dbConnPool->exeInsert(handle, fields, &record);
        dbConnPool->putHandle(handle);
        if ((unsigned int)-1==recode)
        {
                return false;
        }
        return true;
}

bool AccountMgr::dbUpdate(const std::string& account, DWORD zoneid)
{
	if (NULL == dbConnPool || NULL == metaData)
                return false;

        connHandleID handle = dbConnPool->getHandle((const void*)invitcode_mysql_hashcode);
        if ((connHandleID)-1 == handle)
                return false;

        FieldSet* fields = metaData->getFields("account_zone");
        if (NULL == fields)
        {
                dbConnPool->putHandle(handle);
                return false;
        }

        Record record;
        record.put("zoneid", zoneid);

        Record where;
        std::ostringstream oss;
        oss << "account='" << account << "'";
        where.put("account", oss.str());

        unsigned int retcode = dbConnPool->exeUpdate(handle,fields, &record, &where);
        dbConnPool->putHandle(handle);

        return (DWORD)-1 != retcode;
}

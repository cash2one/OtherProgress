/**
 * \file: RecordUserManager.cpp
 * \version  $Id: RecordUserManager.cpp 64 2013-04-23 02:05:08Z  $
 * \author  , @ztgame.com 
 * \date 2007年01月30日 08时15分25秒 CST
 * \brief 档案用户管理器实现
 *
 * 
 */

#include "RecordServer.h"
#include "RecordUserManager.h"
#include "RecordUser.h"
#include "hiredis.h"
#include "zDBConnPool.h"
#include "zMetaData.h"
#include "LoginUserCommand.h"
#include "friend.pb.h"
#include "RecordCommand.h"
#include "RecordTaskManager.h"
#define IDBASE (QWORD(RecordService::getMe().getServerID()) << 32)


bool RecordUserM::init()
{
    if(RecordService::getMe().hasDBtable("t_charbase"))
    {
        FieldSet* charbase = RecordService::metaData->getFields("t_charbase");
        if(NULL == charbase)
        {
            Fir::logger->error("找不到t_charbase的FieldSet");
            return false;
        }

        connHandleID handle = RecordService::dbConnPool->getHandle();
        if ((connHandleID)-1 == handle)
        {
            Fir::logger->error("不能获取数据库句柄");
            return false;
        }

        RecordSet* recordset = NULL;
        Record col,where;

        col.put("f_charid");
        char buf[255];
        sprintf(buf," f_charid & %lu = %lu",IDBASE,IDBASE);
        where.put("f_charid",buf);

        recordset = RecordService::dbConnPool->exeSelect(handle, charbase, &col, &where);//得到所有角色id

        RecordService::dbConnPool->putHandle(handle);

        if(recordset != NULL) 
        {
            for(unsigned int i = 0; i<recordset->size(); i++)
            {   
                Record *rec = recordset->get(i);

                RecordUser* u = new RecordUser();
                u->charid = rec->get("f_charid");

                if (!u->readCharBase())
                {   
                    Fir::logger->error("[角色读写],charid=%lu,初始化档案失败",u->charid);
                    SAFE_DELETE(u);
                    continue;
                }

                if (RecordUserM::getMe().add(u))
                {
                    //同步角色基础信息到内存缓存数据库
                    u->syncBaseMemDB();
                }
                else
                {
                    SAFE_DELETE(u);
                    Fir::logger->error("[角色读写],charid=%lu 添加档案失败，角色已存在", u->charid);
                }

                Fir::logger->error("[预加载测试],charid=%lu,初始化档案成功",u->charid);
            }

            Fir::logger->trace("初始化成功，一共读取档案: %u 个角色", recordset->size());
        }
        // 加载最大的角色id
        if(!loadMaxCharId())
            return false;
        SAFE_DELETE(recordset);    

    }


    loadrelation();
    return true;
}

bool RecordUserM::loadMaxCharId()
{
    if(!RecordService::getMe().hasDBtable("t_charbase"))
    {
        return false;
    }

    connHandleID handle = RecordService::dbConnPool->getHandle();

    if ((connHandleID)-1 == handle)
    {
        Fir::logger->error("不能获取数据库句柄");
        return false;
    }

    const dbCol dbCol[] = 
    {
        { "f_maxcharid",   zDBConnPool::DB_QWORD,  sizeof(QWORD) },
        { NULL, 0, 0}
    };

    struct stReadData
    {   
        stReadData()
        {
            maxcharid = 0;
        }   
        QWORD maxcharid;
    }__attribute__ ((packed)) read_data;
    char buf[255];
    sprintf(buf,"select IFNULL(MAX(f_charid),0) as f_maxcharid from t_charbase where f_charid & %lu = %lu ;",IDBASE,IDBASE);

    std::string sql(buf); 

    unsigned int retcode = RecordService::dbConnPool->execSelectSql(handle, sql.c_str(), sql.length(), dbCol, 1, (BYTE *)(&read_data));

    RecordService::dbConnPool->putHandle(handle);
    if (1 == retcode)
    {  
        maxCharId = read_data.maxcharid;
        QWORD qwBase = IDBASE;
        if(maxCharId < qwBase)
        {
            maxCharId = qwBase;
        }
        Fir::logger->info("[加载最大角色id]:读取档案成功，maxcharid=%lu",maxCharId);
        return true;
    }   
    else
    {   
        Fir::logger->error("[加载最大角色id]:读取档案失败，没有找到记录");
        return false;
    }   
}

bool RecordUserM::add(RecordUser* u)
{
    if(!RecordService::getMe().hasDBtable("t_charbase"))
    {
        Fir::logger->info("ServerCanNot get table t_charbase");
        return false;
    }


    if (!u) return false;

    bool retval = false;

    mlock.lock();

    RecordUserHashmap_iterator it = userMap.find(u->charid);
    if (it==userMap.end())
    {
        userMap[u->charid] = u;
        retval = true;
    }

    mlock.unlock();

    return retval;
}

RecordUserM::~RecordUserM()
{	
    for(auto itr=userMap.begin(); itr!=userMap.end(); itr++)
    {
        SAFE_DELETE(itr->second);
    }
    userMap.clear();
}


//仅用于UUID登录时用，并且取出后，需验证UUID
RecordUser* RecordUserM::getUserByCharid(QWORD charid)
{
    RecordUser* ret = NULL;

    mlock.lock();

    RecordUserHashmap_iterator it = userMap.find(charid);
    if (it!=userMap.end())
    {
        ret = it->second;
    }

    mlock.unlock();

    return ret;
}

bool RecordUserM::cloneSaveChars(const CMD::RECORD::t_Clone_WriteUser_SceneRecord *rev)
{
    if(!RecordService::getMe().hasDBtable("t_charbase"))
    {
        Fir::logger->info("ServerCanNot get table t_charbase");
        return false;
    }
    connHandleID handle = RecordService::dbConnPool->getHandle();
    if ((connHandleID)-1 == handle)
    {   
        Fir::logger->error("[克隆保存]不能获取数据库句柄");
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
    }save_data;

    save_data.role_size = rev->dataSize;
    bcopy(&rev->charbase, &save_data.charbase, sizeof(CharBase));
    bcopy(&rev->data[0], &save_data.role[0], rev->dataSize);

    for(DWORD i=rev->start_index; i<=rev->finish_index; i++)
    {
        QWORD charid = generateCharId();
        std::string prefix(rev->prefix);
        std::ostringstream os;
        os << prefix << i;
        std::string account = os.str();
        save_data.charbase.charid = charid;
        strncpy(save_data.charbase.account,account.c_str(),account.length());
        strncpy(save_data.charbase.nickname,account.c_str(),account.length());
        unsigned int retcode = RecordService::dbConnPool->exeInsert(handle, "t_charbase", record_charbase,(BYTE *)(&save_data));
        if ((unsigned int)-1 == retcode)
        {
            Fir::logger->error("[克隆保存]插入失败,start=%u,finish=%u,i=%u,charid=%lu,account=%s",rev->start_index,rev->finish_index,i,charid,account.c_str());
            return false;
        }
    }

    RecordService::dbConnPool->putHandle(handle);
    return true;	
}

bool RecordUserM::loadrelation()
{
    if(!RecordService::getMe().hasDBtable("relation"))
    {
        return true;
    }
    zMemDB* memhandle = zMemDBPool::getMe().getMemDBHandle();
    if(!memhandle)
        return false;
    FieldSet* relationbase = RecordService::metaData->getFields("relation");
    if(relationbase == NULL)
     return false;

    connHandleID handle = RecordService::dbConnPool->getHandle();

    if ((connHandleID)-1 == handle)
    {
        Fir::logger->error("不能获取数据库句柄");
        return false;
    }

    RecordSet* recordset = NULL;
    recordset = RecordService::dbConnPool->exeSelect(handle, relationbase ,NULL, NULL);
    RecordService::dbConnPool->putHandle(handle);
    if(recordset != NULL) 
    {
        for(unsigned int i = 0; i<recordset->size(); i++)
        {   
            Record *rec = recordset->get(i);
            QWORD PlayerA = QWORD(rec->get("playera"));
            QWORD PlayerB =  QWORD(rec->get("playerb"));
            QWORD Value =   QWORD(rec->get("relation"));

            if(Value > 0)
            {
                memhandle->setInt("rolerelation",PlayerA,PlayerB,Value);
                QWORD tepfriend = QWORD(1) << HelloKittyMsgData::RlationTypeServer_Friend;
                if((Value & tepfriend) > 0)
                {
                    memhandle->setSet("rolerelation",PlayerA,"friend",PlayerB);
                    memhandle->setSet("rolerelation",PlayerB, "fans",PlayerA);
                }


            }
        }


        Fir::logger->trace("初始化成功，一共读取关系档案: %u 个角色", recordset->size());
    }

    SAFE_DELETE(recordset);    
    return true;

}

void RecordUserM::synPlayerNum()
{
    if(!RecordService::getMe().hasDBtable("relation"))
    {
        return ;
    }
    CMD::RECORD::t_SynPlayerNum_GateRecord cmd;
    cmd.playerNum = userMap.size();
    std::string ret;
    if(encodeMessage(&cmd,sizeof(cmd),ret))
        RecordTaskManager::getMe().broadcastByType(GATEWAYSERVER,ret.c_str(),ret.size());


}


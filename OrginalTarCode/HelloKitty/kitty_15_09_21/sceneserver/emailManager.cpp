#include "emailManager.h"
#include "SceneUser.h"
#include "SceneCommand.h"
#include "SceneToOtherManager.h"
#include "SceneServer.h"
#include "RedisMgr.h"
#include "TimeTick.h"
#include "SceneUserManager.h"

QWORD EmailManager::mailID = 0;
EmailManager::EmailManager(SceneUser *owner) : m_owner(owner)
{
    m_full = false;
}

bool EmailManager::load(const HelloKittyMsgData::Serialize& binary)
{
    for(int index = 0;index < binary.email_size();++index)
    {
        HelloKittyMsgData::EmailInfo &email = const_cast<HelloKittyMsgData::EmailInfo&>(binary.email(index));
        email.set_id(++mailID);
        m_emailMap.insert(std::pair<QWORD,HelloKittyMsgData::EmailInfo>(email.id(),email));
    }
    loadDB();
    delTimeOut(false);
    return true;
}

bool EmailManager::save(HelloKittyMsgData::Serialize& binary)
{
    for(auto iter = m_emailMap.begin();iter != m_emailMap.end();++iter)
    {
        HelloKittyMsgData::EmailInfo *email = binary.add_email();
        if(!email)
        {
            continue;
        }
        *email = iter->second;
    }
    return true;
}

bool EmailManager::flushEmail()
{
    if(m_full)
    {
        loadDB();
    }
    HelloKittyMsgData::AckEmail ackEmail;
    for(auto iter = m_emailMap.begin();iter != m_emailMap.end();++iter)
    {
        HelloKittyMsgData::EmailInfo *email = ackEmail.add_email();
        if(!email)
        {
            continue;
        }
        *email = iter->second;
    }
     
    std::string ret;
    encodeMessage(&ackEmail,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

HelloKittyMsgData::EmailInfo* EmailManager::getEmail(const QWORD id)
{
    auto iter = m_emailMap.find(id);
    if(iter == m_emailMap.end())
    {
        return NULL;
    }
    HelloKittyMsgData::EmailInfo* email = const_cast<HelloKittyMsgData::EmailInfo*>(&(iter->second));
    if(!email)
    {
        return NULL;
    }
    HelloKittyMsgData::EmailBase *emailBase = email->mutable_emailbase();
    if(!emailBase)
    {
        return NULL;
    }
    return email;
}


bool EmailManager::updateEmail(const QWORD id)
{
    HelloKittyMsgData::EmailInfo* email = getEmail(id);
    if(!email)
    {
        return false;
    }

    HelloKittyMsgData::AckUpdateEmail updateEmail;
    HelloKittyMsgData::EmailInfo *temp = updateEmail.mutable_email();
    if(!temp)
    {
        return false;
    }
    *temp = *email;
    
    std::string ret;
    encodeMessage(&updateEmail,ret);
    m_owner->sendCmdToMe(ret.c_str(),ret.size());
    return true;
}

bool EmailManager::opEmail(const HelloKittyMsgData::ReqOpEmail *message)
{
    HelloKittyMsgData::EmailInfo* email = getEmail(message->id());
    if(!email && message->optype() != HelloKittyMsgData::Email_Op_Get_Item_All)
    {
        return false;
    }

    bool ret = false;
    std::set<QWORD> delSet;
    switch(message->optype())
    {
        //读取邮件
        case HelloKittyMsgData::Email_Op_Read:
            {
                email->set_status(HelloKittyMsgData::Email_Status_Read);
                return updateEmail(message->id());
            }
            break;
        //提取附件
        case HelloKittyMsgData::Email_Op_Get_Item:
            {
                email->set_status(HelloKittyMsgData::Email_Status_Read);
                if(getItem(message->id()))
                {
                    delSet.insert(message->id());
                }
            }
            break;
        //返回邮件
        case HelloKittyMsgData::Email_Status_Close:
            {
                HelloKittyMsgData::EmailBase *emailBase = email->mutable_emailbase();
                if(!emailBase->item_size())
                {
                    delSet.insert(message->id());
                }
            }
            break;
        //删除邮件
        case HelloKittyMsgData::Email_Op_Delete:
            {
                delSet.insert(message->id());
            }
            break;
        //全部提取
        case HelloKittyMsgData::Email_Op_Get_Item_All:
            {
                for(auto iter = m_emailMap.begin();iter != m_emailMap.end();++iter)
                {
                    if(!getItem(iter->first))
                    {
                        break;
                    }
                    delSet.insert(iter->first);
                }
            }
            break;
        default:
            {
                break;
            }
    }
    for(auto iter = delSet.begin();iter != delSet.end();++iter)
    {
        delEmail(*iter,true,false);
        ret = true;
    }
    return ret;
}

bool EmailManager::delEmail(const QWORD id,const bool notify,const bool system)
{
    HelloKittyMsgData::EmailInfo* email = getEmail(id);
    if(!email)
    {
        return false;
    }
    HelloKittyMsgData::EmailBase *emailBase = email->mutable_emailbase();
    if(!emailBase)
    {
        return false;
    }
    email->set_status(HelloKittyMsgData::Email_Status_Delete);
    if(notify)
    {
        updateEmail(id);
    }
    Fir::logger->debug("[删除邮件%s]:(%lu,%lu,%lu)",system ? "系统超时删除" : "玩家手动删除", email->sender(),emailBase->accepter(),email->createtime());
    m_emailMap.erase(id);
    return true;
}

bool EmailManager::getItem(const QWORD id)
{
    HelloKittyMsgData::EmailInfo* email = getEmail(id);
    if(!email)
    {
        return false;
    }

    HelloKittyMsgData::EmailBase *emailBase = email->mutable_emailbase();
    std::map<DWORD,DWORD> itemMap;
    for(int index = 0;index < emailBase->item_size();++index)
    {
        const HelloKittyMsgData::PbStoreItem &item = emailBase->item(index);
        if(item.itemid() <= ATTR_ITEM_ID_MAX)
        {
            continue;
        }
        if(itemMap.find(item.itemid()) == itemMap.end())
        {
            itemMap.insert(std::pair<DWORD,DWORD>(item.itemid(),item.itemcount()));
        } 
    }
    if(!m_owner->m_store_house.hasEnoughSpace(itemMap))
    {
        m_owner->opErrorReturn(HelloKittyMsgData::WareHouse_Is_Full);
        return false;
    }
    for(int index = 0;index < emailBase->item_size();++index)
    {
        const HelloKittyMsgData::PbStoreItem &item = emailBase->item(index);
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"邮件提取(%lu,%lu,%lu)",email->sender(),emailBase->accepter(),email->createtime());
        if(!m_owner->m_store_house.addOrConsumeItem(item.itemid(),item.itemcount(),temp,true))
        {
            return false;
        }
    }
    return true;
}

bool EmailManager::acceptEmail(HelloKittyMsgData::EmailInfo &emailInfo)
{
    HelloKittyMsgData::EmailBase *emailBase = emailInfo.mutable_emailbase();
    if(!emailBase)
    {
        return false;
    }
    if(m_full)
    {
        EmailManager::insertDB(emailInfo);
        m_owner->opErrorReturn(HelloKittyMsgData::Email_Is_Enough);
    }
    else
    {
        emailInfo.set_id(++mailID);
        m_emailMap.insert(std::pair<QWORD,HelloKittyMsgData::EmailInfo>(emailInfo.id(),emailInfo));
        updateEmail(emailInfo.id());
    }
    return true;
}


bool EmailManager::sendEmail(const HelloKittyMsgData::EmailBase *emailBase)
{
    if(!emailBase)
    {
        return false;
    }

    CharBase charbase;
    if(!RedisMgr::getMe().get_charbase(emailBase->accepter(),charbase))
    {
        Fir::logger->debug("[发送邮件],接受者不存在(%lu,%lu)",m_owner->charid,emailBase->accepter());
        m_owner->opErrorReturn(HelloKittyMsgData::Player_Not_Exist);
        return false;
    }
    if(emailBase->title().size() == 0 && emailBase->conten().size() == 0 && emailBase->item_size() == 0)
    {
        m_owner->opErrorReturn(HelloKittyMsgData::Email_Is_Empty);
        Fir::logger->debug("[发送邮件],邮件为空(%lu,%lu)",m_owner->charid,emailBase->accepter());
        return false;
    }
    std::map<DWORD,DWORD> itemMap;
    for(int index = 0;index < emailBase->item_size();++index)
    {
        const HelloKittyMsgData::PbStoreItem &item = emailBase->item(index);
        auto iter = itemMap.find(item.itemid());
        if(iter == itemMap.end())
        {
            itemMap.insert(std::pair<DWORD,DWORD>(item.itemid(),item.itemcount()));
        }
        else
        {
            itemMap[item.itemid()] += item.itemcount();
        }
    }

    for(auto iter = itemMap.begin();iter != itemMap.end();++iter)
    {
        if(!m_owner->m_store_house.hasEnoughItem(iter->first,iter->second))
        {
            Fir::logger->debug("[发送邮件],道具不够(%lu,%lu,%u,%u)",m_owner->charid,emailBase->accepter(),iter->first,iter->second);
            return false;
        }
    }
    
    HelloKittyMsgData::EmailInfo emailInfo;
    HelloKittyMsgData::EmailBase *temp = emailInfo.mutable_emailbase();
    if(!temp)
    {
        return false;
    }
    *temp = *emailBase;
    emailInfo.set_id(0);
    emailInfo.set_sender(m_owner->charid);
    emailInfo.set_sendername(m_owner->nickname);
    emailInfo.set_createtime(SceneTimeTick::currentTime.msecs());
    emailInfo.set_status(HelloKittyMsgData::Email_Status_Accept);
    
    for(auto iter = itemMap.begin();iter != itemMap.end();++iter)
    {
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"邮件发送(%lu,%lu,%lu)",emailInfo.sender(),emailBase->accepter(),emailInfo.createtime());
        if(!m_owner->m_store_house.addOrConsumeItem(iter->first,iter->second,temp,false))
        {
            Fir::logger->debug("[发送邮件],扣除道具不够(%lu,%lu,%u,%u)",m_owner->charid,emailBase->accepter(),iter->first,iter->second);
            return false;
        }
    }
    return EmailManager::sendEmail(emailInfo);
}

bool EmailManager::loadDB()
{
    RecordSet* recordset = NULL;
    Record where;
    
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"receiver=%lu",m_owner->charid);
    where.put("receiver",temp);

    connHandleID handle = SceneService::dbConnPool->getHandle();
    if ((connHandleID)-1 == handle)
    {
        Fir::logger->error("不能从数据库连接池获取连接句柄");
        return false;
    }   
    recordset = SceneService::dbConnPool->exeSelect(handle,"email", NULL, &where,NULL);
    SceneService::dbConnPool->putHandle(handle);

    if(recordset != NULL) 
    {
        for(DWORD index = 0; index < recordset->size() && m_emailMap.size() < MAX_EMAIL_NUM; ++index)
        {   
            Record *rec = recordset->get(index);
            char conten[1024] = {0};
            char temp[100] = {0};
            memcpy(temp,(const char*)rec->get("sender"),rec->get("sender").getBinSize());
            QWORD sender = atol(temp);
            bzero(temp,sizeof(temp));
            memcpy(temp,(const char*)rec->get("receiver"),rec->get("receiver").getBinSize());
            QWORD receiver = atol(temp);
            bzero(temp,sizeof(temp));
            memcpy(temp,(const char*)rec->get("time"),rec->get("time").getBinSize());
            QWORD time = atol(temp);
            DWORD binarySize = rec->get("conten").getBinSize();
            memcpy(conten,(const char*)rec->get("conten"),binarySize);

            HelloKittyMsgData::EmailInfo emailInfo;
            if(!emailInfo.ParseFromArray(conten,binarySize))
            {
                Fir::logger->debug("[加载邮件] 加载邮件反序列化出错(%lu,%lu,%lu)",sender,receiver,m_owner->charid);
            }
            else
            {
                emailInfo.set_id(++mailID);
                m_emailMap.insert(std::pair<QWORD,HelloKittyMsgData::EmailInfo>(emailInfo.id(),emailInfo));
            }
            bzero(temp,sizeof(temp));
            snprintf(temp,sizeof(temp),"sender=%lu and receiver=%lu and time=%lu",sender,receiver,time);
            connHandleID handle = SceneService::dbConnPool->getHandle();
            if ((connHandleID)-1 == handle)
            {
                Fir::logger->error("不能从数据库连接池获取连接句柄");
                return false;
            }   
            DWORD ret = SceneService::dbConnPool->exeDelete(handle,"email", temp);
            if(ret == (DWORD)-1)
            {
                Fir::logger->debug("[删除数据库邮件] 从数据库中删除邮件失败(%lu,%s)",m_owner->charid,temp);
            }
            SceneService::dbConnPool->putHandle(handle);
            Fir::logger->debug("[加载邮件] 成功(%lu,%lu,%lu,%lu)",sender,receiver,time,m_owner->charid);

        }
    }
    SAFE_DELETE(recordset);
    if(m_emailMap.size() == MAX_EMAIL_NUM)
    {
        m_full = true;
        m_owner->opErrorReturn(HelloKittyMsgData::Email_Is_Enough);
    }
    else
    {
        m_full = false;
    }
    return true;
}

bool EmailManager::insertDB(const HelloKittyMsgData::EmailInfo &emailInfo)
{
    const HelloKittyMsgData::EmailBase &emailBase = emailInfo.emailbase(); 
    Record record;
    record.put("sender",emailInfo.sender());
    record.put("receiver",emailBase.accepter());
    record.put("time",emailInfo.createtime());
    char temp[1024] = {0};
    emailInfo.SerializeToArray(temp,emailInfo.ByteSize());
    record.put("conten",temp,emailInfo.ByteSize());

    connHandleID handle = SceneService::dbConnPool->getHandle();
    if ((connHandleID)-1 == handle)
    {
        Fir::logger->error("不能从数据库连接池获取连接句柄");
        return false;
    }
    DWORD retcode = SceneService::dbConnPool->exeInsert(handle, "email", &record);
    if(retcode == (DWORD)-1)
    {
        Fir::logger->debug("[邮件] 插入数据库出错(%lu,%lu,%lu)",emailInfo.sender(),emailBase.accepter(),SceneTimeTick::currentTime.sec());
        return false;
    }
    return true;
}

bool EmailManager::delTimeOut(const bool notify)
{
    std::set<QWORD> timeOutSet;
    DWORD now = SceneTimeTick::currentTime.msecs();
    for(auto iter = m_emailMap.begin();iter != m_emailMap.end();++iter)
    {
        const HelloKittyMsgData::EmailInfo &email = iter->second;
        if(now <= email.createtime() || now - email.createtime() >= 3 * 3600 *24 * 1000)
        {
            timeOutSet.insert(iter->first);
        }

    }

    for(auto iter = timeOutSet.begin();iter != timeOutSet.end();++iter)
    {
        delEmail(*iter,notify);
    }
    return true;
}

bool EmailManager::sendEmailBySys(const QWORD accepter,const char *title,const char *conten,const std::map<DWORD,DWORD> &itemMap,const bool popup)
{
    HelloKittyMsgData::EmailInfo emailInfo;
    HelloKittyMsgData::EmailBase *emailBase = emailInfo.mutable_emailbase();
    if(!emailBase || accepter == 0 || (!title && !conten && itemMap.empty()))
    {
        return false;
    }
    
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(accepter % MAX_MEM_DB+1);
    if(!handle)
    {
        Fir::logger->error("[系统发送邮件]找不到Mem,%lu",accepter % MAX_MEM_DB+1);
        return false;
    }

    emailBase->set_accepter(accepter);
    emailBase->set_acceptername(handle->get("rolebaseinfo", accepter, "nickname"));
    emailBase->set_title(title);
    emailBase->set_conten(conten);
    for(auto iter = itemMap.begin();iter != itemMap.end();++iter)
    {
        HelloKittyMsgData::PbStoreItem *temp = emailBase->add_item();
        if(!temp)
        {
            continue;
        }
        temp->set_itemid(iter->first);
        temp->set_itemcount(iter->second);
    }

    emailInfo.set_id(0);
    emailInfo.set_sender(0);
    emailInfo.set_sendername("系统");
    emailInfo.set_createtime(SceneTimeTick::currentTime.msecs());
    emailInfo.set_status(HelloKittyMsgData::Email_Status_Accept);
    emailInfo.set_popup(popup);
    return EmailManager::sendEmail(emailInfo);
}

bool EmailManager::sendEmailBySys(const char *nickname,const char *title,const char *conten,const std::map<DWORD,DWORD> &itemMap,const bool popup)
{
    if(!nickname || (!title && !conten && itemMap.empty()))
    {
        return false;
    }
    
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(1);
    if(!handle)
    {
        Fir::logger->error("[系统发送邮件]找不到Mem,%u",1);
        return false;
    }
    QWORD accepter = handle->getInt("rolebaseinfo",nickname, "charid");
    if(accepter == 0)
    {
        return false;
    }
    return EmailManager::sendEmailBySys(accepter,title,conten,itemMap,popup);
}


bool EmailManager::sendEmail(HelloKittyMsgData::EmailInfo &emailInfo)
{
    const HelloKittyMsgData::EmailBase &emailBase = emailInfo.emailbase();
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(emailBase.accepter() % MAX_MEM_DB+1);
    if(!handle)
    {
        Fir::logger->error("[发送邮件]找不到Mem,%lu",emailBase.accepter() % MAX_MEM_DB+1);
        return false;
    }
    bool ret = true;
    DWORD senceId = handle->getInt("playerscene",emailBase.accepter(),"sceneid");
    if(!senceId)
    {
        ret = EmailManager::insertDB(emailInfo);
    }
    else
    {
        SceneUser* acceptUser = SceneUserManager::getMe().getUserByID(emailBase.accepter());
        if(acceptUser)
        {
            ret = acceptUser->m_emailManager.acceptEmail(emailInfo);
        }
        else
        {
            BYTE buf[zSocket::MAX_DATASIZE] = {0};
            CMD::SCENE::t_EmailSendPlayer_scenescene *emailCmd = (CMD::SCENE::t_EmailSendPlayer_scenescene*)buf;
            constructInPlace(emailCmd);
            emailCmd->charid = emailBase.accepter();
            emailCmd->size = emailInfo.ByteSize();
            emailInfo.SerializeToArray(emailCmd->data,emailCmd->size);

            std::string retStr;
            encodeMessage(emailCmd,sizeof(*emailCmd) + emailCmd->size,retStr);
            if(!SceneClientToOtherManager::getMe().SendMsgToOtherScene(senceId,retStr.c_str(),retStr.size()))
            {
                Fir::logger->debug("[发送邮件],发送邮件失败(%lu,%lu,%u)",emailInfo.sender(),emailBase.accepter(),senceId);
                ret = false;
            }
        }
    }
    Fir::logger->debug("[发送邮件%s]:(%lu,%lu,%lu)",ret ? "成功" : "失败",emailInfo.sender(),emailBase.accepter(),emailInfo.createtime());
    return ret;
}

bool EmailManager::reqEmail(const HelloKittyMsgData::ReqEmail *cmd)
{
    if(cmd->id() == 0)
    {
        return flushEmail();
    }
    return updateEmail(cmd->id());
}

    

    






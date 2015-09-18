/**
 * \file
 * \version  $Id: RecordTask.cpp 64 2013-04-23 02:05:08Z  $
 * \author  ,@163.com
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 实现读档连接类
 *
 * 
 */


#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "RecordTask.h"
#include "Fir.h"
#include "zDBConnPool.h"
#include "zString.h"
#include "RecordCommand.h"
#include "SessionCommand.h"
#include "RecordServer.h"
#include "RecordUserManager.h"
#include "RecordUser.h"
#include "zMetaData.h"
#include <string>
#include <vector>
#include "LoginUserCommand.h"
#include "xmlconfig.h"
#include "tbx.h"
#include "RecordTaskManager.h"
#include "extractProtoMsg.h"

/**
 * \brief 验证登陆档案服务器的连接指令
 *
 * 如果验证不通过直接断开连接
 *
 * \param ptCmd 登陆指令
 * \return 验证是否成功
 */
bool RecordTask::verifyLogin(const CMD::RECORD::t_LoginRecord *ptCmd)
{
	using namespace CMD::RECORD;

	if (CMD_LOGIN == ptCmd->cmd
			&& PARA_LOGIN == ptCmd->para)
	{
		const CMD::SUPER::ServerEntry *entry = RecordService::getMe().getServerEntry(ptCmd->wdServerID);
		char strIP[32];
		strncpy(strIP, getIP(), sizeof(strIP)-1);
		if (entry
				&& ptCmd->wdServerType == entry->wdServerType
				&& 0 == strcmp(strIP, entry->pstrIP))
		{
			wdServerID = ptCmd->wdServerID;
			wdServerType = ptCmd->wdServerType;

			return true;
		}
	}

	return false;
}

/**
 * \brief 等待接受验证指令并进行验证
 *
 * 实现虚函数<code>zTCPTask::verifyConn</code>
 *
 * \return 验证是否成功，或者超时
 */
int RecordTask::verifyConn()
{
	int retcode = mSocket.recvToBuf_NoPoll();
	if (retcode > 0)
	{
		BYTE pstrCmd[zSocket::MAX_DATASIZE];
		int nCmdLen = mSocket.recvToCmd_NoPoll(pstrCmd, sizeof(pstrCmd));
		//这里只是从缓冲取数据包，所以不会出错，没有数据直接返回
        if (nCmdLen <= 0)
        {
			return 0;
        }

        BYTE messageType = *(BYTE*)pstrCmd;
        nCmdLen -= sizeof(BYTE);
        if(messageType != STRUCT_TYPE || nCmdLen <= 0)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, messageType,nCmdLen-1); 
            return -1;
        }
        
        using namespace CMD::RECORD;
        if (verifyLogin((t_LoginRecord *)(pstrCmd+sizeof(BYTE))))
        {
            Fir::logger->debug("客户端连接通过验证");
            return 1;
        }
        Fir::logger->error("客户端连接验证失败");
        return -1;
	}
	else
		return retcode;
}

/**
 * \brief 确认一个服务器连接的状态是可以回收的
 *
 * 当一个连接状态是可以回收的状态，那么意味着这个连接的整个生命周期结束，可以从内存中安全的删除了：）<br>
 * 实现了虚函数<code>zTCPTask::recycleConn</code>
 *
 * \return 是否可以回收
 */
int RecordTask::recycleConn()
{
	Fir::logger->debug("关闭服务器:%u", getID());
	//TODO 需要保证存档指令处理完成了
	//
	return 1;
}

bool RecordTask::uniqueAdd()
{
	return RecordTaskManager::getMe().uniqueAdd(this);
}

bool RecordTask::uniqueRemove()
{
	return RecordTaskManager::getMe().uniqueRemove(this);
}

bool RecordTask::msgParse_Session(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
	using namespace CMD::RECORD;

	switch(ptNullCmd->para)
	{
		default:
			break;
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}

bool RecordTask::msgParse_Super(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
	return false;
}

//0成功 1失败 2账号已有角色 3角色名称重复
DWORD RecordTask::create_role_inner(std::string phone_uuid,WORD acctype, std::string account, std::string nickname, std::string password,BYTE bySex, DWORD flatid)
{
	// 账号已经创建了角色
	QWORD charid_ = RecordUserM::getMe().existUserCharid(acctype,account.c_str());
	if (charid_!=0)
	{   
		Fir::logger->info("[创建角色],(%s,0,0)  角色已存在 account=%s",  nickname.c_str(),account.c_str());
		return 2;
	}   

	// 昵称重复
	if(RecordUserM::getMe().existNickname(nickname))
	{   
		Fir::logger->info("[创建角色],(%s,0,0)  角色名重复", nickname.c_str());
		return 3;
	}

	connHandleID handle = RecordService::dbConnPool->getHandle();
	if ((connHandleID)-1 == handle)
	{
		Fir::logger->error("数据库连接失败");
		return 1;
	}

	QWORD charid = RecordUserM::getMe().generateCharId();

	Record record;
	record.put("f_charid",charid);
	record.put("f_nickname",nickname);
	record.put("f_password",password);
	record.put("f_level",1);
	record.put("f_sex",(DWORD)bySex);
	zRTime currentTime;
	record.put("f_createtime",currentTime.sec());
	record.put("f_acctype",acctype);
	record.put("f_account",account);
	record.put("f_store_limit",100);
	record.put("f_sale_grid_count",7);

	unsigned int retcode = RecordService::dbConnPool->exeInsert(handle, "t_charbase", &record);

	RecordService::dbConnPool->putHandle(handle);
	if ((unsigned int)-1 == retcode)
	{
		return 1;
	}

	RecordUser* u = new RecordUser();
	u->charid = charid;

	if (!u->readCharBase())
	{
		Fir::logger->error("[创建角色],读取档案失败");
		return 1;
	}

	if (!RecordUserM::getMe().add(u))
	{
		Fir::logger->error("[创建角色],添加用户管理器失败");
		SAFE_DELETE(u);
		return 1;
	}

	if (u->syncBaseMemDB())
	{
	}
	else
	{
		return 1;
	}

	return 0;
}

bool RecordTask::create_role(const CMD::RECORD::t_CreateChar_GateRecord* rev)
{
	if(!rev) return false;
    
    CMD::RECORD::t_CreateChar_Return_GateRecord ret;
	std::string phone_uuid(rev->phone_uuid);
	WORD acctype = rev->type;
	std::string account(rev->account);
	std::string nickname(rev->name);
	std::string password(rev->password);
	BYTE bySex = rev->bySex;
	DWORD flatid = rev->flatid;

	ret.accid = rev->accid;
	ret.acctype = rev->type;
	strncpy(ret.account, rev->account, MAX_ACCNAMESIZE);
	ret.retcode = create_role_inner(phone_uuid,acctype,account,nickname,password,bySex,flatid);
	if(ret.retcode == 0)
	{
		ret.charid = RecordUserM::getMe().existUserCharid(rev->type, rev->account);
	}
    
    std::string sendRet;
    if(encodeMessage(&ret,sizeof(ret),sendRet))
    {
        sendCmd(sendRet.c_str(),sendRet.size());
    }

	return true;
}

bool RecordTask::msgParse_Gateway(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
	using namespace CMD::RECORD;

	switch(ptNullCmd->para)
	{
		case PARA_GATE_CREATECHAR:
			{
				t_CreateChar_GateRecord* rev = (t_CreateChar_GateRecord*)ptNullCmd;
				create_role(rev);
				return true;
			}
			break;
		default:
			break;
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}

bool RecordTask::msgParse_Scene(const CMD::t_NullCmd *ptNullCmd, const unsigned int nCmdLen)
{
	using namespace CMD::RECORD;

	switch(ptNullCmd->para)
	{
		case PARA_SCENE_USER_WRITE:
			{
				t_WriteUser_SceneRecord* rev = (t_WriteUser_SceneRecord*)ptNullCmd;
				RecordUser* u = RecordUserM::getMe().getUserByCharid(rev->charid);
				if (u && rev->dataSize<nCmdLen)
				{
					if (u->refreshSaveBase(rev))
					{
					}
					else
					{
						Fir::logger->error("回写档案验证失败，不能回写档案,charid=%lu", rev->charid);
					}
				}
				else
				{
					Fir::logger->error("回写档案验证失败，不能回写档案：charid=%lu,%u %u 玩家在RECORDUSERM管理器里找不到", rev->charid,rev->dataSize,nCmdLen);
				}
			
				return true;
			}
			break;
		case PARA_CLONE_USER_WRITE:
			{
				t_Clone_WriteUser_SceneRecord* ptCmd = (t_Clone_WriteUser_SceneRecord*)ptNullCmd;
				RecordUserM::getMe().cloneSaveChars(ptCmd);
				return true;
			}
			break;
		default:
			break;
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}

bool RecordTask::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("RecordTask::msgParseProto 消息没处理");
    return true;
}


/**
 * \brief 解析来自各个服务器连接的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 指令长度
 * \return 处理是否成功
 */
bool RecordTask::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

	using namespace CMD::RECORD;

	switch(ptNullCmd->cmd)
	{
		case CMD_GATE:
			if (msgParse_Gateway(ptNullCmd, nCmdLen))
			{
				return true;
			}
			break;
		case CMD_SCENE:
			if (msgParse_Scene(ptNullCmd, nCmdLen))
			{
				return true;
			}
			break;
		case CMD_SESSION:
			if (msgParse_Session(ptNullCmd, nCmdLen))
			{
				return true;
			}
			break;
		default:
			break;
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}


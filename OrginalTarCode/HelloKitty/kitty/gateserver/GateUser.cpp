/**
 * \file
 * \version  $Id: GateUser.cpp 67 2013-04-23 09:44:20Z  $
 * \author  ,@163.com
 * \date 2005年04月01日 11时56分41秒 CST
 * \brief 实现网关用户类
 */

#include <stdlib.h>
#include "GateUser.h"
#include "GateUserManager.h"
#include "RecordCommand.h"
#include "RecordClient.h"
#include "GatewayTask.h"
#include "SessionClient.h"
#include "SceneClient.h"
#include "GatewayServer.h"
#include "TimeTick.h"


GateUser::GateUser(DWORD accID,GatewayTask *histask)
{
	this->accid=accid;		
	this->charid=0;		
	initState();
	gatewaytask=histask;
	scene=NULL;
	scene_id=0;
	acctype = 0;
	m_byCreate = 0;
	heroid = 0;
	needReceiveWorldChat = false;
	if(gatewaytask)
	{
		gatewaytask->m_pUser=this;
	}
    bzero(nickname,sizeof(nickname));
}

GateUser::GateUser(const std::string& _uuid,GatewayTask *thistask)
{
	this->accid=0;		
	this->charid=0;		
	initState();
	gatewaytask=thistask;
	scene=NULL;
	scene_id=0;
	acctype = 0;
	m_byCreate = 0;

	if(gatewaytask)
	{
		gatewaytask->m_pUser=this;
	}
    bzero(nickname,sizeof(nickname));
}

GateUser::GateUser(WORD wdlogintype, const std::string& strPlatAccount, GatewayTask* thistask)
{
	this->accid=0;		
	this->charid=0;		
	initState();
	gatewaytask=thistask;
	scene=NULL;
	scene_id=0;
	acctype = wdlogintype;
	m_byCreate = 0;
	this->account = strPlatAccount;

	if(gatewaytask)
	{
		gatewaytask->m_pUser=this;
	}
    bzero(nickname,sizeof(nickname));
}

GateUser::~GateUser()
{
	Fir::logger->debug(__PRETTY_FUNCTION__);
}


/**
 * \brief 卸载一个网关用户的信息
 *
 *
 */
void GateUser::final()
{
	Fir::logger->debug("[GS],charid=%lu,%s,结束",this->charid,this->nickname);

	lock();

	GateUserManager::getMe().removeUserCharid(this->charid);

	GateUserManager::getMe().removeUserAccount(this->acctype, this->account);
	
	unlock();

	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if (handle) 
	{
		handle->setInt("gatewaylogin", this->acctype, this->account.c_str(), "state", GATEWAY_USER_LOGINSESSION_STATE_NONE);
	}
}


/**
 * \brief 设置游戏状态
 *
 *
 */
void GateUser::playState(SceneClient *s , DWORD scene_tempid)
{
	lock();
	if(scene_tempid)
	{
		this->scene_id=scene_tempid;
	}
	if(s)
	{
		this->scene=s;
	}
	systemstate = SYSTEM_STATE_PLAY;
	unlock();
}

/**
 * \brief 对选择到一个角色进行初始处理
 *
 *
 * \return 处理是否成功
 */
bool GateUser::beginSelect()
{
	zMutex_scope_lock lock(mlock);

	if (!this->syncMemDBBase())
	{
		return false;
	}

	if (!GateUserManager::getMe().addUserCharid(this))
	{
		Fir::logger->error("[登录]:添加帐号(%u) 失败",accid);
		return false;
	}

	//进入等待游戏状态，然后开始向会话注册，会话注册到场景，成功读档后，返回场景注册成功消息，再进入游戏状态
	Fir::logger->error("[UUID登录]:添加帐号(charid=%lu,%s)成功, 开始向会话注册",this->charid, this->nickname);
	this->reg();
	return true;
}
/**
 * \brief 发送数据给客户端
 *
 *
 * \param pstrCMD: 发送的指令
 * \param nCmdLen: 指令长度
 * \return 发送是否成功
 */
bool GateUser::sendCmd(const void *pstrCmd, const unsigned int nCmdLen,const bool hasPacked)
{
	if (!hasPacked)
	{
		if(gatewaytask)
		{
			return gatewaytask->sendCmd(pstrCmd,nCmdLen);
		}
	}else
	{
		if(gatewaytask)
		{
			return gatewaytask->sendCmdNoPack(pstrCmd,nCmdLen);
		}
	}
	return false;
}

/**
 * \brief 网关注销一个用户
 * \param out: false by default
 *
 */
void GateUser::unreg()
{
	//防止锁加的太大
	bool need=false;

	if (isWaitUnregState())
	{
		return;
	}

	lock();

	if(isWaitPlayState() || isPlayState())
	{
		need=true;

		this->waitUnregState();
	}

	unlock();

	if(need)
	{
		CMD::SESSION::t_unregUser_GateSession send;
		send.charid=charid;
		send.accid=accid;
		send.scene_id=scene_id;
		send.retcode=CMD::SESSION::UNREGUSER_RET_LOGOUT;
		sessionClient->sendCmd(&send,sizeof(send));
		Fir::logger->trace("[登录注销],charid=%lu,nickname=%s, 向会话注销",charid,nickname);
	}
}

/**
 * \brief 网关注册一个用户
 *
 */
void GateUser::reg()
{
	{
        CMD::SESSION::t_regUser_GateSession send;
        send.accid=accid;
		send.charid=charid;
		strncpy((char *)send.name, nickname,MAX_NAMESIZE);
		strncpy(send.flat,strFlat.c_str(),MAX_FLAT_LENGTH);
		strncpy(send.phone_uuid,strPhoneUuid.c_str(),100);
		send.byCreate = m_byCreate;
		send.heroid = heroid;
		send.acctype = this->acctype;
		strncpy(send.account, account.c_str(), MAX_ACCNAMESIZE);
        
        std::string ret;
        encodeMessage(&send,sizeof(send),ret);
		sessionClient->sendCmd(ret.c_str(),ret.size());
		waitPlayState();
	}

	{
        CMD::SESSION::t_saveLoginLog_GateSession send;
		send.type = 1;
		strncpy(send.flat,strFlat.c_str(),MAX_FLAT_LENGTH);
		send.accid = accid;
		send.charid = charid;
		std::string logstep = "denglu";
		strncpy(send.logstep,logstep.c_str(),MAX_NAMESIZE);
        
        std::string ret;
        encodeMessage(&send,sizeof(send),ret);
		sessionClient->sendCmd(ret.c_str(),ret.size());
	}
	/*
	std::string strTime = GatewayTimeTick::currentTime.toString("%y%m%d-%H:%M:%S");
	std::string type = "";
	DWORD linknum = 0; // 连接号
	std::string strExtIp = GatewayService::getMe().getExtIp();
	WORD wExtPort = GatewayService::getMe().getExpPort();
	const GameZone_t& zoneid = GatewayService::getMe().zoneID;
	DWORD usertype = 0; // 用户类型
	DWORD logintype = 0; // 登录类型
	std::string logstep = "登录成功";
	GatewayService::login_logger->info("%s,%s,%u,%s,%s,%u,%s,%u,%u,%u,%lu,%s,%u,%lu,%s",strTime.c_str(),type.c_str(),accid,strMacAddr.c_str(),realIP,linknum,strExtIp.c_str(),wExtPort,
			zoneid.id,zoneid.game,zoneid.zone,uuid.c_str(),usertype,logintype,logstep.c_str());
	*/
}

void GateUser::onCreateCharSuccess() // 创建角色成功
{
	m_byCreate  = 1;

	/*
	std::string strTime = GatewayTimeTick::currentTime.toString("%y%m%d-%H:%M:%S");
	std::string type = ""; 
	DWORD linknum = 0; // 连接号
	std::string strExtIp = GatewayService::getMe().getExtIp();
	WORD wExtPort = GatewayService::getMe().getExpPort();
	const GameZone_t& zoneid = GatewayService::getMe().zoneID;
	DWORD usertype = 0; // 用户类型
	DWORD logintype = 0; // 登录类型
	std::string logstep = "建角";
	GatewayService::login_logger->info("%s,%s,%u,%s,%s,%u,%s,%u,%u,%u,%lu,%s,%u,%lu,%s",strTime.c_str(),type.c_str(),accid,strMacAddr.c_str(),realIP,linknum,strExtIp.c_str(),wExtPort,
			zoneid.id,zoneid.game,zoneid.zone,uuid.c_str(),usertype,logintype,logstep.c_str());
	*/
    CMD::SESSION::t_saveLoginLog_GateSession send;
	send.type = 0;
	strncpy(send.flat,strFlat.c_str(),MAX_FLAT_LENGTH);
	send.accid = accid;
	send.charid = charid;
	std::string logstep = "jianjue";
	strncpy(send.logstep,logstep.c_str(),MAX_NAMESIZE);
	strncpy(send.phone_uuid,strPhoneUuid.c_str(),100);
    
    std::string ret;
    encodeMessage(&send,sizeof(send),ret);
	sessionClient->sendCmd(ret.c_str(),ret.size());
}

/**
 * \brief 中断连接
 *
 */
void GateUser::TerminateWait()
{
	if(gatewaytask)
		gatewaytask->TerminateWait();
}

/**
 * \brief 是否处于等于中断状态
 *
 */
bool GateUser::isTerminateWait()
{
	if(gatewaytask)
		return gatewaytask->isTerminateWait();

	return true;
}

void GateUser::Terminate()
{
	if (gatewaytask)
		return gatewaytask->Terminate();
}

/**
 * \brief 是否已经中断
 *
 */
bool GateUser::isTerminate()
{
	if (gatewaytask)
		return gatewaytask->isTerminate();

	return true;
}

bool GateUser::syncMemDBBase()
{
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if   (!handle) {unlock(); return false;}

	firstrncpy(this->nickname, handle->get("rolebaseinfo", this->charid, "nickname") , MAX_NAMESIZE);
	return true;
}

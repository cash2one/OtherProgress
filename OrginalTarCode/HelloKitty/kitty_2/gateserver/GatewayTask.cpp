/**
 * \file
 * \version  $Id: GatewayTask.cpp 67 2013-04-23 09:44:20Z  $
 * \author  ,@163.com
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 定义登陆连接任务
 *
 */


#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>
#include <stdlib.h>
#include <iconv.h>

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "zMisc.h"
#include "GatewayTask.h"
#include "GatewayServer.h"
#include "Command.h"
#include "SessionClient.h"
#include "RecordClient.h"
#include "SceneCommand.h"
#include "SceneClient.h"
#include "GatewayTaskManager.h"
#include "TimeTick.h"
#include "wordFilter.h"
#include "EncDec/EncDec.h"
#include "LoginUserCommand.h"
#include "login.pb.h"
#include "serialize.pb.h"
#include "item.pb.h"

DWORD GatewayTask::checkTimeInterval = 60000;
GateUserCmdDispatcher GatewayTask::gate_user_cmd_dispatcher("gateusercmd");
GateTaskCmdDispatcher GatewayTask::gate_task_cmd_dispatcher("gatetaskusercmd");
unsigned long long GatewayTask::lastCmdTime = 0;
std::map<const google::protobuf::Descriptor*,ServerType> GatewayTask::s_protoNameToServerTypeMap;

/**
 * \brief 构造函数
 *
 * \param pool 所属连接池指针
 * \param sock TCP/IP套接口
 * \param addr 地址
 */
GatewayTask::GatewayTask(
		zTCPTaskPool *pool,
		const int sock,
		const struct sockaddr_in *addr) :
	zTCPTask(pool, sock, addr, false, false),
	//v_lastSampleTime(GatewayTimeTick::currentTime),
	_retset_gametime(3600), 
	initTime(),
	lastCheckTime(60),
	_login_gametime(1)
{
	//v_lastSampleTime.addDelay(sampleInterval);
	v_lastSampleTime=0;
//	lastCheckTime.addDelay(checkTimeInterval);
	haveCheckTime = true;
	v_samplePackets = 0;
	accid = 0;
	loginTempID = 0;
	versionVerified = false;
    verifyAccid = false;
	inlonginstate = false;
	acctype = 0; //UUID登录，还是通行证登录
	dwTimestampServer=0;
	qwGameTime=0;
	m_pUser=NULL;

	//mSocket.setEncMethod(CEncrypt::ENCDEC_RC5);
	//mSocket.enc.set_key_rc5((const unsigned char *)Fir::global["rc5_key"].c_str(), 16, 12);
	//unsigned char key[16] = {28, 196, 25, 36, 193, 125, 86, 197, 35, 92, 194, 41, 31, 240, 37, 223};
	//unsigned char key[16] = { 0x2c,0xc5,0x29,0x25,0xd1,0x7c,0xa6,0xc6,0x33,0x5d,0xd2,0x2a,0x2f,0xf1,0x35,0xdf};
	//unsigned char key[16] = { 0x3f,0x79,0xd5,0xe2,0x4a,0x8c,0xb6,0xc1,0xaf,0x31,0x5e,0xc7,0xeb,0x9d,0x6e,0xcb};
	//mSocket.set_key_rc5((const unsigned char *)key, 16, 12);
	
	//设置zSocket的加密密钥
	//DES_cblock des_key = {'a','a','a','a','a','a','a','a'};
	//mSocket.setEncMethod(CEncrypt::ENCDEC_DES);
	//mSocket.set_key_des(&des_key);

	timeout_count = 0;
}

/**
 * \brief 析构函数
 *
 */
GatewayTask::~GatewayTask()
{
	if(m_pUser)
	{
		m_pUser->gatewaytask=NULL;
		SAFE_DELETE(m_pUser);
	}
}

/**
 * \brief 验证版本号
 * \param ptNullCmd 待验证的指令
 * \return 验证版本号码是否成功
 */
bool GatewayTask::verifyVersion(const HelloKittyMsgData::ClientRequestVersion *message)
{
    if(!message) return false;
    if(GatewayService::getMe().verify_client_version == 0 || message->clientversion() >= GatewayService::getMe().verify_client_version)
    {
        versionVerified = true;
        return true;
    }
    Fir::logger->debug("[登录]:客户端连接没有通过版本号验证,%s,[%u][%u]",this->getIP(), message->clientversion(),GatewayService::getMe().verify_client_version);
    this->login_return(HelloKittyMsgData::VersionError);
    return false;
}

/**
 * \brief 验证登陆网关指令
 * 验证登陆网关的指令
 * \param ptNullCmd 待验证的登陆指令
 * \return 验证登陆指令是否成功
 */
bool GatewayTask::verifyACCID(const HelloKittyMsgData::LoginGateway *message)
{
    if(!message)
    {
        return false;
    }

	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	if (!handle) 
	{   
		Fir::logger->trace("[登录],用户登录, memdb 连接失败, acctype=%u,account=%s,client_ip=%s", message->usertype(), message->account().c_str(), getIP());
		login_return(HelloKittyMsgData::TimeOut);
		return false;
	}   

	// 应该在need_gate_id上登录
	DWORD need_gate_id = handle->getInt("gatewaylogin",message->usertype(),message->account().c_str(), "gate_id");
	// 当前gateway是
	DWORD cur_gate_id = GatewayService::getMe().getServerID();
	if(need_gate_id != cur_gate_id)
	{   
		Fir::logger->error("[帐号登录],gateid不对，怀疑外挂,acctype=%u,account=%s,client_ip=%s, cur_gate_id:%u, need_gate_id:%u",message->usertype(),message->account().c_str(),getIP(),cur_gate_id, need_gate_id);
		return false;
	}   

	handle->setInt("gatewaylogin", message->usertype(), message->account().c_str(), "state", GATEWAY_USER_LOGINSESSION_STATE_REG);

	this->acctype = message->usertype();//登录类型
	this->strPhoneUuid = message->phoneuuid();
	this->account = message->account().c_str();
	this->changeLoginState();

	this->charid = handle->getInt("charinfo",message->usertype(), message->account().c_str());
	if(this->charid == 0)
    {
        verifyAccid = true;
		return true;
    }

	zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(this->charid%MAX_MEM_DB+1);
	if (!handle2) 
	{   
		Fir::logger->trace("[登录],用户登录, memdb 连接失败, acctype=%u,account=%s,client_ip=%s", message->usertype(), message->account().c_str(), getIP());
		login_return(HelloKittyMsgData::UuidError);
		return false;
	} 

	CharBase charbase;
	if (handle2->getBin("charbase",this->charid,"charbase",(char*)&charbase) == 0)
	{
		Fir::logger->trace("[帐号登录],acctype=%u,account=%s, IPHONE帐号用户登录,失败1", message->usertype(), message->account().c_str());
		return false;
	}
	
	Fir::logger->trace("[帐号登录],acctype=%u,account=%s, IPHONE帐号用户登录,成功", message->usertype(), message->account().c_str());
	verifyAccid = true;
    return true;
}


/**
 * \brief 连接确认
 *
 * \return 如果没有数据返回0,验证成功返回1,验证失败返回-1
 */
int GatewayTask::verifyConn()
{
	int retcode = mSocket.recvToBuf_NoPoll();
	if (retcode > 0)
	{
		while(true)
		{
			unsigned char acceptCmd[zSocket::MAX_DATASIZE];
			int nCmdLen = mSocket.recvToCmd_NoPoll(acceptCmd, sizeof(acceptCmd));
			//这里只是从缓冲取数据包，所以不会出错，没有数据直接返回
            if (nCmdLen <= 0)
			{
				return 0;
			}
            
            BYTE messageType = *(BYTE*)acceptCmd;
            nCmdLen -= sizeof(BYTE);
            BYTE *pstrCmd = acceptCmd + sizeof(BYTE);
            if(nCmdLen <= 0 || messageType != PROTOBUF_TYPE)
            {
                Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, messageType,nCmdLen-1);
                Fir::logger->error("客户端连接验证失败");
                return -1;
            }
            
            if(versionVerified)
            {
                if(msgParseProto(pstrCmd,nCmdLen) && verifyAccid)
                {
                    Fir::logger->info("客户端连接验证成功");
                    return 1;
                }
            }
            else
            {
                if(msgParseProto(pstrCmd,nCmdLen) && versionVerified)
                {
                    continue;
                }
            }

            Fir::logger->error("客户端连接验证失败");
            return -1;
		}
	}
	else
		return retcode;
}

/**
 * \brief 连接同步等待
 *
 *
 * \return 错误返回-1,成功返回1,继续等待返回0
 */
int GatewayTask::waitSync()
{
	return 1;
}

/**
 * \brief 需要主动断开客户端的连接
 *
 * \param method 连接断开方式
 */
void GatewayTask::Terminate(const TerminateMethod method)
{
	bool is_terminate = isTerminate();
	zTCPTask::Terminate(method);

	if (m_pUser)
	{
		Fir::logger->trace("[GS],charid=%lu,%s,注销 ip=%s",m_pUser->charid,m_pUser->nickname,getIP());
		if(!is_terminate)
		{
			m_pUser->unreg();
			m_pUser->final();
		}

		if (this->isUnique())
		{
			this->uniqueRemove();
			this->initUnique();
		}
	}
	else
	{
		Fir::logger->trace("注销但用户已经不存在");
	}
	// */
}

/**
 * \brief 新用户登陆
 *
 */
void GatewayTask::addToContainer()
{
	GateUser* pUser = new GateUser(this->acctype, this->account, this);
	
	if (!GateUserManager::getMe().addUserAccount(pUser))
	{
		Fir::logger->debug("[登录]addUserAccount失败 (%u,%s)",pUser->acctype,pUser->account.c_str());
	}
	else
	{
		Fir::logger->debug("[登录]addUserAccount成功 (%u,%s)",pUser->acctype,pUser->account.c_str());
	}

	pUser->charid = this->charid;
	pUser->accid  = this->accid; 
	pUser->acctype = this->acctype;
	pUser->strMacAddr = this->strMacAddr;
	pUser->strFlat = this->strFlat;
	pUser->strPhoneUuid = this->strPhoneUuid;
	pUser->account = this->account;

	if (pUser)
	{
		Fir::logger->debug("[登录]通行证 (%u) 创建指针:%p,同步游戏时间",pUser->accid, pUser);
		
        //发送游戏时间，开始计时
        HelloKittyMsgData::GameTime message;
		message.set_gametime(Fir::qwGameTime);
		if(!qwGameTime)
		{
			qwGameTime = Fir::qwGameTime; 
			GameTimeSyn.now();
		}
        std::string ret;
        if(encodeMessage(&message,ret))
        {
            sendCmd(ret.c_str(),ret.size());
        }

		initTime = GatewayTimeTick::currentTime;
		if (pUser->charid == 0)
		{
#if 0
            //系统创建角色
            HelloKittyMsgData::ReturnUserInfo infoMessage;
            infoMessage.set_hasuser(false);
            std::string ret;
            if(encodeMessage(&infoMessage,ret))
            {
                sendCmd(ret.c_str(),ret.size());
            }
#endif
			Fir::logger->debug("[登录],acctype=%u,account=%s,角色为空，等待创建角色",pUser->acctype,pUser->account.c_str());
			pUser->createState();

            //没有角色，系统先帮他创建一个吧
            HelloKittyMsgData::RequireCreateRole createMessage;
            DWORD systemID = zMisc::randBetween(1,10000000);
            char systemName[MAX_NAMESIZE] = {0};
            snprintf(systemName,sizeof(systemName),"%s%u","system",systemID);
            createMessage.set_name(systemName);
            createMessage.set_sex(HelloKittyMsgData::Male);
            createMessage.set_heroid(1);
            this->gate_user_cmd_dispatcher.dispatch(pUser,&createMessage);

		}
		else
		{
			if(pUser->beginSelect())
			{
				//通知登陆服务器，网关连接数
				GatewayService::getMe().notifyLoginServer();
			}
			else 
			{
				//SAFE_DELETE(pUser);
				//pUser = NULL;
				//this->Terminate();
			}
		}
	}
}

/**
 * \brief 从容器中删除
 *
 */
void GatewayTask::removeFromContainer()
{
	//通知登陆服务器，网关连接数
	GatewayService::getMe().notifyLoginServer();
}

/**
 * \brief 添加一个连接线程
 *
 *
 * \return 成功返回ture,否则返回false
 */
bool GatewayTask::uniqueAdd()
{
	return GatewayTaskManager::getMe().uniqueAdd(this);
}

/**
 * \brief 删除一个连接线程
 *
 *
 * \return 成功返回ture,否则返回false
 */
bool GatewayTask::uniqueRemove()
{
	return GatewayTaskManager::getMe().uniqueRemove(this);
}


/**
 * \brief 将消息转发到场景
 *
 *
 * \param ptNullCMD: 需要转发的指令
 * \param nCmdLen: 指令长度
 * \return 转发是否成功
 */
bool GatewayTask::forwardScene(const google::protobuf::Message *message)
{
	if(m_pUser && m_pUser->scene)
	{
		BYTE buf[zSocket::MAX_DATASIZE] = {0};
		CMD::SCENE::t_Scene_ForwardScene *sendCmd=(CMD::SCENE::t_Scene_ForwardScene *)buf;
		constructInPlace(sendCmd);
		sendCmd->charid=m_pUser->charid;
		sendCmd->accid = m_pUser->accid;
        
        std::string ret;
		encodeMessage(message,ret);
        sendCmd->size = ret.size();
		bcopy(ret.c_str(),sendCmd->data,sendCmd->size);

        ret.clear();
        encodeMessage(sendCmd,sizeof(CMD::SCENE::t_Scene_ForwardScene)+sendCmd->size,ret);
		m_pUser->scene->sendCmd(ret.c_str(),ret.size());
		return true;
	}
	return false;
}
/**
 * \brief 将消息转发到Session
 *
 *
 * \param ptNullCMD: 需要转发的指令
 * \param nCmdLen: 指令长度
 * \return 转发是否成功
 */
bool GatewayTask::forwardSession(const google::protobuf::Message *message)
{
	if(m_pUser)
	{
		BYTE buf[zSocket::MAX_DATASIZE] = {0};
		CMD::SESSION::t_Session_ForwardUser *sendCmd = (CMD::SESSION::t_Session_ForwardUser *)buf;
		constructInPlace(sendCmd);
		sendCmd->dwID = m_pUser->charid;

        std::string ret;
        encodeMessage(message,ret);
		sendCmd->size = ret.size();
		bcopy(ret.c_str(),sendCmd->data,sendCmd->size);

        ret.clear();
        encodeMessage(sendCmd,sizeof(CMD::SESSION::t_Session_ForwardUser)+sendCmd->size,ret);
		sessionClient->sendCmd(ret.c_str(),ret.size());
		return true;
	}
	return false;
}
/**
 * \brief 解析时间消息
 *
 *
 * \param ptNullCMD: 需要转发的指令
 * \param nCmdLen: 指令长度
 * \return 解析是否成功
 */
bool GatewayTask::msgParse_Time(const CMD::NullCmd *ptNullCmd, const DWORD nCmdLen)
{
	using namespace CMD;

	switch(ptNullCmd->byParam)
	{
		case USERGAMETIME_TIMER_USERCMD_PARA:
			{
				if(!dwTimestampServer)
				{
					dwTimestampServer=GatewayTimeTick::currentTime.msecs() - ptNullCmd->dwTimestamp;
					if(!dwTimestampServer)
					{
						dwTimestampServer = 1; 
					}
				}
				stUserGameTimeTimerUserCmd *rev=(stUserGameTimeTimerUserCmd *)ptNullCmd;
				if(qwGameTime && (SQWORD)(rev->qwGameTime - (qwGameTime + 
								(GatewayTimeTick::currentTime.sec() - GameTimeSyn.sec()))) >= sampleInterval_error_sec)
				{   
					if(this->m_pUser)
					{
						Fir::logger->trace("客户端游戏时间太快，使用了加速器，需要断开连接（accid = %u, %u, %lu）", this->m_pUser->accid, ptNullCmd->dwTimestamp, rev->qwGameTime - (qwGameTime + (GatewayTimeTick::currentTime.sec() - GameTimeSyn.sec())));
					}
					Fir::logger->debug("游戏时间:(accid=%u,%lu,%lu)", accid,rev->qwGameTime, qwGameTime + (GatewayTimeTick::currentTime.sec() - GameTimeSyn.sec()));
					TerminateWait();
				}

				if (Fir::global["validtime"] == "false")
				     return true;

				haveCheckTime = true;
				return true;
			}
			break;
		case PING_TIMER_USERCMD_PARA:
			{       
				stPingTimeTimerUserCmd cmd;
				sendCmd(&cmd, sizeof(cmd));
				return true;
			}       
			break;  
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->byCmd, ptNullCmd->byParam, nCmdLen);
	return false;
}

/**
 * \brief 检测时间
 *
 * \param ct: 当前时间
 * \return 是否通过检测
 */
bool GatewayTask::checkTime(const zRTime &ct)
{
    return false;
#if 0
	Fir::logger->error("%s", __PRETTY_FUNCTION__);
	if (lastCheckTime(ct) && (initTime.elapse(ct)/1000L>60))
	{
		//			Fir::logger->trace("cur: %u, lastCheckTime: %u ", ct.msecs(), lastCheckTime.msecs());			
		//			if ((ct.msecs() - lastCheckTime.msecs())>120) return false;

		Fir::logger->error("%s 到时间了 可以校时", __PRETTY_FUNCTION__);

		if (haveCheckTime)
		{
			//timeout_count = 0;
			//校对时间
			if(_retset_gametime(ct))
			{
				CMD::stGameTimeTimerUserCmd cmd;
				if(qwGameTime)
				{
					Fir::logger->error("%s 重新和客户端校时", __PRETTY_FUNCTION__);
					cmd.qwGameTime = qwGameTime + (GatewayTimeTick::currentTime.sec() - GameTimeSyn.sec());
					sendCmd(&cmd, sizeof(cmd));
				}
				//准备重新设置同步时间
				dwTimestampServer=0;
			}
			Fir::logger->error("%s 到时间了 跟客户端请求校时", __PRETTY_FUNCTION__);
			haveCheckTime = false; //wait to check time between client adn server.
			CMD::stRequestUserGameTimeTimerUserCmd cmd;
			sendCmd(&cmd, sizeof(cmd));
		}
		else
		{
			//	if (timeout_count>=3)
			//	{
			Fir::logger->trace("客户端指定时间内没有返回校对时间指令（accid = %u, snd_queue_size = %u）,注销", 
					accid, mSocket.snd_queue_size());

			TerminateWait();
			//	}
			//	else
			//	{
			//		Fir::logger->trace("客户端指定时间内没有返回校对时间指令（accid = %u, snd_queue_size = %u）,次数:%u", accid, mSocket.snd_queue_size(), timeout_count);
			//		timeout_count++;
			//	}

			return true;
		}

		//			lastCheckTime = ct;
		//			lastCheckTime.addDelay(checkTimeInterval);
	}
	return false;
#endif
}

/**
 * \brief 对客户端发送过来的指令进行检测
 * 主要检测时间戳等，对加速器等进行防止
 * \param pCmd 待检测的指令
 * \param ct 当前时间
 * \return 检测是否成功
 */
bool GatewayTask::checkUserCmd(const CMD::NullCmd *pCmd, const zRTime &ct)
{
	if(dwTimestampServer)
	{
		//		if(abs((dwTimestampServer + pCmd->dwTimestamp) - ct.msecs()) > sampleInterval_error_msecs)
		if(int((dwTimestampServer + pCmd->dwTimestamp) - ct.msecs()) > (int)sampleInterval_error_msecs)
		{
			Fir::logger->trace("客户端指令时间太快，使用了加速器，需要断开连接（accid = %u, %llu, %llu）(%d, %d)", 
					accid, (dwTimestampServer + pCmd->dwTimestamp) - ct.msecs(), initTime.elapse(ct), 
					pCmd->byCmd, pCmd->byParam);

			v_lastSampleTime = pCmd->dwTimestamp + sampleInterval;
			//			dwTimestampServer = ct.msecs() - pCmd->dwTimestamp;

			return false;
		}
#ifdef _ZJW_DEBUG
		else
		{
			//this->debug("服务器相对时间:%d,客户端相对时间:%d",
			//		ct.msec() - _init_timeSyn.msec(), pCmd->dwTimestamp - _init_dwTimestamp);
		}
#endif

#ifdef _ALL_SUPER_GM
		Fir::logger->debug("accid=%u,客户端传过来的时间戮=%u,服务器时间戮=%u",accid, pCmd->dwTimestamp,v_lastSampleTime);
#endif

		if (pCmd->dwTimestamp >= v_lastSampleTime)
		{
			v_lastSampleTime = pCmd->dwTimestamp + sampleInterval;
			/*
			   if(v_samplePackets > 30)
			   {
			   Fir::logger->debug("%d毫秒收到指令个数%d",sampleInterval , v_samplePackets);
			   }
			// */
			v_samplePackets = 0;
			analysisCmd.clear();
#ifdef _ALL_SUPER_GM
			Fir::logger->debug("accid=%u,客户端传过来的时间戮=%u,服务器时间戮=%u,清空指令分析",accid, pCmd->dwTimestamp,v_lastSampleTime);
#endif
		}
		v_samplePackets++;
		analysisCmd[pCmd->_id]++;
		if (v_samplePackets > maxSamplePPS)
		{
			for (auto it = analysisCmd.begin(); it != analysisCmd.end(); ++it)
			{
				Fir::logger->debug("[客户端消息]id:%u,发送的次数:%u",it->first,it->second);
			}

			Fir::logger->trace("客户端指令发送过快，需要断开连接（accid = %u, %u/%u毫秒）(%u, %u)", 
					accid, v_samplePackets, sampleInterval, pCmd->byCmd, pCmd->byParam);

			analysisCmd.clear();

#ifndef _ZJW_DEBUG			
			return false;
#endif			
		}
		/*
		   int interval = pCmd->dwTimestamp - initTime.elapse(ct);
		   if (interval > 1200)
		   {
		   Fir::logger->trace("客户端时间太快，可能使用了加速器，断开连接（accid = %u, %u, %lu）", accid, pCmd->dwTimestamp, initTime.elapse(ct));
		   return false;
		   }
		// */
	}
	return true;
}

bool GatewayTask::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    const google::protobuf::Message *message = extraceProtoMsg(data,nCmdLen);
    bool ret = false;
    if(!message) 
    {
        return ret;
    }
    
    //如果是消息转发，那么就先优先
    if(forward_cmd_dispatch(m_pUser,message))
    {
        SAFE_DELETE(message);
        return true;
    }

    if(!m_pUser)
    {
        ret = this->gate_task_cmd_dispatcher.dispatch(this,message);
    }
    else
    {
        ret = this->gate_user_cmd_dispatcher.dispatch(m_pUser,message);
    }
    
    SAFE_DELETE(message);
	return ret;
}

/**
 * \brief 解析消息
 *
 * \param ptNull: 需要转发的指令
 * \param nCmdLen: 指令长度
 * \return 解析是否成功
 */
bool GatewayTask::msgParseStruct(const CMD::t_NullCmd *ptNull, const DWORD nCmdLen)
{ 
    if(msgParseNullCmd(ptNull,nCmdLen))
    {
        return true;
    }
	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNull->byCmd, ptNull->byParam, nCmdLen);
	return false;
}

/**
 * \brief 检查新创建的人物名字是否合法
 *
 *
 * \param newName 新名字
 * \return 是否合法
 */
bool GatewayTask::checkNewName(char *_newName)
{
	//DWORD i = 0;
	bool ret = true;

	unsigned char* newName = zMisc::stringConv((unsigned char*)_newName, "UTF-8", "GBK");
	if (!newName) return false;

	/*
	while (newName[i]!=0 && i<strlen((char*)newName) && i<16)
	{
		BYTE a = newName[i];
		if (a<0x80)//asc码
		{
			if (!((a>='0' && a<='9') || (a>='A' && a<='Z') || (a>='a' && a<='z'))) {ret=false;break;}
		}
		else//汉字
		{
			if (!(i<strlen((char*)newName)-1 && i<15)) {ret=false;break;}

			BYTE b = newName[i+1];
			if (b==0x7F || b<0x40 || b>0xFE)//尾字节在 40-FE 之间，剔除 xx7F 一条线
			{
				ret=false;break;
			}

			WORD val = (a<<8)|b;
			if (!((val>=0xB0A1 && val<=0xF7FE)))//GB 2312 汉字 6763 个
					//||(val>=0xB140 && val<=0xA0FE)//CJK汉字 6080 个
					//||(val>=0xAA40 && val<=0xFEA0)))//CJK 汉字和增补的汉字 8160 个
			{
				ret=false;break;
			}
			i++;
		}
		i++;
	}
	*/

	//if ((!wordFilter::getMe().doFilter((char*)newName, 16))
	if (strstr((char*)newName, "蒙面人")
			||strstr((char*)newName, "GM")
			||strstr((char*)newName, "GameMaster")
			||strstr((char*)newName, ":"))
	{
		ret=false;
	}

	if (newName) SAFE_DELETE_VEC(newName);
	return ret;
}

void GatewayTask::login_return(const HelloKittyMsgData::LoginFailReason code)
{
    HelloKittyMsgData::ClientLoginFailReturn message;
    message.set_failreason(code);
    
    std::string ret;
    if(encodeMessage(&message,ret))
    {
        this->sendCmd(ret.c_str(),ret.size());
    }
}

bool GatewayTask::sendCmd(const void *pstrCmd, int nCmdLen)
{
	return zTCPTask::sendCmd(pstrCmd,nCmdLen);
}

bool GatewayTask::checkLoginTime()
{
	if (!_login_gametime(GatewayTimeTick::currentTime))
    {
		return false;
    }
	return true;
}

bool GatewayTask::forward_cmd_dispatch(GateUser* u, const google::protobuf::Message *message)
{
    auto iter = s_protoNameToServerTypeMap.find(message->GetDescriptor());
    if(iter == s_protoNameToServerTypeMap.end())
    {
        return false;
    }
    
    if(!u || !u->isPlayState())
    {
        return true;
    }

    ServerType serverType = iter->second;
    if(serverType == SCENESSERVER)
    {
        forwardScene(message);
    }
    else if(serverType == SESSIONSERVER)
    {
        forwardSession(message);
    }
    return true;
}

void GatewayTask::initProtoDispatch()
{
    //注意，此处为注册某个proto消息流转到哪个类型的服务器

    //场景服务器
    s_protoNameToServerTypeMap[HelloKittyMsgData::RequireAddItem::descriptor()] = SCENESSERVER;
    s_protoNameToServerTypeMap[HelloKittyMsgData::RequireSallPutItem::descriptor()] = SCENESSERVER;
    s_protoNameToServerTypeMap[HelloKittyMsgData::RequireStoreItem::descriptor()] = SCENESSERVER;
    s_protoNameToServerTypeMap[HelloKittyMsgData::UseItem::descriptor()] = SCENESSERVER;
}



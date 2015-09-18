#include "SessionUser.h"
#include "zMetaData.h"
#include <stdarg.h>
#include "SessionServer.h"
#include "zMetaData.h"
#include "TimeTick.h"
#include "xmlconfig.h"
#include "SessionUserManager.h"
#include "SessionTaskManager.h"
#include "TimerMgr.h"
#include "RedisMgr.h"
#include "extractProtoMsg.h"

SessionUser::SessionUser(DWORD gateid, DWORD sceneid)
{
	acctype = 0;
	charid = 0;
	accid = 0;
	m_gate_id = gateid;
	m_scene_id = sceneid;
	sex = 0;
	level = 0;
	lastOnlineTime = 0;
	bzero(nickname,sizeof(nickname));
}

SessionUser::~SessionUser()
{
}

SessionTask* SessionUser::getGatewayTask() const
{
	SessionTask* gate = SessionTaskManager::getMe().getTaskByID(m_gate_id);   
	return gate;
}

SessionTask* SessionUser::getSceneTask() const
{
	SessionTask* scene = SessionTaskManager::getMe().getTaskByID(m_scene_id);
	return scene;
}

bool SessionUser::reg(const CMD::SESSION::t_regUser_GateSession* cmd, bool bFirst)
{
	if(NULL == cmd)
    {
        return false;
    }
    
    CMD::SESSION::t_regUser_SceneSession reg;
	this->acctype = cmd->acctype;
	this->account = cmd->account;
	
    Fir::logger->info("[登陆] 登陆类型:%u, 登陆数字帐号:%s",this->acctype,this->account.c_str());
	
    this->accid = cmd->accid;
	this->charid = cmd->charid;

	strncpy(this->nickname, cmd->name, MAX_NAMESIZE);

	reg.accid = cmd->accid;
	reg.charid = cmd->charid;
	strncpy(reg.name, cmd->name, MAX_NAMESIZE);
	reg.heroid = cmd->heroid;
	strncpy(reg.phone_uuid, cmd->phone_uuid, sizeof(reg.phone_uuid));
	reg.gate_id = m_gate_id;
	SessionTask* scene = SessionTaskManager::getMe().getTaskByID(m_scene_id);	
	if(scene) 
	{
		Fir::logger->debug("[登录],%u,%lu,%s,会话注册向场景发消息",accid,charid,nickname);
        
        std::string ret;
        encodeMessage(&reg,sizeof(reg),ret);
		scene->sendCmd(ret.c_str(),ret.size());
	}

	this->_reg();//进入场景注册状态

	return true;
}

bool SessionUser::sendCmd(const void *pstrCmd, const int nCmdLen) const
{
	if ((DWORD)nCmdLen > zSocket::MAX_DATASIZE)
	{
		Fir::logger->debug("发送消息长度过大:%d",nCmdLen);
		return false;
	}

	SessionTask* gate = SessionTaskManager::getMe().getTaskByID(m_gate_id);
	if(gate)
	{
		return gate->sendCmdToUser(charid, pstrCmd, nCmdLen);
	}
	return false;
}

bool SessionUser::sendCmdToScene(const void *pstrCmd, const int nCmdLen) const
{
	SessionTask* scene = SessionTaskManager::getMe().getTaskByID(m_scene_id);
	if(scene)
		return scene->sendCmd(pstrCmd, nCmdLen);

	return false;
}

void SessionUser::online(DWORD gateid)
{
	m_gate_id = gateid;
    
    char buffer[zSocket::MAX_DATASIZE] = {0};
    *(BYTE*)buffer = STRUCT_TYPE;
	CMD::SESSION::t_regUserSuccess_GateSession &cmd = *(CMD::SESSION::t_regUserSuccess_GateSession*)(buffer+sizeof(BYTE));
    constructInPlace(&cmd);

	cmd.charid = this->charid;
	cmd.accid  = this->accid;
	cmd.scene_id = m_scene_id;

	SessionTask* gate = SessionTaskManager::getMe().getTaskByID(m_gate_id);
	if(gate)gate->sendCmd(buffer, sizeof(BYTE)+sizeof(cmd));	
	this->lastOnlineTime = SessionTimeTick::currentTime.sec();
	Fir::logger->trace("[登录]:(charid=%lu,nickname=%s) 登录场景成功，通知网关进入游戏状态", charid, nickname);
	this->_online();
}

void SessionUser::offline()
{
	SessionTask* scene = SessionTaskManager::getMe().getTaskByID(m_scene_id);
	if (scene) scene->total_online--;

	m_gate_id = 0;
#ifdef _DEBUG_WCX
	Fir::logger->debug("清除 网关连接");
#endif
	//this->scene = NULL;
	this->_offline();
}

bool SessionUser::unreg()
{
    char buffer[zSocket::MAX_DATASIZE] = {0};
    *(BYTE*)buffer = STRUCT_TYPE;
	CMD::SESSION::t_unregUser_SessionScene &cmd = *(CMD::SESSION::t_unregUser_SessionScene*)(buffer+sizeof(BYTE));
    constructInPlace(&cmd);

	cmd.charid = this->charid;
	cmd.accid = this->accid;
	cmd.retcode = 0;

	SessionTask* scene = SessionTaskManager::getMe().getTaskByID(m_scene_id);
	//通知场景注销
	if (scene) scene->sendCmd(buffer,sizeof(BYTE)+sizeof(cmd));

	this->offline();
	return true;
}


void SessionUser::scene_online(DWORD sceneid)
{
	m_scene_id = sceneid;
	SessionTask* scene = SessionTaskManager::getMe().getTaskByID(m_scene_id);
	if(scene) scene->total_online++;

	online(m_gate_id);
}

void SessionUser::sync_play_state()
{
	zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
	
	if (handle==NULL) 
	{
		return;
	}

	handle->setInt("sessionlogin", this->charid, "state", player_state); 
}


#include "SceneUser.h"
#include "zMetaData.h"
#include <stdarg.h>
#include "SceneServer.h"
#include "zMetaData.h"
#include "TimeTick.h"
#include "SessionClient.h"
#include "SceneUserManager.h"
#include <zlib.h>
#include <bitset>
#include "RecordClient.h"
#include "LoginUserCommand.h"
#include "firMD5.h"
#include "xmlconfig.h"
#include <limits>
#include "ResType.h"
#include "RedisMgr.h"
#include "json/json.h"
#include "login.pb.h"
#include "extractProtoMsg.h"

SceneUser::SceneUser(SceneTask *t)
	:_trade(this)
	,_store_house(this)
	,gate(t)
{
	gate = t;
	needSave = false;
	_online = false;
	bzero(lastSaveCharBaseMD5,16);
	bzero(lastSaveMD5,16);
	dwOnlineTime = 0;
}

SceneUser::~SceneUser()
{
}

/**
 * \brief 压缩存档数据 , 没有检测数据超过最大值
 * \pUser 存档数据所属用户
 * \zlib 压缩输出buf
 * \return 压缩后数据大小 , 0 表示压缩出错
 */
int compressSaveData(SceneUser *pUser , unsigned char *zlib,bool &canSave)
{
	if (!pUser)
	{
		Fir::logger->error("[压缩档案数据失败] 人物指针为空，存档失败");
		return 0;
	}
	
    unsigned char unBuf[MAX_UZLIB_CHAR];
	bzero(unBuf, sizeof(unBuf));
	
	// 得到二进制存档
	int uzSize = 0;
	uzSize = pUser->saveBinaryArchive(unBuf+uzSize, MAX_UZLIB_CHAR-uzSize-sizeof(CMD::RECORD::t_WriteUser_SceneRecord));

	uLongf zsize = zSocket::MAX_DATASIZE - sizeof(CMD::RECORD::t_WriteUser_SceneRecord);

	//数据过大，内存越界
	if (uzSize >= MAX_UZLIB_CHAR)
	{
		Fir::logger->error("[压缩档案数据]charid=%lu,nickname=%s, 超过最大数值MAX_UZLIB_CHAR=%u, uzsize=%d, zsize=%u", pUser->charid ,pUser->nickname, MAX_UZLIB_CHAR,uzSize ,(DWORD)zsize);
	    return 0;
    }

	if (SceneService::getMe().md5Verify)
	{
		unsigned char md5[16];
		bzero(md5,16);
		MD5SPACE::MD5Data((unsigned char *)unBuf,uzSize,md5);
		if (strncmp((const char*)md5,pUser->lastSaveMD5,16) != 0)
		{
			canSave = true;
		}
		bcopy(md5,pUser->lastSaveMD5,16);
	}

	// 压缩数据
	int retcode = 0;
	retcode = compress((unsigned char *)zlib , &zsize , (unsigned char *)unBuf , (uLongf)uzSize);
	switch(retcode)
	{
		case Z_OK:
			{
				Fir::logger->debug("压缩档案数据成功(charid=%lu,nickname=%s) , uzsize = %d , size = %u)", pUser->charid, pUser->nickname, uzSize , (DWORD)zsize);
				break;
			}
		case Z_MEM_ERROR:
		case Z_BUF_ERROR:
			{
				Fir::logger->debug("压缩档案数据失败(charid=%lu,nickname=%s)",pUser->charid, pUser->nickname);
				zsize = 0;
				break;
			}
		default:
			{
				Fir::logger->debug("压缩档案数据失败,未知原因(charid=%lu,nickname=%s)",pUser->charid, pUser->nickname);
				zsize = 0;
				break;
			}
	}
	return zsize;
}
#if 0
/**
 * \brief 加载二进制数据
 *
 */
void SceneUser::setupBinaryArchive(const Serialize& binary)
{
	//在线时长
	//BINARY_LOAD_INT(dwOnlineTime,online_time);
	_store_house.load(binary);
	_trade.load(binary);
}
#endif
/**
 * \brief 保存二进制数据
 *
 */
DWORD SceneUser::saveBinaryArchive(unsigned char *out , const int maxsize)
{
    return 0;
#if 0
	Serialize binary; // 二进制数据

	_store_house.save(binary);
	_trade.save(binary);

	binary.SerializeToArray(out,maxsize);
	return binary.ByteSize();
#endif
}

std::string SceneUser::getBinaryArchive()
{
	unsigned char unBuf[MAX_UZLIB_CHAR];
	bzero(unBuf, sizeof(unBuf));

	// 得到二进制存档
	int uzSize = 0; 
	uzSize = saveBinaryArchive(unBuf, MAX_UZLIB_CHAR);

	std::string result((const char*)unBuf,uzSize);
	return result;
}


bool SceneUser::sendCmdToMe(const void *pstrCmd, const int nCmdLen) const
{
	if ((DWORD)nCmdLen > zSocket::MAX_DATASIZE)
	{
		Fir::logger->error("发送消息过大:%d",nCmdLen);
		return false;
	}
	if(gate)
		return gate->sendCmdToUser(charid, pstrCmd, nCmdLen);
	
	return false;
}

bool SceneUser::sendCmdToGateway(const void *pstrCmd, const int nCmdLen) const
{
	if ((DWORD)nCmdLen > zSocket::MAX_DATASIZE)
	{    
		Fir::logger->error("发送消息过大:%d",nCmdLen);
		return false;
	} 

	if(gate)
		return gate->sendCmd(pstrCmd,nCmdLen);

	return false;
}

/**
 * \brief  保存角色数据到record服务器
 * \return 保存成功，返回TRUE,否则返回FALSE
 *
 */
bool SceneUser::save()
{
	//保存角色档案信息
    
    char buffer[zSocket::MAX_DATASIZE] = {0};
    *(BYTE*)(buffer) = STRUCT_TYPE;
    CMD::RECORD::t_WriteUser_SceneRecord *saveChar = (CMD::RECORD::t_WriteUser_SceneRecord*)(buffer+sizeof(BYTE));
    constructInPlace(saveChar);

	saveChar->charid = charid; 
	saveChar->dwMapTempID = 0;

	bcopy(&charbase, &saveChar->charbase, sizeof(CharBase));
	bool canSave = true;

	if (SceneService::getMe().md5Verify)
	{
		unsigned char md5[16];
		bzero(md5,sizeof(md5));
		MD5SPACE::MD5Data((unsigned char *)(&charbase),sizeof(CharBase),md5);
		if (strncmp((const char*)md5,lastSaveCharBaseMD5,16) == 0)
		{
			canSave = false;
		}
		bcopy(md5,lastSaveCharBaseMD5,16);
	}

	saveChar->dataSize = compressSaveData(this , (unsigned char *)saveChar->data,canSave);

	if (!canSave)
	{
		return true;
	}
	Fir::logger->debug("[存档]:%s", saveChar->charbase.nickname);
	recordClient->sendCmd(buffer, sizeof(CMD::RECORD::t_WriteUser_SceneRecord) + saveChar->dataSize + sizeof(BYTE));
	return true;
}

// 获取该角色的二进制信息
std::string SceneUser::getAllBinary()
{
	char buf[zSocket::MAX_DATASIZE] = {0};

	bool canSave = true;
	DWORD dataSize = compressSaveData(this , (unsigned char *)buf,canSave);
	return std::string(buf,dataSize);
}

bool SceneUser::reg(const CMD::SESSION::t_regUser_SceneSession* cmd)
{
	this->charid = cmd->charid;
	this->charid = this->charid;
	this->accid = cmd->accid;
	strncpy(this->nickname, cmd->name, MAX_NAMESIZE);

	if(!RedisMgr::getMe().get_charbase(this->charid,this->charbase))
	{
		Fir::logger->error("[登录]:%u,%lu,%s 玩家注册场景，charbase数据异常",this->accid,this->charid,this->nickname);
		return false;
	}
#if 0
	Serialize binary;
	if(!RedisMgr::getMe().get_binary(this->charid,binary))
	{
		Fir::logger->error("[登录]:%u,%lu,%s 玩家注册场景，binary数据异常",this->accid,this->charid,this->nickname);
		return false;
	}

	setupBinaryArchive(binary);
#endif
	return SceneUserManager::getMe().addUser(this);
}

bool SceneUser::reg_unreg(const BYTE retcode)
{
    char buffer[zSocket::MAX_DATASIZE] = {0};
    *(BYTE*)buffer = STRUCT_TYPE;
	CMD::SESSION::t_unregUser_SceneSession &ret = *(CMD::SESSION::t_unregUser_SceneSession*)(buffer+sizeof(BYTE));
    constructInPlace(&ret);
	ret.charid = this->charid;
	ret.accid = this->accid;
	ret.retcode = retcode;

	return sessionClient->sendCmd(buffer,sizeof(BYTE)+sizeof(ret));
}

void SceneUser::offline()
{
    char buffer[zSocket::MAX_DATASIZE] = {0};
    *(BYTE*)buffer = STRUCT_TYPE;
	CMD::RECORD::t_freshUser_SceneRecord &fresh = *(CMD::RECORD::t_freshUser_SceneRecord*)(buffer+sizeof(BYTE));
	constructInPlace(&fresh);
    fresh.charid = this->charid;
	fresh.accid  = this->accid;
	fresh.scene_id = 0;
	recordClient->sendCmd(buffer,sizeof(BYTE)+sizeof(fresh));

	_online = false;

	charbase.offlinetime = SceneTimeTick::currentTime.sec();

	save();
}

bool SceneUser::online(std::string phone_uuid,SceneTask* _gate)
{
	if (_online || !gate) 
	{
		Fir::logger->error("[登录]:%u,%lu,%s 角色状态出错  online %u ", this->accid, this->charid, this->nickname,_online);
		return false;
	}

	gate = _gate;
	_online = true;


	charbase.onlinetime = SceneTimeTick::currentTime.sec();
	//save();
    
    char buffer[zSocket::MAX_DATASIZE] = {0};
    *(BYTE*)buffer = STRUCT_TYPE;
	CMD::RECORD::t_freshUser_SceneRecord &fresh = *(CMD::RECORD::t_freshUser_SceneRecord*)(buffer+sizeof(BYTE));
    constructInPlace(&fresh);

	fresh.charid = this->charid;
	fresh.accid  = this->accid;
	fresh.scene_id = SceneService::getMe().getServerID();
	recordClient->sendCmd(buffer, sizeof(BYTE)+sizeof(fresh));

	Fir::logger->error("[登录]:%u,%lu,%s 角色注册成功", this->accid, this->charid, this->nickname);

	//----所有上线初始化，放在该行以上------
	//通知会话，场景上线成功
    bzero(buffer+sizeof(BYTE),sizeof(buffer)-sizeof(BYTE));
	CMD::SESSION::t_regUserSuccess_SceneSession &ret = *(CMD::SESSION::t_regUserSuccess_SceneSession*)(buffer+sizeof(BYTE));
    constructInPlace(&ret);

	ret.charid = this->charid;
	ret.accid = this->accid;
	ret.gate_id = gate->getID();

	sessionClient->sendCmd(buffer, sizeof(BYTE)+sizeof(ret));
	
    bzero(buffer+sizeof(BYTE),sizeof(buffer)-sizeof(BYTE));
	CMD::SCENE::t_Refresh_LoginScene &ret_gate = *(CMD::SCENE::t_Refresh_LoginScene*)(buffer+sizeof(BYTE));
    constructInPlace(&ret_gate);
	ret_gate.charid = this->charid;
	if (gate) gate->sendCmd(buffer, sizeof(BYTE)+sizeof(ret_gate));
	
	//----上线初始化完成后的处理 都放在onlineInit这个函数里------
	this->onlineInit();
	return true;
}

bool SceneUser::unreg()
{
	//玩家处于离线状态，除了登录消息，不接收任何其它用户指令
	this->offline();
	return true;
}


void SceneUser::onlineInit()
{
#if 0
	if (0 == this->cm.getCounter(IS_FIRST_LOGIN))
    {
        this->cm.addCounter(IS_FIRST_LOGIN);
        this->_trade.initTradeInfo();
        save();
    }	
    
    login::ReturnSceneUserInfoUserCmd send;
    login::UserBaseInfo *userBaseInfo = send.mutable_userbaseinfo();
	userBaseInfo->set_serverstarttime(Fir::qwStartTime);
    userBaseInfo->set_name(nickname);
    userBaseInfo->set_charid(this->charid);
    userBaseInfo->set_sex(this->charbase.sex);
    userBaseInfo->set_level(this->charbase.level);
    userBaseInfo->set_dwservercurrenttime(SceneTimeTick::currentTime.sec());
    std::string ret;
    
    if(encodeMessage(&send,ret))
    {
        this->sendCmdToMe(ret.c_str(),ret.size());
    }
#endif
}

DWORD SceneUser::getStoreLimit()
{
	return charbase.store_limit;
}

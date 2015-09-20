#include "zTCPClientTask.h"
#include "zTCPClientTaskPool.h"
#include "AllZoneClient.h"
#include "SuperServer.h"
#include "SuperCommand.h"
#include "ServerManager.h"
#include "AllZoneClientManager.h"
#include "AllZoneCommand.h"
#include "RecordCommand.h"
#include "SceneCommand.h"
#include "extractProtoMsg.h"

DWORD AllZoneClient::tempidAllocator = 0;
//#define _JJL_TEST
/**
 * \brief 构造函数
 * \param ip 服务器地址
 * \param port 服务器端口
 */
AllZoneClient::AllZoneClient(
		const std::string &ip, 
		const unsigned short port) : zTCPClientTask(ip, port, true), tempid(++tempidAllocator), netType(NetType_near)
{
}

/**
 * \brief 析构函数
 *
 */
AllZoneClient::~AllZoneClient()
{
}

int AllZoneClient::checkRebound()
{
	int retcode = pSocket->recvToBuf_NoPoll();
	if (retcode > 0)
	{
		BYTE acceptCmd[zSocket::MAX_DATASIZE];
		int nCmdLen = pSocket->recvToCmd_NoPoll(acceptCmd, sizeof(acceptCmd));
		//这里只是从缓冲取数据包，所以不会出错，没有数据直接返回
        if (nCmdLen <= 0)
        {
            return 0;
        }
        
        BYTE messageType = *(BYTE*)acceptCmd;
        BYTE *pstrCmd = acceptCmd + sizeof(BYTE); 
        nCmdLen -= sizeof(BYTE);
        if(messageType != STRUCT_TYPE || nCmdLen <= 0)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, messageType,nCmdLen-1);
            return -1;
        }
        
        using namespace CMD::ALLZONE;
        t_LoginCmd_OK *ptCmd = (t_LoginCmd_OK *)pstrCmd;
        if (ZONECMD == ptCmd->cmd && PARA_LOGIN_OK == ptCmd->para)
        {
            Fir::logger->debug("登陆AllZoneServer成功");
            return 1;
        }
        Fir::logger->error("登陆AllZoneServer失败");
        return -1;
	}
	else
		return retcode;
}

void AllZoneClient::addToContainer()
{
	AllZoneClientManager::getMe().add(this);
}

void AllZoneClient::removeFromContainer()
{
	AllZoneClientManager::getMe().remove(this);
}

bool AllZoneClient::connect()
{
	if(SuperService::getMe().getZoneID().id == 0)
		return false;

	if (!zTCPClientTask::connect())
		return false;
    
	using namespace CMD::ALLZONE;
    t_LoginAllZone tCmd;
    tCmd.zoneID = SuperService::getMe().getZoneID();
   
    std::string ret;
    if(encodeMessage(&tCmd,sizeof(tCmd),ret))
    {
        return sendCmd(ret.c_str(),ret.size());
    }
    return false;
}

bool AllZoneClient::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("AllZoneClient::msgParseProto 没有被处理");
    return true;
}

bool AllZoneClient::msgParseAllZoneCmd(const CMD::ALLZONE::AllZoneNull *allZoneNull,const DWORD nCmdLen)
{
    using namespace CMD::ALLZONE;
    using namespace CMD::SUPER;
    switch(allZoneNull->para)
    {
        case PARA_ALL_ZONE_SUPER_FORWARD_SCENE:
            {
                t_AllZone2Super_Forward2Scene* cmd = (t_AllZone2Super_Forward2Scene*)allZoneNull;
				
				BYTE buf[zSocket::MAX_DATASIZE] = {0};
				t_ForwardSceneFromAllZone *scmd=(t_ForwardSceneFromAllZone *)buf;
				constructInPlace(scmd);
				scmd->datasize = cmd->datasize;
				bcopy(cmd->data, scmd->data, cmd->datasize);
                
                std::string ret;
                encodeMessage(scmd,scmd->datasize,ret);
				ServerManager::getMe().broadcastByID(cmd->sceneid,ret.c_str(),ret.size());
				return true;
			}
            break;
    }

    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, allZoneNull->cmd, allZoneNull->para, nCmdLen);
	return false;
}



bool AllZoneClient::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }
    
    using namespace CMD::ALLZONE;
	using namespace CMD::SUPER;
    switch(ptNullCmd->cmd)
    {
        case ZONECMD:
            {
                return msgParseAllZoneCmd((AllZoneNull*)ptNullCmd,nCmdLen);
            }
            break;
    }
	
    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}


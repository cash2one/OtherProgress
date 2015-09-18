/**
 * \file
 * \version  $Id: ZoneTask.cpp 64 2013-04-23 02:05:08Z  $
 * \author  ,@163.com
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 实现服务器连接类
 *
 * 
 */


#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>

#include "ZoneTask.h"
#include "ZoneManager.h"
#include "Fir.h"
#include "zDBConnPool.h"
#include "AllZoneServer.h"
#include "zString.h"
#include "TimeTick.h"
#include "AllZoneCommand.h"
#include "TradeMgr.h"
#include "extractProtoMsg.h"

int ZoneTask::verifyConn()
{
    int retcode = mSocket.recvToBuf_NoPoll();
    if (retcode > 0)
    {
        BYTE acceptCmd[zSocket::MAX_DATASIZE];
        int nCmdLen = mSocket.recvToCmd_NoPoll(acceptCmd, sizeof(acceptCmd));
        if (nCmdLen <= 0)
        {
            return 0;
        }
        
        using namespace CMD::ALLZONE;
        BYTE messageType = *(BYTE*)acceptCmd;
        BYTE *pstrCmd = acceptCmd + sizeof(BYTE);
        nCmdLen -= sizeof(BYTE);
        if(messageType != STRUCT_TYPE || nCmdLen <= 0)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, messageType,nCmdLen-1);
            return -1;
        }
        
        t_LoginAllZone *ptCmd = (t_LoginAllZone *)pstrCmd;
        if (CMD_LOGIN == ptCmd->cmd && PARA_LOGIN == ptCmd->para)
        {
            _zone_id = ptCmd->zoneID.id;
            Fir::logger->debug("客户端连接通过验证: IP=%s,zoneid=%u",getIP(), _zone_id);
            return 1;
        }
        Fir::logger->error("客户端连接指令验证失败: IP:%s", getIP());
        return -1;
    }
    else
        return retcode;
}

int ZoneTask::waitSync()
{
	using namespace CMD::ALLZONE;
    t_LoginCmd_OK tCmd;
    std::string ret;
    if(encodeMessage(&tCmd,sizeof(tCmd),ret) && sendCmd(ret.c_str(),ret.size()))
    {
        return 1;
    }
    return -1;
}

int ZoneTask::recycleConn()
{
	return 1;
}

void ZoneTask::addToContainer()
{
	ZoneManager::getMe().addServer(this);
}

void ZoneTask::removeFromContainer()
{
	ZoneManager::getMe().removeServer(this);
}

bool ZoneTask::uniqueAdd()
{
	return ZoneManager::getMe().uniqueAdd(this);
}

bool ZoneTask::uniqueRemove()
{
	return ZoneManager::getMe().uniqueRemove(this);
}

bool ZoneTask::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    google::protobuf::Message *message = extraceProtoMsg(data,nCmdLen);
    if(message)
    {
        Fir::logger->error("%s(%s, %u)", __PRETTY_FUNCTION__, message->GetTypeName().c_str(),nCmdLen);
    }
    SAFE_DELETE(message);
    return true;
}


/**
 * \brief 解析来自各个服务器连接的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 指令长度
 * \return 处理是否成功
 */
bool ZoneTask::msgParse(const BYTE *data, const DWORD nCmdLen)
{
	return MessageQueue::msgParse(data,nCmdLen);
}

bool ZoneTask::cmdMsgParse(const BYTE *data, const DWORD nCmdLen)
{
    return zProcessor::msgParse(data,nCmdLen);
}

bool ZoneTask::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

	using namespace CMD::ALLZONE;
	switch(ptNullCmd->_id)
	{
		case ID::t_Super2AllZone_SaleCells:
			{
				t_Super2AllZone_SaleCells *ptCmd = (t_Super2AllZone_SaleCells *)ptNullCmd;
				std::vector<CMD::stSaleCell> vecCells;
				for(DWORD i=0; i<ptCmd->count; i++)
				{
					vecCells.push_back(ptCmd->data[i]);
				}
				TradeMgr::getMe().addSaleInfo(ptCmd->charid,vecCells);
				Fir::logger->info("t_Super2AllZone_SaleCells, charid=%lu,vecCells.size=%u",ptCmd->charid,(DWORD)vecCells.size());
				return true;
			}
			break;
		case ID::t_Super2AllZone_ReqSomePlayerSaleCells:
			{
				t_Super2AllZone_ReqSomePlayerSaleCells *ptCmd = (t_Super2AllZone_ReqSomePlayerSaleCells *)ptNullCmd;
				TradeMgr::getMe().reqSomePlayersSaleCells(_zone_id,ptCmd->sceneid,ptCmd->charid);
				return true;
			}
			break;
		default:
			break;
	}

	Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
	return false;
}


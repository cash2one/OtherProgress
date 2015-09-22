/**
 * \file
 * \version  $Id: RecordClient.h 24 2013-03-30 08:04:25Z  $
 * \author  ,@163.com
 * \date 2005年04月01日 11时56分04秒 CST
 * \brief 定义网关服务器到档案服务器连接客户端
 */

#ifndef _RECORDCLIENT_H_
#define _RECORDCLIENT_H_

#include "zTCPClient.h"
#include "zMutex.h"
#include "RecordCommand.h"
/**
 * \brief 网关与档案服务器的连接
 *
 */
class RecordClient : public zTCPBufferClient
{

	public:
		
		/**
		 * \brief 构造函数
		 *
		 * \param name 名称
		 * \param ip 服务器地址
		 * \param port 服务器端口
		 */
		RecordClient(
				const std::string &name, 
				const std::string &ip, 
				const unsigned short port)
			: zTCPBufferClient(name, ip, port),m_playernum(0) {};

		bool connectToRecordServer();
		void run();
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
		bool msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen);
        DWORD playerNum(){ return m_playernum ;}
    private:
        //处理recordCmd 消息
        bool msgParseRecordCmd(const CMD::RECORD::RecordNull *recordNull,const DWORD nCmdLen);
        DWORD m_playernum;


};

class ManagerRecordClient
{
    public:
        RecordClient* GetRecordByServerId(DWORD wServerId);
        void addRecord(DWORD wServerId,RecordClient *pclient);
        RecordClient* GetMinPlayerRecord();
        void final();

private:
    std::map<DWORD,RecordClient*> m_mapRecord; 

};

extern ManagerRecordClient MgrrecordClient;

#endif

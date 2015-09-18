#ifndef _AllZoneClient_h_
#define _AllZoneClient_h_

#include "zTCPClientTask.h"
#include "zTCPClientTaskPool.h"
#include "NetType.h"

/**
 * \brief 信息收集客户端连接类
 */
class AllZoneClient : public zTCPClientTask
{

	public:

		AllZoneClient(
				const std::string &ip,
				const unsigned short port);
		~AllZoneClient();

		int checkRebound();
		void addToContainer();
		void removeFromContainer();
		bool connect();
		bool msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen);
        bool msgParseProto(const BYTE *data, const DWORD nCmdLen);
		const DWORD getTempID() const
		{
			return tempid;
		}

		const NetType getNetType() const
		{
			return netType;
		}

	private:
		const DWORD tempid;
		static DWORD tempidAllocator;
		NetType netType;

};

#endif


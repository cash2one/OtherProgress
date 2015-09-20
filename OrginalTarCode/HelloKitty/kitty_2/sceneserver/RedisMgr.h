#ifndef _REDIS_MGR_H
#define _REDIS_MGR_H

#include "zSingleton.h"
#include "CharBase.h"
#include "serialize.pb.h"

struct stPuppet
{
	CharBase charbase;
    HelloKittyMsgData::Serialize binary;
};

class RedisMgr : public Singleton<RedisMgr>
{
	friend class Singleton<RedisMgr>;
public:
	virtual ~RedisMgr(){}

	bool get_charbase(const QWORD charid, CharBase& charbase); 
	bool get_binary(const QWORD charid, HelloKittyMsgData::Serialize& binary);
	bool get_binary(const QWORD charid, const char* input_buf, DWORD input_size, HelloKittyMsgData::Serialize& binary);
	bool get_puppet(const QWORD charid, stPuppet& puppet);
private:
	RedisMgr(){}
};

#endif

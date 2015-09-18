#ifndef _REDIS_MGR_H
#define _REDIS_MGR_H

#include "zSingleton.h"
#include "CharBase.h"

struct stPuppet
{
	CharBase charbase;
#if 0
	Serialize binary;
#endif
};

class RedisMgr : public Singleton<RedisMgr>
{
	friend class Singleton<RedisMgr>;
public:
	virtual ~RedisMgr(){}

	bool get_charbase(QWORD charid, CharBase& charbase); 
#if 0
	bool get_binary(QWORD charid, Serialize& binary);
	
    bool get_binary(QWORD charid, const char* input_buf, DWORD input_size, Serialize& binary);
#endif
	bool get_puppet(QWORD charid, stPuppet& puppet);
	
	DWORD get_charidbyName(const std::string nickname);

	DWORD get_charid(const QWORD charid);
private:
	RedisMgr(){}
};

#endif

#ifndef _SESSIONUSERMANAGER_H_
#define _SESSIONUSERMANAGER_H_

#include <functional>
#include "SessionUser.h"

class SessionUserManager : public Singleton<SessionUserManager>
{
	friend class Singleton<SessionUserManager>;
	private:
		zRWLock rwlock;

	private:
		SessionUserManager();
		~SessionUserManager();
	protected:
		std::unordered_map<DWORD,SessionUser*> m_mapUsers;
		std::unordered_map<std::string,DWORD> m_mapCharids;

	public:
		SessionUser* getUserByID(QWORD charid);
		SessionUser* getUserByName(std::string nickname);
		bool addUser(SessionUser *user);
		void removeUser(QWORD charid);

		typedef std::function<void (SessionUser*)> UserFunction;
		void execAll(UserFunction func);
		
		void clearReqFriend();
	    // 获得在线人数,多少秒内登陆过的人
	    DWORD getonlinenum(DWORD second = 300);

		void removeUserBySceneID(SessionTask *task);
		void removeUserByGatewayID(SessionTask *task);
	private:

};
#endif

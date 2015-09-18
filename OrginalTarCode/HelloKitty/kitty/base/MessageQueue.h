
#ifndef _MESSAGEQUEUE_H_
#define _MESSAGEQUEUE_H_
#include "zNullCmd.h"
#include "Fir.h"
#include "zTime.h"
#include "zMisc.h"
#include "zSocket.h"
#include "zMutex.h"
class MessageQueue
{
	protected:
		virtual ~MessageQueue(){};
	public:
        // @brief消息分包函数
		bool msgParse(const BYTE *message, const DWORD cmdLen)
		{
			zMutex_scope_lock scope_lock(lock);
			return cmdQueue.put((void*)message, cmdLen);
		}
        //@brief 消息处理虚函数
		virtual bool cmdMsgParse(const BYTE *message, const DWORD cmdLen)=0;
		bool doCmd()
		{
			CmdPair *cmd = cmdQueue.get();
			while(cmd)
			{
				cmdMsgParse((const BYTE*)cmd->second , cmd->first);
				cmdQueue.erase();
				cmd = cmdQueue.get();
			}
			if(cmd)
			{
				cmdQueue.erase();
			}
			return true;
		}

		unsigned char * getMsgAddress()
		{
			return cmdQueue.getMsgAddress();
		}
	private:
		MsgQueue<> cmdQueue;

		zMutex lock;
};

//这个类只会处理c++消息
template <int _Size = 20>
class MessageBuffer : public zNoncopyable
{
        protected:
            virtual ~MessageBuffer(){};
        public: 
            bool put(const CMD::t_NullCmd *ptNullCmd, const unsigned int cmdLen) 
            {
                return cmdQueue.put((void*)ptNullCmd , cmdLen);
            }
            virtual bool cmdMsgParse(const CMD::t_NullCmd *, const unsigned int)=0; 
            bool doCmd() 
            {
                CmdPair *cmd = cmdQueue.get();
                while(cmd)
                {
                    cmdMsgParse((const CMD::t_NullCmd *)cmd->second , cmd->first);
                    cmdQueue.erase();
                    cmd = cmdQueue.get();
                }
                if(cmd) 
                {
                    cmdQueue.erase();
                }
                return true;
            }       

        private:
            MsgQueue<_Size> cmdQueue;
};
#endif

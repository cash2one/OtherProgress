#ifndef _SESSION_H
#define _SESSION_H

#include <map>
#include <vector>
#include "zSceneManager.h"
#include "SessionCommand.h"
#include "SessionTask.h"
#include "zTime.h"

/**
 * \brief 会话类
 * 用户会话和场景会话的基类
 *
 */
class Session:private zNoncopyable
{

	private:
		///创建时间
		time_t createtime;
		///该会话的连接
		SessionTask *task;

	protected:

		/**
		 * \brief 构造函数
		 * \param task 该会话的连接
		 */
		Session(SessionTask *task)
		{
			createtime=time(NULL);
			this->task=task;
		}

	public:

		/**
		 * \brief 得到该会话的连接
		 * \return 该会话的连接
		 */
		SessionTask *  getTask() const
		{//玩家得到的是网关连接，场景会话得到的是场景服务器连接
			return task;
		}
		
		/**
		 * \brief 向对方发送消息
		 * \param pstrCmd 要发送的消息
		 * \param nCmdLen 消息长度
		 * \return 发送是否成功
		 */
		bool sendCmd(const void *pstrCmd, const int nCmdLen) const
		{
			if (task)
				return task->sendCmd(pstrCmd, nCmdLen);
			else
				return false;
		}
		BYTE sex;
		DWORD level;

};

#endif

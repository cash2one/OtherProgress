
#include "zTCPClientTask.h"
#include "zTCPClientTaskPool.h"
#include "AllZoneClient.h"
#include "AllZoneClientManager.h"
#include "zXMLParser.h"
#include "zMisc.h"

/**
 * \brief 类的唯一实例指针
 */
AllZoneClientManager *AllZoneClientManager::instance = NULL;

/**
 * \brief 构造函数
 */
AllZoneClientManager::AllZoneClientManager()
{
	infoClientPool = NULL;
}

/**
 * \brief 析构函数
 */
AllZoneClientManager::~AllZoneClientManager()
{
	SAFE_DELETE(infoClientPool);
}

bool AllZoneClientManager::reload()
{
	zXMLParser xml;
	if (!xml.initFile(Fir::global["loginServerListFile"]))
	{
		Fir::logger->error("加载统一用户平台AllZoneServer列表文件 %s 失败", Fir::global["loginServerListFile"].c_str());
		return false;
	}
	xmlNodePtr root = xml.getRootNode("Fir");
	if (root)
	{
		xmlNodePtr fir_node = xml.getChildNode(root, "AllZoneServerList");
		while(fir_node)
		{
			if (strcmp((char *)fir_node->name, "AllZoneServerList") == 0)
			{
				xmlNodePtr node = xml.getChildNode(fir_node, "server");
				while(node)
				{
					if (strcmp((char *)node->name, "server") == 0)
					{
						Fir::global["AllZoneServer"] = "";
						Fir::global["AllZonePort"] = "";
						if (xml.getNodePropStr(node, "ip", Fir::global["AllZoneServer"])
								&& xml.getNodePropStr(node, "port", Fir::global["AllZonePort"]))
						{
							Fir::logger->debug("AllZoneServer: %s, %s", Fir::global["AllZoneServer"].c_str(), Fir::global["AllZonePort"].c_str());
							infoClientPool->put(new AllZoneClient(Fir::global["AllZoneServer"], atoi(Fir::global["AllZonePort"].c_str())));
						}
					}

					node = xml.getNextNode(node, NULL);
				}
			}

			fir_node = xml.getNextNode(fir_node, NULL);
		}
	}

	Fir::logger->info("加载统一用户平台AllZoneServer列表文件成功");
	return true;

}

/**
 * \brief 初始化管理器
 * \return 初始化是否成功
 */
bool AllZoneClientManager::init()
{
	infoClientPool = new zTCPClientTaskPool();
	if (NULL == infoClientPool
			|| !infoClientPool->init())
		return false;

	zXMLParser xml;
	if (!xml.initFile(Fir::global["loginServerListFile"]))
	{
		Fir::logger->error("加载统一用户平台AllZoneServer列表文件 %s 失败", Fir::global["loginServerListFile"].c_str());
		return false;
	}
	xmlNodePtr root = xml.getRootNode("Fir");
	if (root)
	{
		xmlNodePtr fir_node = xml.getChildNode(root, "AllZoneServerList");
		while(fir_node)
		{
			if (strcmp((char *)fir_node->name, "AllZoneServerList") == 0)
			{
				xmlNodePtr node = xml.getChildNode(fir_node, "server");
				while(node)
				{
					if (strcmp((char *)node->name, "server") == 0)
					{
						Fir::global["AllZoneServer"] = "";
						Fir::global["AllZonePort"] = "";
						if (xml.getNodePropStr(node, "ip", Fir::global["AllZoneServer"])
								&& xml.getNodePropStr(node, "port", Fir::global["AllZonePort"]))
						{
							Fir::logger->debug("AllZoneServer: %s, %s", Fir::global["AllZoneServer"].c_str(), Fir::global["AllZonePort"].c_str());
							infoClientPool->put(new AllZoneClient(Fir::global["AllZoneServer"], atoi(Fir::global["AllZonePort"].c_str())));
						}
					}

					node = xml.getNextNode(node, NULL);
				}
			}

			fir_node = xml.getNextNode(fir_node, NULL);
		}
	}

	Fir::logger->info("加载统一用户平台AllZoneServer列表文件成功");
	return true;
}

/**
 * \brief 周期间隔进行连接的断线重连工作
 * \param ct 当前时间
 */
void AllZoneClientManager::timeAction(const zTime &ct)
{
	if (actionTimer.elapse(ct) > 8)
	{
		if (infoClientPool)
		{
			if (infoClientPool->isReload())
			{
				this->reload();
			}

		//	infoClientPool->timeAction(ct);
		}
		actionTimer = ct;
	}
}

void AllZoneClientManager::resetState()
{
	if (infoClientPool) infoClientPool->resetAll();
}

/**
 * \brief 向容器中添加已经成功的连接
 * \param infoClient 待添加的连接
 */
void AllZoneClientManager::add(AllZoneClient *infoClient)
{
	if (infoClient)
	{
		zRWLock_scope_wrlock scope_wrlock(rwlock);
		const_iter it = allClients.find(infoClient->getTempID());
		if (it == allClients.end())
		{
			allClients.insert(value_type(infoClient->getTempID(), infoClient));
			setter.insert(infoClient);
		}
	}
}

/**
 * \brief 从容器中移除断开的连接
 * \param infoClient 待移除的连接
 */
void AllZoneClientManager::remove(AllZoneClient *infoClient)
{
	if (infoClient)
	{
		zRWLock_scope_wrlock scope_wrlock(rwlock);
		iter it = allClients.find(infoClient->getTempID());
		if (it != allClients.end())
		{
			allClients.erase(it);
			setter.erase(infoClient);
		}
	}
}

/**
 * \brief 向成功的所有连接广播指令
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 待广播指令的长度
 */
bool AllZoneClientManager::broadcastOne(const void *pstrCmd, int nCmdLen)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(AllZoneClient_set::iterator it = setter.begin(); it != setter.end(); ++it)
	{
		if ((*it)->sendCmd(pstrCmd, nCmdLen))
			return true;
	}
	return false;
}

/**
 * \brief 向成功的所有连接随机选一个广播指令
 * \param pstrCmd 待广播的指令
 * \param nCmdLen 待广播指令的长度                      
 */
bool AllZoneClientManager::broadcastRandom(const void *pstrCmd, int nCmdLen)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	
	BYTE bound = 0;
	BYTE index = 0;
	if (!setter.empty())
	{
		bound = zMisc::randBetween(0,setter.size() - 1);
	}
	for(AllZoneClient_set::iterator it = setter.begin(); it != setter.end(); ++it)
	{
		if ((index++ == bound) && (*it)->sendCmd(pstrCmd, nCmdLen))
		{
#ifdef _LX_DEBUG
			Fir::logger->debug("AllZoneServer: random index %u %s %u",index,(*it)->ip.c_str(),(*it)->port);	
#endif
			return true;
		}
	}
	return false;
}

bool AllZoneClientManager::sendTo(const DWORD tempid, const void *pstrCmd, int nCmdLen)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	iter it = allClients.find(tempid);
	if (it == allClients.end())
		return false;
	else
		return it->second->sendCmd(pstrCmd, nCmdLen);
}


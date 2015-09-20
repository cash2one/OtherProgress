#ifndef _TRADE_MGR_H_
#define _TRADE_MGR_H_

#include <string>
#include <map>
#include <vector>
#include <set>
#include <unordered_map>

#include "zType.h"
#include "zMisc.h"
#include "Fir.h"
#include "zRWLock.h"
#include "common.h"
#include "serialize.pb.h"

class TradeMgr : public Singleton<TradeMgr>
{
	private:
		friend class Singleton<TradeMgr>;
		TradeMgr();
		~TradeMgr();

	public:
        //刷新摊位单元格
        void flushCeil(const DWORD zoneID,const HelloKittyMsgData::PbSaleCeilFlushZone *meaasge);
        void reqSomePlayersSaleCells(DWORD zoneid,DWORD sceneid,QWORD charid);		
        //刷新报纸信息(一般每天重新生成一次)
        void flushCellPaper(const DWORD zoneID,const DWORD sceneID,const QWORD charid);
    private:
        struct SellInfo
		{
            //charid(所有服唯一)
			DWORD charid;
            //玩家昵称
            char name[MAX_NAMESIZE];
            // 最后一次修改时间
			DWORD modifyTime;
            //摊位数据
            HelloKittyMsgData::PbSaleCell saleCell;
			SellInfo()
			{
				charid = 0;
                bzero(name,sizeof(name));
				modifyTime = 0;
			}
		};
    private:
        //刷新关注此人摊位的所有人的paper
        void noticeAttention(const QWORD charid);
        //随机生成包含randNum多个人的寄售信息
        void randSallPaper(const QWORD charid,const DWORD randNum = 20);
        //重置寄售报纸信息
        void resetSellPaper(const DWORD zoneID,const DWORD charid);
    private:
        typedef std::unordered_map<QWORD,SellInfo> SellInfoMap;
        //全服务器所有摊位信息<区ID:<角色ID:角色摊位>>
        std::unordered_map<DWORD,SellInfoMap> m_zoneSellInfoMap;

        typedef std::unordered_map<QWORD,HelloKittyMsgData::SellPaperCell> SellPaperMap;
        //全服务器sellpaper <角色ID:<角色ID:角色摊位信息简介>>
        std::unordered_map<QWORD,SellPaperMap> m_sellPaperMap;
        //全服务器被关注信息 <角色ID:<被关注容器>>
		zRWLock rwlock;
};

#endif


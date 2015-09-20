#ifndef _UTRADE_H
#define _UTRADE_H

#include "zType.h"
#include <map>
#include <set>
#include <bitset>
#include "TradeCommand.h"
#include "serialize.pb.h"

class SceneUser;

/**
 * \brief 计数管理器
 *
 */
class UTrade
{
	public:
		UTrade(SceneUser* u);
		~UTrade();
        //序列化保存数据
		void save(HelloKittyMsgData::Serialize& binary);
        //反序列化还原数据
		void load(const HelloKittyMsgData::Serialize& binary);
        //刷新摊位
		bool flushSaleBooth();
        //在某个格子上放上东西
		bool addSallItem(const HelloKittyMsgData::RequireSallPutItem *cmd);
		bool ret_someplayer_salecells(const std::vector<char>& vecBinary);
		//初始化摊位		
		bool initTradeInfo();
        //从全服返回寄售报纸信息
        bool returnSellPaper(const HelloKittyMsgData::ReturnSellPaper *cmd);	
        //物品下架
        bool offSallItem(const HelloKittyMsgData::RequireSallDownItem *cmd);
        //开通某个摊位
        bool openCeil(const HelloKittyMsgData::RequireOpenCell *cmd);
        //请求paper
        bool requireCellPaper(const HelloKittyMsgData::RequirSellPaper *cmd);
    private:
        //扩充一个格子
		bool addSaleCell(const DWORD cellid);
        //判断格子是否存在
		bool hasCell(const DWORD cellid);
        //获得摊位的格子
        HelloKittyMsgData::PbSaleCell* getCell(const DWORD cellid);
        //刷新单个单元格(全区)
        bool flushSaleCeilZone(const DWORD cellID);
        //刷新单个单元格(客户端)
        bool flushSaleCeilClient(const DWORD cellID);
        //东西下架刷新下一个待售物品
        void flushZoneNextSaleCell();
    private:
        SceneUser* m_owner;
        bool m_wait;
        HelloKittyMsgData::ReturnSellPaper m_sellPaper;
        HelloKittyMsgData::PbSaleBooth m_saleBooth;
};

#endif


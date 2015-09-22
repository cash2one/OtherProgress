#ifndef _UTRADE_H
#define _UTRADE_H

#include "zType.h"
#include <map>
#include <set>
#include <bitset>
#include "TradeCommand.h"
#include "serialize.pb.h"
#include "enterkitty.pb.h"
#include "zRWLock.h"
#include "SceneCommand.h"

//开通一个摊位格子需要花费10个钻石
const DWORD PURCHASE_SALL_CELL = 10;
//下架物品支付10个钻石
const DWORD DWON_GOOD_PAY = 10;
//报纸刷新频率
const DWORD RAND_PAPER_CD = 2 * 3600;
//初始化有3个没有开通的摊位格子
const DWORD CLOSE_CELL_NUM = 3;
//初始化开通7个
const DWORD OPEN_CELL_NUM = 7;
enum TradeStatusType
{
    Trade_status_Normal      =  0,   //正常状态
    Trade_status_Wait_Paper  =  1,   //等待生成paper状态
    Trade_status_Sync_Cell   =  2,   //等待sync状态
};

class SceneUser;
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
		bool addSallItem(const HelloKittyMsgData::ReqSallPutItem *cmd);
		bool ret_someplayer_salecells(const std::vector<char>& vecBinary);
		//初始化摊位		
		bool initTradeInfo();
        //从全服返回寄售报纸信息
        bool returnSellPaper(const HelloKittyMsgData::SellPaper *cmd);	
        //物品下架
        bool offSallItem(const DWORD cellID);
        //开通某个摊位
        bool openCeil();
        //请求paper
        bool requireCellPaper(const HelloKittyMsgData::ReqSellPaper *cmd);
        //打广告
        bool advertise(const HelloKittyMsgData::ReqAdvertise *cmd);
        //gm刷新报纸
        bool requireCellPaper(const BYTE randType = 0);
        //对被购买物品加锁
        void purchaseItemLock(const CMD::SCENE::t_UserPurchaseLockItem *cmd );
        //解锁和转移道具
        void purchaseUnLockItem(const CMD::SCENE::t_UserPurchaseUnlockeItem *cmd);
        //拿钱
        bool reqGetCellMoney(const DWORD cellID);
        //刷新摊位数据
        void flushSaleBooth(HelloKittyMsgData::AckFlushSaleBooth &flush);
    private:
        //扩充一个格子
		bool addSaleCell(const DWORD cellid);
        //判断格子是否存在
		bool hasCell(const DWORD cellid);
        //刷新单个单元格(全区)
        bool flushSaleCeilZone(const DWORD cellID,const bool addFlg = true);
        //获得摊位的格子
        HelloKittyMsgData::PbSaleCell* getCell(const DWORD cellid);
        //刷新单个单元格(客户端)
        bool flushSaleCeilClient(const DWORD cellID);
        //东西下架刷新下一个待售物品
        void flushZoneNextSaleCell();
        //摊位操作失败原因
        bool opFailReturn(const HelloKittyMsgData::ErrorCodeType &commonError = HelloKittyMsgData::Error_Common_Occupy,const HelloKittyMsgData::TradeFailCodeType &code = HelloKittyMsgData::Trade_Occupy);
        //重置数据
        void reset();
    private:
        SceneUser* m_owner;
        DWORD m_status; 
        //有2种报纸,好友跟路人
        std::map<BYTE,HelloKittyMsgData::SellPaper> m_sellPaper;
        HelloKittyMsgData::PbSaleBooth m_saleBooth;
        bool m_advertiseFlg;
        //被购买道具枷锁
        zRWLock itemLock;
};

#endif


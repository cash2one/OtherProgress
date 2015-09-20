#ifndef _USTORE_HOUSE_H
#define _USTORE_HOUSE_H

#include "zType.h"
#include "CharBase.h"
#include <map>
#include <set>
#include <bitset>
#include "serialize.pb.h"
#include "itemInfo.pb.h"
#include "Fir.h"
#include "item.pb.h"

class SceneUser;

/**
 * \brief 计数管理器
 *
 */
class UStoreHouse
{
	public:
		UStoreHouse(SceneUser* u);
		~UStoreHouse();
        //序列化保存数据
		void save(HelloKittyMsgData::Serialize& binary);
        //反序列化加载数据
		void load(const HelloKittyMsgData::Serialize& binary);
		//刷新仓库
        bool flushWareHouse();
	    //增加道具信息	
		bool addItem(const HelloKittyMsgData::PbStoreItem &item);
        //是否有足够道具
		bool hasEnoughItem(const DWORD itemid, const DWORD itemcount);
		//消费某道具
        bool consumeItem(const DWORD itemid, const DWORD itemcount);
        //使用道具
        bool useItem(const DWORD itemid,const DWORD num);
        //仓库空间是否足够
        bool hasEnoughSpace(const DWORD itemcount);
        //道具使用回调函数
        typedef bool (*ITEM_FUN)(SceneUser*,const DWORD,const DWORD);
        
    private:
        //获得仓库现有道具数量
        DWORD getItemCount();
        //添加道具
		bool addItemInner(const HelloKittyMsgData::PbStoreItem &item);
        //初始化s_itemFumMap
	    bool initItemFun();	
	private:
		SceneUser* m_owner;
		std::map<DWORD,HelloKittyMsgData::PbStoreItem> m_itemMap; // 仓库道具
        //道具类型对应回调函数
        static std::map<DWORD,ITEM_FUN> s_itemFumMap;
        //s_itemFumMap初始化标志
        static bool s_initItemFunFlg;
};

#endif


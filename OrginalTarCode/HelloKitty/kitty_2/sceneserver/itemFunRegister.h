#ifndef ITEM_FUN_REGISTER_H
#define  ITEM_FUN_REGISTER_H
#include "UStoreHouse.h"

//道具大类型
enum ItemType
{
    ItemType_Test = 0,         //测试类型
    ItemType_Max  = 20,
};




bool itemTest(SceneUser* owner,const DWORD itemid,const DWORD num);


#endif

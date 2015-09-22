#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include "Fir.h"

#pragma pack(1)

namespace CMD
{ 
    struct stSaleCell
    {
        DWORD cellid;
        DWORD itemid;
        DWORD itemcount;
        DWORD status; // 0空 1放上物品 2已售
        char nickname[MAX_NAMESIZE]; // 购买者的名字
        stSaleCell()
        {
            bzero(this,sizeof(*this));
        }
    };

}
#pragma pack()

#ifdef _MSC_VER
#pragma warning( pop )
#endif
#endif

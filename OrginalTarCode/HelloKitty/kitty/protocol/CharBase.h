/**
 * \file
 * \version  $Id: CharBase.h 53 2013-04-17 05:03:41Z  $
 * \author  ,@163.com
 * \date 2005年01月07日 21时09分24秒 CST
 * \brief 定义人物角色相关信息
 *
 * 
 */

 
#ifndef _CharBase_h_
#define _CharBase_h_

#include "zType.h"
#pragma pack(1)

struct CharBase
{
	QWORD 	charid;				// 角色编号,charid,全区唯一编号
	DWORD   acctype;                        //登陆类型
        char    account[50];     //绑定的数字帐号
	char    password[50];
	char  	nickname[50];	// 角色名称
	DWORD   level;
	BYTE  	sex;							/// 角色性别
	DWORD   createtime;                                             //角色创建时间
	DWORD 	onlinetime;						//在线时间
	DWORD 	offlinetime;					//离线时间
	DWORD   gold;
	DWORD   gem;
	DWORD   store_limit;           //仓库容量
	DWORD   sale_grid_count; // 寄卖中心出售格子数量
	//CharBase()
	//{
	//	bzero(this,sizeof(*this));
	//}
};

enum ChangeType
{
	CHANGE_NONE             = 0,
	CHANGE_DAY              = 1,                // 按天
	CHANGE_WEEK             = 2,                // 按周
	CHANGE_MONTH            = 3,                // 按月
	CHANGE_PHASE            = 4,                // 按时间段
	CHANGE_DIY              = 5,                // 自定义时间
	CHANGE_SIXHOUR          = 6,                // 每天六点
};

enum CounterType
{
	IS_FIRST_LOGIN 					= 0,    //是否是新玩家

};

#pragma pack()

#endif


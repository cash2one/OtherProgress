#ifndef MISC_H__
#define MISC_H__
#include <set>
#include <vector> 
#include <map>
#include "zType.h"
#include "zSingleton.h"
enum eParam
{
    eParam_Rubbish_Create = 1,//垃圾刷新间隔时间，用vector
    eParam_SweetBoxMax   = 2,//糖果罐容积 ，用single
    eParam_SweetBoxClear_Award = 3,//糖果罐奖励，用vector
    eParam_Family_recommend = 4,//家族推荐列表长度
    eParam_Family_ApplyMax = 5,//申请家族长度
    eParam_Family_MemberMax =6,//家族最大人数
    eParam_Family_NameMax = 7,//家族名最大长度
    eParam_Family_NameMin = 8,//家族名最小长度
    eParam_Family_NoticeMax = 9,//家族公告最大长度
    eParam_Family_TopLen = 10,//排行榜置顶显示名次
    eParam_Family_NearRank = 11,//排行榜自己前后显示名次
    eParam_Family_CreateRes = 12,//创建需求资源
    eParam_Family_CreateNeedBulid = 13,//创建家族需求建筑
};


class ParamManager : public Singleton<ParamManager>
{
    friend class Singleton<ParamManager>;
    public:
    DWORD GetSingleParam(eParam eparamType);
    std::vector<DWORD> GetVecParam(eParam eparamType);
    private:
    ParamManager(){}


};
#define PARAM_SINGLE(type) ParamManager::getMe().GetSingleParam(type)
#define PARAM_VEC(type) ParamManager::getMe().GetVecParam(type)
#endif// MISC_H__

#include "taskRegister.h"
#include "SceneUser.h"
#include "zMemDBPool.h"
#include "zMemDB.h"

TargetRetType checkBuildTarger(SceneUser *owner,const pb::Conf_t_Task *taskConf,HelloKittyMsgData::Task *task,const TaskArgue &arg)
{
    TargetRetType ret = Target_Ret_None;
    if(!taskConf || !owner || (!arg.initFlg && (arg.attrID < Attr_Build || arg.attrID > Attr_Add_Build_or_Level)))
    {
        return ret;
    }
    const std::map<DWORD,pb::TaskTarget>& targetMap = taskConf->getTargetMap();
    if(!arg.initFlg)
    {
        auto iter = targetMap.find(arg.key);
        if(iter == targetMap.end())
        {
            return ret;
        }
    }
    
    DWORD process = 0,total = 0;
    for(auto iter = targetMap.begin();iter != targetMap.end();++iter)
    {
        const pb::TaskTarget& taskTarget = iter->second;
        total += taskTarget.para1;
        DWORD num = 0;
        if(iter->first == Attr_Add_Build_or_Level)
        {
            HelloKittyMsgData::DailyData *dailyData = owner->charbin.mutable_dailydata();
            if(arg.initFlg)
            {
                dailyData->set_buildorlevel(0);
            }
            num = dailyData->buildorlevel();
        }
        else
        {
            num = owner->m_buildManager.getBuildLevel(iter->first);
        }
        process += num > taskTarget.para1 ? taskTarget.para1 : num;
    }
    if(!task->total())
    {
        task->set_total(total);
        ret = Target_Ret_Update;
    }
    if(task->current() != process)
    {
        task->set_current(process);
        ret = Target_Ret_Update;
    }
    if(task->current() >= task->total())
    {
        ret = Target_Ret_Finish;
    }
    return ret;
}

TargetRetType checkInterActiveTarger(SceneUser *owner,const pb::Conf_t_Task *taskConf,HelloKittyMsgData::Task *task,const TaskArgue &arg)
{
    TargetRetType ret = Target_Ret_None;
    if(!taskConf || !owner || (!arg.initFlg && (arg.attrID < Attr_Frined || arg.attrID > Attr_Add_Finish_Burst_Event)))
    {
        return ret;
    }
    const std::map<DWORD,pb::TaskTarget>& targetMap = taskConf->getTargetMap();
    if(!arg.initFlg)
    {
        auto iter = targetMap.find(arg.key);
        if(iter == targetMap.end())
        {
            return ret;
        }
    }
    DWORD process = 0,total = 0;
    for(auto iter = targetMap.begin();iter != targetMap.end();++iter)
    {
        const pb::TaskTarget& taskTarget = iter->second;
        total += taskTarget.para1;
        DWORD num = 0;
        switch(iter->first)
        {
            case Attr_Enter_Garden:
                {
                    HelloKittyMsgData::DailyData *dailyData = owner->charbin.mutable_dailydata();
                    if(dailyData)
                    {
                        num = dailyData->vistorother();
                    }
                }
                break;
            case Attr_Add_Friend:
                {
                    HelloKittyMsgData::DailyData *dailyData = owner->charbin.mutable_dailydata();
                    if(dailyData)
                    {
                        num = dailyData->addfriend();
                    }
                }
                break;
            case Attr_Frined:
                {
                    std::set<QWORD> friendSet;
                    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
                    if(!handle)
                    {
                        break;
                    }
                    handle->getSet("rolerelation", owner->charid, "friend", friendSet);
                    num = friendSet.size();
                }
                break;
            default:
                {
                    break;
                }
        }
        process += num > taskTarget.para1 ? taskTarget.para1 : num;
    }
    if(!task->total())
    {
        task->set_total(total);
        ret = Target_Ret_Update;
    }
    if(task->current() != process)
    {
        task->set_current(process);
        ret = Target_Ret_Update;
    }
    if(task->current() >= task->total())
    {
        ret = Target_Ret_Finish;
    }
    return ret;
}

TargetRetType checkSourceTarger(SceneUser *owner,const pb::Conf_t_Task *taskConf,HelloKittyMsgData::Task *task,const TaskArgue &arg)
{
    TargetRetType ret = Target_Ret_None;
    if(!taskConf || !owner || (!arg.initFlg && (arg.attrID < Attr_Money_Gold || arg.attrID > Attr_Add_Happy_Val)))
    {
        return ret;
    }
    const std::map<DWORD,pb::TaskTarget>& targetMap = taskConf->getTargetMap();
    if(!arg.initFlg)
    {
        auto iter = targetMap.find(arg.key);
        if(iter == targetMap.end())
        {
            return ret;
        }
    }
    DWORD process = 0,total = 0;
    for(auto iter = targetMap.begin();iter != targetMap.end();++iter)
    {
        const pb::TaskTarget& taskTarget = iter->second;
        total += taskTarget.para1;
        DWORD num = 0;
        switch(iter->first)
        {
            case Attr_Visitor:
                {
                    num = owner->m_store_house.getAttr(HelloKittyMsgData::Attr_Exp);
                }
                break;
            case Attr_Happy_val:
                {
                    num = owner->m_store_house.getAttr(HelloKittyMsgData::Attr_Happy_Val);
                }
                break;
            case Attr_Money_Gold:
                {
                    num = owner->m_store_house.getAttr(HelloKittyMsgData::Attr_Gold);
                }
                break;
            case Attr_Money_Gem:
                {
                    num = owner->m_store_house.getAttr(HelloKittyMsgData::Attr_Gem);
                }
                break;
            case Attr_Add_Money_Gold:
                {
                    HelloKittyMsgData::DailyData *dailyData = owner->charbin.mutable_dailydata();
                    if(arg.initFlg)
                    {
                        dailyData->set_addgold(0);
                    }
                    num = dailyData->addgold();
                }
                break;
            case Attr_Add_Money_Gem:
                {
                    HelloKittyMsgData::DailyData *dailyData = owner->charbin.mutable_dailydata();
                    if(arg.initFlg)
                    {
                        dailyData->set_addgem(0);
                    }
                    num = dailyData->addgem();
                }
                break;
            case Attr_Add_Visitor:
                {   
                    HelloKittyMsgData::DailyData *dailyData = owner->charbin.mutable_dailydata();
                    if(arg.initFlg)
                    {
                        dailyData->set_addexp(0);
                    }
                    num = dailyData->addexp();
                }
                break;
            case Attr_Add_Happy_Val:
                {
                    HelloKittyMsgData::DailyData *dailyData = owner->charbin.mutable_dailydata();
                    if(arg.initFlg)
                    {
                        dailyData->set_addhappy(0);
                    }
                    num = dailyData->addhappy();
                }
                break;
            default:
                {
                    break;
                }
                break;
        }
        process += num > taskTarget.para1 ? taskTarget.para1 : num;
    }
    if(!task->total())
    {
        task->set_total(total);
        ret = Target_Ret_Update;
    }
    if(task->current() != process) 
    {
        task->set_current(process);
        ret = Target_Ret_Update;
    }
    if(task->current() >= task->total())
    {
        ret = Target_Ret_Finish;
    }
    return ret;
}

TargetRetType checkRoleLevelTarget(SceneUser *owner,const pb::Conf_t_Task *taskConf,HelloKittyMsgData::Task *task,const TaskArgue &arg)
{
    TargetRetType ret = Target_Ret_None;
    if(!taskConf || !owner || (!arg.initFlg && arg.attrID != Attr_Role_Level))
    {
        return ret;
    }
    const std::map<DWORD,pb::TaskTarget>& targetMap = taskConf->getTargetMap();
    if(!arg.initFlg)
    {
        auto iter = targetMap.find(arg.key);
        if(iter == targetMap.end())
        {
            return ret;
        }
    }
    DWORD process = 0,total = 0;
    for(auto iter = targetMap.begin();iter != targetMap.end();++iter)
    {
        const pb::TaskTarget& taskTarget = iter->second;
        total += taskTarget.para1;
        DWORD num = 0;
        switch(iter->first)
        {
            case Attr_Role_Level:
                {
                    num = owner->charbase.level;
                }
                break;
            default:
                {
                    break;
                }
                break;
        }
        process += num > taskTarget.para1 ? taskTarget.para1 : num;
    }
    if(!task->total())
    {
        task->set_total(total);
        ret = Target_Ret_Update;
    }
    if(task->current() != process)
    {
        task->set_current(process);
        ret = Target_Ret_Update;
    }
    if(task->current() >= task->total())
    {
        ret = Target_Ret_Finish;
    }
    return ret;
}

TargetRetType checkAtlasTarget(SceneUser *owner,const pb::Conf_t_Task *taskConf,HelloKittyMsgData::Task *task,const TaskArgue &arg)
{
    TargetRetType ret = Target_Ret_None;
    if(!taskConf || !owner || (!arg.initFlg && (arg.attrID < Attr_Open_Avartar || arg.attrID > Attr_Add_Atlas)))
    {
        return ret;
    }
    const std::map<DWORD,pb::TaskTarget>& targetMap = taskConf->getTargetMap();
    if(!arg.initFlg)
    {
        auto iter = targetMap.find(arg.key);
        if(iter == targetMap.end())
        {
            return ret;
        }
    }
    DWORD process = 0,total = 0;
    for(auto iter = targetMap.begin();iter != targetMap.end();++iter)
    {
        const pb::TaskTarget& taskTarget = iter->second;
        total += taskTarget.para1;
        DWORD num = 0;
        switch(iter->first)
        {
            case Attr_Open_Avartar:
            case Attr_Avartar:
                {
                    num = owner->m_atlasManager.getAtlasNum();
                }
                break;
            case Attr_Fashion_Get:
                {
                    num = owner->m_dressManager.getDressNum();
                }
                break;
            case Attr_Fashion_Has:
                {
                    num = owner->m_dressManager.findLevel(taskTarget.para2);
                }
                break;
            case Attr_Fashion_Dress:
                {
                    num = owner->charbin.dress().id() ? 1 : 0;
                }
                break;
            case Attr_Add_Atlas:
                {
                    HelloKittyMsgData::DailyData *dailyData = owner->charbin.mutable_dailydata();
                    if(arg.initFlg)
                    {
                        dailyData->set_addatlas(0);
                    }
                    num = dailyData->addatlas();
                }
                break;
            default:
                {
                    break;
                }
                break;
        }
        process += num > taskTarget.para1 ? taskTarget.para1 : num;
    }
    if(!task->total())
    {
        task->set_total(total);
        ret = Target_Ret_Update;
    }
    if(task->current() != process) 
    {
        task->set_current(process);
        ret = Target_Ret_Update;
    }
    if(task->current() >= task->total())
    {
        ret = Target_Ret_Finish;
    }
    return ret;
}

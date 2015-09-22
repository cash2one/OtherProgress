#include "dataManager.h"
#include "key.h"
#include "zMisc.h"
#include "tbx.h"

namespace pb
{
    void parseTagString(const std::string &src,const std::string &tag,std::vector<std::string> &retVec)
    {
        std::string parseSrc = src;
        for(size_t pos = parseSrc.find(tag);pos != std::string::npos;)
        {
            size_t len = parseSrc.length();
            retVec.push_back(parseSrc.substr(0,pos));
            parseSrc = parseSrc.substr(pos+1,len-pos-1);
            pos = parseSrc.find(tag);
        }
        if(parseSrc.size())
        {
            retVec.push_back(parseSrc);
        }
    }
    void parsePoint(const std::string &src,Point &destPoint)
    {
        std::vector<std::string> pointVec;
        parseTagString(src,",",pointVec);
        if(pointVec.size() == 2)
        {
            destPoint.x = atoi(pointVec[0].c_str());
            destPoint.y = atoi(pointVec[1].c_str());
        }
    }

    void parseDWORDToDWORDMap(const std::string &src,std::map<DWORD,DWORD> &resultMap,const std::string &separatorTag,const std::string &tag)
    {
        std::vector<std::string> strVec;
        std::string parseSrc = src;
        parseTagString(parseSrc,separatorTag,strVec);
        if(strVec.empty())
        {
            return;
        }

        for(size_t index = 0;index < strVec.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(strVec[index],tag,tempVec);
            if(tempVec.size() != 2)
            {
                continue;
            }

            int key = atol(tempVec[0].c_str());
            if(resultMap.find(key) != resultMap.end())
            {
                continue;
            }
            resultMap.insert(std::pair<DWORD,DWORD>(key,atol(tempVec[1].c_str())));
        }
    }
    
    void parseDWORDToVec(const std::string &src,std::vector<DWORD> &resultVec,const std::string &separatorTag)
    {
        std::vector<std::string> strVec;
        std::string parseSrc = src;
        parseTagString(parseSrc,separatorTag,strVec);
        if(strVec.empty())
        {
            return;
        }

        for(size_t index = 0;index < strVec.size();++index)
        {
            DWORD val = atol(strVec[index].c_str());
            resultVec.push_back(val);
        }
    }


    void parseDWORDSet(const std::string &src,std::set<DWORD> &resultSet,const std::string &separatorTag,const std::string &tag)
    {
        std::vector<std::string> strVec;
        std::string parseSrc = src;
        parseTagString(parseSrc,separatorTag,strVec);
        if(strVec.empty())
        {
            return;
        }

        for(size_t index = 0;index < strVec.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(strVec[index],tag,tempVec);
            int key = atol(tempVec[0].c_str());
            if(resultSet.find(key) != resultSet.end())
            {
                continue;
            }
            resultSet.insert(key);
        }
    }

    void parseStringToStringMap(const std::string &src,std::map<std::string,std::string> &resultMap,const std::string &separatorTag,const std::string &tag)
    {
        std::vector<std::string> strVec;
        std::string parseSrc = src;
        parseTagString(parseSrc,separatorTag,strVec);
        if(strVec.empty())
        {
            return;
        }

        for(size_t index = 0;index < strVec.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(strVec[index],tag,tempVec);
            if(tempVec.size() != 2)
            {
                continue;
            }

            if(resultMap.find(tempVec[0]) != resultMap.end())
            {
                continue;
            }
            resultMap.insert(std::pair<std::string,std::string>(tempVec[0],tempVec[1]));
        }
    }
    
    void parseBuffer(const std::string &src,std::map<DWORD,pb::BufferMsg>& bufferMap)
    {
        std::vector<std::string> strVec;
        parseTagString(src,",",strVec);
        if(strVec.empty())
        {
            return;
        }
        for(size_t index = 0;index < strVec.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(strVec[index],"_",tempVec);
            if(tempVec.size() < 2)
            {
                continue;
            }
            BufferMsg temp;
            temp.id = atol(tempVec[0].c_str());
            temp.val = atol(tempVec[1].c_str());
            temp.time = 0;
            if(tempVec.size() >= 3)
            {
                temp.time = atol(tempVec[2].c_str());
            }
            if(bufferMap.find(temp.id) != bufferMap.end())
            {
                continue;
            }
            bufferMap.insert(std::pair<DWORD,pb::BufferMsg>(temp.id,temp));
        }
    }
    
    std::map<DWORD,std::vector<DWORD>> Conf_t_itemInfo::starMap;
    bool Conf_t_itemInfo::init()
    {
        key = itemInfo ? itemInfo->id() : 0;
        parseBuffer(itemInfo->buffer(),bufferMap);
        initStarMap(itemInfo->starlevel(),itemInfo->id());
        return key;
    }

    void Conf_t_itemInfo::initStarMap(const DWORD starLevel,const DWORD itemID)
    {
        auto iter = starMap.find(starLevel);
        if(iter == starMap.end())
        {
            std::vector<DWORD> temp;
            temp.push_back(itemID);
            starMap.insert(std::pair<DWORD,std::vector<DWORD>>(starLevel,temp));
        }
        else
        {
            std::vector<DWORD> &temp = const_cast<std::vector<DWORD>&>(iter->second);
            temp.push_back(itemID);
        }
    }

    DWORD Conf_t_itemInfo::randStarItem(const DWORD starLevel)
    {
        auto iter = starMap.find(starLevel);
        if(iter == starMap.end())
        {
            return 0;
        }
        const std::vector<DWORD> &temp = iter->second;
        if(temp.empty())
        {
            return 0;
        }
        DWORD randIndex = zMisc::randBetween(0,temp.size()-1);
        return temp[randIndex];
    }


    bool Conf_t_building::init()
    {
        key = buildInfo ? hashKey(buildInfo->dependid(),buildInfo->level()) : 0;
        initAttrMap(); 
        return key;
    }

    void Conf_t_building::initAttrMap()
    {
        if(!buildInfo)
        {
            return;
        }

        parseDWORDToDWORDMap(buildInfo->premisebuild(),dependBuildMap);
        parseDWORDToDWORDMap(buildInfo->requireitem(),materialMap);
        parsePoint(buildInfo->buildgridinfo(),gridPoint);
        parsePoint(buildInfo->effectrange(),effectPoint);
        parseBuffer(buildInfo->effectval(),effectMap);
        if((effectPoint.x || effectPoint.y) && !effectMap.empty())
        {
            bufferFlg = true;
        }
        else
        {
            bufferFlg = false;
        }
    }

    bool Conf_t_newRoleAttr::init()
    {
        key = roleAttr ? roleAttr->tbxid() : 0;
        initItemMap();
        initBuildLevelSet();
        return key;
    }

    void Conf_t_newRoleAttr::initBuildLevelSet()
    {
        if(!roleAttr)
        {
            return;
        }

        std::vector<std::string> buildInfoStrVec;
        parseTagString(roleAttr->initbuild(),",",buildInfoStrVec);
        for(size_t index = 0;index < buildInfoStrVec.size();++index)
        {
            std::vector<std::string> buildInfoVec;
            parseTagString(buildInfoStrVec[index],"_",buildInfoVec);
            if(buildInfoVec.size() != 4)
            {
                Fir::logger->debug("[配置错误],读取新角色属性表的初始建筑字段错误");
                continue;
            }
            InitBuildInfo buildInfo;
            buildInfo.buildID = atol(buildInfoVec[0].c_str());
            buildInfo.buildLevel = atol(buildInfoVec[1].c_str());
            buildInfo.point.x = atoi(buildInfoVec[2].c_str());
            buildInfo.point.y = atoi(buildInfoVec[3].c_str());

            if(buildLevelSet.find(buildInfo) != buildLevelSet.end())
            {
                Fir::logger->debug("[配置错误],读取新角色属性表的初始建筑字段重复");
                continue;
            }
            buildLevelSet.insert(buildInfo);
        }
    }

    void Conf_t_newRoleAttr::initItemMap()
    {
        if(!roleAttr)
        {
            return;
        }
        parseDWORDToDWORDMap(roleAttr->inititem(),itemMap);
    }

    std::map<QWORD,std::set<QWORD>> Conf_t_Task::s_allPreTaskMap;
    bool Conf_t_Task::init()
    {
        key = task ? task->id() : 0;
        initPreTaskSet();
        initRewardMap();
        initTargetMap();
        return key;
    }

    void Conf_t_Task::initPreTaskSet()
    {
        if(!task)
        {
            return;
        }
        std::vector<std::string> tempStrVec;
        parseTagString(task->pre_id(),",",tempStrVec);
        for(size_t index = 0;index < tempStrVec.size();++index)
        {
            QWORD taskID = atol(tempStrVec[index].c_str());
            if(preTaskSet.find(taskID) != preTaskSet.end())
            {
                Fir::logger->debug("[配置错误],读取任务表前置任务字段重复");
                continue;
            }
            preTaskSet.insert(taskID);
            auto iter = s_allPreTaskMap.find(taskID);
            if(iter == s_allPreTaskMap.end())
            {
                std::set<QWORD>temp;
                temp.insert(key);
                s_allPreTaskMap.insert(std::pair<QWORD,std::set<QWORD>>(taskID,temp));
            }
            else
            {
                std::set<QWORD> &temp = const_cast<std::set<QWORD>&>(iter->second);
                temp.insert(key);
            }

        }
    }
    void Conf_t_Task::initRewardMap()
    {
        if(!task)
        {
            return;
        }
        parseDWORDToDWORDMap(task->reward(),rewardMap);
    }
    void Conf_t_Task::initTargetMap()
    {
        if(!task)
        {
            return;
        }

        std::vector<std::string> temp;
        parseTagString(task->target(),",",temp);
        for(size_t index = 0;index < temp.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(temp[index],"_",tempVec);
            if(tempVec.empty())
            {
                Fir::logger->debug("[配置错误],读取任务目标为空(%lu)",key);
                continue;
            }

            DWORD mapKey = atol(tempVec[0].c_str());

            TaskTarget target;
            if(tempVec.size() > 1)
            {
                target.para1 = atol(tempVec[1].c_str());
            }
            if(tempVec.size() > 2)
            {
                target.para2 = atol(tempVec[2].c_str());
            }

            targetMap.insert(std::pair<DWORD,TaskTarget>(mapKey,target));
        }
    }

    bool Conf_t_upgrade::init()
    {
        key = upgrade ? upgrade->level() : 0;
        return key;
    }


    std::map<DWORD,DWORD> Conf_t_Handbook::s_itemAtlasMap;
    bool Conf_t_Handbook::init()
    {
        key = handBook ? handBook->id() : 0;
        initItemMap();
        return key;
    }

    bool Conf_t_Handbook::initItemMap()
    {
        if(!handBook)
        {
            return false;
        }
        auto iter = s_itemAtlasMap.find(handBook->itemid());
        if(iter != s_itemAtlasMap.end())
        {
            Fir::logger->debug("[加载配置表] 图鉴表的道具id重复(%lu,%u)",key,handBook->itemid());
            return false;
        }
        s_itemAtlasMap.insert(std::pair<DWORD,DWORD>(handBook->itemid(),key));
        return true;
    }

    DWORD Conf_t_Handbook::getAtlatID(const DWORD itemID)
    {
        auto iter = s_itemAtlasMap.find(itemID);
        if(iter == s_itemAtlasMap.end())
        {
            return 0;
        }
        return iter->second;
    }

    bool Conf_t_Achievement::init()
    {
        key = achievement ? hashKey(achievement->id(),achievement->stars()) : 0;
        initRewardMap();
        initTargetMap();
        return key;
    }

    void Conf_t_Achievement::initRewardMap()
    {
        if(!achievement)
        {
            return;
        }
        parseDWORDToDWORDMap(achievement->reward(),rewardMap);
    }

    void Conf_t_Achievement::initTargetMap()
    {
        if(!achievement)
        {
            return;
        }

        std::vector<std::string> temp;
        parseTagString(achievement->target(),",",temp);
        for(size_t index = 0;index < temp.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(temp[index],"_",tempVec);
            if(tempVec.empty())
            {
                Fir::logger->debug("[配置错误],读取成就目标为空(%lu)",key);
                continue;
            }

            DWORD mapKey = atol(tempVec[0].c_str());

            TaskTarget target;
            if(tempVec.size() > 1)
            {
                target.para1 = atol(tempVec[1].c_str());
            }
            if(tempVec.size() > 2)
            {
                target.para1 = atol(tempVec[2].c_str());
            }

            targetMap.insert(std::pair<DWORD,TaskTarget>(mapKey,target));
        }
    }

    bool Conf_t_CarnivalData::init()
    {
        key = carnival ? carnival->id() : 0; 

        return key;
    }

    bool Conf_t_rubbish::init()
    {
        key = rubbish ? rubbish->id() : 0; 
        std::vector<std::string> temp;
        parseTagString(rubbish->reward(),";",temp); 
        for(size_t index = 0;index < temp.size();++index)
        {
            std::vector<std::string> tempVec; 
            parseTagString(temp[index],"|",tempVec);
            if(tempVec.size() != 2)
            {
                Fir::logger->debug("[配置错误],读取rubbish rewardower (%lu)",key); 
                continue;
            }

            DWORD resType = atoi(tempVec[0].c_str());
            DWORD value   = atoi(tempVec[1].c_str()); 
            if(resType == 0 || value  == 0)
            {
                Fir::logger->debug("[配置错误],读取rubbish rewardowerower (%lu)",key); 
                continue;


            }
            HelloKittyMsgData::Award *pAward = reward.add_award();
            if(pAward)
            {
                pAward->set_awardtype(resType);
                pAward->set_awardval(value);
            }

        }

        return key;
    }

    bool Conf_t_event::init()
    {
        key = event ? event->id() : 0; 
        std::vector<std::string> temp;
        parseTagString(event->reflushtime(),";",temp); 
        reflushtimemin  = 0;
        reflushtimemax  = 0;
        if(temp.size() == 1)
        {
            reflushtimemin = atoi(temp[0].c_str());
            reflushtimemax =  reflushtimemin;

        }
        else if(temp.size() > 1)
        {
            reflushtimemin = atoi(temp[0].c_str());
            reflushtimemax = atoi(temp[1].c_str());
            if(reflushtimemin > reflushtimemax)
            {
                DWORD tep = reflushtimemin;
                reflushtimemin = reflushtimemax;
                reflushtimemax = tep;
            }

        }
        temp.clear();
        parseTagString(event->buildevent(),";",temp); 
        for(auto it = temp.begin(); it != temp.end();it++)
        {
            DWORD tep = atoi((*it).c_str());
            if(tep > 0)
            {
                buildevent.push_back(tep);
            }
        }
        temp.clear();
        parseTagString(event->target(),";",temp);
        for(auto it = temp.begin(); it != temp.end();it++)
        {
            DWORD tep = atoi((*it).c_str());
            if(tep > 0)
            {
                target.push_back(tep);
            }
        }
        temp.clear(); 
        parseTagString(event->rewardower(),";",temp); 
        for(size_t index = 0;index < temp.size();++index)
        {
            std::vector<std::string> tempVec; 
            parseTagString(temp[index],"|",tempVec);
            if(tempVec.size() != 2)
            {
                Fir::logger->debug("[配置错误],读取rubbish rewardowerower (%lu)",key); 
                continue;
            }


            DWORD resType = atoi(tempVec[0].c_str());
            DWORD value   = atoi(tempVec[1].c_str()); 
            if(resType == 0 || value  == 0)
            {
                Fir::logger->debug("[配置错误],读取rubbish rewardowerower (%lu)",key); 
                continue;


            }
            HelloKittyMsgData::Award *pAward = rewardower.add_award();
            if(pAward)
            {
                pAward->set_awardtype(resType);
                pAward->set_awardval(value);
            }


        }

        temp.clear(); 
        parseTagString(event->rewardguess(),";",temp); 
        for(size_t index = 0;index < temp.size();++index)
        {
            std::vector<std::string> tempVec; 
            parseTagString(temp[index],"|",tempVec);
            if(tempVec.size() != 2)
            {
                Fir::logger->debug("[配置错误],读取rubbish rewardguessower (%lu)",key); 
                continue;
            }
            DWORD resType = atoi(tempVec[0].c_str());
            DWORD value   = atoi(tempVec[1].c_str()); 
            if(resType == 0 || value  == 0)
            {
                Fir::logger->debug("[配置错误],读取rubbish rewardowerower (%lu)",key); 
                continue;


            }
            HelloKittyMsgData::Award *pAward = rewardguess.add_award();
            if(pAward)
            {
                pAward->set_awardtype(resType);
                pAward->set_awardval(value);
            }


        }






        return key;
    }

    bool Conf_t_param::init()
    {
        key = param ? param->id() : 0; 
        std::vector<std::string> temp;
        parseTagString(param->strparam(),";",temp); 
        for(auto it = temp.begin(); it != temp.end();it++)
        {
            DWORD tep = atoi((*it).c_str());
            if(tep > 0)
            {
                vecParam.push_back(tep);
            }
        }

        return key;
    }

    bool Conf_t_produceItem::init()
    {
        key = produceItem ? produceItem->id() : 0;
        parseDWORDToDWORDMap(produceItem->userprop(),materialMap);
        return key;
    }

    bool Conf_t_buffer::init()
    {
        key = buffer ? buffer->id() : 0;
        return key;
    }
    
    DWORD Conf_t_Toy::sumWeight = 0;
    std::map<DWORD,DWORD> Conf_t_Toy::idToWeightMap;
    bool Conf_t_Toy::init()
    {
        key = toy ? toy->id() : 0;
        if(toy->open())
        {
            sumWeight += toy->weight();
            idToWeightMap.insert(std::pair<DWORD,DWORD>(key,sumWeight));
        }
        return key;
    }

    DWORD Conf_t_Toy::randToyKey()
    {
        DWORD randVal = zMisc::randBetween(0,sumWeight);
        for(auto iter = idToWeightMap.begin();iter != idToWeightMap.end();++iter)
        {
            if(randVal > iter->second)
            {
                continue;
            }
            return iter->first;
        }
        return 0;
    }

    bool Conf_t_Dress::init()
    {
        key = dress ? hashKey(dress->id(),dress->level()) : 0;
        parseDWORDToDWORDMap(dress->material(),materialMap);
        parseBuffer(dress->buffer(),bufferMap);
        return key;
    }
    
    bool Conf_t_Paper::init()
    {
        key = paper ? paper->id() : 0;
        parseDWORDToDWORDMap(paper->material(),materialMap);
        parseDWORDToDWORDMap(paper->produce(),produceMap);
        return key;
    }

    std::map<DWORD,DWORD> Conf_t_Divine::retWeightMap;
    bool Conf_t_Divine::init()
    {
        key = divine ? hashKey(divine->id(),divine->lucklevel()) : 0;
        parseDWORDToDWORDMap(divine->reward(),rewardMap);
        parseBuffer(divine->buffer(),bufferMap);
        if(retWeightMap.find(divine->id()) == retWeightMap.end())
        {
            retWeightMap.insert(std::pair<DWORD,DWORD>(divine->id(),divine->weight()));
            weight = divine->weight();
        }
        else
        {
            retWeightMap[divine->id()] += divine->weight();
            weight = retWeightMap[divine->id()];
        }
        return key;
    }

    bool Conf_t_CarnivalShop::init()
    {
        key = carnivalShop ? carnivalShop->id() : 0;
        initWeight();
        parsePoint(carnivalShop->point(),point);
        return key;
    }

    void Conf_t_CarnivalShop::initWeight()
    {
        weight = 0;
        parseDWORDToVec(carnivalShop->weight(),weightVec);
        for(DWORD index = 0;index < weightVec.size();++index)
        {
            weight += weightVec[index];
            weightVec[index] = weight;
        }
    }
    
    std::map<DWORD,std::vector<DWORD>> Conf_t_BurstEventReward::levelGradeRewardMap;
    bool Conf_t_BurstEventReward::init()
    {
        key = burstEventReward ? burstEventReward->id() : 0;
        parseDWORDToDWORDMap(burstEventReward->needitem(),randItemMap);
        parseDWORDToDWORDMap(burstEventReward->reward(),rewardMap);
        auto iter = levelGradeRewardMap.find(burstEventReward->levelgrade());
        if(iter == levelGradeRewardMap.end())
        {
            std::vector<DWORD> levelGradeVec;
            levelGradeVec.push_back(burstEventReward->id());
            levelGradeRewardMap.insert(std::pair<DWORD,std::vector<DWORD>>(burstEventReward->levelgrade(),levelGradeVec));
        }
        else
        {
            std::vector<DWORD> &levelGradeVec = const_cast<std::vector<DWORD>&>(iter->second);
            levelGradeVec.push_back(burstEventReward->id());
        }
        return key;
    }

    DWORD Conf_t_BurstEventReward::randExceptReward(const DWORD level,const std::set<DWORD>&exceptRewardSet)
    {
        DWORD levelGrade = level / 5 + 1;
        levelGrade = zMisc::randBetween(1,levelGrade);
        auto iter = levelGradeRewardMap.find(levelGrade);
        while(iter == levelGradeRewardMap.end())
        {
            levelGrade = zMisc::randBetween(1,levelGrade);
            iter = levelGradeRewardMap.find(levelGrade);
        }
        const std::vector<DWORD> &levelGradeVec = iter->second;
        //避免死循环，限定上线为10次
        for(DWORD cnt = 0;cnt < 10;++cnt)
        {
            DWORD rand = zMisc::randBetween(0,levelGradeVec.size()-1);
            return levelGradeVec[rand];
        }
        return 0;
    }
    
    std::map<DWORD,std::set<DWORD>> Conf_t_BurstEventNpc::levelGradeNpcMap;
    bool Conf_t_BurstEventNpc::init()
    {
        key = burstEventNpc ? burstEventNpc->id() : 0;
        auto iter = levelGradeNpcMap.find(burstEventNpc->levelgrade());
        if(iter == levelGradeNpcMap.end())
        {
            std::set<DWORD> levelGradeSet;
            levelGradeSet.insert(burstEventNpc->id());
            levelGradeNpcMap.insert(std::pair<DWORD,std::set<DWORD>>(burstEventNpc->levelgrade(),levelGradeSet));
        }
        else
        {
            std::set<DWORD> &levelGradeSet = const_cast<std::set<DWORD>&>(iter->second);
            levelGradeSet.insert(burstEventNpc->id());
        }
        return key;
    }
    
    DWORD Conf_t_BurstEventNpc::randExceptNpc(const DWORD level,const std::set<DWORD>&exceptNpcSet)
    {
        DWORD levelGrade = level / 5 + 1;
        levelGrade = zMisc::randBetween(1,levelGrade);
        auto iter = levelGradeNpcMap.find(levelGrade);
        while(iter == levelGradeNpcMap.end())
        {
            levelGrade = zMisc::randBetween(1,levelGrade);
            iter = levelGradeNpcMap.find(levelGrade);
        }
        const std::set<DWORD> &levelGradeSet = iter->second;
        if(levelGradeSet.size() == exceptNpcSet.size() || levelGradeSet.empty())
        {
            return 0;
        }
        std::vector<DWORD> levelGradeVec;
        for(auto it = levelGradeSet.begin();it != levelGradeSet.end();++it)
        {
            if(exceptNpcSet.find(*it) == exceptNpcSet.end())
            {
                levelGradeVec.push_back(*it);
            }
        }

        if(levelGradeVec.empty())
        {
            return 0;
        }

        //避免死循环，限定上线为10次
        for(DWORD cnt = 0;cnt < 10;++cnt)
        {
            DWORD rand = zMisc::randBetween(0,levelGradeVec.size()-1);
            return levelGradeVec[rand];
        }
        return 0;
    }
}

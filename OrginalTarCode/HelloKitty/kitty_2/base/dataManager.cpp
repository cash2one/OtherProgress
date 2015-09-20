#include "dataManager.h"

namespace pb
{
    void parseTagString(const std::string src,const std::string tag,std::vector<std::string> &retVec)
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
    
    bool Conf_t_itemInfo::init()
    {
        key = itemInfo ? itemInfo->tbxid() : 0;
        return key;
    }
    
    bool Conf_t_building::init()
    {
        key = buildInfo ? (buildInfo->dependid() << 16) + buildInfo->level() : 0;
        return key;
    }
    
    bool Conf_t_newRoleAttr::init()
    {
        key = roleAttr ? roleAttr->tbxid() : 0;
        initbuildLevelMap();
        return key;
    }
    
    void Conf_t_newRoleAttr::initbuildLevelMap()
    {
        if(!roleAttr)
        {
            return;
        }

        std::vector<std::string> strVec;
        parseTagString(roleAttr->initbuild(),";",strVec);
        for(size_t index = 0;index < strVec.size();++index)
        {
            std::vector<std::string> tempVec;
            parseTagString(strVec[index],"-",tempVec);
            if(tempVec.size() != 2)
            {
                Fir::logger->debug("错误:Conf_t_newRoleAttr::initbuildLevelMap 中initbuild字段格式错误 %s,%s",roleAttr->initbuild().c_str(),strVec[index].c_str());
                return;
            }
           
            int buildID = atol(tempVec[0].c_str());
            if(buildLevelMap.find(buildID) != buildLevelMap.end())
            {
                Fir::logger->debug("错误:Conf_t_newRoleAttr::initbuildLevelMap 中initbuild建筑id重复");
                continue;
            }
            buildLevelMap[buildID] = atol(tempVec[1].c_str());
        }
    }
}


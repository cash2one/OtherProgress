#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

//此文件是进一步包装excel打出来protobuf的类，方便程序中读取,类的命名规则为Conf_+需要包装的类,一定要包含一个key，此处的key可以自由发挥
#include "zType.h"
#include "Fir.h"
#include "itemInfo.pb.h"
#include "building.pb.h"

namespace pb
{
    //以tag来划开字符串
    void parseTagString(const std::string src,const std::string tag,std::vector<std::string> &retVec);
    //道具表
    class Conf_t_itemInfo
    {
        private:
            QWORD key;
        public:
            inline DWORD getKey() const
            {
                return key;
            }
        public:
            Conf_t_itemInfo(const pb::itemInfo::t_itemInfo *_itemInfo) : itemInfo(_itemInfo) {};
            Conf_t_itemInfo() : itemInfo(NULL) {};
            bool init();
        public:
            const pb::itemInfo::t_itemInfo *itemInfo;
    };
    
    //建筑表
    class Conf_t_building
    {
        private:
            QWORD key;
        public:
            inline DWORD getKey() const
            {
                return key;
            }
        public:
            Conf_t_building(const pb::building::t_building *_buildInfo) : buildInfo(_buildInfo) {};
            Conf_t_building() : buildInfo(NULL) {};
            bool init();
        public:
            const pb::building::t_building *buildInfo;
    };
    
    //新角色属性表
    class Conf_t_newRoleAttr
    {
        private:
            QWORD key;
            std::map<DWORD,DWORD> buildLevelMap;
        public:
            inline DWORD getKey() const
            {
                return key;
            }
        public:
            Conf_t_newRoleAttr(const pb::newRoleAttr::t_newRoleAttr *_roleAttr) : roleAttr(_roleAttr) {};
            Conf_t_newRoleAttr() : roleAttr(NULL) {};
            bool init();
        private:
            //解析buildLevelMap
            void initbuildLevelMap();
        public:
            const pb::newRoleAttr::t_newRoleAttr *roleAttr;
    };
}


#endif

            


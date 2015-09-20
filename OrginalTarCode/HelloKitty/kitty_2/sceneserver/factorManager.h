#ifndef FACTOR_MANAGER_H
#define FACTOR_MANAGER_H
#include "login.pb.h"
#include "serialize.pb.h"
#include "zType.h"
#include "item.pb.h"
# if 0
class SceneUser;
class FactorManager
{
    public:
        FactorManager(SceneUser *owner);
        ~FactorManager();
        void save(HelloKittyMsgData::Serialize& binary);
        void load(HelloKittyMsgData::Serialize& binary);
    private:
        SceneUser *m_owner;
        std::map<DWORD,HelloKittyMsgData::Factor>m_factorMap;
};
#endif
#endif

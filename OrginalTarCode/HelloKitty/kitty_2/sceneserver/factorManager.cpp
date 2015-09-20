#include "factorManager.h"
#include "SceneUser.h"

#if 0

FactorManager::FactorManager(SceneUser *owner)
{
    m_owner = onwer;
}

void FactorManager::save(HelloKittyMsgData::Serialize& binary)
{
    for(auto iter = m_factorMap.begin();iter != m_factorMap.end();++iter)
    {
        HelloKittyMsgData::Factor* factor = binary.add_factor();
        *factor = iter->second;
    }
}

void FactorManager::load(HelloKittyMsgData::Serialize& binary)
{
    for(size_t index=0; index<binary.store_items_size(); index++)
    {
        const HelloKittyMsgData::Factor& factor = binary.factor(index);
        DWORD key = factor.point.x() << 8 + factor.point.y();
        if(m_factorMap.find(key) != m_factorMap.end())
        {
            Fir::logger->debug("工厂管理器加载 位置重复:%u%u",factor.point().x(),factor.point().y());
            continue;
        }
        m_factorMap[key] = factor;
    }
}

#endif

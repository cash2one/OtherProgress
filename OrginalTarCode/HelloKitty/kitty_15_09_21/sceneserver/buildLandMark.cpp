#include "buildLandMark.h"
#include "SceneUser.h"
#include "dataManager.h"
#include "tbx.h"
#include "buffer.h"

BuildTypeLandMark::BuildTypeLandMark(SceneUser* owner,const DWORD typeID,const DWORD level,const Point &point,const bool active) : BuildBase(owner,typeID,level,point,active)
{
}

BuildTypeLandMark::BuildTypeLandMark(SceneUser* owner,const pb::Conf_t_building *buildConf,const Point &point) : BuildBase(owner,buildConf,point)
{
}

BuildTypeLandMark::BuildTypeLandMark(SceneUser* owner,const HelloKittyMsgData::BuildBase &buildBase) : BuildBase(owner,buildBase)
{
}

bool BuildTypeLandMark::checkBuffer(const bool opAdd,const bool notify)
{
    if(!confBase->getBufferFlg() || !isActive())
    {
        return true;
    }

    const std::map<DWORD,pb::BufferMsg> &bufferMap = confBase->getEffectMap();
    Point beginPt,endPt;
    beginPt.x = m_point.x - confBase->getEffectPoint().x;
    beginPt.y = m_point.y - confBase->getEffectPoint().y;
    endPt.x =  m_point.x + confBase->getEffectPoint().x;
    endPt.y =  m_point.y + confBase->getEffectPoint().y;
    
    std::set<QWORD> bufferSet;
    for(int tempX = beginPt.x;tempX <= endPt.x;++tempX)
    {
        for(int tempY = beginPt.y;tempY <= endPt.y;++tempY)
        {
            Point temp(tempX,tempY);
            const std::map<Point,std::set<QWORD>>& tempMap = m_owner->m_kittyGarden.getPointBuildMap();
            auto iter = tempMap.find(temp);
            if(iter == tempMap.end())
            {
                continue;
            }
            const std::set<QWORD> &tempSet = iter->second;
            for(auto setIter = tempSet.begin();setIter != tempSet.end();++setIter)
            {
                if(bufferSet.find(*setIter) != bufferSet.end())
                {
                    continue;
                }
                BuildBase *temp = m_owner->m_buildManager.getBuild(*setIter);
                if(temp == this)
                {
                    continue;
                }
                if(temp->isTypeBuid(Build_Type_Road) || temp->isTypeBuid(Build_Type_Land_Mark))
                {
                    continue;
                }
                opBuffer(temp,m_id,HelloKittyMsgData::BST_Build,bufferMap,opAdd,notify);
                bufferSet.insert(*setIter);
            }
        }
    }
    return true;
}



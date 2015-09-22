#ifndef BUFFER_H
#define BUFFER_H
#include "bufferData.h"
#include "dataManager.h"
#include "buildBase.h"
#include "SceneUser.h"
#include "TimeTick.h"
#include <vector>
#include "common.pb.h"

template<typename T>
bool opBuffer(T *owner,const QWORD srcID,const HelloKittyMsgData::BufferSrcType&srcType,const pb::BufferMsg &bufferMsg,const bool opType = true)
{
    Buffer temp;
    temp.srcID = srcID;
    temp.srcType = srcType;
    temp.id = bufferMsg.id;
    temp.beginTime = SceneTimeTick::currentTime.sec();
    temp.lastTime = bufferMsg.time;
    temp.value = bufferMsg.val;

    auto iter = owner->m_bufferMap.find(srcID);
    if(iter == owner->m_bufferMap.end())
    {
        if(opType)
        {
            std::map<DWORD,Buffer> tempMap;
            tempMap.insert(std::pair<DWORD,Buffer>(temp.id,temp));
            owner->m_bufferMap.insert(std::pair<QWORD,std::map<DWORD,Buffer>>(srcID,tempMap));
        }
        return true;
    }
    std::map<DWORD,Buffer> &tempMap = const_cast<std::map<DWORD,Buffer>&>(iter->second); 
    if(opType)
    {
        auto it = tempMap.find(temp.id);
        if(it != tempMap.end())
        {
            return false;
        }
        tempMap.insert(std::pair<DWORD,Buffer>(temp.id,temp));
        return true;
    }
    auto it = tempMap.find(temp.id);
    if(it == tempMap.end())
    {
        return false;
    }
    tempMap.erase(it);
    if(tempMap.empty())
    {
        owner->m_bufferMap.erase(iter);
    }
    return true;
}

template<typename T>
bool opBuffer(T *owner,const QWORD srcID,const HelloKittyMsgData::BufferSrcType &srcType,const std::map<DWORD,pb::BufferMsg> &bufferMap,const bool opType = true,const bool notify = true)
{
    if(!owner || bufferMap.empty() || !srcID)
    {
        return true;
    }
    for(auto iter = bufferMap.begin();iter != bufferMap.end();++iter)
    {
        opBuffer(owner,srcID,srcType,iter->second,opType);
    }
    if(notify)
    {
        owner->updateBufferMsg();
    }
    return true;
}

template<typename T>
bool loopBuffer(T *owner)
{
    if(!owner)
    {
        return false;
    }
    DWORD now = SceneTimeTick::currentTime.sec();
    bool changeFlg = false;
    std::vector<QWORD> emptyVec;
    for(auto iter = owner->m_bufferMap.begin();iter != owner->m_bufferMap.end();++iter)
    {
        std::map<DWORD,Buffer> &tempMap = const_cast<std::map<DWORD,Buffer>&>(iter->second);
        std::vector<DWORD> delVec;
        for(auto it = tempMap.begin();it != tempMap.end();++it)
        {
            const Buffer& temp = it->second;
            if(temp.lastTime && now > temp.lastTime + temp.beginTime)
            {
                delVec.push_back(temp.id);
            }
        }
        for(auto it = delVec.begin();it != delVec.end();++it)
        {
            tempMap.erase(*it);
            changeFlg = true;
        }
        if(tempMap.empty())
        {
            emptyVec.push_back(iter->first);
        }
    }
    for(auto iter = emptyVec.begin();iter != emptyVec.end();iter++)
    {
        owner->m_bufferMap.erase(*iter);
    }
    if(changeFlg)
    {
        owner->updateBufferMsg();
    }
    return true;
}

template<typename T>
DWORD getBufferVal(T *owner,const HelloKittyMsgData::BufferTypeID &type)
{
    DWORD sum = 0;
    if(!owner)
    {
        return sum;
    }
    for(auto iter = owner->m_bufferMap.begin();iter != owner->m_bufferMap.end();++iter)
    {
        const std::map<DWORD,Buffer> &tempMap = iter->second;
        auto it = tempMap.find(type);
        if(it != tempMap.end())
        {
            const Buffer &bufferInst = it->second;
            sum += bufferInst.value; 
        }
    }
    return sum;
}



#endif


#ifndef BUFFER_DATA_H
#define BUFFER_DATA_H
#include "build.pb.h"
#include "zType.h"

struct Buffer
{
    //来源实例id
    QWORD srcID;
    //来源类型
    DWORD srcType;
    //bufferID
    DWORD id;
    //开始时间
    DWORD beginTime;
    //持续时间
    DWORD lastTime;
    //buffer值
    DWORD value;
    Buffer()
    {
        srcID = 0;
        srcType = 0;
        id = 0;
        beginTime = 0;
        lastTime = 0;
        value = 0;
    }
    void save(HelloKittyMsgData::BufferData &bufferData) const
    {
        bufferData.set_srcid(srcID);
        bufferData.set_srctype(HelloKittyMsgData::BufferSrcType(srcType));
        bufferData.set_bufferid(HelloKittyMsgData::BufferTypeID(id));
        bufferData.set_begintime(beginTime);
        bufferData.set_lasttime(lastTime);
        bufferData.set_value(value);
        return;
    }
    void load(const HelloKittyMsgData::BufferData &bufferData)
    {
        srcID = bufferData.srcid();
        srcType = bufferData.srctype();
        id = bufferData.bufferid();
        beginTime = bufferData.begintime();
        lastTime = bufferData.lasttime();
        value = bufferData.value();
        return;
    }
};

#endif

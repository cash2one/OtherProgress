#include "extractProtoMsg.h"

//通过消息的名称，查找且拷贝出一份消息
google::protobuf::Message* createMessage(const char *messageName)
{
    google::protobuf::Message *message = NULL;
    if(!messageName)
    {
        return message;
    }
    
    const google::protobuf::Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(messageName);
    if(!descriptor)
    {
        return message;
    }

    const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
    if(prototype)
    {
        message = prototype->New();
    }
    return message;
}

//把接收到的消息萃取Message
google::protobuf::Message* extraceProtoMsg(const BYTE *data, const DWORD nCmdLen)
{
    google::protobuf::Message *message = NULL;

    DWORD dataOffset = 0;
    DWORD messageNameLen = *(DWORD*)(data+dataOffset);
    if(!messageNameLen)
    {
        return message;
    }
    
    dataOffset += sizeof(DWORD);
    char messageName[messageNameLen+1];
    bzero(messageName,sizeof(messageName));
    strncpy(messageName,(const char*)(data+dataOffset),messageNameLen);

    dataOffset += messageNameLen;
    message = createMessage(messageName);
    if(!message)
    {
        return message;
    }

    if(nCmdLen <= dataOffset)
    {
        SAFE_DELETE(message);
        return message;
    }

    message->ParseFromArray(data+dataOffset, nCmdLen-dataOffset);

	return message;
}

bool encodeMessage(const google::protobuf::Message *message,std::string &result)
{
    if(!message)
    {
        return false;
    }
    BYTE messageType = PROTOBUF_TYPE;
    result.append(reinterpret_cast<char*>(&messageType), sizeof(BYTE));
    const std::string& typeName = message->GetTypeName();
    int32_t nameLen = static_cast<int32_t>(typeName.size()+1);
    result.append(reinterpret_cast<char*>(&nameLen), sizeof(int32_t));
    result.append(typeName.c_str(), nameLen);
    return message->AppendToString(&result);
}
 
bool encodeMessage(const _null_cmd_ *message,const DWORD len,std::string &result)
{
    if(!message || len <= 0 )
    {
        return false;
    }
    BYTE messageType = STRUCT_TYPE;
    result.append(reinterpret_cast<char*>(&messageType), sizeof(BYTE));
    result.append((char*)(&(*message)),len);
    return true;
}

void logStructMessage(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen,const bool sendFlg)
{
    Fir::logger->debug("c++ [%s消息统计](%u,%u,%u)",sendFlg ? "发送" : "接收",ptNullCmd->cmd,ptNullCmd->para,nCmdLen);
}

bool encodeMessage(const char *data,const DWORD size,std::string &result)
{
    if(!data || size <= 0)
    {
        return false;
    }
    
    BYTE messageType = STRUCT_TYPE;
    result.append(reinterpret_cast<char*>(&messageType), sizeof(BYTE));
    result.append(data,size);
    return true;
}

void logProtoMessage(const char *name,const DWORD nCmdLen,const bool sendFlg)
{    
    Fir::logger->debug("proto [%s消息统计](%s,%u)",sendFlg ? "发送" : "接收",name,nCmdLen);
}

void logMessage(const char *data,const DWORD nCmdLen,const bool sendFlg)
{
    if(!data || nCmdLen <= 0)
    {
        return;
    }
    
    BYTE messageType = *(BYTE*)data;
    if(messageType == STRUCT_TYPE)
    {
        return logStructMessage((CMD::t_NullCmd*)data,nCmdLen-1,sendFlg);
    }
    else if(messageType != PROTOBUF_TYPE)
    {
        return;
    }
    DWORD nameLen = *(DWORD*)(data+sizeof(BYTE));
    if(nameLen <= 0)
    {
        return;
    }
    char messageName[nameLen + 1];
    bzero(messageName,sizeof(messageName));
    strncpy(messageName,data+sizeof(BYTE)+sizeof(DWORD),nameLen);
    return logProtoMessage(messageName,nCmdLen-sizeof(BYTE)-sizeof(DWORD)-nameLen,sendFlg);
}



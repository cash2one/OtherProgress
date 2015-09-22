//此文件为user的序列化和反序列化函数

#include "SceneUser.h"
#include "zMetaData.h"
#include <stdarg.h>
#include "SceneServer.h"
#include "zMetaData.h"
#include "TimeTick.h"
#include "SceneUserManager.h"
#include <zlib.h>
#include <bitset>
#include "RecordClient.h"
#include "LoginUserCommand.h"
#include "firMD5.h"
#include "xmlconfig.h"
#include <limits>
#include "ResType.h"
#include "RedisMgr.h"
#include "json/json.h"
#include "login.pb.h"
#include "extractProtoMsg.h"
#include "serialize.pb.h"
#include "dataManager.h"
#include "tbx.h"

/**
 * \brief 压缩存档数据 , 没有检测数据超过最大值
 * \pUser 存档数据所属用户
 * \zlib 压缩输出buf
 * \return 压缩后数据大小 , 0 表示压缩出错
 */
int compressSaveData(SceneUser *pUser , unsigned char *zlib,bool &canSave)
{
    if (!pUser)
    {
        Fir::logger->error("[压缩档案数据失败] 人物指针为空，存档失败");
        return 0;
    }

    unsigned char unBuf[MAX_UZLIB_CHAR];
    bzero(unBuf, sizeof(unBuf));

    // 得到二进制存档
    int uzSize = 0;
    uzSize = pUser->saveBinaryArchive(unBuf+uzSize, MAX_UZLIB_CHAR-uzSize-sizeof(CMD::RECORD::t_WriteUser_SceneRecord));

    uLongf zsize = zSocket::MAX_DATASIZE - sizeof(CMD::RECORD::t_WriteUser_SceneRecord);

    //数据过大，内存越界
    if (uzSize >= MAX_UZLIB_CHAR)
    {
        Fir::logger->error("[压缩档案数据]charid=%lu,nickname=%s, 超过最大数值MAX_UZLIB_CHAR=%u, uzsize=%d, zsize=%u", pUser->charid ,pUser->nickname, MAX_UZLIB_CHAR,uzSize ,(DWORD)zsize);
        return 0;
    }

    if (SceneService::getMe().md5Verify)
    {
        unsigned char md5[16];
        bzero(md5,16);
        MD5SPACE::MD5Data((unsigned char *)unBuf,uzSize,md5);
        if (strncmp((const char*)md5,pUser->lastSaveMD5,16) != 0)
        {
            canSave = true;
        }
        bcopy(md5,pUser->lastSaveMD5,16);
    }

    // 压缩数据
    int retcode = 0;
    retcode = compress((unsigned char *)zlib , &zsize , (unsigned char *)unBuf , (uLongf)uzSize);
    switch(retcode)
    {
        case Z_OK:
            {
                Fir::logger->debug("压缩档案数据成功(charid=%lu,nickname=%s) , uzsize = %d , size = %u)", pUser->charid, pUser->nickname, uzSize , (DWORD)zsize);
                break;
            }
        case Z_MEM_ERROR:
        case Z_BUF_ERROR:
            {
                Fir::logger->debug("压缩档案数据失败(charid=%lu,nickname=%s)",pUser->charid, pUser->nickname);
                zsize = 0;
                break;
            }
        default:
            {
                Fir::logger->debug("压缩档案数据失败,未知原因(charid=%lu,nickname=%s)",pUser->charid, pUser->nickname);
                zsize = 0;
                break;
            }
    }
    return zsize;
}

/**
 * \brief 加载二进制数据
 *
 */
void SceneUser::setupBinaryArchive(HelloKittyMsgData::Serialize& binary)
{
    HelloKittyMsgData::CharBin *dataCharBin = binary.mutable_charbin();
    *(&charbin) = *dataCharBin;

    //反序列化二进制数据，不要插队
    m_store_house.load(binary);
    m_trade.load(binary);
    m_kittyGarden.loadMapData(binary);
    m_buildManager.load(binary);
    m_taskManager.load(binary);
    m_atlasManager.load(binary);
    m_emailManager.load(binary);
    m_eventmanager.load(binary);
    m_achievementManager.load(binary);
    m_dressManager.load(binary);
    m_paperManager.load(binary);
    m_burstEventManager.load(binary);
}

/**
 * \brief 保存二进制数据
 *
 */
DWORD SceneUser::saveBinaryArchive(unsigned char *out , const int maxsize)
{
    HelloKittyMsgData::Serialize binary; // 二进制数据

    HelloKittyMsgData::CharBin *dataCharBin = binary.mutable_charbin();
    *dataCharBin = charbin;

    //保存二进制数据，千万不要插队
    m_store_house.save(binary);
    m_trade.save(binary);
    m_kittyGarden.saveMapData(binary);
    m_buildManager.save(binary);
    m_taskManager.save(binary);
    m_atlasManager.save(binary);
    m_emailManager.save(binary);
    m_eventmanager.save(binary);
    m_achievementManager.save(binary);
    m_dressManager.save(binary);
    m_paperManager.save(binary);
    m_burstEventManager.save(binary);
    binary.SerializeToArray(out,maxsize);
    m_friend.load();
 
    return binary.ByteSize();
}

std::string SceneUser::getBinaryArchive()
{
    unsigned char unBuf[MAX_UZLIB_CHAR];
    bzero(unBuf, sizeof(unBuf));

    // 得到二进制存档
    int uzSize = 0; 
    uzSize = saveBinaryArchive(unBuf, MAX_UZLIB_CHAR);

    std::string result((const char*)unBuf,uzSize);
    return result;
}


/**
 * \brief  保存角色数据到record服务器
 * \return 保存成功，返回TRUE,否则返回FALSE
 *
 */
bool SceneUser::save()
{
    //保存角色档案信息

    char buffer[zSocket::MAX_DATASIZE] = {0};
    CMD::RECORD::t_WriteUser_SceneRecord *saveChar = (CMD::RECORD::t_WriteUser_SceneRecord*)(buffer);
    constructInPlace(saveChar);

    saveChar->charid = charid; 
    saveChar->dwMapTempID = 0;

    bcopy(&charbase, &saveChar->charbase, sizeof(CharBase));
    bool canSave = true;

    if (SceneService::getMe().md5Verify)
    {
        unsigned char md5[16];
        bzero(md5,sizeof(md5));
        MD5SPACE::MD5Data((unsigned char *)(&charbase),sizeof(CharBase),md5);
        if (strncmp((const char*)md5,lastSaveCharBaseMD5,16) == 0)
        {
            canSave = false;
        }
        bcopy(md5,lastSaveCharBaseMD5,16);
    }

    saveChar->dataSize = compressSaveData(this , (unsigned char *)saveChar->data,canSave);

    if (!canSave)
    {
        return true;
    }
    Fir::logger->debug("[存档]:%s,binary=%u", saveChar->charbase.nickname,saveChar->dataSize);

    std::string ret;
    encodeMessage(saveChar,sizeof(CMD::RECORD::t_WriteUser_SceneRecord) + saveChar->dataSize,ret);
    RecordClient  * recordClient = getSelfRecord();
    if(recordClient)
        recordClient->sendCmd(ret.c_str(),ret.size());
    return true;
}

// 获取该角色的二进制信息
std::string SceneUser::getAllBinary()
{
    char buf[zSocket::MAX_DATASIZE] = {0};

    bool canSave = true;
    DWORD dataSize = compressSaveData(this , (unsigned char *)buf,canSave);
    return std::string(buf,dataSize);
}

RecordClient  *SceneUser::getSelfRecord()
{
    DWORD RecordId =  charid >> 32;
    return MgrrecordClient.GetRecordByServerId(RecordId);

}

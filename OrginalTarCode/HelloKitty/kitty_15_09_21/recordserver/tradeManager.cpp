#include "tradeManager.h"
#include "TimeTick.h"
#include "RecordTask.h"
#include "RecordUserManager.h"
#include "zSocket.h"
#include "zMemDBPool.h"
#include "RecordUserManager.h"
#include "RecordUser.h"

TradeManager::TradeManager()
{
}

TradeManager::~TradeManager()
{
    m_advertiseMap.clear();
}

bool TradeManager::update(const CMD::RECORD::t_AdvertiseUser_SceneRecord * advertiseCmd)
{
    if(!advertiseCmd)
    {
        return false;
    }
    
    if(!advertiseCmd->addFlg)
    {
        m_advertiseMap.erase(advertiseCmd->charid);
        return true;
    }

    HelloKittyMsgData::PbSaleCell advertiseCell;
    try
    {
        advertiseCell.ParseFromArray(advertiseCmd->data, advertiseCmd->datasize);
    }
    catch(...)
    {
        return false;
    }
    RecordUser* recordUser = RecordUserM::getMe().getUserByCharid(advertiseCmd->charid);
    if(!recordUser)
    {
        return false;
    }
    auto iter = m_advertiseMap.find(advertiseCmd->charid);
    if(iter == m_advertiseMap.end())
    {
        HelloKittyMsgData::SellPaperCell temp;
        temp.set_charid(advertiseCmd->charid);
        temp.set_nickname(recordUser->account);
        HelloKittyMsgData::PbSaleCell *cell = temp.mutable_salecell();
        *cell = advertiseCell;
        m_advertiseMap.insert(std::pair<QWORD,HelloKittyMsgData::SellPaperCell>(advertiseCmd->charid,temp));
        return true;
    }
    
    HelloKittyMsgData::SellPaperCell &temp = const_cast<HelloKittyMsgData::SellPaperCell&>(iter->second);
    HelloKittyMsgData::PbSaleCell *cell = temp.mutable_salecell();
    *cell = advertiseCell;
    return true;
}

bool TradeManager::randAdvertise(RecordTask *recordTask,const CMD::RECORD::t_RequirePaperUser_SceneRecord *cmd)
{   
    RecordUser* user = RecordUserM::getMe().getUserByCharid(cmd->charid);
    if(!user || !recordTask || cmd->randType > CMD::RECORD::RAND_Friend)
    {
        return false;
    }

    HelloKittyMsgData::SellPaper paper;
    if(!randAdvertise(paper,cmd->charid,cmd->randType))
    {
        return false;
    }

    char buffer[zSocket::MAX_DATASIZE] = {0};
    CMD::RECORD::t_PaperUser_SceneRecord *paperCmd = (CMD::RECORD::t_PaperUser_SceneRecord*)(buffer);
    constructInPlace(paperCmd);
    paperCmd->charid = cmd->charid;
    paper.SerializeToArray(paperCmd->data,paper.ByteSize());
    paperCmd->datasize = paper.ByteSize();

    std::string ret;
    encodeMessage(paperCmd,sizeof(CMD::RECORD::t_PaperUser_SceneRecord) + paperCmd->datasize,ret);
    recordTask->sendCmd(ret.c_str(),ret.size());
    return true;
}


bool TradeManager::randAdvertise(HelloKittyMsgData::SellPaper &paper,const QWORD charid,const BYTE randType)
{   
    paper.set_createtime(RecordTimeTick::currentTime.sec());
    DWORD size = 0;
    if(randType ==  CMD::RECORD::RAND_Friend)
    {
        std::set<QWORD> friendSet;
        zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
        if(!handle)
        {
            return false;
        }
        handle->getSet("rolerelation", charid, "friend", friendSet);
        for(auto iter = friendSet.begin();iter != friendSet.end() && size < PAPER_CELL_NUM;++iter)
        {
            auto advertiseIter = m_advertiseMap.find(*iter);
            if(advertiseIter == m_advertiseMap.end() || advertiseIter->first == charid)
            {
                continue;
            }
            HelloKittyMsgData::SellPaperCell *paperCell = paper.add_papercell();
            if(!paperCell)
            {
                continue;
            }
            *paperCell = advertiseIter->second;
            ++size;
        }
        paper.set_randtype(HelloKittyMsgData::Rand_Friend);
    }
    else if(randType ==  CMD::RECORD::RAND_PASSER_BY) 
    {
        for(auto iter = m_advertiseMap.begin();iter != m_advertiseMap.end() && size < PAPER_CELL_NUM;++iter)
        {
            if(iter->first == charid)
            {
                continue;
            }
            HelloKittyMsgData::SellPaperCell *paperCell = paper.add_papercell();
            if(!paperCell)
            {
                continue;
            }
            *paperCell = iter->second;
            ++size;
        }
        paper.set_randtype(HelloKittyMsgData::Rand_Passer_By);
    }
    else
    {
        return false;
    }

    if(size < PAPER_CELL_NUM)
    {
        Fir::logger->debug("[全区随机刷新报纸数量不够]:%lu,%u,%u,%u",charid,randType,size,PAPER_CELL_NUM);
    }
    return true;
}

bool TradeManager::load(const HelloKittyMsgData::RecordSerialize &recordBinary)
{  
    for(int index = 0;index < recordBinary.advertise_size();++index)
    {
        const HelloKittyMsgData::SellPaperCell &temp = recordBinary.advertise(index);
        m_advertiseMap.insert(std::pair<QWORD,HelloKittyMsgData::SellPaperCell>(temp.charid(),temp));
    }
    print();
    return true;
}

bool TradeManager::save(HelloKittyMsgData::RecordSerialize &recordBinary)
{
    print();
    for(auto iter = m_advertiseMap.begin();iter != m_advertiseMap.end();++iter)
    {
        HelloKittyMsgData::SellPaperCell *temp = recordBinary.add_advertise();
        if(!temp)
        {
            continue;
        }
        *temp = iter->second;
    }
    return true;
}

void TradeManager::print()
{
    Fir::logger->debug("[测试全服广告数据]:开始 %lu",m_advertiseMap.size());
    for(auto iter = m_advertiseMap.begin();iter != m_advertiseMap.end();++iter)
    {
        const HelloKittyMsgData::SellPaperCell &paperCell = iter->second;
        const HelloKittyMsgData::PbSaleCell &temp = paperCell.salecell();
        Fir::logger->debug("[测试全服广告数据]:角色id:%lu,摊位格子id:%u,道具id:%u,道具数量:%u,道具价格:%u,道具状态:%u,购买者名称:%s,是否打过广告:%d",iter->first,temp.cellid(),temp.itemid(),temp.itemcount(),temp.price(),(int)temp.status(),temp.nickname().c_str(),temp.advertise());
    }
    Fir::logger->debug("[测试全服广告数据]:结束 %lu",m_advertiseMap.size());
    return;
}
        

#ifndef TRADE_MANAGER_H
#define TRADE_MANAGER_H
#include "zSingleton.h"
#include "trade.pb.h"
#include "RecordCommand.h"
#include "recordserialize.pb.h"
class RecordTask;

//报纸广告数量
const DWORD PAPER_CELL_NUM = 20;
class TradeManager : public Singleton<TradeManager>
{
    private:
        friend class Singleton<TradeManager>;
        TradeManager();
        ~TradeManager();
    public:
        //更新广告位
        bool update(const CMD::RECORD::t_AdvertiseUser_SceneRecord * advertiseCmd);
        //随机生成报纸
        bool randAdvertise(RecordTask *recordTask,const CMD::RECORD::t_RequirePaperUser_SceneRecord *cmd);
        //加载数据
        bool load(const HelloKittyMsgData::RecordSerialize &recordBinary);
        //保存数据
        bool save(HelloKittyMsgData::RecordSerialize &recordBinary);
        //日志测试
        void print();
    private:
        //随机生成报纸
        bool randAdvertise(HelloKittyMsgData::SellPaper &paper,const QWORD charid,const BYTE randType);
    private:
        std::unordered_map<QWORD,HelloKittyMsgData::SellPaperCell> m_advertiseMap;
};

#endif



#include "SceneMail.h"

void SceneMailManager::sendSysMailToPlayer(QWORD PlayerId,DWORD TitleID ,DWORD TextId ,const std::vector<std::string>* vecPara ,const HelloKittyMsgData::vecAward* rvecAward )
{
}

void SceneMailManager::sendSysMailToPlayerForEvent(QWORD PlayerId,DWORD eventId,QWORD OwerId,const HelloKittyMsgData::vecAward& rvecAward,bool bAddItem )
{
    Fir::logger->info("send mail to %lu , event %u ,owergarden %lu",PlayerId,eventId,OwerId);
}




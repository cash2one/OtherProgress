#/bin/bash
source sqlconfig.sh 


mysql -h$HostIp -P$HostPort -u$User -p$Pwd $DATADB < clearmobile_kitty.sql

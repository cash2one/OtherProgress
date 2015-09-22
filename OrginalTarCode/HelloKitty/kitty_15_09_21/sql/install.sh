#/bin/bash
source sqlconfig.sh 

exp_sql="CREATE DATABASE /*!32312 IF NOT EXISTS*/$FLDB/*!40100 DEFAULT CHARACTER SET latin1 */;"
#mysql -h$host -u$user -p$passwd $dbname < $dir/$sqlname 
mysql -h$HostIp -P$HostPort -u$User -p$Pwd -e "$exp_sql"
mysql -h$HostIp -P$HostPort -u$User -p$Pwd $FLDB < flserver.sql

exp_sql="CREATE DATABASE /*!32312 IF NOT EXISTS*/$DATADB/*!40100 DEFAULT CHARACTER SET latin1 */;"
#mysql -h$host -u$user -p$passwd $dbname < $dir/$sqlname 
mysql -h$HostIp -P$HostPort -u$User -p$Pwd -e "$exp_sql"
mysql -h$HostIp -P$HostPort -u$User -p$Pwd $DATADB < mobile_kitty.sql

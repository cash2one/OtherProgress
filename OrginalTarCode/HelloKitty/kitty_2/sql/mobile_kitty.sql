/*
SQLyog 企业�?- MySQL GUI v8.14 
MySQL - 5.0.75-log : Database - mobile_luandun
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`mobile_kitty` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `mobile_kitty`;

/*Table structure for table `t_serverlist` */

DROP TABLE IF EXISTS `t_serverlist`;

CREATE TABLE `t_serverlist` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `TYPE` int(10) unsigned NOT NULL default '0',
  `NAME` varchar(32) NOT NULL default '',
  `IP` varchar(16) NOT NULL default '127.0.0.1',
  `PORT` int(10) unsigned NOT NULL default '0',
  `EXTIP` varchar(16) NOT NULL default '127.0.0.1',
  `EXTPORT` int(10) unsigned NOT NULL default '0',
  `NETTYPE` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM AUTO_INCREMENT=2204 DEFAULT CHARSET=utf8;

/*Data for the table `t_serverlist` */

insert  into `t_serverlist`(`ID`,`TYPE`,`NAME`,`IP`,`PORT`,`EXTIP`,`EXTPORT`,`NETTYPE`) values (1,1,'SuperServer','192.168.2.24',10000,'192.168.2.24',10000,0),(20,20,'SessionServer','192.168.2.24',6000,'192.168.2.24',6000,0),(21,21,'ScenesServer','192.168.2.24',6010,'192.168.2.24',6010,0),(2202,22,'GatewayServer','192.168.2.24',9000,'192.168.2.24',9000,0),(11,11,'RecordServer','192.168.2.24',7010,'192.168.2.24',7010,0);

/*Table structure for table `t_charbase` */

DROP TABLE IF EXISTS `t_charbase`;

CREATE TABLE `t_charbase` (
  `f_charid` bigint(20) NOT NULL default '0',
  `f_acctype` int(10) unsigned NOT NULL default '0',
  `f_account` varchar(50) NOT NULL default '',
  `f_password` varchar(50) NOT NULL default '',
  `f_nickname` varchar(50) NOT NULL default '',
  `f_level` int(10) unsigned NOT NULL default '0',
  `f_sex` tinyint(3) unsigned NOT NULL default '0',
  `f_createtime` int(10) unsigned NOT NULL default '0',
  `f_onlinetime` int(10) unsigned NOT NULL default '0',
  `f_offlinetime` int(10) unsigned NOT NULL default '0',
  `f_gold` int(10) unsigned NOT NULL default '0',
  `f_gem` int(10) unsigned NOT NULL default '0',
  `f_store_limit` int(10) unsigned NOT NULL default '0',
  `f_sale_grid_count` int(10) unsigned NOT NULL default '0',
  `f_allbinary` blob,
  PRIMARY KEY  (`f_charid`),
  KEY `f_nickname` (`f_nickname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `t_version`;

CREATE TABLE `t_version` (
  `f_updatetime` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `f_version` int(10) unsigned NOT NULL default '0',
  KEY `index_time` (`f_updatetime`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Data for the table `t_version` */

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

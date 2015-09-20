/*
SQLyog 企业版 - MySQL GUI v8.14 
MySQL - 5.0.75-log : Database - FLServer
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`flserver` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `flserver`;

/*Table structure for table `account_zone` */

DROP TABLE IF EXISTS `account_zone`;

CREATE TABLE `account_zone` (
  `account` varchar(24) NOT NULL default '',
  `zoneid` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`account`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Data for the table `account_zone` */

insert  into `account_zone`(`account`,`zoneid`) values ('xby18',1),('xby17',1),('xby19',1),('xby8999',1),('xby20',1),('lbs21',1),('lbs22',1),('lbs23',1),('lbs24',1),('lbs25',1),('lbs26',1),('lbs27',1),('lbs28',1),('lbs29',1),('lbs1',1),('lbs2',1),('lbs3',1),('lbs5',1),('lbs6',1);

/*Table structure for table `zoneInfo` */

DROP TABLE IF EXISTS `t_zone`;

CREATE TABLE t_zone (
  `game` int(10) unsigned NOT NULL default '0',
  `zone` int(10) unsigned NOT NULL default '0',
  `zoneType` tinyint(3) unsigned NOT NULL default '0',
  `ip` varchar(100) NOT NULL default '',
  `port` smallint(5) unsigned NOT NULL default '0',
  `name` varchar(100) NOT NULL default '',
  `type` tinyint(3) unsigned NOT NULL default '0',
  `cap` varchar(16) NOT NULL default '',
  `x` int(10) unsigned NOT NULL default '0',
  `y` int(10) unsigned NOT NULL default '0',
  `desc` varchar(100) NOT NULL default '',
  `IsUse` int(10) unsigned NOT NULL default '0',
  `desc_order` varchar(100) NOT NULL default '',
  `destGame` int(10) unsigned NOT NULL default '0',
  `destZone` int(10) unsigned NOT NULL default '0',
  `operation` varchar(255) NOT NULL default '',
  `flag_test` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`game`,`zone`),
  UNIQUE KEY `ip_port` (`ip`,`port`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*Data for the table `zoneInfo` */

insert  into `t_zone`(`game`,`zone`,`zoneType`,`ip`,`port`,`name`,`type`,`cap`,`x`,`y`,`desc`,`IsUse`,`desc_order`,`destGame`,`destZone`,`operation`,`flag_test`) values (42,1,1,'192.168.2.24',10000,'lbs',0,'',0,0,'',0,'',0,0,'','');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

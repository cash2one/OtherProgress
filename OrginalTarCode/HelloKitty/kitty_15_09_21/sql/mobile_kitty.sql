

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


DROP TABLE IF EXISTS `relation`;

CREATE TABLE `relation` (
    `playera` bigint(20) unsigned NOT NULL DEFAULT '0',
    `playerb` bigint(20) unsigned NOT NULL DEFAULT '0',
    `relation` bigint(20) unsigned DEFAULT NULL,
    PRIMARY KEY (`playera`,`playerb`)
) ENGINE=Innodb DEFAULT CHARSET=utf8;

/*Table structure for table `t_charbase` */

DROP TABLE IF EXISTS `t_charbase`;

CREATE TABLE `t_charbase` (
    `f_charid` bigint(20) NOT NULL DEFAULT '0',
    `f_acctype` int(10) unsigned NOT NULL DEFAULT '0',
    `f_account` varchar(50) NOT NULL DEFAULT '',
    `f_password` varchar(50) NOT NULL DEFAULT '',
    `f_nickname` varchar(50) NOT NULL DEFAULT '',
    `f_level` int(10) unsigned NOT NULL DEFAULT '0',
    `f_sex` tinyint(3) unsigned NOT NULL DEFAULT '0',
    `f_createtime` int(10) unsigned NOT NULL DEFAULT '0',
    `f_onlinetime` int(10) unsigned NOT NULL DEFAULT '0',
    `f_offlinetime` int(10) unsigned NOT NULL DEFAULT '0',
    `f_gold` int(10) unsigned NOT NULL DEFAULT '0',
    `f_gem` int(10) unsigned NOT NULL DEFAULT '0',
    `f_store_limit` int(10) unsigned NOT NULL DEFAULT '0',
    `f_sale_grid_count` int(10) unsigned NOT NULL DEFAULT '0',
    `f_allbinary` blob,
    PRIMARY KEY (`f_charid`),
    KEY `f_nickname` (`f_nickname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `t_serverlist` */

DROP TABLE IF EXISTS `t_serverlist`;

CREATE TABLE `t_serverlist` (
    `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
    `TYPE` int(10) unsigned NOT NULL DEFAULT '0',
    `NAME` varchar(32) NOT NULL DEFAULT '',
    `IP` varchar(16) NOT NULL DEFAULT '127.0.0.1',
    `PORT` int(10) unsigned NOT NULL DEFAULT '0',
    `EXTIP` varchar(16) NOT NULL DEFAULT '127.0.0.1',
    `EXTPORT` int(10) unsigned NOT NULL DEFAULT '0',
    `NETTYPE` int(10) unsigned NOT NULL DEFAULT '0',
    `DBTABLE` varchar(100) NOT NULL DEFAULT '',
    PRIMARY KEY (`ID`)
) ENGINE=MyISAM AUTO_INCREMENT=2204 DEFAULT CHARSET=utf8;

/*Table structure for table `t_version` */

DROP TABLE IF EXISTS `t_version`;

CREATE TABLE `t_version` (
    `f_updatetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `f_version` int(10) unsigned NOT NULL DEFAULT '0',
    KEY `index_time` (`f_updatetime`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `t_family`;

CREATE TABLE `t_family` (
    `f_familyid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'id',
    `f_charid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'leader',
    `f_name` varchar(50)  NOT NULL DEFAULT '' COMMENT 'family name',
    `f_icon` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'family icon',
    `f_limittype` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT '0,public 1, no public 2,need requir',
    `f_limitow` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'level limit',
    `f_limithigh` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'level limit',
    `f_level` int(10) unsigned NOT NULL DEFAULT '1' COMMENT 'family level',
    `f_ranking` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'today clock zero get',
    `f_lastranking` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'yesterday clock zero get',
    `f_notice`   varchar(500) NOT NULL DEFAULT '' COMMENT 'family notice',
    `f_createtime`  int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'ctreatetime',
     PRIMARY KEY (`f_familyid` )
) ENGINE=Innodb DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `t_familymember`;
CREATE TABLE `t_familymember` (
    `f_familyid` bigint(20) unsigned NOT NULL DEFAULT '0' ,
    `f_charid` bigint(20) unsigned NOT NULL DEFAULT '0',
    `f_type` tinyint(3)  unsigned NOT NULL DEFAULT '0' COMMENT '0 is member,1 is apply',
    `f_opTimer` int(10)  unsigned NOT NULL DEFAULT '0'  COMMENT 'set time',
    PRIMARY KEY (`f_familyid`,`f_charid`)
) ENGINE=Innodb DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `t_lastflush`;
CREATE TABLE IF  `t_lastflush` (
    `f_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '1 is family rank cal ' ,
    `f_opTimer` int(10)  unsigned NOT NULL DEFAULT '0'  COMMENT 'cal time',
    PRIMARY KEY (`f_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `email`;
CREATE TABLE  email(
`sender` BIGINT(20) UNSIGNED,
`receiver` BIGINT(20) UNSIGNED,
`time` BIGINT(20) UNSIGNED,
`conten` blob default NULL, 
PRIMARY KEY(sender,receiver,time)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `t_recordbinary`;
CREATE TABLE t_recordbinary(
`f_allbinary` blob default NULL
) ENGINE=Innodb DEFAULT CHARSET=utf8;


/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

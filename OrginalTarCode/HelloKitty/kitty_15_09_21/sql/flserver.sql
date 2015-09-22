/*
SQLyog 企业版 - MySQL GUI v8.14 
MySQL - 5.1.73 : Database - yhsflserver
*********************************************************************
*/


DROP TABLE IF EXISTS `account_zone`;

CREATE TABLE `account_zone` (
  `account` varchar(24) NOT NULL DEFAULT '',
  `zoneid` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`account`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `t_zone`;

CREATE TABLE `t_zone` (
  `game` int(10) unsigned NOT NULL DEFAULT '0',
  `zone` int(10) unsigned NOT NULL DEFAULT '0',
  `zoneType` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `ip` varchar(100) NOT NULL DEFAULT '',
  `port` smallint(5) unsigned NOT NULL DEFAULT '0',
  `name` varchar(100) NOT NULL DEFAULT '',
  `type` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `cap` varchar(16) NOT NULL DEFAULT '',
  `x` int(10) unsigned NOT NULL DEFAULT '0',
  `y` int(10) unsigned NOT NULL DEFAULT '0',
  `desc` varchar(100) NOT NULL DEFAULT '',
  `IsUse` int(10) unsigned NOT NULL DEFAULT '0',
  `desc_order` varchar(100) NOT NULL DEFAULT '',
  `destGame` int(10) unsigned NOT NULL DEFAULT '0',
  `destZone` int(10) unsigned NOT NULL DEFAULT '0',
  `operation` varchar(255) NOT NULL DEFAULT '',
  `flag_test` varchar(100) NOT NULL DEFAULT '',
  PRIMARY KEY (`game`,`zone`),
  UNIQUE KEY `ip_port` (`ip`,`port`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


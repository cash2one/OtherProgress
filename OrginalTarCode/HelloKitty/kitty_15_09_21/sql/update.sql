#yhs   20150-08-05 关系表
CREATE TABLE IF NOT EXISTS relation(
`playera` BIGINT(20) UNSIGNED,
`playerb` BIGINT(20) UNSIGNED,
`relation` BIGINT(20) UNSIGNED,
PRIMARY KEY(playera,playerb)
)ENGINE=MyISAM DEFAULT CHARSET=utf8;
#flyer 20150-08-07
CREATE TABLE IF NOT EXISTS t_recordbinary(
`f_allbinary` blob default NULL
);

#flyer   20150-08-17 邮件表
CREATE TABLE IF NOT EXISTS email(
`sender` BIGINT(20) UNSIGNED,
`receiver` BIGINT(20) UNSIGNED,
`time` BIGINT(20) UNSIGNED,
`conten` blob default NULL, 
PRIMARY KEY(sender,receiver,time)
);

#flyer 2015-08-28
#ALTER TABLE t_serverlist add DBTABLE varchar(100) NOT NULL;

#yhs 2015-09-06 家族表
CREATE TABLE IF NOT EXISTS `t_family` (
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
    PRIMARY KEY (`f_familyid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

#yhs 2015-09-08 家族表
CREATE TABLE IF NOT EXISTS `t_familymember` (
    `f_familyid` bigint(20) unsigned NOT NULL DEFAULT '0' ,
    `f_charid` bigint(20) unsigned NOT NULL DEFAULT '0',
    `f_type` tinyint(3)  unsigned NOT NULL DEFAULT '0' COMMENT '0 is member,1 is apply',
    `f_opTimer` int(10)  unsigned NOT NULL DEFAULT '0'  COMMENT 'set time',
    PRIMARY KEY (`f_familyid`,`f_charid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `t_lastflush` (
    `f_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '1 is family rank cal ' ,
    `f_opTimer` int(10)  unsigned NOT NULL DEFAULT '0'  COMMENT 'cal time',
    PRIMARY KEY (`f_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
#yhs  2015-09-16
ALTER TABLE t_family  change `f_limittype`  `f_limittype` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '0,public 1, no public 2,need requir';

#flyer 2015-09-14
ALTER TABLE t_charbase drop f_gold;
ALTER TABLE t_charbase drop f_gem;
ALTER TABLE t_charbase drop f_store_limit;
ALTER TABLE t_charbase drop f_sale_grid_count;

#yhs 2015-09-15 家族表
CREATE TABLE IF NOT EXISTS `t_familymember` (
    `f_familyid` bigint(20) unsigned NOT NULL DEFAULT '0' ,
    `f_charid` bigint(20) unsigned NOT NULL DEFAULT '0',
    `f_type` int(3)  unsigned NOT NULL DEFAULT '0' COMMENT '0 is member,1 is apply',
    `f_opTimer` int(10)  unsigned NOT NULL DEFAULT '0'  COMMENT 'set time',
    PRIMARY KEY (`f_familyid`,`f_charid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;



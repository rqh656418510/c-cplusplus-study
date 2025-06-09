-- ----------------------------
-- 创建数据库
-- ----------------------------
DROP DATABASE IF EXISTS `cxx_study`;
CREATE DATABASE `cxx_study` DEFAULT CHARACTER SET UTF8;

-- ----------------------------
-- 切换数据库
-- ----------------------------
USE `cxx_study`;

-- ----------------------------
-- 创建数据库表
-- ----------------------------
DROP TABLE IF EXISTS `properties`;
CREATE TABLE `properties` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `KEY` varchar(200) DEFAULT NULL,
  `VALUE` varchar(200) DEFAULT NULL,
  `REMARK` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=UTF8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- 往数据库表插入数据
-- ----------------------------
INSERT INTO `properties` (`KEY`, `VALUE`, `REMARK`) VALUES ('test_limit_number', '430', 'Limit Number');
INSERT INTO `properties` (`KEY`, `VALUE`, `REMARK`) VALUES ('test_limit_balance', '929.32', 'Limit Balance');

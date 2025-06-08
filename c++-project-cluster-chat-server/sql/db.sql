-- 创建数据库
CREATE DATABASE `chat` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- 切换数据库
USE `chat`;

-- 创建用户表
CREATE TABLE `user` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `password` varchar(50) DEFAULT NULL,
  `state` enum('online','offline') DEFAULT 'offline',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8mb4;

-- 创建好友表
CREATE TABLE `friend` (
  `userid` int NOT NULL,
  `friendid` int NOT NULL,
  UNIQUE KEY `userid` (`userid`,`friendid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 创建用户组表
CREATE TABLE `allgroup` (
  `id` int NOT NULL AUTO_INCREMENT,
  `groupname` varchar(50) NOT NULL,
  `groupdesc` varchar(200) DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `groupname` (`groupname`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4;

-- 创建用户与用户组关联表
CREATE TABLE `groupuser` (
  `groupid` int NOT NULL,
  `userid` int NOT NULL,
  `grouprole` enum('creator','normal') DEFAULT NULL,
  UNIQUE KEY `groupid` (`groupid`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 创建离线消息表
CREATE TABLE `offlinemessage` (
  `userid` int NOT NULL,
  `message` varchar(500) NOT NULL,
  `createtime` bigint NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;


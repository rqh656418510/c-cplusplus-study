-- --------------------------------------------------------
--    XXL-JOB 数据库的初始化脚本，仅用于跑 C++ 的单元测试    
-- --------------------------------------------------------

-- 创建数据库
CREATE DATABASE IF NOT EXISTS `xxl_job_test` CHARACTER SET utf8mb4;

-- 切换数据库
USE `xxl_job_test`

-- 创建表
CREATE TABLE IF NOT EXISTS `xxl_job_log` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `job_group` int NOT NULL COMMENT '执行器主键ID',
  `job_id` int NOT NULL COMMENT '任务，主键ID',
  `executor_address` varchar(255) DEFAULT NULL COMMENT '执行器地址，本次执行的地址',
  `executor_handler` varchar(255) DEFAULT NULL COMMENT '执行器任务handler',
  `executor_param` varchar(512) DEFAULT NULL COMMENT '执行器任务参数',
  `executor_sharding_param` varchar(20) DEFAULT NULL COMMENT '执行器任务分片参数，格式如 1/2',
  `executor_fail_retry_count` int NOT NULL DEFAULT '0' COMMENT '失败重试次数',
  `trigger_time` datetime DEFAULT NULL COMMENT '调度-时间',
  `trigger_code` int NOT NULL COMMENT '调度-结果',
  `trigger_msg` text COMMENT '调度-日志',
  `handle_time` datetime DEFAULT NULL COMMENT '执行-时间',
  `handle_code` int NOT NULL COMMENT '执行-状态',
  `handle_msg` text COMMENT '执行-日志',
  `alarm_status` tinyint NOT NULL DEFAULT '0' COMMENT '告警状态：0-默认、1-无需告警、2-告警成功、3-告警失败',
  PRIMARY KEY (`id`),
  KEY `I_trigger_time` (`trigger_time`),
  KEY `I_handle_code` (`handle_code`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- 插入表数据
INSERT INTO xxl_job_log (job_group,job_id,executor_address,executor_handler,executor_param,executor_sharding_param,executor_fail_retry_count,trigger_time,trigger_code,trigger_msg,handle_time,handle_code,handle_msg,alarm_status) VALUES
	 (3,11,'http://192.168.2.140:9099/','optionProvidePricePush','',NULL,0,'2026-01-28 19:49:20',500,'任务触发类型：Cron触发<br>调度机器：192.168.2.140<br>执行器-注册方式：自动注册<br>执行器-地址列表：[http://192.168.2.140:9099/]<br>路由策略：轮询<br>阻塞处理策略：丢弃后续调度<br>任务超时时间：30<br>失败重试次数：0<br><br><span style="color:#00c0ef;" > >>>>>>>>>>>触发调度<<<<<<<<<<< </span><br>触发调度：<br>address：http://192.168.2.140:9099/<br>code：500<br>msg：xxl-job remoting error(拒绝连接 (Connection refused)), for url : http://192.168.2.140:9099/run',NULL,0,'',3),
	 (3,11,NULL,'optionProvidePricePush','',NULL,0,'2026-02-06 08:07:23',500,'任务触发类型：Cron触发<br>调度机器：192.168.2.140<br>执行器-注册方式：自动注册<br>执行器-地址列表：null<br>路由策略：轮询<br>阻塞处理策略：丢弃后续调度<br>任务超时时间：30<br>失败重试次数：0<br><br><span style="color:#00c0ef;" > >>>>>>>>>>>触发调度<<<<<<<<<<< </span><br>调度失败：执行器地址为空<br><br>',NULL,0,'',3);

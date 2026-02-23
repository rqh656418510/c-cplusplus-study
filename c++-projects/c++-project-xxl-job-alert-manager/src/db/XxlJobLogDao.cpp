
#include "XxlJobLogDao.h"

#include <iostream>
#include <sstream>

#include "AppConfigLoader.h"
#include "MySqlConnectionPool.h"
#include "XxlJobMonitor.h"

// 查询最新的任务调度日志记录
XxlJobLog XxlJobLogDao::selectLastest() {
    // 数据库表的名称
    const std::string table = AppConfigLoader::getInstance().getConfig().mysql.table;

    // 拼接SQL语句（查询最新的任务调度日志记录）
    std::ostringstream oss;
    oss << "select id, executor_handler, trigger_time, trigger_code, trigger_msg from " << table << " "
        << "order by trigger_time desc limit 1";
    std::string sql = oss.str();

    // 查询结果
    XxlJobLog log;

    // 获取MySQL连接
    std::shared_ptr<MySqlConnection> conn = MySqlConnectionPool::getInstance()->getConnection();

    // 判断连接是否有效
    if (!conn) {
        return log;
    }

    // 执行SQL语句
    MYSQL_RES* res = conn->query(sql);
    if (res != nullptr && mysql_num_rows(res) > 0) {
        // 封装查询结果
        MYSQL_ROW row = mysql_fetch_row(res);
        log.setId(atoi(row[0]));
        log.setExecutorHandler(row[1] ? row[1] : "");
        log.setTriggerTime(row[2] ? row[2] : "");
        log.setTriggerCode(atoi(row[3]));
        log.setTriggerMsg(row[4] ? row[4] : "");
    }

    // 释放资源
    mysql_free_result(res);

    return log;
}

// 查询最新的任务调度失败日志记录
XxlJobLog XxlJobLogDao::selectLastestFatal() {
    // 获取全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 分钟数（查询范围）
    int minutes = config.alert.xxljobFatalStatusScanIntervalTime / 60;
    if (minutes <= 0) {
        minutes = 1;
    }

    // 数据库表的名称
    const std::string table = AppConfigLoader::getInstance().getConfig().mysql.table;

    // 拼接SQL语句（查询最近几分钟内，最新的一条任务调度失败日志记录）
    std::ostringstream oss;
    oss << "select id, executor_handler, trigger_time, trigger_code, trigger_msg from " << table << " "
        << "where trigger_code != 200 and trigger_time between now() - interval " << minutes << " minute and now() "
        << "and trigger_msg like '%执行器地址为空%' "
        << "order by trigger_time desc limit 1";
    std::string sql = oss.str();

    // 查询结果
    XxlJobLog log;

    // 获取MySQL连接
    std::shared_ptr<MySqlConnection> conn = MySqlConnectionPool::getInstance()->getConnection();

    // 判断连接是否有效
    if (!conn) {
        return log;
    }

    // 执行SQL语句
    MYSQL_RES* res = conn->query(sql);
    if (res != nullptr && mysql_num_rows(res) > 0) {
        // 封装查询结果
        MYSQL_ROW row = mysql_fetch_row(res);
        log.setId(atoi(row[0]));
        log.setExecutorHandler(row[1] ? row[1] : "");
        log.setTriggerTime(row[2] ? row[2] : "");
        log.setTriggerCode(atoi(row[3]));
        log.setTriggerMsg(row[4] ? row[4] : "");
    }

    // 释放资源
    mysql_free_result(res);

    return log;
}
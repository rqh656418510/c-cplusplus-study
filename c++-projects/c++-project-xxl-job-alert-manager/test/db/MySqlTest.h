#pragma once

#include "AppConfigLoader.h"
#include "CurrentThread.h"
#include "Logger.h"
#include "MySqlConnectionPool.h"
#include "XxlJobLog.h"
#include "XxlJobLogDao.h"

// MySQL测试
class MySqlTest {
public:
    // 查询XXL-JOB最新的调度日志记录
    void selectLastestXxlJobLog() {
        XxlJobLogDao log_dao;
        XxlJobLog log = log_dao.selectLastest();
        if (log.getId() == 0) {
            LOG_WARN("XXL-JOB lastest log not found");
        } else {
            json j = log;
            LOG_INFO("XXL-JOB lastest log: %s", j.dump().c_str());
        }
    }

    // 查询XXL-JOB最新的调度失败日志记录
    void selectLastestFatalXxlJobLog() {
        XxlJobLogDao log_dao;
        XxlJobLog log = log_dao.selectLastestFatal();
        if (log.getId() == 0) {
            LOG_WARN("XXL-JOB lastest fatal log not found");
        } else {
            json j = log;
            LOG_INFO("XXL-JOB lastest fatal log: %s", j.dump().c_str());
        }
    }

    // 通过单个数据库连接查询数据
    void selectBySingleConnection() {
        // 获取全局配置信息
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();

        // 查询结果
        XxlJobLog log;

        // 创建数据库连接
        MySqlConnection* conn = new MySqlConnection();
        bool connected = conn->connect(config.mysql.ip, config.mysql.port, config.mysql.user, config.mysql.password,
                                       config.mysql.database);
        // 执行查询操作
        if (connected) {
            MYSQL_RES* res = conn->query("select id, executor_handler, trigger_time, trigger_code, trigger_msg from " +
                                         config.mysql.table + " order by trigger_time desc limit 1");
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

            // JSON序列化
            json j = log;

            // 打印查询结果
            LOG_INFO("%s", j.dump().c_str());
        }

        // 释放连接
        delete conn;
    }

    // 单个线程从数据库连接池获取连接执行更新操作
    void connectionPoolSingleThread() {
        // 获取全局配置信息
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();

        // 数据库连接池
        MySqlConnectionPool* pool = MySqlConnectionPool::getInstance();

        // 获取数据库连接
        std::shared_ptr<MySqlConnection> conn = pool->getConnection();

        // 判断连接是否有效
        if (!conn) {
            LOG_ERROR("Connection invalid");
        }

        // SQL语句
        const std::string sql =
            "update " + config.mysql.table +
            " set `handle_msg` = `handle_msg` where trigger_time between now() - interval 1 minute and now()";

        // 执行更新操作
        conn->update(sql);

        // 打印连接池信息
        LOG_INFO("Thread %d, current connection pool size: %d", CurrentThread::tid(), pool->getSize());

        // 手动关闭连接池（可选）
        // pool->close();
    }

    // 多个线程从数据库连接池获取连接执行更新操作
    void connectionPoolMultiThread() {
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();

        // SQL语句
        const std::string sql =
            "update " + config.mysql.table +
            " set `handle_msg` = `handle_msg` where trigger_time between now() - interval 1 minute and now()";

        // 数据库连接池
        MySqlConnectionPool* pool = MySqlConnectionPool::getInstance();

        // 多个线程执行更新操作
        const int num_threads = 30;
        std::thread threads[num_threads];
        for (int i = 0; i < num_threads; i++) {
            threads[i] = std::thread([&, i]() {
                for (int n = 0; n < 100; n++) {
                    // 获取数据连接
                    std::shared_ptr<MySqlConnection> conn = pool->getConnection();
                    if (!conn) {
                        LOG_ERROR("Connection invalid");
                        continue;
                    }
                    // 执行更新操作
                    conn->update(sql);
                    // 打印连接池信息
                    LOG_INFO("Thread %d, current connection pool size: %d", i, pool->getSize());
                }
            });
        }

        // 等待所有线程执行完成
        for (int i = 0; i < num_threads; ++i) {
            threads[i].join();
        }

        // 等待一段时间，触发数据库连接池回收空闲连接
        LOG_INFO("Waiting to recycle idle connection...");
        std::this_thread::sleep_for(std::chrono::seconds(config.mysql.connectionPoolMaxIdleTime * 3));
        LOG_INFO("Final connection pool size: %d", pool->getSize());

        // 手动关闭连接池（可选）
        // pool->close();
    }
};
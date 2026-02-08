#include <chrono>
#include <iostream>

#include "BaseTest.h"
#include "Logger.h"
#include "MySqlTest.h"

int main(int argc, char** argv) {
    // 设置默认日志级别
    Logger::instance().setLogLevel(LogLevel::DEBUG);

    BaseTest baseTest;
    MySqlTest mysqlTest;

    // 加载配置文件
    // baseTest.loadConfigFile();

    // 获取公网IP地址
    // baseTest.getPublicIp();

    // 发送企业微信应用消息
    // baseTest.sendWxQyTextMsg1();

    // 发送企业微信应用消息
    // baseTest.sendWxQyTextMsg2();

    // 通过单个数据库连接查询数据
    // mysqlTest.selectByConnection();

    // 单个线程从数据库连接池获取连接
    // mysqlTest.connectionPoolSingleThread();

    // 多个线程从数据库连接池获取连接
    mysqlTest.connectionPoolMultiThread();

    // 查询XXL-JOB最新的调度日志记录
    // mysqlTest.selectLastestXxlJobLog();

    // 查询XXL-JOB最新的调度失败日志记录
    // mysqlTest.selectLastestFatalXxlJobLog();

    // 等待一段时间后（日志落盘），程序再结束运行
    std::this_thread::sleep_for(std::chrono::seconds(2));
    LOG_INFO("Test finished.");

    return 0;
}
#include <chrono>
#include <iostream>

#include "BaseTest.h"
#include "Logger.h"
#include "MonitorTest.h"
#include "MySqlTest.h"
#include "WxQyTest.h"

int main(int argc, char** argv) {
    // 设置默认日志级别
    Logger::instance().setLogLevel(LogLevel::DEBUG);

    BaseTest baseTest;

    // 加载配置文件
    // baseTest.loadConfigFile();

    // 获取公网IP地址
    // baseTest.getPublicIp();

    WxQyTest wxQyTest;

    // 发送企业微信应用消息
    // wxQyTest.sendWxQyTextMsg1();

    // 发送企业微信应用消息
    // wxQyTest.sendWxQyTextMsg2();

    // 启动与关闭AccessToken刷新器
    // wxQyTest.startAndStopTokenRefresher();

    MySqlTest mysqlTest;

    // 通过单个数据库连接查询数据
    // mysqlTest.selectBySingleConnection();

    // 单个线程从数据库连接池获取连接执行更新操作
    // mysqlTest.connectionPoolSingleThread();

    // 多个线程从数据库连接池获取连接执行更新操作
    mysqlTest.connectionPoolMultiThread();

    // 查询XXL-JOB最新的调度日志记录
    // mysqlTest.selectLastestXxlJobLog();

    // 查询XXL-JOB最新的调度失败日志记录
    // mysqlTest.selectLastestFatalXxlJobLog();

    MonitorTest monitorTest;

    // 启动与关闭监控器
    // monitorTest.startAndStopMonitor();

    // 等待用户任意输入，然后结束程序
    LOG_INFO("Wait to user any input to exit.");
    char c = getchar();

    // 等待日志全部落盘，最后结束程序
    std::this_thread::sleep_for(std::chrono::seconds(2));
    LOG_INFO("Test finished.");

    return 0;
}
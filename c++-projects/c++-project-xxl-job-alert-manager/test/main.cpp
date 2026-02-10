#include <chrono>
#include <iostream>

#include "AlertTest.h"
#include "BaseTest.h"
#include "ConfigTest.h"
#include "JobTest.h"
#include "MySqlTest.h"
#include "NetworkTest.h"
#include "WxQyAlertTest.h"

int main(int argc, char** argv) {
    // 设置默认日志级别
    Logger::instance().setLogLevel(LogLevel::DEBUG);

    BaseTest baseTest;

    // 获取当前时间
    // baseTest.nowDateTime();

    ConfigTest configTest;

    // 加载配置文件
    // configTest.loadConfigFile();

    NetworkTest networkTest;

    // 获取公网IP地址
    // networkTest.getPublicIp();

    AlertTest alertTest;

    // 邮件渠道告警
    // alertTest.emailAlert();

    // 企业微信渠道告警
    // alertTest.wxQyAlert();

    // 异步邮件渠道告警
    // alertTest.asyncEmailAlert();

    // 异步企业微信渠道告警
    // alertTest.asyncwxQyAlert();

    // 复合渠道告警
    // alertTest.compositeAlert();

    // 告警管理器
    // alertTest.alertManager();

    WxQyAlertTest wxQyAlertTest;

    // 发送企业微信应用消息
    // wxQyAlertTest.sendWxQyTextMsg1();

    // 发送企业微信应用消息
    // wxQyAlertTest.sendWxQyTextMsg2();

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

    JobTest jobTest;

    // 获取企业微信AccessToken
    // jobTest.getAccessToken();

    // 启动与关闭监控器
    // jobTest.startAndStopMonitor();

    // 启动与关闭AccessToken刷新器
    // jobTest.startAndStopTokenRefresher();

    // 等待用户任意输入，然后结束程序
    LOG_INFO("Wait to user any input to exit.");
    char c = getchar();

    // 等待日志全部落盘，最后结束程序
    std::this_thread::sleep_for(std::chrono::seconds(2));
    LOG_INFO("Test finished.");

    return 0;
}
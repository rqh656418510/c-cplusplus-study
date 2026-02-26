#include <chrono>
#include <iostream>

#include "AlertTest.h"
#include "BaseTest.h"
#include "ConfigTest.h"
#include "JobTest.h"
#include "MySqlTest.h"
#include "NetworkTest.h"

// 基础测试
void baseTest() {
    BaseTest baseTest;

    // 获取当前时间
    // baseTest.getTimestamp();

    // 当前时间戳转换为日期字符串
    // baseTest.toDateString();

    // 当前时间戳转换为日期时间字符串
    // baseTest.toDateTimeString();

    // 将UTC时间字符串转换为UTC时间戳（秒）
    // baseTest.toUtcTimestampSec();

    // 将UTC时间字符串转换为UTC时间戳（毫秒）
    // baseTest.toUtcTimestampMs();

    // 将UTC时间字符串转换为UTC时间戳（微秒）
    // baseTest.toUtcTimestampUs();

    // 将本地时间字符串转换为UTC时间戳（秒）
    // baseTest.localToUtcTimestampSec();

    // 将本地时间字符串转换为UTC时间戳（毫秒）
    // baseTest.localToUtcTimestampMs();

    // 将本地时间字符串转换为UTC时间戳（微秒）
    // baseTest.localToUtcTimestampUs();
}

// 配置测试
void configTest() {
    ConfigTest configTest;

    // 加载配置文件
    // configTest.loadConfigFile();
}

// 网络测试
void networkTest() {
    NetworkTest networkTest;

    // 获取公网IP地址
    // networkTest.getPublicIp();
}

// 告警测试
void alertTest() {
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

    // 发送XXL-JOB告警消息
    // alertTest.sendXxlJobAlertMsg();
}

// MySQL测试
void mysqlTest() {
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
}

// 调度测试
void jobTest() {
    JobTest jobTest;

    // 获取企业微信AccessToken
    // jobTest.getAccessToken();

    // 启动与关闭监控器
    // jobTest.startAndStopMonitor();

    // 启动与关闭AccessToken刷新器
    // jobTest.startAndStopTokenRefresher();
}

// 打印命令帮助内容
void ShowArgsHelp() {
    std::cout << "Usage: alert-manager-test [options]\n"
              << "Options:\n"
              << "  -i <config_file>   specify config file (default: ./alert.conf)\n"
              << "  -h                 show help\n";
}

// 获取用户配置文件
std::string getConfigFile(int argc, char** argv) {
    // 获取命令行参数
    int c = 0;
    opterr = 0;               // 关闭 getopt 自身的报错
    std::string config_file;  // 用户指定的配置文件
    while ((c = getopt(argc, argv, "hi:")) != -1) {
        switch (c) {
            case 'h':
                ShowArgsHelp();
                exit(EXIT_SUCCESS);
            case 'i':
                config_file = optarg;
                break;
            case '?':
            default:
                std::cout << "invalid command args!" << std::endl;
                ShowArgsHelp();
                exit(EXIT_FAILURE);
        }
    }

    // 返回用户配置文件
    return config_file;
}

int main(int argc, char** argv) {
    // 获取用户配置文件
    std::string configFile = getConfigFile(argc, argv);

    // 设置全局的配置文件
    if (!configFile.empty()) {
        AppConfigLoader::CONFIG_FILE = configFile;
    }

    // 设置默认日志级别
    std::string logLevelStr = AppConfigLoader::getInstance().getConfig().alertCommon.logLevel;
    LogLevel logLevel = Logger::stringToLogLevel(logLevelStr);
    Logger::getInstance().setLogLevel(logLevel);

    // 基础测试
    baseTest();

    // 配置测试
    configTest();

    // 网络测试
    networkTest();

    // 告警测试
    alertTest();

    // MySQL测试
    mysqlTest();

    // 调度测试
    jobTest();

    // 等待用户输入任意字符，然后结束程序
    LOG_INFO("Wait to user any input to exit");
    char c = getchar();

    LOG_INFO("Test finished");
    return 0;
}
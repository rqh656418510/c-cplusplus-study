#include <unistd.h>

#include <iostream>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "WxQyTokenRefresher.h"
#include "XxlJobMonitor.h"

// 打印命令帮助内容
void ShowArgsHelp() {
    std::cout << "Usage: xxl_job_alert_manager [options]\n"
              << "Options:\n"
              << "  -i <config_file>   specify config file (default: ./alert.conf)\n"
              << "  -h                 show help\n";
}

// 初始化应用程序
void initApplication(int argc, char** argv) {
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

    // 设置全局的日志级别
    Logger::instance().setLogLevel(LogLevel::DEBUG);

    // 设置全局的配置文件路径
    if (!config_file.empty()) {
        AppConfigLoader::CONFIG_FILE_PATH = config_file;
    }
}

int main(int argc, char** argv) {
    // 初始化应用程序
    initApplication(argc, argv);

    // 启动AccessToken刷新器
    WxQyTokenRefresher::getInstance().start();

    // 启动XXL-JOB监控器
    XxlJobMonitor::getInstance().start();

    getchar();
    LOG_INFO("program exited.");

    return 0;
}
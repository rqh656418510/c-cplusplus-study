#include <unistd.h>

#include <atomic>
#include <csignal>
#include <iostream>

#include "AppConfigLoader.h"
#include "Application.h"
#include "Logger.h"

// 应用程序
static std::atomic<Application*> appPtr_{nullptr};

// 信号处理
void signalHandler(int signal) {
    Application* app = appPtr_.load(std::memory_order_acquire);
    if (app) {
        // 停止应用程序
        app->stop();
    }
}

// 打印命令帮助内容
void ShowArgsHelp() {
    std::cout << "Usage: alert_manager [options]\n"
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
    // 创建应用程序
    Application app;

    // 让信号处理器能访问应用程序
    appPtr_.store(&app);

    // 信号处理注册
    std::signal(SIGTERM, signalHandler);
    std::signal(SIGINT, signalHandler);

    // 初始化应用程序
    app.init(getConfigFile(argc, argv));

    // 运行应用程序（会阻塞等待）
    app.run();

    // 重置指针
    appPtr_.store(nullptr, std::memory_order_relaxed);

    return 0;
}
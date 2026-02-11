#pragma once

#include <atomic>
#include <string>

// 应用程序
class Application {
public:
    // 初始化应用程序
    void init(const std::string& config_file);

    // 运行应用程序
    void run();

    // 停止应用程序
    void stop();

private:
    // 关闭应用程序
    void shutdown();

private:
    std::atomic<bool> appRunning_{true};  // 应用运行标识
};
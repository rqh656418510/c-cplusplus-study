#pragma once

#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>

#include <atomic>
#include <string>

#include "CurrentThread.h"
#include "Timestamp.h"

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

    // 通过锁文件加排他锁，防止应用程序被启动多个实例
    int lockfile(const char* path);

private:
    int appLockFd_;                       // 应用程序的文件描述符
    std::atomic<bool> appRunning_{true};  // 应用程序的运行标识
};
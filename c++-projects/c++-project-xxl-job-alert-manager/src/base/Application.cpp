#include "Application.h"

#include <exception>
#include <thread>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "MySqlConnectionPool.h"
#include "WxQyTokenRefresher.h"
#include "XxlJobMonitor.h"

// 应用程序的锁文件
static const std::string APP_LOCK_FILE = "/tmp/alert-manager.lock";

// 初始化应用程序
void Application::init(const std::string& configFile) {
    // 通过锁文件加排他锁，防止应用程序被启动多个实例
    this->appLockFd_ = lockfile(APP_LOCK_FILE.c_str());
    if (this->appLockFd_ < 0) {
        // 退出应用程序
        exit(EXIT_FAILURE);
    }

    // 设置全局的配置文件
    if (!configFile.empty()) {
        AppConfigLoader::CONFIG_FILE_PATH = configFile;
    }

    // 设置全局的日志输出级别
    Logger::getInstance().setLogLevel(
        Logger::stringToLogLevel(AppConfigLoader::getInstance().getConfig().alert.logLevel));
}

// 通过锁文件加排他锁，防止应用程序被启动多个实例
int Application::lockfile(const char* path) {
    // 打开锁文件（不存在会自动创建）
    int fd = open(path, O_RDWR | O_CREAT, 0644);

    // 打开锁文件失败
    if (fd < 0) {
        // 打印日志信息
        char buf[1024] = {};
        std::string timestamp = Timestamp::now().toString();
        snprintf(buf, sizeof(buf), "%s => %d [FATAL] Failed to open lock file [%s]", timestamp.c_str(),
                 CurrentThread::tid(), APP_LOCK_FILE.c_str());
        std::cout << buf << std::endl;

        // 加锁失败返回-1
        return -1;
    }

    // 尝试加非阻塞排他锁，若失败则说明已经有其他实例正在运行
    if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
        // 打印日志信息
        char buf[1024] = {};
        std::string timestamp = Timestamp::now().toString();
        snprintf(buf, sizeof(buf), "%s => %d [FATAL] Another instance is running", timestamp.c_str(),
                 CurrentThread::tid());
        std::cout << buf << std::endl;

        // 释放文件描述符
        close(fd);

        // 加锁失败返回-1
        return -1;
    }

    // 加锁成功，返回 fd（需要在程序生命周期内保持该fd不关闭）
    return fd;
}

// 运行应用程序
void Application::run() {
    try {
        // 打印日志信息
        LOG_INFO("Alert manager started.");

        // 启动AccessToken刷新器
        WxQyTokenRefresher::getInstance().start();

        // 启动XXL-JOB监控器
        XxlJobMonitor::getInstance().start();

        // 循环等待应用程序关闭
        while (this->appRunning_.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        // 正常退出循环后关闭应用程序
        shutdown();
    } catch (const std::exception& e) {
        LOG_ERROR("Alert manager exited, fatal exception: {}", e.what());
        // 让Systemd可以触发[Restart=on-failure]
        std::abort();
    } catch (...) {
        LOG_FATAL("Alert manager exited, fatal unknown exception");
        // 让Systemd可以触发[Restart=on-failure]
        std::abort();
    }
}

// 停止应用程序
void Application::stop() {
    // 更新应用运行标识
    this->appRunning_.store(false, std::memory_order_release);
}

// 工作循环
void Application::shutdown() {
    // 停止业务线程（阻塞等待）
    XxlJobMonitor::getInstance().stop();
    WxQyTokenRefresher::getInstance().stop();
    MySqlConnectionPool::getInstance()->close();

    // 释放文件描述符
    if (appLockFd_ >= 0) {
        close(appLockFd_);
        appLockFd_ = -1;
    }

    // 打印日志信息
    LOG_INFO("Alert manager stopped.");
}
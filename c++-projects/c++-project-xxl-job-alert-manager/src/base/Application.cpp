#include "Application.h"

#include <exception>
#include <thread>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "MySqlConnectionPool.h"
#include "WxQyTokenRefresher.h"
#include "XxlJobMonitor.h"

// 初始化应用程序
void Application::init(const std::string& configFile) {
    // 设置全局的日志级别
    Logger::instance().setLogLevel(LogLevel::DEBUG);

    // 设置全局的配置文件路径
    if (!configFile.empty()) {
        AppConfigLoader::CONFIG_FILE_PATH = configFile;
    }
}

// 运行应用程序
void Application::run() {
    try {
        // 打印日志信息
        LOG_INFO("Alert Manager Started.");

        // 启动AccessToken刷新器
        WxQyTokenRefresher::getInstance().start();

        // 启动XXL-JOB监控器
        XxlJobMonitor::getInstance().start();

        // 循环等待应用程序关闭
        while (this->appRunning_.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Alert Manager Exited, Fatal Error: {}", e.what());
    }

    // 退出循环后关闭应用程序
    shutdown();
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

    // 打印日志信息
    LOG_INFO("Alert Manager Stopped.");
}
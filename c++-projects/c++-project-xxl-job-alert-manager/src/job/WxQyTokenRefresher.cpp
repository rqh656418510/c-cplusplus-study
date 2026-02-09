#include "WxQyTokenRefresher.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "WxQyApi.h"

// 私有构造函数
WxQyTokenRefresher::WxQyTokenRefresher() : accessToken_(""), refreshRunning_(false) {
}

// 私有析构函数
WxQyTokenRefresher::~WxQyTokenRefresher() {
    // 关闭刷新器
    if (refreshRunning_) {
        this->stop();
    }
}

// 获取单例对象
WxQyTokenRefresher& WxQyTokenRefresher::getInstance() {
    // 静态局部变量（线程安全）
    static WxQyTokenRefresher instance;
    return instance;
}

// 启动刷新器
void WxQyTokenRefresher::start() {
    // 判断刷新器是否处于关闭状态
    if (!refreshRunning_) {
        // 更改运行状态
        refreshRunning_ = true;

        // 创建刷新AccessToken的线程
        refreshThread_ = std::thread(std::bind(&WxQyTokenRefresher::refreshLocalTokenLoop, this));

        // 打印日志信息
        LOG_INFO("wx-qy token refresher started");
    }
}

// 关闭刷新器
void WxQyTokenRefresher::stop() {
    // 判断刷新器是否已关闭
    if (!refreshRunning_) {
        return;
    }

    // 更改运行状态
    refreshRunning_ = false;

    // 通知刷新线程结束运行
    refreshCv_.notify_all();

    // 等待刷新线程结束运行
    if (refreshThread_.joinable()) {
        refreshThread_.join();
    }

    // 打印日志信息
    LOG_INFO("wx-qy token refresher stoped");
}

// 循环刷新本地的AccessToken
void WxQyTokenRefresher::refreshLocalTokenLoop() {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    while (refreshRunning_) {
        // 刷新的时间间隔（秒）
        int wait_seconds = config.alert.wechatRefreshTokenIntervalTime;

        try {
            // 获取新的AccessToken
            std::string new_token = WxQyApi::getAccessToken();
            if (!new_token.empty()) {
                // 获取成功后，设置本地的AccessToken
                {
                    std::lock_guard<std::mutex> lock(accessTokenMutex_);
                    accessToken_ = new_token;
                }
            } else {
                // 获取失败后，使用较短的等待时间后重试
                wait_seconds = config.alert.wechatRetryRefreshIntervalTime;
                LOG_WARN("failed to get wx-qy access token, will retry after %ds", wait_seconds);
            }
        } catch (const std::exception& e) {
            // 获取失败后，使用较短的等待时间后重试
            wait_seconds = config.alert.wechatRetryRefreshIntervalTime;
            LOG_ERROR("wx-qy token refresher occure exception: %s, will retry refresh after %ds", e.what(),
                      wait_seconds);
        } catch (...) {
            // 获取失败后，使用较短的等待时间后重试
            wait_seconds = config.alert.wechatRetryRefreshIntervalTime;
            LOG_ERROR("wx-qy token refresher occure unknown exception, will retry refresh after %ds", wait_seconds);
        }

        // 使用条件变量进行可中断的定时等待，在每次被唤醒（包括虚假唤醒）时都会检查运行标志；若检测到已停止刷新则立即返回，以保证刷新线程能够安全退出
        std::unique_lock<std::mutex> lock(accessTokenMutex_);
        if (refreshCv_.wait_for(lock, std::chrono::seconds(wait_seconds),
                                [this]() { return !refreshRunning_.load(); })) {
            // 当被唤醒时，说明已停止刷新，退出刷新线程
            break;
        }
    }
}

// 获取本地的AccessToken
std::string WxQyTokenRefresher::getLocalAccessToken() {
    // 获取本地的AccessToken（只短暂持有锁）
    {
        std::lock_guard<std::mutex> lock(accessTokenMutex_);
        if (!accessToken_.empty()) {
            return accessToken_;
        }
    }

    // 当本地的AccessToken为空，则获取最新的AccessToken（网络耗时操作）
    std::string access_token = WxQyApi::getAccessToken();

    // 成功获取最新的AccessToken时，加锁后再更新本地的AccessToken
    if (!access_token.empty()) {
        std::lock_guard<std::mutex> lock(accessTokenMutex_);
        accessToken_ = access_token;
        return access_token;
    }

    // 获取最新的AccessToken失败时，加锁后返回本地的AccessToken（可能为空）
    std::lock_guard<std::mutex> lock(accessTokenMutex_);
    return accessToken_;
}
#include "WxQyTokenRefresher.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "WxQyApi.h"

// 私有构造函数
WxQyTokenRefresher::WxQyTokenRefresher() : accessToken_(""), refreshRunning_(true) {
}

// 私有析构函数
WxQyTokenRefresher::~WxQyTokenRefresher() {
}

// 获取单例对象
WxQyTokenRefresher& WxQyTokenRefresher::getInstance() {
    // 静态局部变量（线程安全）
    static WxQyTokenRefresher instance;
    return instance;
}

// 启动刷新器
void WxQyTokenRefresher::start() {
    // 后台启动刷新AccessToken的线程
    std::thread t_refresh(std::bind(&WxQyTokenRefresher::refreshLocalTokenLoop, this));
    t_refresh.detach();
}

// 关闭刷新器
void WxQyTokenRefresher::stop() {
    // 更改运行状态
    refreshRunning_ = false;
}

// 循环刷新本地的AccessToken
void WxQyTokenRefresher::refreshLocalTokenLoop() {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    while (refreshRunning_) {
        // 刷新的时间间隔（秒）
        int wait_seconds = config.alert.wechatRefreshTokenIntervalSeconds;

        try {
            // 获取 AccessToken
            std::string access_token = WxQyApi::getAccessToken();
            if (!access_token.empty()) {
                // 获取成功后，设置本地的AccessToken
                {
                    std::lock_guard<std::mutex> lock(accessTokenMutex_);
                    accessToken_ = access_token;
                }
            } else {
                // 获取失败后，使用较短的等待时间后重试
                wait_seconds = config.alert.wechatRetryRefreshIntervalSeconds;
                LOG_WARN("failed to get wx-qy access token, will retry after %ds", wait_seconds);
            }
        } catch (const std::exception& e) {
            // 获取失败后，使用较短的等待时间后重试
            wait_seconds = config.alert.wechatRetryRefreshIntervalSeconds;
            LOG_ERROR("wx-qy token refresher occure exception: %s, will retry refresh after %ds", e.what(),
                      wait_seconds);
        } catch (...) {
            // 获取失败后，使用较短的等待时间后重试
            wait_seconds = config.alert.wechatRetryRefreshIntervalSeconds;
            LOG_ERROR("wx-qy token refresher occure unknown exception, will retry refresh after %ds", wait_seconds);
        }

        // 模拟定时刷新
        std::this_thread::sleep_for(std::chrono::seconds(wait_seconds));
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
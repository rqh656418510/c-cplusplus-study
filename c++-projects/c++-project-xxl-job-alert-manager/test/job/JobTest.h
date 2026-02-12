#pragma once

#include <chrono>
#include <thread>

#include "AppConfigLoader.h"
#include "WxQyTokenRefresher.h"
#include "XxlJobMonitor.h"

// XXL-JOB监控测试
class JobTest {
public:
    // 获取企业微信AccessToken
    void getAccessToken() {
        std::string access_token = WxQyTokenRefresher::getInstance().getLocalAccessToken();
        LOG_INFO("Access token: %s", access_token.c_str());
    }

    // 启动与关闭监控器
    void startAndStopMonitor() {
        // 启动监控器
        XxlJobMonitor::getInstance().start();

        // 等待一段时间
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        std::this_thread::sleep_for(std::chrono::seconds(config.alert.xxljobStopStatusScanIntervalTime * 3));

        // 关闭监控器
        XxlJobMonitor::getInstance().stop();
    }

    // 启动与关闭AccessToken刷新器
    void startAndStopTokenRefresher() {
        // 启动刷新器
        WxQyTokenRefresher::getInstance().start();

        // 等待一段时间
        std::this_thread::sleep_for(std::chrono::seconds(15));

        // 关闭刷新器
        WxQyTokenRefresher::getInstance().stop();
    }
};
#pragma once

#include <iostream>
#include <thread>

#include "Alert.h"
#include "AppConfigLoader.h"
#include "Logger.h"
#include "NetworkUtil.h"
#include "Timestamp.h"
#include "WxQyTokenRefresher.h"
#include "XxlJobLog.h"

// 企业微信应用消息测试
class WxQyTest {
public:
    // 启动与关闭AccessToken刷新器
    void startAndStopTokenRefresher() {
        // 启动刷新器
        WxQyTokenRefresher::getInstance().start();

        // 等待一段时间
        std::this_thread::sleep_for(std::chrono::seconds(15));

        // 关闭刷新器
        WxQyTokenRefresher::getInstance().stop();
    }

    // 获取企业微信AccessToken
    void getAccessToken() {
        std::string access_token = WxQyTokenRefresher::getInstance().getLocalAccessToken();
        LOG_INFO("access token: %s", access_token.c_str());
    }

    // 发送企业微信应用消息
    void sendWxQyTextMsg1() {
        char buf[1024] = {0};
        sprintf(buf, "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s", Timestamp::now().toString().c_str(),
                NetworkUtil::getInstance().getPublicIp().c_str());

        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        Alert::sendWxQyTextMsg(config.wechatAccount.agentId, config.wechatAccount.toUser, std::string(buf));
    }

    // 发送企业微信应用消息
    void sendWxQyTextMsg2() {
        std::string msg =
            R"(任务触发类型: Cron触发<br>调度机器: 192.168.1.3<br>执行器-注册方式: 自动注册<br>执行器-地址列表: null
        <br>路由策略: 轮询<br>阻塞处理策略: 丢弃后续调度<br>任务超时时间: 30<br>失败重试次数: 0<br><br>
        <span style="color:#00c0ef;" > >>>>>>>>>>>触发调度<<<<<<<<<<< </span><br>调度失败: 执行器地址为空<br><br>)";

        XxlJobLog job_log;
        job_log.setId(54529936);
        job_log.setExecutorHandler("optionProvidePricePush");
        job_log.setTriggerTime(Timestamp::now().toString());
        job_log.setTriggerCode(500);
        job_log.setTriggerMsg(msg);

        const AppConfig& config = AppConfigLoader::getInstance().getConfig();
        Alert::sendWxQyTextMsg(config.wechatAccount.agentId, config.wechatAccount.toUser, job_log);
    }
};
#pragma once

#include <iostream>
#include <thread>

#include "AlertChannelFactory.h"
#include "AlertManager.h"
#include "AppConfigLoader.h"
#include "Logger.h"
#include "Network.h"
#include "Timestamp.h"
#include "XxlJobLog.h"

// 企业微信告警测试
class WxQyAlertTest {
public:
    // 获取企业微信AccessToken
    void getAccessToken() {
        std::string access_token = WxQyTokenRefresher::getInstance().getLocalAccessToken();
        LOG_INFO("access token: %s", access_token.c_str());
    }

    // 发送企业微信应用消息
    void sendWxQyTextMsg1() {
        AlertManager alertManager;
        alertManager.registerChannel(AlertLevel::CRITICAL, AlertChannelFactory::getInstance().createAsyncWxQyAlert());

        char buf[1024] = {0};
        sprintf(buf, "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s", Timestamp::now().toString().c_str(),
                Network::getInstance().getPublicIp().c_str());

        alertManager.alert(AlertLevel::CRITICAL, "XXL-JOB 监控告警", std::string(buf));
    }

    // 发送企业微信应用消息
    void sendWxQyTextMsg2() {
        AlertManager alertManager;
        alertManager.registerChannel(AlertLevel::CRITICAL, AlertChannelFactory::getInstance().createAsyncWxQyAlert());

        std::string msg =
            R"(任务触发类型: Cron触发<br>调度机器: 192.168.1.3<br>执行器-注册方式: 自动注册<br>执行器-地址列表: null
        <br>路由策略: 轮询<br>阻塞处理策略: 丢弃后续调度<br>任务超时时间: 30<br>失败重试次数: 0<br><br>
        <span style="color:#00c0ef;" > >>>>>>>>>>>触发调度<<<<<<<<<<< </span><br>调度失败: 执行器地址为空<br><br>)";

        XxlJobLog jobLog;
        jobLog.setId(54529936);
        jobLog.setExecutorHandler("optionProvidePricePush");
        jobLog.setTriggerTime(Timestamp::now().toString());
        jobLog.setTriggerCode(500);
        jobLog.setTriggerMsg(msg);

        alertManager.alert(AlertLevel::CRITICAL, "XXL-JOB 监控告警", jobLog.parseAlertMsg());
    }
};
#pragma once

#include <memory>

#include "AlertChannel.h"
#include "AlertChannelFactory.h"
#include "AlertManager.h"
#include "AsyncAlert.h"
#include "CompositeAlert.h"
#include "EmailAlert.h"
#include "Timestamp.h"
#include "WxQyAlert.h"
#include "XxlJobLog.h"

// 告警测试
class AlertTest {
public:
    // 邮件渠道告警
    void emailAlert() {
        std::shared_ptr<AlertChannel> emailAlert = AlertChannelFactory::getInstance().createEmailAlert();
        emailAlert->sendMsg("XXL-JOB告警", "XXL-JOB已停止运行");
    }

    // 企业微信渠道告警
    void wxQyAlert() {
        std::shared_ptr<AlertChannel> wxQyAlert = AlertChannelFactory::getInstance().createWxQyAlert();
        wxQyAlert->sendMsg("XXL-JOB告警", "XXL-JOB已停止运行");
    }

    // 异步邮件渠道告警
    void asyncEmailAlert() {
        std::shared_ptr<AlertChannel> asyncEmailAlert = AlertChannelFactory::getInstance().createAsyncEmailAlert();
        asyncEmailAlert->sendMsg("XXL-JOB告警", "XXL-JOB已停止运行");
    }

    // 异步企业微信渠道告警
    void asyncwxQyAlert() {
        std::shared_ptr<AlertChannel> asyncWxQyAlert = AlertChannelFactory::getInstance().createAsyncWxQyAlert();
        asyncWxQyAlert->sendMsg("XXL-JOB告警", "XXL-JOB已停止运行");
    }

    // 复合渠道告警
    void compositeAlert() {
        std::shared_ptr<CompositeAlert> compositeAlert = AlertChannelFactory::getInstance().createCompositeAlert();
        compositeAlert->addChannel(AlertChannelFactory::getInstance().createEmailAlert());
        compositeAlert->addChannel(AlertChannelFactory::getInstance().createWxQyAlert());
        compositeAlert->sendMsg("XXL-JOB告警", "XXL-JOB已停止运行");
    }

    // 告警管理器
    void alertManager() {
        AlertManager manager;
        manager.registerChannel(AlertLevel::INFO, AlertChannelFactory::getInstance().createEmailAlert());
        manager.registerChannel(AlertLevel::CRITICAL, AlertChannelFactory::getInstance().createWxQyAlert());
        manager.alert(AlertLevel::INFO, "XXL-JOB告警", "XXL-JOB已停止运行");
        manager.alert(AlertLevel::CRITICAL, "XXL-JOB告警", "XXL-JOB已停止运行");
    }

    // 发送XXL-JOB告警消息
    void sendXxlJobAlertMsg() {
        AlertManager alertManager;
        alertManager.registerChannel(AlertLevel::CRITICAL, AlertChannelFactory::getInstance().createAsyncWxQyAlert());

        std::string msg =
            R"(任务触发类型: Cron触发<br>调度机器: 192.168.1.3<br>执行器-注册方式: 自动注册<br>执行器-地址列表: null
        <br>路由策略: 轮询<br>阻塞处理策略: 丢弃后续调度<br>任务超时时间: 30<br>失败重试次数: 0<br><br>
        <span style="color:#00c0ef;" > >>>>>>>>>>>触发调度<<<<<<<<<<< </span><br>调度失败: 执行器地址为空<br><br>)";

        XxlJobLog jobLog;
        jobLog.setId(54529936);
        jobLog.setExecutorHandler("optionProvidePricePush");
        jobLog.setTriggerTime(Timestamp::now().toDateTimeString());
        jobLog.setTriggerCode(500);
        jobLog.setTriggerMsg(msg);

        alertManager.alert(AlertLevel::CRITICAL, "XXL-JOB 监控告警", jobLog.parseAlertMsg());
    }
};
#pragma once

#include <memory>

#include "AlertChannel.h"
#include "AlertChannelFactory.h"
#include "AlertManager.h"
#include "AsyncAlert.h"
#include "CompositeAlert.h"
#include "EmailAlert.h"
#include "WxQyAlert.h"

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
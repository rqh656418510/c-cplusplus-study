#pragma once

#include <memory>
#include <string>

#include "AlertChannel.h"

// 告警管理器
class AlertManager {
public:
    // 构造函数
    explicit AlertManager(std::shared_ptr<AlertChannel> channel) : channel_(std::move(channel)) {
    }

    // 执行告警
    void alert(const std::string& title, const std::string& content) {
        channel_->sendMsg(title, content);
    }

private:
    // 告警渠道
    std::shared_ptr<AlertChannel> channel_;
};
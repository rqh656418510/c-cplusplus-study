#pragma once

#include <memory>
#include <string>

#include "AlertChannel.h"
#include "NonCopyable.h"

// 告警管理器
class AlertManager : NonCopyable {
public:
    // 构造函数
    explicit AlertManager(std::shared_ptr<AlertChannel> channel);

    // 执行告警
    void alert(const std::string& title, const std::string& content);

private:
    // 告警渠道
    std::shared_ptr<AlertChannel> channel_;
};
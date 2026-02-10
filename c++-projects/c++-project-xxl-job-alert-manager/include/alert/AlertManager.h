#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "AlertChannel.h"
#include "NonCopyable.h"
#include "unordered_map"
#include "vector"

// 告警管理器（线程安全）
class AlertManager : NonCopyable {
public:
    // 注册告警渠道
    void registerChannel(AlertLevel level, std::shared_ptr<AlertChannel> channel);

    // 执行告警
    bool alert(AlertLevel level, const std::string& title, const std::string& content);

private:
    // 告警路由
    std::unordered_map<AlertLevel, std::vector<std::shared_ptr<AlertChannel>>> routes_;
    // 互斥锁（保证Map线程安全）
    std::mutex mutex_;
};
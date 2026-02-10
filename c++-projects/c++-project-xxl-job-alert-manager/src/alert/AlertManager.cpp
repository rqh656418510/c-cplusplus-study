
#include "AlertManager.h"

#include <exception>

#include "Logger.h"

// 注册告警渠道
void AlertManager::registerChannel(AlertLevel level, std::shared_ptr<AlertChannel> channel) {
    if (!channel) {
        LOG_WARN("Alert channel is invalid");
        return;
    }

    routes_[level].push_back(channel);
}

// 执行告警
void AlertManager::alert(AlertLevel level, const std::string& title, const std::string& content) {
    // 查找告警渠道
    auto it = routes_.find(level);
    if (it == routes_.end()) {
        LOG_WARN("Not found alert channel for level: %d", static_cast<int>(level));
        return;
    }

    // 发送告警消息
    for (const auto& channel : it->second) {
        if (!channel) {
            LOG_WARN("Alert channel is invalid");
            continue;
        }

        try {
            channel->sendMsg(title, content);
        } catch (const std::exception& e) {
            LOG_ERROR("Failed to send alert message, exception: %s", e.what());
        } catch (...) {
            LOG_ERROR("Failed to send alert message, unknown exception");
        }
    }
}
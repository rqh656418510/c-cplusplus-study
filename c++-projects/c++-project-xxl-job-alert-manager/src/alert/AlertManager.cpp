
#include "AlertManager.h"

#include <exception>

#include "Logger.h"

// 注册告警渠道
void AlertManager::registerChannel(AlertLevel level, std::shared_ptr<AlertChannel> channel) {
    if (!channel) {
        LOG_WARN("Failed to register alert channel, channel is invalid");
        return;
    }

    // 获取互斥锁
    std::lock_guard<std::mutex> lock(mutex_);

    // 将数据放入Map
    routes_[level].push_back(channel);
}

// 执行告警
bool AlertManager::alert(AlertLevel level, const std::string& title, const std::string& content) {
    std::unordered_map<AlertLevel, std::vector<std::shared_ptr<AlertChannel>>> routesCopy;
    {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(mutex_);
        // 先拷贝一份Map，后续再遍历，减少持锁时间
        routesCopy = routes_;
    }

    // 全部发送成功标记
    bool allSucceeded = true;

    // 查找告警渠道
    auto it = routesCopy.find(level);
    if (it == routesCopy.end()) {
        LOG_WARN("Not found alert channel for level: %d", static_cast<int>(level));
        return false;
    }

    // 发送告警消息
    for (const auto& channel : it->second) {
        if (!channel) {
            allSucceeded = false;
            LOG_WARN("Invalid alert channels for level %d", static_cast<int>(level));
            continue;
        }

        try {
            allSucceeded &= channel->sendMsg(title, content);
        } catch (const std::exception& e) {
            allSucceeded = false;
            LOG_ERROR("Failed to send alert message, exception: %s", e.what());
        } catch (...) {
            allSucceeded = false;
            LOG_ERROR("Failed to send alert message, unknown exception");
        }
    }

    return allSucceeded;
}
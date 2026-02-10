#include "CompositeAlert.h"

#include <exception>

#include "Logger.h"

// 添加告警渠道
void CompositeAlert::addChannel(std::shared_ptr<AlertChannel> channel) {
    if (!channel) {
        LOG_WARN("Failed to add alert channel, channel is invalid");
        return;
    }

    // 获取互斥锁
    std::lock_guard<std::mutex> lock(mutex_);

    // 将数据放入集合
    channels_.push_back(channel);
}

// 发送消息
bool CompositeAlert::sendMsg(const std::string& title, const std::string& content) {
    std::vector<std::shared_ptr<AlertChannel>> channelsCopy;
    {
        // 获取互斥锁
        std::lock_guard<std::mutex> lock(mutex_);
        // 先拷贝一份集合，后续再遍历，减少持锁时间
        channelsCopy = channels_;
    }

    // 全部发送成功标记
    bool allSucceeded = true;

    // 遍历所有告警渠道
    for (const auto& channel : channelsCopy) {
        if (!channel) {
            allSucceeded = false;
            LOG_WARN("Invalid alert channel");
            continue;
        }

        // 必须捕获异常，不能影响任何业务执行
        try {
            // 发送告警消息
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
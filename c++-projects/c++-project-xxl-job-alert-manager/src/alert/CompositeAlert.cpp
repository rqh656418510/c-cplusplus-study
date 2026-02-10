#include "CompositeAlert.h"

#include <exception>

#include "Logger.h"

// 添加告警渠道
void CompositeAlert::addChannel(std::shared_ptr<AlertChannel> channel) {
    if (!channel) {
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
        // 拷贝一份集合，减少持锁时间
        channelsCopy = channels_;
    }

    // 成功发送标记
    bool allSucceeded = true;

    // 遍历所有告警渠道
    for (const auto& channel : channelsCopy) {
        if (!channel) {
            allSucceeded = false;
            continue;
        }

        try {
            allSucceeded &= channel->sendMsg(title, content);
        } catch (const std::exception& e) {
            LOG_ERROR("Failed to execute composite alert, exception: %s", e.what());
            allSucceeded = false;
        } catch (...) {
            LOG_ERROR("Failed to execute composite alert, unknown exception");
            allSucceeded = false;
        }
    }

    return allSucceeded;
}
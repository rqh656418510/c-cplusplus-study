#include "CompositeAlert.h"

#include <exception>

#include "Logger.h"

// 添加告警渠道
void CompositeAlert::addChannel(std::shared_ptr<AlertChannel> channel) {
    if (!channel) {
        return;
    }
    channels_.push_back(channel);
}

// 发送消息
bool CompositeAlert::sendMsg(const std::string& title, const std::string& content) {
    bool allSucceeded = true;

    // 遍历所有告警渠道
    for (const auto& channel : channels_) {
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
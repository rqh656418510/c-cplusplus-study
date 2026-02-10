#pragma once

#include <memory>
#include <string>

#include "AlertChannel.h"
#include "LockQueue.h"

// 告警任务
struct AlertTask {
    std::string title;                      // 告警标题
    std::string content;                    // 告警内容
    std::shared_ptr<AlertChannel> channel;  // 告警渠道
};

// 异步告警
class AsyncAlert : public AlertChannel {
public:
    // 构造函数
    AsyncAlert(std::shared_ptr<AlertChannel> channel) : channel_(channel) {
    }

    // 发送消息
    bool sendMsg(const std::string& title, const std::string& content) override {
        // 入队操作
        AlertTask task{title, content, channel_};
        queue_.Push(task);
        return true;
    }

private:
    static LockQueue<AlertTask> queue_;      // 存储告警任务的队列
    std::shared_ptr<AlertChannel> channel_;  // 告警渠道
};
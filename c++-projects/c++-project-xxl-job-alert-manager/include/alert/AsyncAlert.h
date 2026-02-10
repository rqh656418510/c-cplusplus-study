#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <thread>

#include "AlertChannel.h"
#include "LockQueue.h"

// 告警任务
struct AlertTask {
    std::string title;                      // 告警标题
    std::string content;                    // 告警内容
    std::shared_ptr<AlertChannel> channel;  // 告警渠道
};

// 异步告警（装饰器模式，异步发送，线程安全）
// 特别注意：不允许频繁创建AsyncAlert对象，否则会占用过多的系统线程资源，建议在AsyncAlert对象创建后，保留其引用或者指针
class AsyncAlert : public AlertChannel {
public:
    // 构造函数
    AsyncAlert(std::shared_ptr<AlertChannel> channel, size_t maxQueueSize = 4096);

    // 析构函数
    ~AsyncAlert();

    // 停止告警
    void stop();

    // 发送消息
    bool sendMsg(const std::string& title, const std::string& content) override;

private:
    // 处理队列里的任务
    void processQueue();

    std::shared_ptr<AlertChannel> channel_;  // 告警渠道
    std::thread thread_;                     // 告警线程
    std::atomic_bool stoped_;                // 停止告警的标记
    LockQueue<AlertTask> queue_;             // 告警队列（线程安全）
};
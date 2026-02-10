#include "AsyncAlert.h"

#include <functional>

// 构造函数
AsyncAlert::AsyncAlert(std::shared_ptr<AlertChannel> channel, size_t maxQueueSize)
    : channel_(std::move(channel)), queue_(maxQueueSize), stoped_(false) {
    // 创建处理队列的线程
    thread_ = std::thread(std::bind(&AsyncAlert::processQueue, this));
}

// 析构函数
AsyncAlert::~AsyncAlert() {
    if (!stoped_) {
        stop();
    }
}

// 停止告警
void AsyncAlert::stop() {
    // 更新告警标记
    stoped_ = true;

    // 关闭队列
    queue_.stop();

    // 等待队列处理线程结束运行
    if (thread_.joinable()) {
        thread_.join();
    }
}

// 发送消息
bool AsyncAlert::sendMsg(const std::string& title, const std::string& content) {
    // 封装任务
    AlertTask task{title, content, channel_};
    // 将任务放入队列 （阻塞直到队列有空间）
    queue_.push(std::move(task));
    return true;
}

// 处理队列里的任务
void AsyncAlert::processQueue() {
    while (!stoped_) {
        // 从队列获取任务（阻塞直到队列中有任务）
        AlertTask task = queue_.pop();
        // 检查任务是否有效
        if (task.channel && !task.title.empty() && !task.content.empty()) {
            // 发送消息
            task.channel->sendMsg(task.content, task.content);
        }
    }
}
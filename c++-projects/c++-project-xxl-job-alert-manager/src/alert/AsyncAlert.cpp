#include "AsyncAlert.h"

#include <functional>

#include "Logger.h"

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
    // 如果已经停止告警，则不再接受新数据
    if (stoped_) {
        return false;
    }

    // 封装任务
    AlertTask task{title, content, channel_};

    // 将任务放入队列 （阻塞直到队列有空间）
    queue_.push(std::move(task));
    return true;
}

// 处理队列里的任务
void AsyncAlert::processQueue() {
    while (true) {
        // 从队列获取任务（阻塞直到队列中有任务）
        AlertTask task = queue_.pop();

        // 只有告警已停止且队列里不存在有效任务时，才退出循环（结束子线程），否则继续执行直到队列为空为止
        if (stoped_ && !task.channel) {
            break;
        }

        // 检查任务是否有效
        if (!task.channel || task.title.empty() || task.content.empty()) {
            continue;
        }

        // 必须捕获异常，不能影响任何业务执行
        try {
            // 发送告警消息
            task.channel->sendMsg(task.title, task.content);
        } catch (const std::exception& e) {
            LOG_ERROR("Failed to send alert message, exception: %s", e.what());
        } catch (...) {
            LOG_ERROR("Failed to send alert message, unknown exception");
        }
    }
}
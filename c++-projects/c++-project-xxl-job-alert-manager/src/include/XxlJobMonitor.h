#pragma once

#include <atomic>
#include <cstdint>
#include <ctime>

// XXL-JOB监控器（单例对象）
class XxlJobMonitor {
public:
    // 获取单例对象
    static XxlJobMonitor& getInstance();

    // 循环监控XXL-JOB是否停止运行
    void monitorStopStatusLoop();

    // 循环监控XXL-JOB是否调度失败
    void monitorFatalStatusLoop();

    // 停止监控XXL-JOB
    void stopMonitor();

    // 删除拷贝构造函数
    XxlJobMonitor(const XxlJobMonitor&) = delete;

    // 删除赋值操作运算符
    XxlJobMonitor& operator=(const XxlJobMonitor&) = delete;

private:
    // 私有构造函数（创建eventfd）
    XxlJobMonitor();

    // 私有析构函数（关闭eventfd）
    ~XxlJobMonitor();

    // 用于唤醒poll()的eventfd文件描述符
    int eventFd_;

    // 定期扫描任务调度日志的开关
    std::atomic<bool> monitorRunning_;

    // 上次告警的任务调度失败日志的触发时间
    std::atomic<time_t> lastAlertFatalTriggerTime_;

    // 是否已发送空闲（无新的任务调度日志）告警，用于防止重复发送
    std::atomic<bool> idleAlertSended_;
};
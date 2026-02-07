#pragma once

#include <atomic>
#include <ctime>

// XXL-JOB监控器（单例对象）
class XxlJobMonitor {
public:
    // 启动监控器
    void start();

    // 关闭监控器
    void stop();

    // 获取单例对象
    static XxlJobMonitor& getInstance();

    // 删除拷贝构造函数
    XxlJobMonitor(const XxlJobMonitor&) = delete;

    // 删除赋值操作运算符
    XxlJobMonitor& operator=(const XxlJobMonitor&) = delete;

private:
    // 私有构造函数
    XxlJobMonitor();

    // 私有析构函数
    ~XxlJobMonitor();

    // 循环监控XXL-JOB是否停止运行
    void monitorStopStatusLoop();

    // 循环监控XXL-JOB是否调度失败
    void monitorFatalStatusLoop();

    // 定期扫描任务调度日志的开关
    std::atomic_bool monitorRunning_;

    // 上次告警的任务调度失败日志的触发时间
    std::atomic<time_t> lastAlertFatalTriggerTime_;

    // 是否已发送空闲（无新的任务调度日志）告警，用于防止重复发送
    std::atomic_bool idleAlertSended_;
};
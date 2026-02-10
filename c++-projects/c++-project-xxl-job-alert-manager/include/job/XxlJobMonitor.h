#pragma once

#include <atomic>
#include <condition_variable>
#include <ctime>
#include <thread>

#include "AlertManager.h"
#include "NonCopyable.h"

// XXL-JOB监控器（单例模式）
class XxlJobMonitor : NonCopyable {
public:
    // 启动监控器
    void start();

    // 关闭监控器
    void stop();

    // 获取单例对象
    static XxlJobMonitor& getInstance();

private:
    // 私有构造函数
    XxlJobMonitor();

    // 私有析构函数
    ~XxlJobMonitor();

    // 循环监控XXL-JOB是否停止运行
    void monitorStopStatusLoop();

    // 循环监控XXL-JOB是否调度失败
    void monitorFatalStatusLoop();

    // 告警管理器
    AlertManager alertManager_;

    // 定期扫描任务调度日志的开关
    std::atomic_bool monitorRunning_;

    // 上次告警的任务调度失败日志的触发时间
    std::atomic<time_t> lastAlertFatalTriggerTime_;

    // 是否已发送空闲（无新的任务调度日志）告警，用于防止重复发送
    std::atomic_bool idleAlertSended_;

    // 监控XXL-JOB的互斥锁
    std::mutex monitorMutex_;

    // 监控XXL-JOB的条件变量
    std::condition_variable monitorCv_;

    // 监控XXL-JOB是否停止运行的线程
    std::thread monitorStopStatusThread_;

    // 监控XXL-JOB是否调度失败的线程
    std::thread monitorFatalStatusThread_;
};
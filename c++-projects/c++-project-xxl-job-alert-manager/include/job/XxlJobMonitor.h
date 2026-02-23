#pragma once

#include <atomic>
#include <condition_variable>
#include <ctime>
#include <memory>
#include <thread>

#include "AlertManager.h"
#include "NonCopyable.h"
#include "XxlJobLog.h"

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

    // 处理 XXL-JOB 停止运行状态
    void processStopStatus();

    // 处理 XXL-JOB 调度失败状态
    void processFatalStatus(const XxlJobLog& fatalLog);

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

    // 连续监控到XXL-JOB停止运行的次数
    std::atomic_int consecutiveStopStatusCount_;

    // 当天已执行"处理XXL-JOB停止运行"命令的次数
    std::atomic_int timesProcessedStopStatusToday_;

    // 最后一次执行"处理XXL-JOB停止运行"命令的日期 (YYYY-MM-DD 格式)
    std::string lastProcessedStopStatusDate_;

    // 保护 lastProcessedStopStatusDate_ 的互斥锁
    std::mutex processedStopStatusDateMutex_;

    // 连续监控到XXL-JOB调度失败的次数
    std::atomic_int consecutiveFatalStatusCount_;

    // 当天已执行"处理XXL-JOB调度失败"命令的次数
    std::atomic_int timesProcessedFatalStatusToday_;

    // 最后一次执行"处理XXL-JOB调度失败"命令的日期 (YYYY-MM-DD 格式)
    std::string lastProcessedFatalStatusDate_;

    // 保护 lastProcessedFatalStatusDate_ 的互斥锁
    std::mutex processedFatalStatusDateMutex_;
};
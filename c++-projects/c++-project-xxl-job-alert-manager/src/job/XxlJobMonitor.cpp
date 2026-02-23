#include "XxlJobMonitor.h"

#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>

#include "AlertChannelFactory.h"
#include "AppConfigLoader.h"
#include "Logger.h"
#include "NetworkHelper.h"
#include "Timestamp.h"
#include "XxlJobLogDao.h"
#include "XxlJobMonitor.h"

// 私有构造函数
XxlJobMonitor::XxlJobMonitor()
    : monitorRunning_(false),
      lastAlertFatalTriggerTime_(-1),
      idleAlertSended_(false),
      consecutiveStopStatusCount_(0),
      timesProcessedStopStatusToday_(0),
      lastProcessedStopStatusDate_(""),
      consecutiveFatalStatusCount_(0),
      timesProcessedFatalStatusToday_(0),
      lastProcessedFatalStatusDate_("") {
    // 初始化告警管理器
    alertManager_.registerChannel(AlertLevel::ERROR, AlertChannelFactory::getInstance().createAsyncWxQyAlert());
    alertManager_.registerChannel(AlertLevel::CRITICAL, AlertChannelFactory::getInstance().createAsyncWxQyAlert());
}

// 私有析构函数
XxlJobMonitor::~XxlJobMonitor() {
    // 关闭监控器
    if (monitorRunning_) {
        this->stop();
    }
}

// 获取单例对象
XxlJobMonitor& XxlJobMonitor::getInstance() {
    // 静态局部变量（线程安全）
    static XxlJobMonitor instance;
    return instance;
}

// 启动监控器
void XxlJobMonitor::start() {
    // 判断监控器是否处于关闭状态
    if (!monitorRunning_) {
        // 更改运行状态
        monitorRunning_ = true;

        // 创建监控XXL-JOB是否停止运行的线程
        monitorStopStatusThread_ = std::thread(std::bind(&XxlJobMonitor::monitorStopStatusLoop, this));

        // 创建监控XXL-JOB是否调度失败的线程
        monitorFatalStatusThread_ = std::thread(std::bind(&XxlJobMonitor::monitorFatalStatusLoop, this));

        // 打印日志信息
        LOG_INFO("XXL-JOB monitor started");
    }
}

// 关闭监控器
void XxlJobMonitor::stop() {
    try {
        // 判断监控器是否已关闭
        if (!monitorRunning_) {
            return;
        }

        // 更改运行状态
        monitorRunning_ = false;

        // 通知所有监控线程结束运行
        monitorCv_.notify_all();

        // 等待监控XXL-JOB是否停止运行的线程结束运行
        if (monitorStopStatusThread_.joinable()) {
            monitorStopStatusThread_.join();
        }

        // 等待监控XXL-JOB是否调度失败的线程结束运行
        if (monitorFatalStatusThread_.joinable()) {
            monitorFatalStatusThread_.join();
        }

        // 打印日志信息
        LOG_INFO("XXL-JOB monitor stoped");
    } catch (const std::exception& e) {
        LOG_ERROR("XXL-JOB monitor stop failed, exception: %s", e.what());
    } catch (...) {
        LOG_ERROR("XXL-JOB monitor stop failed, unknown exception");
    }
}

// 循环监控XXL-JOB是否停止运行
void XxlJobMonitor::monitorStopStatusLoop() {
    // 获取全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    while (monitorRunning_) {
        try {
            XxlJobLogDao logDao;

            // 获取最新的任务调度日志记录
            XxlJobLog lastestLog = logDao.selectLastest();

            // 判断是否有任务调度日志记录
            if (lastestLog.getId() <= 0) {
                // 处理停止运行状态
                processStopStatus();
            } else {
                // 当前系统时间
                time_t t_now = time(nullptr);

                // 最新触发时间
                time_t t_lastest_trigger_time = Timestamp::toUtcTimestamp(lastestLog.getTriggerTime());
                if (t_lastest_trigger_time == static_cast<time_t>(-1)) {
                    LOG_ERROR("XXL-JOB log lastest trigger time parse failed, time: %s",
                              lastestLog.getTriggerTime().c_str());
                    continue;
                }

                // 如果在指定时间内没有任务调度日志记录，则发送告警消息
                double diff_seconds = difftime(t_now, t_lastest_trigger_time);
                if (diff_seconds >= config.alertCore.xxljobStopStatusMaxLogIdleTime) {
                    // 处理停止运行状态
                    processStopStatus();
                } else {
                    // 如果恢复了正常（有新的任务调度日志），重置空闲告警标志和连续停止运行计数器
                    idleAlertSended_.store(false);
                    consecutiveStopStatusCount_.store(0);
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR("XXL-JOB monitor occure exception: %s", e.what());
        } catch (...) {
            LOG_ERROR("XXL-JOB monitor occure unknown exception");
        }

        // 使用条件变量进行可中断的定时等待，在每次被唤醒（包括虚假唤醒）时都会检查运行标志；若检测到已停止监控则立即返回，以保证监控线程能够安全退出
        std::unique_lock<std::mutex> lock(monitorMutex_);
        if (monitorCv_.wait_for(lock, std::chrono::seconds(config.alertCore.xxljobStopStatusScanIntervalTime),
                                [this]() { return !monitorRunning_.load(); })) {
            // 当被唤醒时，说明已停止监控，退出监控线程
            break;
        }
    }
}

// 处理 XXL-JOB 停止运行状态
void XxlJobMonitor::processStopStatus() {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 仅在尚未发送过空闲告警时发送，避免重复告警
    if (!idleAlertSended_.load()) {
        char buf[1024] = {0};
        snprintf(buf, sizeof(buf), "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s\n告警环境: %s",
                 Timestamp::now().toString().c_str(), NetworkHelper::getInstance().getPublicIp().c_str(),
                 config.alertCommon.envName.c_str());
        alertManager_.alert(AlertLevel::CRITICAL, "XXL-JOB 监控告警", std::string(buf));
        idleAlertSended_.store(true);
    }

    // 处理XXL-JOB停止运行的命令
    const std::string stopStatusProcessCommand = config.alertCore.xxljobStopStatusProcessCommand;
    if (stopStatusProcessCommand.empty()) {
        LOG_WARN("XXL-JOB stop status process command is empty");
        return;
    }

    // 递增连续停止运行计数器
    int consecutive_stop_status_count = consecutiveStopStatusCount_.load() + 1;
    consecutiveStopStatusCount_.store(consecutive_stop_status_count);

    // 检查是否达到连续停止运行阈值
    if (consecutive_stop_status_count >= config.alertCore.xxljobStopStatusConsecutiveThreshold) {
        // 获取当前时间
        time_t now = time(nullptr);
        struct tm* tm_now = localtime(&now);
        char date_buf[16] = {0};
        strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", tm_now);
        std::string current_date(date_buf);

        // 检查是否跨天，如果跨天则重置计数器
        {
            std::unique_lock<std::mutex> lock(processedStopStatusDateMutex_);
            if (lastProcessedStopStatusDate_ != current_date) {
                // 跨天，重置计数器
                lastProcessedStopStatusDate_ = current_date;
                timesProcessedStopStatusToday_.store(0);
            }
        }

        // 检查当天是否还有剩余的命令执行次数
        int times_processed = timesProcessedStopStatusToday_.load();
        if (times_processed < config.alertCore.xxljobStopStatusProcessMaxTimesPerDay) {
            // 打印日志信息
            LOG_INFO("Executing xxl-job stop status process command: %s. Times processed today: %d / %d",
                     stopStatusProcessCommand.c_str(), times_processed + 1,
                     config.alertCore.xxljobStopStatusProcessMaxTimesPerDay);

            // 执行处理命令
            int ret_code = system(stopStatusProcessCommand.c_str());
            if (ret_code == 0) {
                // 命令执行成功，更新计数器
                timesProcessedStopStatusToday_.store(times_processed + 1);
                // 重置连续停止运行计数器
                consecutiveStopStatusCount_.store(0);
                LOG_INFO("XXL-JOB stop status process command executed succeeded. Command: %s",
                         stopStatusProcessCommand.c_str());
            } else {
                LOG_ERROR("XXL-JOB stop status process command executed failed, code: %d. Command: %s", ret_code,
                          stopStatusProcessCommand.c_str());
            }
        } else {
            // 当天已达到最大处理次数
            LOG_WARN(
                "Maximum times per day reached for xxl-job stop status process command. Times "
                "processed today: %d / %d. Command: %s",
                times_processed, config.alertCore.xxljobStopStatusProcessMaxTimesPerDay,
                stopStatusProcessCommand.c_str());
        }
    }
}

// 循环监控XXL-JOB是否调度失败
void XxlJobMonitor::monitorFatalStatusLoop() {
    // 获取全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    while (monitorRunning_) {
        try {
            XxlJobLogDao logDao;

            // 空闲告警优先级更高，出现后抑制调度失败告警
            if (!idleAlertSended_.load()) {
                // 获取最新的任务调度失败日志记录
                XxlJobLog lastestFatalLog = logDao.selectLastestFatal();

                // 判断是否存在任务调度失败日志记录
                if (lastestFatalLog.getId() > 0) {
                    // 处理调度失败状态
                    processFatalStatus(lastestFatalLog);
                } else {
                    // 没有调度失败日志，重置连续调度失败计数器
                    consecutiveFatalStatusCount_.store(0);
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR("XXL-JOB monitor occure exception: %s", e.what());
        } catch (...) {
            LOG_ERROR("XXL-JOB monitor occure unknown exception");
        }

        // 使用条件变量进行可中断的定时等待，在每次被唤醒（包括虚假唤醒）时都会检查运行标志；若检测到已停止监控则立即返回，以保证监控线程能够安全退出
        std::unique_lock<std::mutex> lock(monitorMutex_);
        if (monitorCv_.wait_for(lock, std::chrono::seconds(config.alertCore.xxljobFatalStatusScanIntervalTime),
                                [this]() { return !monitorRunning_.load(); })) {
            // 当被唤醒时，说明已停止监控，退出监控线程
            break;
        }
    }
}

// 处理 XXL-JOB 调度失败状态
void XxlJobMonitor::processFatalStatus(const XxlJobLog& fatalLog) {
    // 获取全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 最新失败触发时间
    time_t t_lastest_fatal_trigger_time = Timestamp::toUtcTimestamp(fatalLog.getTriggerTime());
    if (t_lastest_fatal_trigger_time == static_cast<time_t>(-1)) {
        LOG_ERROR("XXL-JOB log lastest fatal trigger time parse failed, time: %s", fatalLog.getTriggerTime().c_str());
        return;
    }

    // 如果不是已告警过，则发送告警消息
    if (t_lastest_fatal_trigger_time > lastAlertFatalTriggerTime_.load()) {
        // 发送告警消息
        alertManager_.alert(AlertLevel::ERROR, "XXL-JOB 监控告警", fatalLog.parseAlertMsg());
        // 更新已告警状态
        lastAlertFatalTriggerTime_.store(t_lastest_fatal_trigger_time);
    }

    // 处理调度失败的命令
    const std::string fatalStatusProcessCommand = config.alertCore.xxljobFatalStatusProcessCommand;
    if (fatalStatusProcessCommand.empty()) {
        LOG_WARN("XXL-JOB fatal status process command is empty");
        return;
    }

    // 递增连续调度失败计数器
    int consecutive_fatal_status_count = consecutiveFatalStatusCount_.load() + 1;
    consecutiveFatalStatusCount_.store(consecutive_fatal_status_count);

    // 检查是否达到连续调度失败阈值
    if (consecutive_fatal_status_count >= config.alertCore.xxljobFatalStatusConsecutiveThreshold) {
        // 获取当前时间
        time_t now = time(nullptr);
        struct tm* tm_now = localtime(&now);
        char date_buf[16] = {0};
        strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", tm_now);
        std::string current_date(date_buf);

        // 检查是否跨天，如果跨天则重置计数器
        {
            std::unique_lock<std::mutex> lock(processedFatalStatusDateMutex_);
            if (lastProcessedFatalStatusDate_ != current_date) {
                // 跨天，重置计数器
                lastProcessedFatalStatusDate_ = current_date;
                timesProcessedFatalStatusToday_.store(0);
            }
        }

        // 检查当天是否还有剩余的命令执行次数
        int times_processed = timesProcessedFatalStatusToday_.load();
        if (times_processed < config.alertCore.xxljobFatalStatusProcessMaxTimesPerDay) {
            // 打印日志信息
            LOG_INFO("Executing xxl-job fatal status process command: %s. Times processed today: %d / %d",
                     fatalStatusProcessCommand.c_str(), times_processed + 1,
                     config.alertCore.xxljobFatalStatusProcessMaxTimesPerDay);

            // 执行处理命令
            int ret_code = system(fatalStatusProcessCommand.c_str());
            if (ret_code == 0) {
                // 命令执行成功，更新计数器
                timesProcessedFatalStatusToday_.store(times_processed + 1);
                // 重置连续调度失败计数器
                consecutiveFatalStatusCount_.store(0);
                LOG_INFO("XXL-JOB fatal status process command executed succeeded. Command: %s",
                         fatalStatusProcessCommand.c_str());
            } else {
                LOG_ERROR("XXL-JOB fatal status process command executed failed, code: %d. Command: %s", ret_code,
                          fatalStatusProcessCommand.c_str());
            }
        } else {
            // 当天已达到最大处理次数
            LOG_WARN(
                "Maximum times per day reached for xxl-job fatal status process command. Times "
                "processed today: %d / %d. Command: %s",
                times_processed, config.alertCore.xxljobFatalStatusProcessMaxTimesPerDay,
                fatalStatusProcessCommand.c_str());
        }
    }
}
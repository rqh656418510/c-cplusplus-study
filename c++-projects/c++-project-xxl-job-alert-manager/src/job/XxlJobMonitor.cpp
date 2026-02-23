#include "XxlJobMonitor.h"

#include <chrono>
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
XxlJobMonitor::XxlJobMonitor() : monitorRunning_(false), lastAlertFatalTriggerTime_(-1), idleAlertSended_(false) {
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
                // 仅在尚未发送过空闲告警时发送，避免重复告警
                if (!idleAlertSended_.load()) {
                    char buf[1024] = {0};
                    snprintf(buf, sizeof(buf), "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s\n告警环境: %s",
                             Timestamp::now().toString().c_str(), NetworkHelper::getInstance().getPublicIp().c_str(),
                             config.alert.environmentName.c_str());
                    alertManager_.alert(AlertLevel::CRITICAL, "XXL-JOB 监控告警", std::string(buf));
                    idleAlertSended_.store(true);
                }
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
                if (diff_seconds >= config.alert.xxljobLogMaxIdleTimeForStop) {
                    // 仅在尚未发送过空闲告警时发送，避免重复告警
                    if (!idleAlertSended_.load()) {
                        char buf[1024] = {0};
                        snprintf(
                            buf, sizeof(buf), "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s\n告警环境: %s",
                            Timestamp::now().toString().c_str(), NetworkHelper::getInstance().getPublicIp().c_str(),
                            config.alert.environmentName.c_str());
                        alertManager_.alert(AlertLevel::CRITICAL, "XXL-JOB 监控告警", std::string(buf));
                        idleAlertSended_.store(true);
                    }
                } else {
                    // 如果恢复了正常（有新的任务调度日志），重置空闲告警标志
                    idleAlertSended_.store(false);
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR("XXL-JOB monitor occure exception: %s", e.what());
        } catch (...) {
            LOG_ERROR("XXL-JOB monitor occure unknown exception");
        }

        // 使用条件变量进行可中断的定时等待，在每次被唤醒（包括虚假唤醒）时都会检查运行标志；若检测到已停止监控则立即返回，以保证监控线程能够安全退出
        std::unique_lock<std::mutex> lock(monitorMutex_);
        if (monitorCv_.wait_for(lock, std::chrono::seconds(config.alert.xxljobStopStatusScanIntervalTime),
                                [this]() { return !monitorRunning_.load(); })) {
            // 当被唤醒时，说明已停止监控，退出监控线程
            break;
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

            // 空闲告警优先级更高，出现后抑制失败告警
            if (!idleAlertSended_.load()) {
                // 获取最新的任务调度失败日志记录
                XxlJobLog lastestFatalLog = logDao.selectLastestFatal();

                // 判断是否存在任务调度失败日志记录
                if (lastestFatalLog.getId() > 0) {
                    // 最新失败触发时间
                    time_t t_lastest_fatal_trigger_time = Timestamp::toUtcTimestamp(lastestFatalLog.getTriggerTime());
                    if (t_lastest_fatal_trigger_time == static_cast<time_t>(-1)) {
                        LOG_ERROR("XXL-JOB log lastest fatal trigger time parse failed, time: %s",
                                  lastestFatalLog.getTriggerTime().c_str());
                        continue;
                    }

                    // 如果不是已告警过，则发送告警消息
                    if (t_lastest_fatal_trigger_time > lastAlertFatalTriggerTime_.load()) {
                        // 发送告警消息
                        alertManager_.alert(AlertLevel::ERROR, "XXL-JOB 监控告警", lastestFatalLog.parseAlertMsg());
                        // 更新已告警状态
                        lastAlertFatalTriggerTime_.store(t_lastest_fatal_trigger_time);
                    }
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR("XXL-JOB monitor occure exception: %s", e.what());
        } catch (...) {
            LOG_ERROR("XXL-JOB monitor occure unknown exception");
        }

        // 使用条件变量进行可中断的定时等待，在每次被唤醒（包括虚假唤醒）时都会检查运行标志；若检测到已停止监控则立即返回，以保证监控线程能够安全退出
        std::unique_lock<std::mutex> lock(monitorMutex_);
        if (monitorCv_.wait_for(lock, std::chrono::seconds(config.alert.xxljobFatalStatusScanIntervalTime),
                                [this]() { return !monitorRunning_.load(); })) {
            // 当被唤醒时，说明已停止监控，退出监控线程
            break;
        }
    }
}
#include "XxlJobMonitor.h"

#include <chrono>
#include <iostream>

#include "Alert.h"
#include "AppConfigLoader.h"
#include "Logger.h"
#include "NetworkUtil.h"
#include "Timestamp.h"
#include "XxlJobLogDao.h"
#include "XxlJobMonitor.h"

// 私有构造函数
XxlJobMonitor::XxlJobMonitor() : monitorRunning_(true), lastAlertFatalTriggerTime_(-1), idleAlertSended_(false) {
    LOG_DEBUG("xxl-job monitor initialized");
}

// 私有析构函数
XxlJobMonitor::~XxlJobMonitor() {
    LOG_DEBUG("xxl-job monitor destroyed");
}

// 获取单例对象
XxlJobMonitor& XxlJobMonitor::getInstance() {
    // 静态局部变量（线程安全）
    static XxlJobMonitor instance;
    return instance;
}

// 循环监控XXL-JOB是否停止运行
void XxlJobMonitor::monitorStopStatusLoop() {
    // 全局配置信息
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
                    sprintf(buf, "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s\n告警环境名称: %s",
                            Timestamp::now().toString().c_str(), NetworkUtil::getInstance().getPublicIp().c_str(),
                            config.alert.xxljobEnvironmentName.c_str());
                    Alert::sendWxQyTextMsg(config.wechatAccount.agentId, config.wechatAccount.toUser, std::string(buf));
                    idleAlertSended_.store(true);
                }
            } else {
                // 当前系统时间
                time_t t_now = time(nullptr);

                // 最新触发时间
                time_t t_lastest_trigger_time = Timestamp::toUtcTimestamp(lastestLog.getTriggerTime());
                if (t_lastest_trigger_time == static_cast<time_t>(-1)) {
                    LOG_ERROR("xxl-job log lastest trigger time parse failed, time: %s",
                              lastestLog.getTriggerTime().c_str());
                    continue;
                }

                // 如果在指定时间内没有任务调度日志记录，则发送告警消息
                double diff_seconds = difftime(t_now, t_lastest_trigger_time);
                if (diff_seconds >= config.alert.xxljobLogMaxIdleSecondsForStop) {
                    // 仅在尚未发送过空闲告警时发送，避免重复告警
                    if (!idleAlertSended_.load()) {
                        char buf[1024] = {0};
                        sprintf(buf, "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s\n告警环境名称: %s",
                                Timestamp::now().toString().c_str(), NetworkUtil::getInstance().getPublicIp().c_str(),
                                config.alert.xxljobEnvironmentName.c_str());
                        Alert::sendWxQyTextMsg(config.wechatAccount.agentId, config.wechatAccount.toUser,
                                               std::string(buf));
                        idleAlertSended_.store(true);
                    }
                } else {
                    // 如果恢复了正常（有新的任务调度日志），重置空闲告警标志
                    idleAlertSended_.store(false);
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR("xxl-job monitor occure exception: %s", e.what());
        } catch (...) {
            LOG_ERROR("xxl-job monitor occure unknown exception");
        }

        // 模拟定时扫描
        std::this_thread::sleep_for(std::chrono::seconds(config.alert.xxljobStopStatusScanIntervalSeconds));
    }
}

// 循环监控XXL-JOB是否调度失败
void XxlJobMonitor::monitorFatalStatusLoop() {
    // 全局配置信息
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
                        LOG_ERROR("xxl-job log lastest fatal trigger time parse failed, time: %s",
                                  lastestFatalLog.getTriggerTime().c_str());
                        continue;
                    }

                    // 如果不是已告警过，则发送告警消息
                    if (t_lastest_fatal_trigger_time > lastAlertFatalTriggerTime_.load()) {
                        // 发送告警消息
                        Alert::sendWxQyTextMsg(config.wechatAccount.agentId, config.wechatAccount.toUser,
                                               lastestFatalLog);
                        // 更新已告警状态
                        lastAlertFatalTriggerTime_.store(t_lastest_fatal_trigger_time);
                    }
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR("xxl-job monitor occure exception: %s", e.what());
        } catch (...) {
            LOG_ERROR("xxl-job monitor occure unknown exception");
        }

        // 模拟定时扫描
        std::this_thread::sleep_for(std::chrono::seconds(config.alert.xxljobFatalStatusScanIntervalSeconds));
    }
}

// 停止监控XXL-JOB
void XxlJobMonitor::stopMonitor() {
    // 更改监控器的运行状态
    monitorRunning_ = false;
}
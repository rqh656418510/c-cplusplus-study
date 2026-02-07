#include "XxlJobMonitor.h"

#include <errno.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <chrono>
#include <ctime>
#include <iostream>

#include "Alert.h"
#include "AppConfigLoader.h"
#include "Logger.h"
#include "NetworkUtil.h"
#include "Timestamp.h"
#include "XxlJobLogDao.h"
#include "XxlJobMonitor.h"

// 获取单例对象
XxlJobMonitor& XxlJobMonitor::getInstance() {
    // 静态局部变量（线程安全）
    static XxlJobMonitor instance;
    return instance;
}

// 私有构造函数（创建eventfd）
XxlJobMonitor::XxlJobMonitor()
    : eventFd_(-1), monitorRunning_(true), lastAlertFatalTriggerTime_(-1), idleAlertSended_(false) {
    // 创建eventfd，用于唤醒多个监控线程，不使用 EFD_NONBLOCK
    eventFd_ = ::eventfd(0, EFD_CLOEXEC | EFD_SEMAPHORE);
    if (eventFd_ < 0) {
        LOG_FATAL("failed to create eventfd for xxl-job monitor");
    }
    LOG_INFO("xxl-job monitor initialized");
}

// 私有析构函数（关闭eventfd）
XxlJobMonitor::~XxlJobMonitor() {
    if (eventFd_ >= 0) {
        close(eventFd_);
        eventFd_ = -1;
    }
    LOG_INFO("xxl-job monitor cleaned up");
}

// 循环监控XXL-JOB是否停止运行
void XxlJobMonitor::monitorStopStatusLoop() {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    while (monitorRunning_.load()) {
        try {
            XxlJobLogDao logDao;

            // 获取最新的任务调度日志记录
            XxlJobLog lastestLog = logDao.selectLastest();

            // 判断是否有任务调度日志记录
            if (lastestLog.getId() <= 0) {
                // 仅在尚未发送过空闲告警时发送，避免重复告警
                if (!idleAlertSended_.load()) {
                    char buf[1024] = {0};
                    sprintf(buf, "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s",
                            Timestamp::now().toString().c_str(), NetworkUtil::getInstance().getPublicIp().c_str());
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
                        sprintf(buf, "【XXL-JOB 已停止运行】\n告警时间: %s\n告警 IP 地址: %s",
                                Timestamp::now().toString().c_str(), NetworkUtil::getInstance().getPublicIp().c_str());
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

        // 使用poll()等待超时或eventfd事件（可被信号唤醒）
        struct pollfd pfd;
        pfd.fd = eventFd_;
        pfd.events = POLLIN;
        int timeout_ms = config.alert.xxljobStopStatusScanIntervalSeconds * 1000;  // 转换为毫秒
        int poll_ret = poll(&pfd, 1, timeout_ms);                                  // 阻塞等待

        // 当前线程接收到事件，被唤醒
        if (poll_ret > 0) {
            // 先检查eventfd是否有效
            if (pfd.revents & POLLNVAL) {
                LOG_WARN("xxl-job monitor poll: eventfd invalid (POLLNVAL), exiting loop");
                // 退出循环，避免 Read EBADF
                break;
            }
            // 如果poll()被eventfd唤醒，则消费事件
            if (pfd.revents & POLLIN) {
                uint64_t buf = 0;
                ssize_t n = read(eventFd_, &buf, sizeof(buf));
                if (n != sizeof(buf)) {
                    if (n < 0) {
                        if (errno == EINTR) {
                            LOG_INFO("xxl-job monitor eventfd read interrupted by signal");
                        } else {
                            LOG_WARN("xxl-job monitor eventfd read failed, errno=%d (%s)", errno, strerror(errno));
                        }
                    } else {
                        LOG_WARN("xxl-job monitor eventfd partial read, expected=%zu, got=%zd", sizeof(buf), n);
                    }
                }
            }
        } else if (poll_ret < 0) {
            if (errno != EINTR) {
                LOG_ERROR("poll failed during xxl-job monitor wait: %d", errno);
            }
        }
    }
}

// 循环监控XXL-JOB是否调度失败
void XxlJobMonitor::monitorFatalStatusLoop() {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    while (monitorRunning_.load()) {
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

        // 使用poll()等待超时或eventfd事件（可被信号唤醒）
        struct pollfd pfd;
        pfd.fd = eventFd_;
        pfd.events = POLLIN;
        int timeout_ms = config.alert.xxljobFatalStatusScanIntervalSeconds * 1000;  // 转换为毫秒
        int poll_ret = poll(&pfd, 1, timeout_ms);                                   // 阻塞等待

        // 当前线程接收到事件，被唤醒
        if (poll_ret > 0) {
            // 先检查eventfd是否有效
            if (pfd.revents & POLLNVAL) {
                LOG_WARN("xxl-job monitor poll: eventfd invalid (POLLNVAL), exiting loop");
                // 退出循环，避免 Read EBADF
                break;
            }
            // 如果poll()被eventfd唤醒，则消费事件
            if (pfd.revents & POLLIN) {
                uint64_t buf = 0;
                ssize_t n = read(eventFd_, &buf, sizeof(buf));
                if (n != sizeof(buf)) {
                    if (n < 0) {
                        if (errno == EINTR) {
                            LOG_INFO("xxl-job monitor eventfd read interrupted by signal");
                        } else {
                            LOG_WARN("xxl-job monitor eventfd read failed, errno=%d (%s)", errno, strerror(errno));
                        }
                    } else {
                        LOG_WARN("xxl-job monitor eventfd partial read, expected=%zu, got=%zd", sizeof(buf), n);
                    }
                }
            }
        } else if (poll_ret < 0) {
            if (errno != EINTR) {
                LOG_ERROR("poll failed during xxl-job monitor wait: %d", errno);
            }
        }
    }
}

// 停止监控XXL-JOB
void XxlJobMonitor::stopMonitor() {
    // 更改监控器的运行状态
    monitorRunning_.store(false);

    // 写入eventfd以唤醒正在poll()中等待的线程
    if (eventFd_ >= 0) {
        // 写入一个极大值用于广播唤醒多个等待线程（或者直接写等待的线程数）
        uint64_t wakeup_count = UINT32_MAX / 2;
        ssize_t n = write(eventFd_, &wakeup_count, sizeof(wakeup_count));
        if (n != sizeof(wakeup_count)) {
            if (n < 0) {
                LOG_WARN("xxl-job monitor eventfd write failed, errno=%d", errno);
            } else {
                LOG_WARN("xxl-job monitor eventfd partial write, size=%zd", n);
            }
        }
    }
}
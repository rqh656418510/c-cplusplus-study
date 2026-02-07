#include "WxQyTokenRefresher.h"

#include <errno.h>
#include <poll.h>
#include <string.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "WxQyApi.h"

// 获取单例对象
WxQyTokenRefresher& WxQyTokenRefresher::getInstance() {
    // 静态局部变量（线程安全）
    static WxQyTokenRefresher instance;
    return instance;
}

// 私有构造函数（创建eventfd）
WxQyTokenRefresher::WxQyTokenRefresher() : eventFd_(-1), accessToken_(""), refreshRunning_(true) {
    // 创建eventfd，用于唤醒刷新线程，不使用 EFD_NONBLOCK
    eventFd_ = ::eventfd(0, EFD_CLOEXEC);
    if (eventFd_ < 0) {
        LOG_FATAL("failed to create eventfd for wx-qy token refresher");
    }
    LOG_INFO("wx-qy token refresher initialized");
}

// 私有析构函数（关闭eventfd）
WxQyTokenRefresher::~WxQyTokenRefresher() {
    if (eventFd_ >= 0) {
        close(eventFd_);
        eventFd_ = -1;
    }
    LOG_INFO("wx-qy token refresher cleaned up");
}

// 循环刷新本地的AccessToken
void WxQyTokenRefresher::refreshLocalTokenLoop() {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    while (refreshRunning_.load()) {
        // 刷新的时间间隔（秒）
        int wait_seconds = config.alert.wechatRefreshTokenIntervalSeconds;

        try {
            // 获取 AccessToken
            std::string access_token = WxQyApi::getAccessToken();
            if (!access_token.empty()) {
                // 获取成功后，设置本地的AccessToken
                {
                    std::lock_guard<std::mutex> lock(accessTokenMutex_);
                    accessToken_ = access_token;
                }
            } else {
                // 获取失败后，使用较短的等待时间后重试
                wait_seconds = config.alert.wechatRetryRefreshIntervalSeconds;
                LOG_WARN("failed to get wx-qy access token, will retry after %ds", wait_seconds);
            }
        } catch (const std::exception& e) {
            // 获取失败后，使用较短的等待时间后重试
            wait_seconds = config.alert.wechatRetryRefreshIntervalSeconds;
            LOG_ERROR("wx-qy token refresher occure exception: %s, will retry refresh after %ds", e.what(),
                      wait_seconds);
        } catch (...) {
            // 获取失败后，使用较短的等待时间后重试
            wait_seconds = config.alert.wechatRetryRefreshIntervalSeconds;
            LOG_ERROR("wx-qy token refresher occure unknown exception, will retry refresh after %ds", wait_seconds);
        }

        // 使用poll()等待超时或eventfd事件（可被信号唤醒）
        struct pollfd pfd;
        pfd.fd = eventFd_;
        pfd.events = POLLIN;
        int timeout_ms = wait_seconds * 1000;      // 转换为毫秒
        int poll_ret = poll(&pfd, 1, timeout_ms);  // 阻塞等待

        // 当前线程接收到事件，被唤醒
        if (poll_ret > 0) {
            // 先检查eventfd是否有效
            if (pfd.revents & POLLNVAL) {
                LOG_WARN("wx-qy token refresher poll: eventfd invalid (POLLNVAL), exiting loop");
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
                            LOG_INFO("wx-qy token refresher eventfd read interrupted by signal");
                        } else {
                            LOG_WARN("wx-qy token refresher eventfd read failed, errno=%d (%s)", errno,
                                     strerror(errno));
                        }
                    } else {
                        LOG_WARN("wx-qy token refresher eventfd partial read, expected=%zu, got=%zd", sizeof(buf), n);
                    }
                }
            }
        } else if (poll_ret < 0) {
            if (errno != EINTR) {
                LOG_ERROR("poll failed during wx-qy token refresher wait: %d", errno);
            }
        }
    }
}

// 停止刷新本地的AccessToken
void WxQyTokenRefresher::stopRefreshLocalToken() {
    // 更改运行状态
    refreshRunning_.store(false);

    // 写入eventfd以唤醒正在poll()中等待的线程
    if (eventFd_ >= 0) {
        uint64_t buf = 1;
        ssize_t n = write(eventFd_, &buf, sizeof(buf));
        if (n != sizeof(buf)) {
            if (n < 0) {
                LOG_WARN("wx-qy token refresher eventfd write failed, errno=%d", errno);
            } else {
                LOG_WARN("wx-qy token refresher eventfd partial write, size=%zd", n);
            }
        }
    }
}

// 获取本地的AccessToken
std::string WxQyTokenRefresher::getLocalAccessToken() {
    // 获取本地的AccessToken（只短暂持有锁）
    {
        std::lock_guard<std::mutex> lock(accessTokenMutex_);
        if (!accessToken_.empty()) {
            return accessToken_;
        }
    }

    // 当本地的AccessToken为空，则获取最新的AccessToken（网络耗时操作）
    std::string access_token = WxQyApi::getAccessToken();

    // 成功获取最新的AccessToken时，加锁后再更新本地的AccessToken
    if (!access_token.empty()) {
        std::lock_guard<std::mutex> lock(accessTokenMutex_);
        accessToken_ = access_token;
        return access_token;
    }

    // 获取最新的AccessToken失败时，加锁后返回本地的AccessToken（可能为空）
    std::lock_guard<std::mutex> lock(accessTokenMutex_);
    return accessToken_;
}
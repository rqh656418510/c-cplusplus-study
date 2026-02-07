#pragma once

#include <atomic>
#include <mutex>
#include <string>

// 企业微信AccessToken刷新器（单例对象）
class WxQyTokenRefresher {
public:
    // 获取单例对象
    static WxQyTokenRefresher& getInstance();

    // 循环刷新本地的AccessToken
    void refreshLocalTokenLoop();

    // 停止刷新本地的AccessToken
    void stopRefreshLocalToken();

    // 获取本地的AccessToken
    std::string getLocalAccessToken();

    // 删除拷贝构造函数
    WxQyTokenRefresher(const WxQyTokenRefresher&) = delete;

    // 删除赋值操作运算符
    WxQyTokenRefresher& operator=(const WxQyTokenRefresher&) = delete;

private:
    // 私有构造函数
    WxQyTokenRefresher();

    // 私有析构函数
    ~WxQyTokenRefresher();

    // 企业微信AccessToken
    std::string accessToken_;

    // 企业微信AccessToken的互斥锁
    std::mutex accessTokenMutex_;

    // 企业微信AccessToken刷新的开关
    std::atomic_bool refreshRunning_;
};
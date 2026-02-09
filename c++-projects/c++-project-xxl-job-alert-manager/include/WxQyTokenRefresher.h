#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

// 企业微信AccessToken刷新器（单例对象）
class WxQyTokenRefresher {
public:
    // 启动刷新器
    void start();

    // 关闭刷新器
    void stop();

    // 获取本地的AccessToken
    std::string getLocalAccessToken();

    // 获取单例对象
    static WxQyTokenRefresher& getInstance();

    // 删除拷贝构造函数
    WxQyTokenRefresher(const WxQyTokenRefresher&) = delete;

    // 删除赋值操作运算符
    WxQyTokenRefresher& operator=(const WxQyTokenRefresher&) = delete;

private:
    // 私有构造函数
    WxQyTokenRefresher();

    // 私有析构函数
    ~WxQyTokenRefresher();

    // 循环刷新本地的AccessToken
    void refreshLocalTokenLoop();

    // 企业微信AccessToken
    std::string accessToken_;

    // 企业微信AccessToken的互斥锁
    std::mutex accessTokenMutex_;

    // 企业微信AccessToken刷新的线程
    std::thread refreshThread_;

    // 企业微信AccessToken刷新的条件变量
    std::condition_variable refreshCv_;

    // 企业微信AccessToken刷新的开关
    std::atomic_bool refreshRunning_;
};
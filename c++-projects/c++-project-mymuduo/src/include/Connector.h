#pragma once

#include <atomic>
#include <functional>
#include <memory>

#include "InetAddress.h"
#include "noncopyable.h"

// 类前置声明
class Channel;
class EventLoop;

// TCP 连接器类
class Connector : noncopyable, public std::enable_shared_from_this<Connector> {
public:
    // 有新连接到来时的回调操作类型定义
    using NewConnectionCallback = std::function<void(int sockfd)>;

    // 构造函数
    Connector(EventLoop* loop, const InetAddress& serverAddr);

    // 析构函数
    ~Connector();

    // 设置有新连接到来时的回调操作类型定义
    void setNewConnectionCallback(const NewConnectionCallback& cb);

    // 启动连接器
    void start();

    // 重启连接器（必须在 EventLoop 所处的线程上执行）
    void restart();

    // 停止连接器
    void stop();

    // 获取服务器地址
    const InetAddress& serverAddress() const;

private:
    // 连接器的状态
    enum States { kDisconnected, kConnecting, kConnected };
    // 最大重试延迟时间（毫秒）
    static const int kMaxRetryDelayMs = 30 * 1000;
    // 初始重试延迟时间（毫秒）
    static const int kInitRetryDelayMs = 500;

    // 设置连接状态
    void setState(States s);

    // 在 EventLoop 所处的线程上启动连接器
    void startInLoop();

    // 在 EventLoop 所处的线程上停止连接器
    void stopInLoop();

    // 发起连接操作
    void connect();

    // 处理正在连接的 Socket
    void connecting(int sockfd);

    // 处理写事件
    void handleWrite();

    // 处理错误事件
    void handleError();

    // 重试连接
    void retry(int sockfd);

    // 移除并重置 Channel
    int removeAndResetChannel();

    // 重置 Channel
    void resetChannel();

    EventLoop* loop_;                              // 连接器所在的事件循环
    InetAddress serverAddr_;                       // 服务器地址
    std::atomic_int connect_;                      // 标记是否需要连接
    States state_;                                 // 连接状态
    std::unique_ptr<Channel> channel_;             // 连接器对应的 Channel
    NewConnectionCallback newConnectionCallback_;  // 新连接到来时的回调操作
    int retryDelayMs_;                             // 重试延迟时间（毫秒）
};
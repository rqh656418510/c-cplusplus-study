#ifndef REDIS_H
#define REDIS_H

#include <hiredis/hiredis.h>

#include <functional>
#include <iostream>
#include <thread>

using namespace std;

// Redis 操作类
class Redis {
public:
    // 构造函数
    Redis();

    // 析构函数
    ~Redis();

    // 连接redis服务器
    bool connect();

    // 向redis指定的通道subscribe消息
    bool subscribe(int channel);

    // 向redis指定的通道unsubscribe消息
    bool unsubscribe(int channel);

    // 在独立线程中异步接收订阅通道中的消息
    void observer_channel_message();

    // 向redis指定的通道publish消息
    bool publish(int channel, string message);

    // 初始化向业务层上报通道消息的回调对象
    void init_notify_handler(function<void(int, string)> fn);

private:
    // hiredis同步上下文对象（即redis客户端），负责publish消息
    redisContext *_publish_context;

    // hiredis同步上下文对象（即redis客户端），负责subscribe消息
    redisContext *_subcribe_context;

    // 回调操作，收到订阅的消息，给service层上报
    function<void(int, string)> _notify_message_handler;
};

#endif
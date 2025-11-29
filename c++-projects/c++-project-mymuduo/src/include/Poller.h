#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "Timestamp.h"
#include "noncopyable.h"

// 类前置声明
class Channel;
class EventLoop;

/**
 * I/O 多路复用器抽象类
 */
class Poller : noncopyable {
public:
    // Channel 列表类型定义
    using ChannelList = std::vector<Channel*>;

    // 构造函数
    Poller(EventLoop* loop);

    // 虚析构函数
    virtual ~Poller();

    /********** 统一定义所有 I/O 多路复用器的接口 **********/

    // 监听就绪事件，返回活跃的 Channel 列表
    virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;

    // 更新 Channel
    virtual void updateChannel(Channel* channel) = 0;

    // 移除 Channel
    virtual void removeChannel(Channel* channel) = 0;

    // 判断 Poller 中是否存在某个 Channel
    virtual bool hasChannel(Channel* channel) const;

    /********** 创建 I/O 多路复用器实例 **********/

    static Poller* newDefaultPoller(EventLoop* loop);

protected:
    // Channel 集合的类型定义，key 是 fd，而 value 是 fd 所属的 Channel
    using ChannelMap = std::unordered_map<int, Channel*>;

    ChannelMap channels_;  // 保存所有的 Channel

private:
    EventLoop* owerLoop_;  // Poller 所属的事件循环
};
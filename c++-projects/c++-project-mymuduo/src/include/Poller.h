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
 * 基于 epoll 实现的 I/O 多路复用器
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

    virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;

    virtual void updateChannel(Channel* channel) = 0;

    virtual void removeChannel(Channel* channel) = 0;

    virtual bool hasChannel(Channel* channel) const;

    /********** 创建 I/O 多路复用器实例 **********/

    static Poller* newDefaultPoller(EventLoop* loop);

protected:
    // ChannelMap 类型定义，key 是 fd，而 value 是 fd 所属的 Channel
    using ChannelMap = std::unordered_map<int, Channel*>;

    ChannelMap channels_;  // 保存所有的 Channel

private:
    EventLoop* owerLoop_;  // Poller 所属的事件循环
};
#pragma once

#include <sys/epoll.h>

#include <vector>

#include "EventLoop.h"
#include "Poller.h"
#include "Timestamp.h"

// 基于 Epoll 的 I/O 多路复用器
class EPollPoller : public Poller {
public:
    EPollPoller(EventLoop* loop);

    ~EPollPoller() override;

    // 监听就绪事件，返回活跃的 Channels 列表
    Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;

    // 更新 Channel
    void updateChannel(Channel* channel) override;

    // 移除 Channel
    void removeChannel(Channel* channel) override;

private:
    // epoll 事件列表的初始大小
    static const int kInitEventListSize = 16;

    // 填充活跃的 Channels 列表
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    // 更新 Channel
    void update(int operation, Channel* channel);

    // epoll 事件列表类型定义
    using EventList = std::vector<::epoll_event>;

    int epollfd_;       // epoll 文件描述符
    EventList events_;  // epoll 事件列表
};
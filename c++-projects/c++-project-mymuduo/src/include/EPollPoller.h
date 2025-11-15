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
    // Epoll 事件列表的初始大小
    static const int kInitEventListSize = 16;

    // 填充活跃的 Channels 列表
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    /**
     * 更新 Channel，其中 operation 参数的值有以下几种
     * EPOLL_CTL_ADD   添加 fd 到 Epoll 实例
     * EPOLL_CTL_DEL   从 Epoll 实例中删除 fd
     * EPOLL_CTL_MOD   修改 fd 的监听事件
     */
    void update(int operation, Channel* channel);

    // Epoll 事件列表类型定义
    using EventList = std::vector<::epoll_event>;

    int epollfd_;       // Epoll 文件描述符
    EventList events_;  // Epoll 事件列表
};
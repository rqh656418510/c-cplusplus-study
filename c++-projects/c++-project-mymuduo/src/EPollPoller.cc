#include "EPollPoller.h"

#include <cstring>

#include "Channel.h"
#include "Logger.h"
#include "error.h"
#include "unistd.h"

// Channel 在 Epoll 中的状态
const int kNew = -1;     // 新创建的 Channel
const int kAdded = 1;    // 已经添加到 Epoll 中的 Channel
const int kDeleted = 2;  // 已经从 Epoll 中删除的 Channel

EPollPoller::EPollPoller(EventLoop* loop)
    : Poller(loop), epollfd_(::epoll_create1(EPOLL_CLOEXEC)), events_(kInitEventListSize) {
    if (epollfd_ < 0) {
        LOG_FATAL("EPollPoller::EPollPoller - epoll_create1 error:%d \n", errno);
    }
}

EPollPoller::~EPollPoller() {
    ::close(epollfd_);
}

Timestamp EPollPoller::poll(int timeoutMs, ChannelList* activeChannels) {
    return Timestamp::now();
}

void EPollPoller::updateChannel(Channel* channel) {
    const int index = channel->index();
    LOG_INFO("fd=%d events=%d index=%d \n", channel->fd(), channel->events(), index);

    if (index == kNew || index == kDeleted) {
        if (index == kNew) {
            // 获取 socket 的 fd
            int fd = channel->fd();
            // 将 Channel 添加到 channels_ 中
            channels_[fd] = channel;
        }
        // 更新 Channel 在 Epoll 中的状态
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    } else {
        // 获取 socket 的 fd
        int fd = channel->fd();
        // 如果当前没有任何事件感兴趣，则将 Channel 从 Epoll 中删除
        if (channel->isNoneEvent()) {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }
        // 否则，更新 Channel 的状态
        else {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EPollPoller::removeChannel(Channel* channel) {
    // 获取 socket 的 fd
    int fd = channel->fd();

    // 从 channels_ 中将 fd 对应的 Channel 移除掉
    channels_.erase(fd);

    // 获取 Channel 在 Epoll 中的状态
    int index = channel->index();
    if (index == kAdded) {
        // 更新 Channel
        update(EPOLL_CTL_DEL, channel);
    }

    // 更新 Channel 在 Epoll 中的状态
    channel->set_index(kNew);
}

void EPollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const {
}

void EPollPoller::update(int operation, Channel* channel) {
    // 获取 socket 的 fd
    int fd = channel->fd();

    // Epoll 事件
    ::epoll_event event;
    memset(&event, 0, sizeof event);
    event.data.ptr = channel;
    event.data.fd = fd;

    // 设置 fd 相应的 Epoll 事件
    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0) {
        if (operation == EPOLL_CTL_DEL) {
            LOG_ERROR("epoll_ctl del error:%d \n", errno);
        } else {
            LOG_FATAL("epoll_ctl add or mod error:%d \n", errno);
        }
    }
}
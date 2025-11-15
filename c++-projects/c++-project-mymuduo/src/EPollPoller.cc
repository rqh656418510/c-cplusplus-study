#include "EPollPoller.h"

#include "Logger.h"
#include "error.h"
#include "unistd.h"

const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

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
}

void EPollPoller::removeChannel(Channel* channel) {
}
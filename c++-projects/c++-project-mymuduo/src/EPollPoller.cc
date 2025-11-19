#include "EPollPoller.h"

#include <strings.h>

#include "Channel.h"
#include "Logger.h"
#include "error.h"
#include "unistd.h"

// 定义 Channel 在 Epoll 中的状态
const int kNew = -1;     // 新创建的 Channel
const int kAdded = 1;    // 已经添加到 Epoll 中的 Channel
const int kDeleted = 2;  // 已经从 Epoll 中移除的 Channel

// 构造函数
EPollPoller::EPollPoller(EventLoop* loop)
    : Poller(loop), epollfd_(::epoll_create1(EPOLL_CLOEXEC)), events_(kInitEventListSize) {
    // 如果创建 Epoll 文件描述符失败，则记录日志并终止程序
    if (epollfd_ < 0) {
        LOG_FATAL("func=%s => epoll_create1() error:%d \n", __FUNCTION__, errno);
    }
}

// 析构函数
EPollPoller::~EPollPoller() {
    // 关闭 Epoll 文件描述符
    ::close(epollfd_);
}

// 监听就绪事件，返回活跃的 Channel 列表
Timestamp EPollPoller::poll(int timeoutMs, ChannelList* activeChannels) {
    // 打印日志信息
    LOG_DEBUG("func=%s => fd total count:%lu \n", __FUNCTION__, channels_.size());

    // 监听就绪事件，会阻塞当前线程，超时等待返回 0（表示本次等待期间没有任何就绪事件发生）
    int numEvents = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeoutMs);

    // 保存错误码
    int savedErrno = errno;

    // 获取当前时间戳
    Timestamp now(Timestamp::now());

    // 如果有就绪事件发生
    if (numEvents > 0) {
        // 打印日志信息
        LOG_DEBUG("func=%s => epoll happend %d events \n", __FUNCTION__, numEvents);

        // 填充活跃的 Channel 列表
        fillActiveChannels(numEvents, activeChannels);

        // 如果本次监听返回的就绪事件数量等于当前 Epoll 事件列表的大小，则将 Epoll 事件列表的容量扩大一倍
        if (numEvents == events_.size()) {
            events_.resize(events_.size() * 2);
        }
    }
    // 如果监听超时没有任何就绪事件发生
    else if (numEvents == 0) {
        LOG_DEBUG("func=%s => epoll wait timeout, nothing happened \n", __FUNCTION__);
    }
    // 如果监听出错
    else {
        // 只有在错误码不是 EINTR（系统调用被中断）时，才记录错误日志
        if (savedErrno != EINTR) {
            // 恢复错误码
            errno = savedErrno;
            // 打印日志信息
            LOG_ERROR("func=%s => epoll wait error \n", __FUNCTION__);
        }
    }

    return now;
}

// 填充活跃的 Channel 列表
void EPollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const {
    // 遍历所有就绪的事件
    for (int i = 0; i < numEvents; ++i) {
        // 获取就绪的 Channel
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        // 设置 Channel 上发生的具体事件
        channel->set_revents(events_[i].events);
        // 将就绪的 Channel 添加到活跃的 Channel 列表中
        activeChannels->push_back(channel);
    }
}

// 更新 Channel
void EPollPoller::updateChannel(Channel* channel) {
    // 获取 Channel 在 Epoll 中的状态
    const int index = channel->index();

    // 打印日志信息
    LOG_INFO("func=%s => fd=%d events=%d index=%d \n", __FUNCTION__, channel->fd(), channel->events(), index);

    if (index == kNew || index == kDeleted) {
        if (index == kNew) {
            // 获取 socket 的 fd
            int fd = channel->fd();
            // 将 Channel 添加到 Channel 集合中
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

// 更新 Channel
void EPollPoller::update(int operation, Channel* channel) {
    // 获取 socket 的 fd
    int fd = channel->fd();

    // Epoll 事件
    ::epoll_event event;
    bzero(&event, sizeof event);
    event.data.ptr = channel;
    event.data.fd = fd;

    // 设置 fd 相应的 Epoll 事件
    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0) {
        if (operation == EPOLL_CTL_DEL) {
            LOG_ERROR("epoll_ctl delete error:%d \n", errno);
        } else {
            LOG_FATAL("epoll_ctl add or mod error:%d \n", errno);
        }
    }
}

// 移除 Channel
void EPollPoller::removeChannel(Channel* channel) {
    // 获取 socket 的 fd
    int fd = channel->fd();

    // 从 Channel 集合中将 fd 对应的 Channel 移除掉
    channels_.erase(fd);

    // 打印日志信息
    LOG_INFO("func=%s => fd=%d \n", __FUNCTION__, fd);

    // 获取 Channel 在 Epoll 中的状态
    int index = channel->index();
    if (index == kAdded) {
        // 更新 Channel
        update(EPOLL_CTL_DEL, channel);
    }

    // 更新 Channel 在 Epoll 中的状态
    channel->set_index(kNew);
}

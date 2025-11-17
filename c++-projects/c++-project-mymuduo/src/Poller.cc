#include "Poller.h"

#include "Channel.h"

// 构造函数
Poller::Poller(EventLoop* loop) : owerLoop_(loop) {
}

// 虚析构函数
Poller::~Poller() {
}

// 判断 Poller 中是否存在某个 Channel
bool Poller::hasChannel(Channel* channel) const {
    auto iterator = channels_.find(channel->fd());
    return iterator != channels_.end() && iterator->second == channel;
}
#include "Poller.h"

#include "Channel.h"

Poller::Poller(EventLoop* loop) : owerLoop_(loop) {
}

Poller::~Poller() {
}

bool Poller::hasChannel(Channel* channel) const {
    auto iterator = channels_.find(channel->fd());
    return iterator != channels_.end() && iterator->second == channel;
}

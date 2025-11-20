#include "Channel.h"

#include <sys/epoll.h>

#include "EventLoop.h"
#include "Logger.h"

// 定义 Channel 支持的事件类型（与 Epoll 兼容）
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

// 构造函数
Channel::Channel(EventLoop* loop, int fd) : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1), tied_(false) {
}

// 析构函数
Channel::~Channel() {
}

// 防止当 Channel 被手动 remove 掉后，Channel 还在执行事件的回调操作
void Channel::tie(const std::shared_ptr<void>& obj) {
    tie_ = obj;
    tied_ = true;
}

// 从 Poller 中删除自己
void Channel::remove() {
    // 通过 Channel 所属的 EventLoop，将当前的 Channel 删除掉
    loop_->removeChannel(this);
}

// 更新 Channel 状态到 Poller 中
void Channel::update() {
    // 通过 Channel 所属的 EventLoop，调用 Poller 相应的方法，注册 fd 的感兴趣的事件（events_）
    loop_->updateChannel(this);
}

// fd 得到 poller 通知以后，处理事件的函数
void Channel::handleEvent(Timestamp receiveTime) {
    if (tied_) {
        std::shared_ptr<void> guad = tie_.lock();
        if (guad) {
            handleEventWithGuard(receiveTime);
        }
    } else {
        handleEventWithGuard(receiveTime);
    }
}

/**
 * 处理事件，有了 guard 之后，Channel 就不会在被手动 remove 掉后还继续执行事件的回调操作了
 *
 * EPOLLIN：可读，文件描述符有数据可读且读取不会阻塞（如 socket 或 pipe 有数据）。
 * EPOLLOUT：可写，文件描述符可以写入且不会阻塞（如 socket 可发送数据、pipe 可写入）。
 * EPOLLERR：错误，文件描述符发生错误，无法正常读写（如 TCP reset、I/O 错误）。
 * EPOLLHUP：挂断，文件描述符被挂断（如对端关闭连接）。注意：通常与 EPOLLIN 一起出现。
 * EPOLLPRI：紧急数据，文件描述符有优先数据（TCP OOB 或特殊设备的紧急数据）。
 */
void Channel::handleEventWithGuard(Timestamp receiveTime) {
    LOG_INFO("channel handle event, revents: %d\n", revents_);

    // 发生挂断事件且没有读事件发生
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        if (closeCallback_) {
            closeCallback_();
        }
    }

    // 发生错误事件
    if (revents_ & EPOLLERR) {
        if (errorCallback_) {
            errorCallback_();
        }
    }

    // 发生读事件
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLHUP)) {
        if (readCallback_) {
            readCallback_(receiveTime);
        }
    }

    // 发生写事件
    if (revents_ & EPOLLOUT) {
        if (writeCallback_) {
            writeCallback_();
        }
    }
}

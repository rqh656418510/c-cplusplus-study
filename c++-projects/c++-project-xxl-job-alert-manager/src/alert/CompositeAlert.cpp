#include "CompositeAlert.h"

// 添加告警渠道
void CompositeAlert::addChannel(std::shared_ptr<AlertChannel> channel) {
    channels_.push_back(std::move(channel));
}

// 发送消息
bool CompositeAlert::sendMsg(const std::string& title, const std::string& content) {
    bool successed = true;
    for (auto& c : channels_) {
        successed &= c->sendMsg(title, content);
    }
    return successed;
}
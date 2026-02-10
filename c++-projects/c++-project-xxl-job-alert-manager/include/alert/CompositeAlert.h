#pragma once

#include <memory>
#include <string>
#include <vector>

#include "AlertChannel.h"

// 复合告警
class CompositeAlert : public AlertChannel {
public:
    // 添加告警渠道
    void addChannel(std::shared_ptr<AlertChannel> channel);

    // 发送消息
    bool sendMsg(const std::string& title, const std::string& content);

private:
    // 告警渠道集合
    std::vector<std::shared_ptr<AlertChannel>> channels_;
};
#include "AlertManager.h"

// 构造函数
AlertManager::AlertManager(std::shared_ptr<AlertChannel> channel) : channel_(std::move(channel)) {
}

// 执行告警
void AlertManager::alert(const std::string& title, const std::string& content) {
    channel_->sendMsg(title, content);
}
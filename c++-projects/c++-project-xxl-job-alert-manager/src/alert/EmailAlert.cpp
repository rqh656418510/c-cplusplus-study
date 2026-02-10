#include "EmailAlert.h"

#include "Logger.h"

// 发送消息
bool EmailAlert::sendMsg(const std::string& title, const std::string& content) {
    LOG_INFO("发送邮件告警信息: %s", content.c_str());
    return true;
}
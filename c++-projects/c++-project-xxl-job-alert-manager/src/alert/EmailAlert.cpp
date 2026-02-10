#include "EmailAlert.h"

#include <algorithm>
#include <string>

#include "Logger.h"

// 发送消息
bool EmailAlert::sendMsg(const std::string& title, const std::string& content) {
    // 日志内容去掉换行符
    std::string log_conent = content;
    std::replace(log_conent.begin(), log_conent.end(), '\n', ' ');

    // 记录日志信息
    LOG_INFO("发送邮件告警信息: %s", content.c_str());

    // TODO 邮件发送

    return true;
}
#pragma once

#include <string>

// 告警级别
enum class AlertLevel : uint8_t {
    TRACE = 0,  // 超细粒度跟踪
    DEBUG,      // 调试信息
    INFO,       // 正常但重要的信息
    NOTICE,     // 业务态的变化信息
    WARN,       // 潜在风险
    ERROR,      // 功能异常
    CRITICAL    // 系统不可用
};

// 告警渠道（抽象类）
class AlertChannel {
public:
    // 虚析构函数
    virtual ~AlertChannel() = default;

    // 发送消息（纯虚函数）
    virtual bool sendMsg(const std::string& title, const std::string& content) = 0;
};
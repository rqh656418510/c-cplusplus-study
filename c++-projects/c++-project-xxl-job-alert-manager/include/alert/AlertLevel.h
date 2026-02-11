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

// clang-format off

namespace std {
    // 为 unordered_map 支持 enum class key 特化 std::hash
    template <>
    struct hash<AlertLevel> {
        std::size_t operator()(const AlertLevel& level) const noexcept {
            return std::hash<uint8_t>()(static_cast<uint8_t>(level));
        }
    };
}

// clang-format on
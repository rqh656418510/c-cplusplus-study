#pragma once

#include <memory>

#include "AlertChannel.h"
#include "CompositeAlert.h"
#include "NonCopyable.h"

// 创建告警渠道的工厂（单例模式）
class AlertChannelFactory : NonCopyable {
public:
    // 获取单例对象
    static AlertChannelFactory& getInstance();

    // 创建邮件告警渠道
    std::shared_ptr<AlertChannel> createEmailAlert();

    // 创建企业微信告警渠道
    std::shared_ptr<AlertChannel> createWxQyAlert();

    // 创建异步邮件告警渠道
    std::shared_ptr<AlertChannel> createAsyncEmailAlert();

    // 创建异步微信告警渠道
    std::shared_ptr<AlertChannel> createAsyncWxQyAlert();

    // 创建复合告警渠道
    std::shared_ptr<CompositeAlert> createCompositeAlert();

private:
    // 私有构造函数
    AlertChannelFactory() = default;

    // 私有析构函数
    ~AlertChannelFactory() = default;
};
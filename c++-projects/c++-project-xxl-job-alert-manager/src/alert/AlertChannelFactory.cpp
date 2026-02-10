#include "AlertChannelFactory.h"

#include "AsyncAlert.h"
#include "CompositeAlert.h"
#include "EmailAlert.h"
#include "WxQyAlert.h"

// 获取单例对象
AlertChannelFactory& AlertChannelFactory::getInstance() {
    // 静态局部变量（线程安全）
    static AlertChannelFactory instance;
    return instance;
}

// 创建邮件告警渠道
std::shared_ptr<AlertChannel> AlertChannelFactory::createEmailAlert() {
    return std::make_shared<EmailAlert>();
}

// 创建企业微信告警渠道
std::shared_ptr<AlertChannel> AlertChannelFactory::createWxQyAlert() {
    return std::make_shared<WxQyAlert>();
}

// 创建异步邮件告警渠道
std::shared_ptr<AlertChannel> AlertChannelFactory::createAsyncEmailAlert() {
    return std::make_shared<AsyncAlert>(createEmailAlert());
}

// 创建异步微信告警渠道
std::shared_ptr<AlertChannel> AlertChannelFactory::createAsyncWxQyAlert() {
    return std::make_shared<AsyncAlert>(createWxQyAlert());
}

// 创建复合告警渠道
std::shared_ptr<CompositeAlert> AlertChannelFactory::createCompositeAlert() {
    return std::make_shared<CompositeAlert>();
}
#include "WxQyAlert.h"

#include <string>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "WxQyApi.h"
#include "WxQyMsgType.h"
#include "WxQySendMsgReq.h"

// 发送消息
bool WxQyAlert::sendMsg(const std::string& title, const std::string& content) {
    // 获取全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 封装请求参数
    WxQySendMsgReq req;
    req.setAgentid(config.wxQyAccount.agentId);
    req.setTouser(config.wxQyAccount.toUser);
    req.setMsgtype(toMsgTypeString(WxQyMsgType::Text));
    req.setContent(content);
    req.setSafe(0);

    // 日志信息去掉换行符
    std::string logConent = content;
    std::replace(logConent.begin(), logConent.end(), '\n', ' ');

    // 记录日志信息
    LOG_INFO("发送企业微信告警信息: %s", logConent.c_str());

    // 发送应用消息
    return WxQyApi::sendMessage(req);
}
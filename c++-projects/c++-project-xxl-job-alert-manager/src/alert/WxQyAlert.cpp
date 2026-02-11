#include "WxQyAlert.h"

#include <algorithm>
#include <string>

#include "AppConfigLoader.h"
#include "Logger.h"
#include "WxQyApi.h"
#include "WxQyMsgType.h"
#include "WxQySendMsgReq.h"

// 发送消息
bool WxQyAlert::sendMsg(const std::string& title, const std::string& content) {
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();

    // 封装请求参数
    WxQySendMsgReq req;
    req.setAgentid(config.wxQyAccount.agentId);
    req.setTouser(config.wxQyAccount.toUser);
    req.setMsgtype(toMsgTypeString(WxQyMsgType::Text));
    req.setContent(content);
    req.setSafe(0);

    // 日志内容去掉换行符
    std::string log_conent = content;
    std::replace(log_conent.begin(), log_conent.end(), '\n', ' ');

    // 记录日志信息
    LOG_INFO("发送企业微信告警信息: %s", log_conent.c_str());

    // 发送应用消息
    return WxQyApi::sendMessage(req);
}
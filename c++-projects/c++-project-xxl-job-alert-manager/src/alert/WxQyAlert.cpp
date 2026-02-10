#include "WxQyAlert.h"

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
    req.setAgentid(config.wechatAccount.agentId);
    req.setTouser(config.wechatAccount.toUser);
    req.setMsgtype(toMsgTypeString(WxQyMsgType::Text));
    req.setContent(content);
    req.setSafe(0);

    LOG_INFO("发送企业微信告警信息: %s", content.c_str());

    // 发送应用消息
    bool result = WxQyApi::sendMessage(req);

    return result;
}
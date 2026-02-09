// clang-format off

#include "Alert.h"
#include "Logger.h"
#include "WxQyApi.h"
#include "AppConfigLoader.h"
#include "NetworkUtil.h"
#include "WxQySendMsgReq.h"
#include <algorithm>

// 发送企业微信应用信息
void Alert::sendWxQyTextMsg(const int agentId, const std::string& toUser, const std::string& msg) {
    return;

    std::string log_msg = msg;
    std::replace(log_msg.begin(), log_msg.end(), '\n', ' ');
    LOG_INFO("发送企业微信应用信息: %s", log_msg.c_str());

    // 封装企业微信应用信息
    WxQySendMsgReq req;
    req.setAgentid(agentId);
    req.setTouser(toUser);
    req.setContent(msg);
    req.setMsgtype("text");
    req.setSafe(0);

    // 发送企业微信应用信息
    WxQyApi::sendMessage(req);
}

// 发送企业微信应用信息
void Alert::sendWxQyTextMsg(const int agentId, const std::string& toUser, const XxlJobLog& log) {
    return;
    
    // 全局配置信息
    const AppConfig& config = AppConfigLoader::getInstance().getConfig();
    
    // 应用信息内容
    std::string msg =
        "【XXL-JOB 任务执行失败】\n"
        "【IP】" + NetworkUtil::getInstance().getPublicIp() + "\n" +
        "【Env】" + config.alert.xxljobEnvironmentName + "\n" +
        "【Job】" + log.getExecutorHandler() + "\n" +
        "【Time】" + log.getTriggerTime() + "\n" +
        "【Code】" + std::to_string(log.getTriggerCode()) + "\n" +
        "【Message】" + log.getTriggerMsg();

    std::string log_msg = msg;
    std::replace(log_msg.begin(), log_msg.end(), '\n', ' ');
    LOG_INFO("发送企业微信应用信息: %s", log_msg.c_str());

    // 封装企业微信应用信息
    WxQySendMsgReq req;
    req.setAgentid(agentId);
    req.setTouser(toUser);
    req.setContent(msg);
    req.setMsgtype("text");
    req.setSafe(0);

    // 发送企业微信应用信息
    WxQyApi::sendMessage(req);
}
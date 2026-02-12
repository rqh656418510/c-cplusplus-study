#pragma once

#include <cstdint>
#include <regex>
#include <string>

#include "AppConfigLoader.h"
#include "NetworkHelper.h"
#include "json.hpp"

// 类型重定义
using json = nlohmann::json;

// XXL-JOB任务调度日志表的映射类
class XxlJobLog {
public:
    XxlJobLog() = default;
    ~XxlJobLog() = default;

    // ---------- Getter ----------
    int64_t getId() const {
        return id_;
    }
    int32_t getJobGroup() const {
        return jobGroup_;
    }
    int32_t getJobId() const {
        return jobId_;
    }
    const std::string& getExecutorAddress() const {
        return executorAddress_;
    }
    const std::string& getExecutorHandler() const {
        return executorHandler_;
    }
    const std::string& getExecutorParam() const {
        return executorParam_;
    }
    const std::string& getExecutorShardingParam() const {
        return executorShardingParam_;
    }
    int32_t getExecutorFailRetryCount() const {
        return executorFailRetryCount_;
    }
    const std::string& getTriggerTime() const {
        return triggerTime_;
    }
    int32_t getTriggerCode() const {
        return triggerCode_;
    }
    const std::string& getTriggerMsg() const {
        return triggerMsg_;
    }
    const std::string& getHandleTime() const {
        return handleTime_;
    }
    int32_t getHandleCode() const {
        return handleCode_;
    }
    const std::string& getHandleMsg() const {
        return handleMsg_;
    }
    int8_t getAlarmStatus() const {
        return alarmStatus_;
    }

    // ---------- Setter ----------
    void setId(int64_t id) {
        id_ = id;
    }
    void setJobGroup(int32_t jobGroup) {
        jobGroup_ = jobGroup;
    }
    void setJobId(int32_t jobId) {
        jobId_ = jobId;
    }
    void setExecutorAddress(const std::string& address) {
        executorAddress_ = address;
    }
    void setExecutorHandler(const std::string& handler) {
        executorHandler_ = handler;
    }
    void setExecutorParam(const std::string& param) {
        executorParam_ = param;
    }
    void setExecutorShardingParam(const std::string& shardingParam) {
        executorShardingParam_ = shardingParam;
    }
    void setExecutorFailRetryCount(int32_t count) {
        executorFailRetryCount_ = count;
    }
    void setTriggerTime(const std::string& triggerTime) {
        triggerTime_ = triggerTime;
    }
    void setTriggerCode(int32_t triggerCode) {
        triggerCode_ = triggerCode;
    }
    void setTriggerMsg(const std::string& msg) {
        triggerMsg_ = msg;
    }
    void setHandleTime(const std::string& handleTime) {
        handleTime_ = handleTime;
    }
    void setHandleCode(int32_t handleCode) {
        handleCode_ = handleCode;
    }
    void setHandleMsg(const std::string& msg) {
        handleMsg_ = msg;
    }
    void setAlarmStatus(int8_t status) {
        alarmStatus_ = status;
    }

    // ---------- Other ----------
    std::string parseAlertMsg() {
        // 全局配置信息
        const AppConfig& config = AppConfigLoader::getInstance().getConfig();

        // 拼接告警消息
        char buf[2048];
        snprintf(buf, sizeof(buf),
                 "【XXL-JOB 调度失败】\n"
                 "【IP】%s\n"
                 "【Env】%s\n"
                 "【Job】%s\n"
                 "【Time】%s\n"
                 "【Code】%d\n"
                 "【Message】%s",
                 NetworkHelper::getInstance().getPublicIp().c_str(), config.alert.xxljobEnvironmentName.c_str(),
                 executorHandler_.c_str(), triggerTime_.c_str(), triggerCode_, triggerMsg_.c_str());

        // 告警消息降噪
        std::regex regexPattern(R"(<br>\s*<span style="color:#00c0ef;" > >>>>>>>>>>>触发调度<<<<<<<<<<< </span><br>)");
        std::string content = std::regex_replace(std::string(buf), regexPattern, std::string(""));
        content = std::regex_replace(content, std::regex("<br><br>"), std::string(""));

        // 返回告警消息
        return content;
    }

private:
    int64_t id_{0};  // 主键ID（自增）

    int32_t jobGroup_{0};  // 执行器主键ID
    int32_t jobId_{0};     // 任务主键ID

    std::string executorAddress_;        // 执行器地址（本次执行的地址）
    std::string executorHandler_;        // 执行器任务 handler
    std::string executorParam_;          // 执行器任务参数
    std::string executorShardingParam_;  // 执行器任务分片参数（格式如：1/2）

    int32_t executorFailRetryCount_{0};  // 失败重试次数

    std::string triggerTime_;  // 调度时间
    int32_t triggerCode_{0};   // 调度结果
    std::string triggerMsg_;   // 调度日志

    std::string handleTime_;  // 执行时间
    int32_t handleCode_{0};   // 执行状态
    std::string handleMsg_;   // 执行日志

    int8_t alarmStatus_{0};  // 告警状态：0-默认，1-无需告警，2-告警成功，3-告警失败
};

// JSON 序列化
inline void to_json(json& j, const XxlJobLog& log) {
    // 数值字段：一般都序列化
    j["id"] = log.getId();
    j["jobGroup"] = log.getJobGroup();
    j["jobId"] = log.getJobId();
    j["executorFailRetryCount"] = log.getExecutorFailRetryCount();
    j["triggerCode"] = log.getTriggerCode();
    j["handleCode"] = log.getHandleCode();
    j["alarmStatus"] = log.getAlarmStatus();

    // 字符串字段：非空才序列化
    if (!log.getExecutorAddress().empty()) j["executorAddress"] = log.getExecutorAddress();
    if (!log.getExecutorHandler().empty()) j["executorHandler"] = log.getExecutorHandler();
    if (!log.getExecutorParam().empty()) j["executorParam"] = log.getExecutorParam();
    if (!log.getExecutorShardingParam().empty()) j["executorShardingParam"] = log.getExecutorShardingParam();
    if (!log.getTriggerTime().empty()) j["triggerTime"] = log.getTriggerTime();
    if (!log.getTriggerMsg().empty()) j["triggerMsg"] = log.getTriggerMsg();
    if (!log.getHandleTime().empty()) j["handleTime"] = log.getHandleTime();
    if (!log.getHandleMsg().empty()) j["handleMsg"] = log.getHandleMsg();
}
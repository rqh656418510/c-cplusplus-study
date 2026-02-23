// clang-format off

#include "AppConfigLoader.h"

#include <cstdlib>

#include "Logger.h"

// 初始化类静态变量（定义全局配置文件）
std::string AppConfigLoader::CONFIG_FILE = "alert.conf";

// 私有构造函数
AppConfigLoader::AppConfigLoader() {
    // 加载配置文件
    config_ = load(CONFIG_FILE.c_str());
}

// 私有析构函数
AppConfigLoader::~AppConfigLoader() {
}

// 获取单例对象
AppConfigLoader& AppConfigLoader::getInstance() {
    // 静态局部变量（线程安全）
    static AppConfigLoader instance;
    return instance;
}

// 获取全局配置
const AppConfig& AppConfigLoader::getConfig() const {
    return config_;
}

// 转换数字
int toInt(const std::string& v, const char* key) {
    if (v.empty()) {
        LOG_FATAL("Config [%s] is missing", key);
    }
    return std::stoi(v);
}

// 转换字符串
std::string toStr(const std::string& v, const char* key) {
    if (v.empty()) {
        LOG_FATAL("Config [%s] is missing", key);
    }
    return v;
}

// 加载配置文件
AppConfig AppConfigLoader::load(const char* configFile) {
    ConfigFileUtil cfg_util;
    cfg_util.loadConfigFile(configFile);

    AppConfig app;

    // MySQL Config
    app.mysql.ip = toStr(cfg_util.load("mysql.ip"), "mysql.ip");
    app.mysql.port = toInt(cfg_util.load("mysql.port"), "mysql.port");
    app.mysql.user = toStr(cfg_util.load("mysql.user"), "mysql.user");
    app.mysql.password = toStr(cfg_util.load("mysql.password"), "mysql.password");
    app.mysql.database = toStr(cfg_util.load("mysql.db"), "mysql.db");
    app.mysql.table = toStr(cfg_util.load("mysql.table"), "mysql.table");
    app.mysql.connectionPoolInitSize = toInt(cfg_util.load("mysql.connection.pool.init_size"), "mysql.connection.pool.init_size");
    app.mysql.connectionPoolMaxSize = toInt(cfg_util.load("mysql.connection.pool.max_size"), "mysql.connection.pool.max_size");
    app.mysql.connectionPoolMaxIdleTime = toInt(cfg_util.load("mysql.connection.pool.max_idle_time"), "mysql.connection.pool.max_idle_time");
    app.mysql.connectionPoolConnectionTimeout = toInt(cfg_util.load("mysql.connection.pool.connection_timeout"), "mysql.connection.pool.connection_timeout");
    app.mysql.connectionPoolHeartbeatIntervalTime = toInt(cfg_util.load("mysql.connection.pool.heartbeat_interval_time"), "mysql.connection.pool.heartbeat_interval_time");
    
    // WxQy Account Config
    app.wxQyAccount.agentId = toInt(cfg_util.load("wxqy.account.agent_id"), "wxqy.account.agent_id");
    app.wxQyAccount.toUser = toStr(cfg_util.load("wxqy.account.to_user"), "wxqy.account.to_user");
    app.wxQyAccount.corpId = toStr(cfg_util.load("wxqy.account.corp_id"), "wxqy.account.corp_id");
    app.wxQyAccount.corpSecret = toStr(cfg_util.load("wxqy.account.corp_secret"), "wxqy.account.corp_secret");

    // WxQy API Config
    app.wxQyApi.host = toStr(cfg_util.load("wxqy.api.host"), "wxqy.api.host");
    app.wxQyApi.getTokenPath = toStr(cfg_util.load("wxqy.api.get_token"), "wxqy.api.get_token");
    app.wxQyApi.sendMsgPath = toStr(cfg_util.load("wxqy.api.send_msg"), "wxqy.api.send_msg");
    app.wxQyApi.refreshTokenIntervalTime = toInt(cfg_util.load("wxqy.api.refresh_token_interval_time"), "wxqy.api.refresh_token_interval_time");
    app.wxQyApi.retryRefreshTokenIntervalTime = toInt(cfg_util.load("wxqy.api.retry_refresh_token_interval_time"), "wxqy.api.retry_refresh_token_interval_time");
    
    // Alert Core Config
    app.alertCore.xxljobStopStatusScanIntervalTime = toInt(cfg_util.load("alert.xxljob.stop_status_scan_interval_time"), "alert.xxljob.stop_status_scan_interval_time");
    app.alertCore.xxljobStopStatusMaxLogIdleTime = toInt(cfg_util.load("alert.xxljob.stop_status_max_log_idle_time"), "alert.xxljob.stop_status_max_log_idle_time");
    app.alertCore.xxljobStopStatusProcessMaxTimesPerDay = toInt(cfg_util.load("alert.xxljob.stop_status_process_max_times_per_day"), "alert.xxljob.stop_status_process_max_times_per_day");
    app.alertCore.xxljobStopStatusConsecutiveThreshold = toInt(cfg_util.load("alert.xxljob.stop_status_consecutive_threshold"), "alert.xxljob.stop_status_consecutive_threshold");
    app.alertCore.xxljobStopStatusProcessCommand = toStr(cfg_util.load("alert.xxljob.stop_status_process_command"), "alert.xxljob.stop_status_process_command");
    app.alertCore.xxljobFatalStatusScanIntervalTime = toInt(cfg_util.load("alert.xxljob.fatal_status_scan_interval_time"), "alert.xxljob.fatal_status_scan_interval_time");
    app.alertCore.xxljobFatalStatusProcessMaxTimesPerDay = toInt(cfg_util.load("alert.xxljob.fatal_status_process_max_times_per_day"), "alert.xxljob.fatal_status_process_max_times_per_day");
    app.alertCore.xxljobFatalStatusConsecutiveThreshold = toInt(cfg_util.load("alert.xxljob.fatal_status_consecutive_threshold"), "alert.xxljob.fatal_status_consecutive_threshold");
    app.alertCore.xxljobFatalStatusProcessCommand = toStr(cfg_util.load("alert.xxljob.fatal_status_process_command"), "alert.xxljob.fatal_status_process_command");

    // Alert Common Config
    app.alertCommon.envName = toStr(cfg_util.load("alert.env.name"), "alert.env.name");
    app.alertCommon.lockFile = toStr(cfg_util.load("alert.lock.file"), "alert.lock.file");
    app.alertCommon.logLevel = toStr(cfg_util.load("alert.log.level"), "alert.log.level");

    return app;
}
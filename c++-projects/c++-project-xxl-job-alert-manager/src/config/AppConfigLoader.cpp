// clang-format off

#include "AppConfigLoader.h"

#include <cstdlib>

#include "Logger.h"

// 初始化类静态变量（定义全局配置文件）
std::string AppConfigLoader::CONFIG_FILE_PATH = "alert.conf";

// 私有构造函数
AppConfigLoader::AppConfigLoader() {
    // 加载配置文件
    config_ = load(CONFIG_FILE_PATH.c_str());
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

    // MySQL
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
    
    // WxQy Account
    app.wxQyAccount.agentId = toInt(cfg_util.load("wxqy.account.agent_id"), "wxqy.account.agent_id");
    app.wxQyAccount.toUser = toStr(cfg_util.load("wxqy.account.to_user"), "wxqy.account.to_user");
    app.wxQyAccount.corpId = toStr(cfg_util.load("wxqy.account.corp_id"), "wxqy.account.corp_id");
    app.wxQyAccount.corpSecret = toStr(cfg_util.load("wxqy.account.corp_secret"), "wxqy.account.corp_secret");

    // WxQy API
    app.wxQyApi.host = toStr(cfg_util.load("wxqy.api.host"), "wxqy.api.host");
    app.wxQyApi.getTokenPath = toStr(cfg_util.load("wxqy.api.get_token"), "wxqy.api.get_token");
    app.wxQyApi.sendMsgPath = toStr(cfg_util.load("wxqy.api.send_msg"), "wxqy.api.send_msg");

    // Alert
    app.alert.wxQyRefreshTokenIntervalTime = toInt(cfg_util.load("alert.wxqy.refresh_token_interval_time"), "alert.wxqy.refresh_token_interval_time");
    app.alert.wxQyRetryRefreshIntervalTime = toInt(cfg_util.load("alert.wxqy.retry_refresh_interval_time"), "alert.wxqy.retry_refresh_interval_time");
    app.alert.xxljobStopStatusScanIntervalTime = toInt(cfg_util.load("alert.xxljob.stop_status_scan_interval_time"), "alert.xxljob.stop_status_scan_interval_time");
    app.alert.xxljobFatalStatusScanIntervalTime = toInt(cfg_util.load("alert.xxljob.fatal_status_scan_interval_time"), "alert.xxljob.fatal_status_scan_interval_time");
    app.alert.xxljobLogMaxIdleTimeForStop = toInt(cfg_util.load("alert.xxljob.log_max_idle_time_for_stop"), "alert.xxljob.log_max_idle_time_for_stop");
    app.alert.xxljobEnvironmentName = toStr(cfg_util.load("alert.xxljob.environment_name"), "alert.xxljob.environment_name");
    app.alert.logLevel = toStr(cfg_util.load("alert.log.level"), "alert.log.level");
    app.alert.lockFile = toStr(cfg_util.load("alert.lock_file"), "alert.lock_file");

    return app;
}
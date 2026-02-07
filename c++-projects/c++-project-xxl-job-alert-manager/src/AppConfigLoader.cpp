// clang-format off

#include "AppConfigLoader.h"

#include <cstdlib>

#include "Logger.h"

// 初始化类静态变量
std::string AppConfigLoader::CONFIG_FILE_PATH = "alert.conf";

// 获取单例对象
AppConfigLoader& AppConfigLoader::getInstance() {
    // 静态局部变量（线程安全）
    static AppConfigLoader instance;
    return instance;
}

// 私有构造函数
AppConfigLoader::AppConfigLoader() {
    // 加载配置文件
    config_ = load(CONFIG_FILE_PATH.c_str());
}

// 私有析构函数
AppConfigLoader::~AppConfigLoader() {
}

// 获取全局配置
const AppConfig AppConfigLoader::getConfig() const {
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
    app.mysql.connectionPoolInitSize = toInt(cfg_util.load("mysql.connection.pool.initSize"), "mysql.connection.pool.initSize");
    app.mysql.connectionPoolMaxSize = toInt(cfg_util.load("mysql.connection.pool.maxSize"), "mysql.connection.pool.maxSize");
    app.mysql.connectionPoolMaxIdleTime = toInt(cfg_util.load("mysql.connection.pool.maxIdleTime"), "mysql.connection.pool.maxIdleTime");
    app.mysql.connectionPoolConnectionTimeout = toInt(cfg_util.load("mysql.connection.pool.connectionTimeout"), "mysql.connection.pool.connectionTimeout");
    
    // WeChat Account
    app.wechatAccount.agentId = toInt(cfg_util.load("wechat.agent_id"), "wechat.agent_id");
    app.wechatAccount.toUser = toStr(cfg_util.load("wechat.to_user"), "wechat.to_user");
    app.wechatAccount.corpId = toStr(cfg_util.load("wechat.corp_id"), "wechat.corp_id");
    app.wechatAccount.corpSecret = toStr(cfg_util.load("wechat.corp_secret"), "wechat.corp_secret");

    // WeChat API
    app.wechatApi.host = toStr(cfg_util.load("wechat.api.host"), "wechat.api.host");
    app.wechatApi.port = toInt(cfg_util.load("wechat.api.port"), "wechat.api.port");
    app.wechatApi.getTokenPath = toStr(cfg_util.load("wechat.api.get_token"), "wechat.api.get_token");
    app.wechatApi.sendMsgPath = toStr(cfg_util.load("wechat.api.send_msg"), "wechat.api.send_msg");

    // Alert
    app.alert.wechatRefreshTokenIntervalSeconds = toInt(cfg_util.load("alert.wechat.refresh_token_interval_seconds"), "alert.wechat.refresh_token_interval_seconds");
    app.alert.wechatRetryRefreshIntervalSeconds = toInt(cfg_util.load("alert.wechat.retry_refresh_interval_seconds"), "alert.wechat.retry_refresh_interval_seconds");
    app.alert.xxljobStopStatusScanIntervalSeconds = toInt(cfg_util.load("alert.xxljob.stop_status_scan_interval_seconds"), "alert.xxljob.stop_status_scan_interval_seconds");
    app.alert.xxljobFatalStatusScanIntervalSeconds = toInt(cfg_util.load("alert.xxljob.fatal_status_scan_interval_seconds"), "alert.xxljob.fatal_status_scan_interval_seconds");
    app.alert.xxljobLogMaxIdleSecondsForStop = toInt(cfg_util.load("alert.xxljob.log_max_idle_seconds_for_stop"), "alert.xxljob.log_max_idle_seconds_for_stop");
    
    return app;
}
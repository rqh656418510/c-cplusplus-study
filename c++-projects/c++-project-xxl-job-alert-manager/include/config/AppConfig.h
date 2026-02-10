#pragma once

#include <string>

// MySQL 连接配置
struct MySQLConfig {
    int port;                       // MySQL服务器的端口（mysql.port）
    std::string ip;                 // MySQL服务器的IP地址（mysql.ip）
    std::string user;               // MySQL的登录用户名（mysql.user）
    std::string password;           // MySQL的登录密码（mysql.password）
    std::string database;           // 连接的数据库名称（mysql.db）
    std::string table;              // XXL-JOB调度日志表的名称（mysql.table）
    int connectionPoolInitSize;     // 连接池的初始连接数（mysql.connection.pool.init_size）
    int connectionPoolMaxSize;      // 连接池的最大连接数（mysql.connection.pool.max_size）
    int connectionPoolMaxIdleTime;  // 连接池的最大空闲时间，单位秒（mysql.connection.pool.max_idle_time）
    int connectionPoolConnectionTimeout;  // 从连接池获取连接的超时时间，单位毫秒（mysql.connection.pool.connection_timeout）
};

// 企业微信账号配置
struct WeChatAccountConfig {
    int agentId;             // 企业微信应用的AgentId（wechat.agent_id）
    std::string toUser;      // 接收消息的企业微信用户ID（wechat.to_user）
    std::string corpId;      // 企业微信的公司ID（CorpId）（wechat.corp_id）
    std::string corpSecret;  // 企业微信应用的Secret（wechat.corp_secret）
};

// 企业微信API配置
struct WxQyApiConfig {
    int port;                  // 企业微信API服务器的端口（wxqy.api.port）
    std::string host;          // 企业微信API服务器的地址（wxqy.api.host）
    std::string getTokenPath;  // 获取企业微信AccessToken的接口路径（wxqy.api.get_token）
    std::string sendMsgPath;   // 发送企业微信应用消息的接口路径（wxqy.api.send_msg）
};

// 监控告警配置
struct AlertConfig {
    int wxQyRefreshTokenIntervalTime;  // 企业微信AccessToken刷新的时间间隔，单位秒（alert.wxqy.refresh_token_interval_time）
    int wxQyRetryRefreshIntervalTime;  // 企业微信AccessToken刷新失败后的重试间隔，单位秒（alert.wxqy.retry_refresh_interval_time）
    int xxljobStopStatusScanIntervalTime;  // 监控XXL-JOB是否停止运行的时间间隔，单位秒（alert.xxljob.stop_status_scan_interval_time）
    int xxljobFatalStatusScanIntervalTime;  // 监控XXL-JOB是否调度失败的时间间隔，单位秒（alert.xxljob.fatal_status_scan_interval_time）
    int xxljobLogMaxIdleTimeForStop;  // 任务调度日志记录的最大空闲时间，单位秒（alert.xxljob.log_max_idle_time_for_stop）
    std::string xxljobEnvironmentName;  //监控XXL-JOB的环境名称（alert.xxljob.environment_name）
};

// 全局配置
struct AppConfig {
    MySQLConfig mysql;                  // MySQL相关配置
    WxQyApiConfig wechatApi;            // 企业微信API相关配置
    WeChatAccountConfig wechatAccount;  // 企业微信账号相关配置
    AlertConfig alert;                  // 监控告警相关配置
};
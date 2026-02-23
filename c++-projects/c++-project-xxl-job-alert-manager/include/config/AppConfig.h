// clang-format off

#pragma once

#include <string>

// MySQL 连接配置
struct MySQLConfig {
    int port;                                 // MySQL服务器的端口（mysql.port）
    std::string ip;                           // MySQL服务器的IP地址（mysql.ip）
    std::string user;                         // MySQL的登录用户名（mysql.user）
    std::string password;                     // MySQL的登录密码（mysql.password）
    std::string database;                     // 连接的数据库名称（mysql.db）
    std::string table;                        // XXL-JOB调度日志表的名称（mysql.table）
    int connectionPoolInitSize;               // 连接池的初始连接数（mysql.connection.pool.init_size）
    int connectionPoolMaxReconnect;           // 连接断开后的最大重连次数（mysql.connection.pool.max_reconnect）
    int connectionPoolMaxSize;                // 连接池的最大连接数（mysql.connection.pool.max_size）
    int connectionPoolMaxIdleTime;            // 连接池的最大空闲回收时间，单位秒（mysql.connection.pool.max_idle_time）
    int connectionPoolConnectionTimeout;      // 从连接池获取连接的超时时间，单位毫秒（mysql.connection.pool.connection_timeout）
    int connectionPoolHeartbeatIntervalTime;  // 连接发送心跳的时间间隔，单位秒（mysql.connection.pool.heartbeat_interval_time）
};

// 企业微信账号配置
struct WxQyAccountConfig {
    int agentId;             // 企业微信应用的AgentId（wxqy.account.agent_id）
    std::string toUser;      // 接收消息的企业微信用户ID（wxqy.account.to_user）
    std::string corpId;      // 企业微信的公司ID（CorpId）（wxqy.account.corp_id）
    std::string corpSecret;  // 企业微信应用的Secret（wxqy.account.corp_secret）
};

// 企业微信API配置
struct WxQyApiConfig {
    std::string host;                   // 企业微信API服务器的地址（wxqy.api.host）
    std::string getTokenPath;           // 获取企业微信AccessToken的接口路径（wxqy.api.get_token）
    std::string sendMsgPath;            // 发送企业微信应用消息的接口路径（wxqy.api.send_msg）
    int refreshTokenIntervalTime;       // 企业微信AccessToken刷新的时间间隔，单位秒（wxqy.api.refresh_token_interval_time）
    int retryRefreshTokenIntervalTime;  // 企业微信AccessToken刷新失败后的重试间隔，单位秒（wxqy.api.retry_refresh_token_interval_time）
};

// 监控告警核心配置
struct AlertCoreConfig {
    int xxljobStopStatusScanIntervalTime;         // 监控XXL-JOB是否停止运行的时间间隔，单位秒（alert.xxljob.stop_status_scan_interval_time）
    int xxljobStopStatusMaxLogIdleTime;           // 任务调度日志记录的最大空闲时间，单位秒（alert.xxljob.stop_status_max_log_idle_time）
    int xxljobStopStatusConsecutiveThreshold;     // 连续监控到XXL-JOB停止运行达到该次数后，才会执行处理命令（alert.xxljob.stop_status_consecutive_threshold）
    int xxljobStopStatusProcessMaxTimesPerDay;    // 每天最多执行“处理XXL-JOB停止运行”的命令次数（alert.xxljob.stop_status_process_max_times_per_day）
    std::string xxljobStopStatusProcessCommand;   // 处理XXL-JOB停止运行的命令（alert.xxljob.stop_status_process_command）
    int xxljobFatalStatusScanIntervalTime;        // 监控XXL-JOB是否调度失败的时间间隔，单位秒（alert.xxljob.fatal_status_scan_interval_time）
    int xxljobFatalStatusConsecutiveThreshold;    // 连续监控到XXL-JOB调度失败达到该次数后，才会执行处理命令（alert.xxljob.fatal_status_consecutive_threshold）
    int xxljobFatalStatusProcessMaxTimesPerDay;   // 每天最多执行“处理XXL-JOB调度失败”的命令次数（alert.xxljob.fatal_status_process_max_times_per_day）
    std::string xxljobFatalStatusProcessCommand;  // 处理XXL-JOB调度失败的命令（alert.xxljob.fatal_status_process_command）
};

// 监控告警基础配置
struct AlertCommonConfig {
    std::string envName;   // 监控告警程序的运行环境（alert.env.name）
    std::string lockFile;  // 监控告警程序的锁文件（alert.lock.file）
    std::string logLevel;  // 监控告警程序的日志输出级别，优先级：DEBUG < INFO < WARN < ERROR < FATAL（alert.log.level）
};

// 全局配置
struct AppConfig {
    MySQLConfig mysql;              // MySQL相关配置
    WxQyApiConfig wxQyApi;          // 企业微信API相关配置
    WxQyAccountConfig wxQyAccount;  // 企业微信账号相关配置
    AlertCoreConfig alertCore;      // 监控告警核心配置
    AlertCommonConfig alertCommon;  // 监控告警基础配置
};
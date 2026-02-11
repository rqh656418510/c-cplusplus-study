## C++ 实现 XXL-JOB 监控告警

### 项目介绍

基于 C++ 开发的 XXL-JOB 监控告警应用，采用的技术栈包括：

- 单例模式
- 智能指针
- 配置文件读取
- 企业微信 API
- 数据库连接池
- HTTP 网络编程
- 多线程并发编程
- MySQL 数据库操作
- CMake 构建与编译
- JSON 序列化与反序列化

### 开发工具

| 软件                       | 版本        | 说明                                                                 |
| -------------------------- | ----------- | -------------------------------------------------------------------- |
| C++                        | `11`        |                                                                      |
| OpenSSL                    | `3.0.18`    | [httplib](https://github.com/yhirose/cpp-httplib) 库依赖 OpenSSL     |
| MySQL C API（Connector/C） | `8.4.5`     | [MySQL C API 库使用教程](https://www.techgrow.cn/posts/c9e38d0.html) |
| MySQL Server               | `8.4.5`     |                                                                      |
| Linux System               | `Debian 12` | 本项目只支持 Linux 平台，不兼容 Windows 平台                         |

### 项目配置

- 打开 `config/alert.conf` 配置文件，更改 MySQL 连接信息和企业微信账号信息，如下所示：

``` conf
# ==================== MySQL连接配置 ====================
# MySQL服务器的IP地址
mysql.ip=127.0.0.1
# MySQL服务器的端口
mysql.port=3306
# MySQL的登录用户名
mysql.user=root
# MySQL的登录密码
mysql.password=123456
# 数据库的名称
mysql.db=xxl_job
# 任务调度日志表的名称
mysql.table=xxl_job_log

# ==================== 企业微信账号配置 ====================
# 企业微信应用的AgentId
wxqy.account.agent_id=1000001
# 接收消息的企业微信用户ID
wxqy.account.to_user=ZhangSan
# 企业微信的公司ID（CorpId）
wxqy.account.corp_id=xxxxxxxxxx
# 企业微信应用的Secret
wxqy.account.corp_secret=xxxxxxxxxx
```

### 项目编译

> 注意：在编译项目之前，请务必在本地 Linux 操作系统中安装好 CMake、OpenSSL、MySQL C API（Connector/C），详细教程请参考 [这里](https://www.techgrow.cn/posts/c9e38d0.html)。

``` sh
# 进入项目根目录
cd c++-project-xxl-job-alert-manager

# 脚本文件授权执行
chmod +x autobuild.sh

# 执行一键编译构建脚本
./autobuild.sh
```

> 在 CentOS 系统上，编译项目之前可以执行命令 `yum install -y cmake3 openssl openssl-devel mysql-devel` 一键安装所需的依赖软件。

### 项目运行

> 注意：在运行项目之前，请务必确保 XXL-JOB 数据库已经初始化完成（开发环境可以执行 `sql/mysql.sql` 脚本来初始化数据库）

``` sh
# 进入项目 bin 目录
cd c++-project-xxl-job-alert-manager/bin

# 运行可执行文件（默认配置文件为 ./alert.conf）
./xxl-job-alert-manager

# 或者运行可执行文件时指定配置文件
./xxl-job-alert-manager -i alert.conf
```

### 参考项目

- [基于 C++ 实现 MySQL 数据库连接池](https://github.com/rqh656418510/c-cplusplus-study/tree/main/c%2B%2B-projects/c%2B%2B-project-db-connection-pool)

### 企业微信官方文档

- [企业微信开发文档 - 简易教程](https://developer.work.weixin.qq.com/document/path/90487)
- [企业微信开发文档 - 发送应用消息](https://developer.work.weixin.qq.com/document/path/90236)

## 项目说明

基于 C++ 开发的 XXL-JOB 监控工具，采用的技术栈包括：

- 单例设计模式
- 配置文件读取
- 数据库连接池
- HTTP 网络编程
- 多线程并发编程
- MySQL 数据库操作
- CMake 构建与编译
- JSON 序列化与反序列化

## 开发工具

| 软件                       | 版本        | 说明                                         |
| -------------------------- | ----------- | -------------------------------------------- |
| C++                        | `11`        |                                              |
| MySQL C API（Connector/C） | `8.4.5`     |                                              |
| MySQL Server               | `8.4.5`     |                                              |
| Linux System               | `Debian 12` | 本项目只支持 Linux 平台，不兼容 Windows 平台 |

## 项目配置

- 打开 `conf/alert.conf` 配置文件，更改 MySQL 连接信息和企业微信账号信息，如下所示：

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
wechat.agent_id=1000001
# 接收消息的企业微信用户ID
wechat.to_user=ZhangSan
# 企业微信的公司ID（CorpId）
wechat.corp_id=xxxxxxxxxx
# 企业微信应用的Secret
wechat.corp_secret=xxxxxxxxxx
```

## 项目编译

> 注意：在编译项目之前，请务必在本地 Linux 操作系统中安装好 OpenSSL、MySQL C API（Connector/C）库，否则项目会编译失败。

``` sh
# 进入项目根目录
cd c++-project-xxl-job-alert-manager

# 脚本文件授权执行
chmod +x autobuild.sh

# 执行一键编译构建脚本
./autobuild.sh
```

## 项目运行

``` sh
# 进入项目 bin 目录
cd c++-project-xxl-job-alert-manager/bin

# 运行可执行文件（默认配置文件为 ./alert.conf）
./xxl-job-alert-manager

# 或者运行可执行文件时指定配置文件
./xxl-job-alert-manager -i alert.conf
```

## 企业微信官方文档

- [企业微信开发文档 - 简易教程](https://developer.work.weixin.qq.com/document/path/90487)
- [企业微信开发文档 - 发送应用消息](https://developer.work.weixin.qq.com/document/path/90236)

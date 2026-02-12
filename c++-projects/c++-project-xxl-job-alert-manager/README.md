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
| OpenSSL                    | `3.0.18`    | [libcurl](https://github.com/curl/curl) 库依赖 OpenSSL               |
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

> 注意：在编译项目之前，请务必在本地 Linux 操作系统中安装好 CMake、OpenSSL、Libcurl、MySQL C API（Connector/C），详细教程请参考 [这里](https://www.techgrow.cn/posts/c9e38d0.html)。

``` sh
# 进入项目根目录
cd c++-project-xxl-job-alert-manager

# 脚本文件授权执行
chmod +x autobuild.sh

# 执行一键编译构建脚本
./autobuild.sh
```

> 在 CentOS 7 系统上，编译项目之前可以执行命令 `yum install cmake3 openssl openssl-devel libcurl-devel mysql-devel` 一键安装所需的依赖软件。

### 项目运行

> 注意：在运行项目之前，请务必确保 XXL-JOB 数据库已经初始化完成（开发环境可以执行 `sql/mysql.sql` 脚本来初始化数据库）

``` sh
# 进入项目 bin 目录
cd c++-project-xxl-job-alert-manager/bin

# 运行可执行文件（默认配置文件为 ./alert.conf）
./alert-manager

# 或者运行可执行文件时指定配置文件
./alert-manager -i alert.conf
```

### 服务管理

Linux 平台（比如 Debian、CentOS）可以通过 Systemd 管理监控告警程序，具体配置如下（以 CentOS 配置为例）：

- 拷贝可执行文件

``` sh
# 创建工作目录
mkdir -p /home/centos/alert

# 拷贝可执行文件到工作目录
cp -r {YOUR_PROJECT_PATH}/bin/* /home/centos/alert
```

- 创建系统服务配置文件

``` sh
# 创建并编辑系统服务配置文件，然后添加以下配置内容
sudo vim /etc/systemd/system/alert-manager.service
```

``` conf
[Unit]
Description=Alert Manager Service
After=network.target

# 在 60 秒时间窗口内，最多重启 5 次，防止频繁崩溃无限重启
StartLimitIntervalSec=60
StartLimitBurst=5

[Service]
# 以 centos 用户运行
User=centos
Group=centos

# 工作目录
WorkingDirectory=/home/centos/alert

# 启动命令
ExecStart=/home/centos/alert/alert-manager -i /home/centos/alert/alert.conf

# 服务类型（前台运行）
Type=simple

# 异常退出则自动重启
Restart=on-failure
RestartSec=3

# 停止服务的最大等待时间，超时将被强制 Kill
TimeoutStopSec=30

# 进程杀死策略
KillMode=control-group

# 文件描述符上限
LimitNOFILE=65535

# 输出到 journal
StandardOutput=journal
StandardError=journal

[Install]
WantedBy=multi-user.target
```

- 通过 Systemd 管理监控告警程序

``` sh
# 重新加载系统配置
sudo systemctl daemon-reload

# 设置开机启动
sudo systemctl enable alert-manager

# 启动程序
sudo systemctl start alert-manager

# 查看状态
sudo systemctl status alert-manager

# 关闭程序
sudo systemctl stop alert-manager

# 查看系统日志
sudo journalctl -u alert-manager -f

# 查询应用日志
tail -f -n 50 /home/centos/alert/2026-2-12.log
```

### 参考项目

- [基于 C++ 实现 MySQL 数据库连接池](https://github.com/rqh656418510/c-cplusplus-study/tree/main/c%2B%2B-projects/c%2B%2B-project-db-connection-pool)

### 企业微信官方文档

- [企业微信开发文档 - 简易教程](https://developer.work.weixin.qq.com/document/path/90487)
- [企业微信开发文档 - 发送应用消息](https://developer.work.weixin.qq.com/document/path/90236)

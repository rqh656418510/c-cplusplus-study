# 基于 C++ 手写 Muduo 高性能网络库

## 博客教程

- [基于 C++ 手写 Muduo 高性能网络库](https://www.techgrow.cn/posts/dbb10768.html)

## 项目介绍

基于 C++ 开发一个类似 [Muduo](https://github.com/chenshuo/muduo) 的高性能网络库，项目代码大部分是从 Muduo 移值过来，同时去掉 Boost 依赖，并使用 C++ 11 进行代码重构，重点是学习 Muduo 的底层设计思想。

> 注意：本项目开发的 MyMuduo 网络库只实现了 Muduo 的核心功能，并不支持 Muduo 的定时事件机制（`TimerQueue`）、IPV6 / DNS / HTTP / RPC 协议等。

### 项目结构

| 目录名称          | 目录说明                                                            |
| ----------------- | ------------------------------------------------------------------- |
| `build`           | CMake 编译构建项目的目录（项目首次编译后才会有）                    |
| `bin`             | 存放项目编译生成的可执行文件的目录（项目首次编译后才会有）          |
| `lib`             | 存放项目编译生成的 MyMuduo 动态链接库的目录（项目首次编译后才会有） |
| `src`             | MyMuduo 网络库的源码                                                |
| `src/include`     | MyMuduo 网络库的头文件                                              |
| `test`            | MyMuduo 网络库的的测试代码                                          |
| `example`         | 各种案例代码                                                        |
| `example/epoll`   | epoll 的使用案例代码                                                |
| `example/mymuduo` | MyMuduo 网络库的使用案例代码                                        |
| `autobuild.sh`    | 项目一键编译构建的脚本文件                                          |

### 项目技术栈

- 单例设计模式
- epoll 等 I/O 多路复用技术
- Linux 网络编程基础（`socket()`、`bind()`、`listen()`、`accept()`、`readv()`、`write()` 等）
- C++ 11 多线程编程（`std::thread`、`std::unique_lock`、`std::mutex`、`std::condition_variable` 等）
- 使用 CMake 构建与集成项目的编译环境

### 项目开发工具

| 软件               | 版本        | 说明                                  |
| ------------------ | ----------- | ------------------------------------- |
| C++ 标准           | `11`        | C++ 标准的版本                        |
| G++（GCC）         | `12.2.0`    | 建议使用 `9` 版本的 G++（GCC） 编译器 |
| CMake              | `3.25.1`    | C/C++ 项目构建工具                    |
| Linux              | `Debian 12` | Muduo 库不支持 Windows 平台           |
| Visual Studio Code | `1.100.2`   | 使用 VSCode 远程开发特性              |

## 项目编译

``` sh
# 进入项目根目录
cd c++-project-mymuduo

# 执行项目自动构建脚本
./autobuild.sh
```

## 项目测试

``` sh
# 进入项目根目录
cd c++-project-mymuduo

# 执行 MyMuduo 网络库使用案例的可执行文件
./bin/mymuduo_example

# 执行 telnet 命令连接 TCP 服务器（成功连接后，输入任意字符，按回车键即可发送消息给服务器，之后服务器会返回相应的消息内容）
telnet 127.0.0.1 6000
```

测试程序输出的日志信息如下：

```
2025-11-15 22:10:01 => 6609 [INFO] ChatServer - start success, listening on 127.0.0.1:6000
2025-11-15 22:10:01 => 6614 [INFO] TcpClient::TcpClient(EventLoop*, const InetAddress&, const std::string&) => crate tcp client [ChatClient] - connector 0x7f52b8000e20
2025-11-15 22:10:01 => 6614 [INFO] void TcpClient::connect() => connect to 127.0.0.1:6000
2025-11-15 22:10:01 => 6614 [INFO] ChatClient - new connection [127.0.0.1:42170] -> [127.0.0.1:6000], state: connected
2025-11-15 22:10:01 => 6610 [INFO] ChatServer - Connection UP : 127.0.0.1:42170
2025-11-15 22:10:01 => 6610 [INFO] ChatServer - receive message: [I'm ChatClient], time: 2025-11-15 22:10:01, ip: 127.0.0.1:42170
2025-11-15 22:10:01 => 6614 [INFO] ChatClient - receive message: [You just said: I'm ChatClient], time: 2025-11-15 22:10:01
```

## 项目扩展

MyMuduo 网络库只实现了 Muduo 的核心功能，并不支持 Muduo 的定时事件机制（`TimerQueue`）、IPV6 / DNS / HTTP / RPC 协议等，日后可以从以下几方面继续对其进行扩展：

- (1) 定时事件机制
    - TimerQueue：支持 EventLoop 内的定时任务调度，常见实现方式包括：
        - 链表队列：实现简单，但不适合大量定时器场景（需要线性扫描）。
        - 红黑树（如 `nginx`）：按照到期时间排序，可快速找到最早到期的定时器，插入 / 删除的时间复杂度为 `O(logN)`。
        - 时间轮（如 `libevent`）：适合大量、定时精度要求不高的场景，插入 / 删除的时间复杂度为 `O(1)`，整体性能出色。

- (2) IPV6 / DNS / HTTP / RPC 协议支持
    - IPV6：支持 IPv6 套接字、地址解析与双栈接入，确保网络库的所有连接与事件处理流程均可透明兼容 IPv6。
    - DNS：实现异步域名解析（如 `getaddrinfo_a`），将域名解析和网络事件循环结合，避免阻塞 I/O。
    - HTTP：构建基础的 HTTP 请求解析、响应封装，可扩展为简单的 Web 服务器或客户端；需要支持 Keep-Alive、Chunked 等机制。
    - RPC：在已有 TCP 框架上封装请求 / 响应协议，实现序列化、服务注册、方法调用、超时与重试等功能（可仿照 gRPC 实现）。

- (3) 服务器性能测试
    - 为了验证网络库的性能，需要进行专业的性能压测和系统配置优化：
    - 系统性能优化
        - Linux 最大文件描述符数设置：包括
            - `/proc/sys/fs/file-max`（系统级限制）
            - `/etc/security/limits.conf`（进程级限制）
            - `ulimit -n`（当前会话限制）
    - 性能测试工具
        - [JMeter](https://github.com/apache/jmeter?utm_source=chatgpt.com)：可压测 HTTP 服务与自定义 TCP 服务，能够生成聚合报告和可视化图表。
        - [wrk](https://github.com/wg/wrk?utm_source=chatgpt.com)：高性能 HTTP 压测工具，支持多线程 + `epoll`，需要手动编译安装，仅支持 HTTP 协议。

# C++ 实现 RPC 分布式网络通信框架

## 博客教程

- [C++ 实现 RPC 分布式网络通信框架](https://www.techgrow.cn/posts/5e6aa28a.html)

## 项目介绍

基于 Muduo 高性能网络库 + Protobuf 开发 RPC 框架，并使用了中间件 ZooKeeper。

### 项目结构

| 目录名称           | 目录说明                                            |
| ------------------ | --------------------------------------------------- |
| `build`            | CMake 编译构建项目的目录                            |
| `bin`              | 存放项目编译生成的可执行文件                        |
| `lib`              | 存放项目编译生成的 RPC 框架头文件和静态库           |
| `conf`           | 存放 RPC 框架的配置文件                             |
| `generated`        | 存放根据 `.proto` 协议文件生成的 C++ 头文件和源文件 |
| `proto`            | 存放 Protobuf 的 `.proto` 协议文件                  |
| `src`              | RPC 框架源码                                        |
| `test`             | 第三方库的测试代码                                  |
| `test/protobuf/`   | Protobuf 的测试代码                                 |
| `test/zookeeper/`  | ZooKeeper 的测试代码                                |
| `example`          | RPC 框架的使用案例代码                              |
| `example/provider` | RPC 框架（服务提供者）的使用案例代码                |
| `example/consumer` | RPC 框架（服务调用者）的使用案例代码                |
| `autobuild.sh`     | 项目一键编译构建的脚本文件                          |

### 项目技术栈

- 单例模式
- Conf 配置文件读取
- Muduo 网络库编程
- CMake 构建项目集成编译环境
- 异步日志记录（线程同步通信实现）
- Protobuf 数据序列化和反序列化协议
- ZooKeeper 分布式一致性协调服务应用以及编程

### 项目开发工具

| 软件               | 版本        | 说明                                                                                  |
| ------------------ | ----------- | ------------------------------------------------------------------------------------- |
| C++ 标准           | `17`        | 高版本的 Protobuf 库依赖 C++ 17                                                       |
| Boost              | `1.74.0.3`  | Muduo 库依赖 Boost 库                                                                 |
| Muduo              | `2.0.3`     | [Muduo 库](https://github.com/chenshuo/muduo)，基于 C++ 开发，用于网络编程            |
| Protobuf           | `31.1`      | [Protobuf 库](https://github.com/protocolbuffers/protobuf)，核心代码主要是用 C++ 开发 |
| ZooKeeper C API    | `3.8.0`     | ZooKeeper 提供的原生 C API，基于 C 语言开发                                           |
| G++（GCC）         | `12.2.0`    | 建议使用 `9` 版本的 G++（GCC） 编译器                                                 |
| CMake              | `3.25.1`    | C/C++ 项目构建工具                                                                    |
| ZooKeeper          | `3.8.0`     | ZooKeeper 服务器                                                                      |
| Linux              | `Debian 12` | Muduo 库不支持 Windows 平台                                                           |

## 项目测试

> 注意：在编译项目之前，请务必在本地操作系统中安装好 Muduo 库、Protobuf 库、ZooKeeper C API 库。

- (1) 更改 `conf` 目录下的 `rpc.conf` 配置文件，指定 ZooKeeper 服务器的 IP 和端口号等信息

``` conf
# ZooKeeper的IP地址（必填）
zk_server_host=127.0.0.1
# ZooKeeper的端口号（必填）
zk_server_port=2181
# RPC服务提供者优先使用的网卡接口（可选）
rpc_network_interface=eth1
```

- (2) 通过 CMake 编译构建整个项目

``` sh
# 进入项目的根目录
cd c++-project-mprpc

# 授权脚本执行
chmod +x autobuild.sh

# 执行一键编译构建脚本
./autobuild.sh
```

- (3) 启动 ZooKeeper 服务器

``` sh
# 启动 ZooKeeper 服务器
sudo systemctl start zookeeper

# 查看 ZooKeeper 服务器的运行状态
sudo systemctl status zookeeper
```

- (4) 启动 RPC 服务提供者的案例程序

``` sh
# 进入项目的 bin 目录
cd c++-project-mprpc/bin

# 启动 RPC 服务提供者的案例程序（可使用相同的命令启动多个 RPC 服务提供者，不需要考虑端口冲突问题）
./example_rpc_provider -i rpc.conf
```

- (5) 启动 RPC 服务调用者的案例程序

``` sh
# 进入项目的 bin 目录
cd c++-project-mprpc/bin

# 启动 RPC 服务调用者的案例程序（可使用相同的命令启动多个 RPC 服务调用者，不需要考虑端口冲突问题）
./example_rpc_consumer -i rpc.conf
```

- (6) 查看 RPC 框架运行输出的日志文件

``` sh
# 进入项目的 bin 目录
cd c++-project-mprpc/bin

# 查看 RPC 框架运行输出的日志文件（请自行更改日志文件名）
vim 2025-06-12-log.txt
```

## 集群聊天服务器

### 博客地址

- [基于 C++ 开发集群聊天服务器](https://techgrow.cn/posts/e635f0aa.html)

### 开发工具

| 软件               | 版本        | 说明                                                                                   |
| ------------------ | ----------- | -------------------------------------------------------------------------------------- |
| C++ 标准           | `11`        |                                                                                        |
| Boost              | `1.74.0.3`  | Boost 库                                                                               |
| Muduo              | `2.0.3`     | [Muduo 库](https://github.com/chenshuo/muduo)，基于 C++ 开发，用于网络编程             |
| hiredis            | `1.3.0`     | [Reids 库](https://github.com/redis/hiredis) ，基于 C 语言开发，用于操作 Redis         |
| nlohmann/json      | `3.12.0`    | [Json 库](https://github.com/nlohmann/json)，基于 C++ 开发，用于 Json 序列化和反序列化 |
| Redis              | `7.0.15`    | Redis 服务器                                                                           |
| MySQL              | `8.4.5`     | MySQL 服务器                                                                           |
| Nginx              | `1.28.0`    | Nginx 服务器                                                                           |
| G++（GCC）         | `12.2.0`    | 建议使用 `5.5`、`7.5` 版本的 G++（GCC） 编译器                                         |
| CMake              | `3.25.1`    | C/C++ 项目构建工具                                                                     |
| Linux              | `Debian 12` | Muduo 库不支持 Windows 平台                                                            |

> 注意：由于使用了 Muduo 库，且 Muduo 库仅支持 Linux 平台；因此本项目提供的所有 C++ 集群聊天服务器代码支持在 Linux 平台运行，不支持 Windows 平台，默认是基于 Debian 12 进行开发。

### 项目构建

``` sh
# 进入项目根目录
cd c++-project-cluster-chat-server

# 配置项目，生成构建文件
cmake -S . -B build

# 编译项目，在bin目录下生成可执行文件
cmake --build build
```

### 项目运行

- 1. 启动 Nginx、Redis、MySQL 服务

- 2. 启动集群聊天服务端程序
    - 启动第一个聊天服务端程序：`./bin/chat_server 127.0.0.1 6000`
    - 启动第二个聊天服务端程序：`./bin/chat_server 127.0.0.1 6002`

- 3. 启动集群聊天客户端程序
    - 启动第一个聊天客户端程序：`./bin/chat_client 127.0.0.1 8000`，连接的是 Nginx 的 TCP 负载均衡器
    - 启动第二个聊天客户端程序：`./bin/chat_client 127.0.0.1 8000`，连接的是 Nginx 的 TCP 负载均衡器

### 项目接口

- 用户注册

``` json
{"msgType": 3, "name": "jim", "password": "12345"}

{"msgType": 3, "name": "tom", "password": "12345"}
```

- 用户登录

``` json
{"msgType": 1, "name": "jim", "password": "12345"}

{"msgType": 1, "name": "tom", "password": "12345"}
```

- 添加好友

``` json
{"msgType": 7, "userId": 22, "friendId": 23}

{"msgType": 7, "userId": 23, "friendId": 22}
```

- 发送一对一聊天消息

``` json
{"msgType": 5, "fromId": 22, "fromName": "jim", "fromMsg": "hello", "fromTimestamp": 1748926809683, "toId": 23}

{"msgType": 5, "fromId": 23, "fromName": "tom", "fromMsg": "hello", "fromTimestamp": 1748926809785, "toId": 22}
```

- 创建群组

``` json
{"msgType": 9, "userId": 22, "groupName": "c++", "groupDesc": "c++ study"}
```

- 加入群组

``` json
{"msgType": 11, "userId": 23, "groupId": 1}
```

- 发送群聊消息

``` json
{"msgType": 13, "fromId": 22, "fromName": "jim", "fromTimestamp": 1748926803682, "groupId": 1, "groupMsg": "go to study c++"}

{"msgType": 13, "fromId": 23, "fromName": "tom", "fromTimestamp": 1748926805372, "groupId": 1, "groupMsg": "go to study rust"}
```

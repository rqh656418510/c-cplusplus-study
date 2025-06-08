## 集群聊天服务器

### 博客地址

- [基于 C++ 开发集群聊天服务器](https://techgrow.cn/posts/e635f0aa.html)

### 项目构建

``` sh
# 进入项目根目录
cd c++-project-cluster-chat-server

# 配置项目，生成构建文件
cmake -S . -B build

# 编译项目，生成可执行文件
cmake --build build
```

### 项目运行

- 1. 启动 Nginx、Redis、MySQL 服务

- 2. 启动集群聊天服务端程序
    - 启动第一个聊天服务端程序：`chat_server 127.0.0.1 6000`
    - 启动第二个聊天服务端程序：`chat_server 127.0.0.1 6002`

- 3. 启动集群聊天客户端程序
    - 启动第一个聊天客户端程序：`chat_client 127.0.0.1 8000`，连接的是 Nginx 的 TCP 负载均衡器
    - 启动第二个聊天客户端程序：`chat_client 127.0.0.1 8000`，连接的是 Nginx 的 TCP 负载均衡器

### 项目接口定义

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
{"msgType": 13, "fromId": 22, "fromName": "jim", "fromTimestamp": 1748926809683, "groupId": 1, "groupMsg": "go to study c++"}

{"msgType": 13, "fromId": 23, "fromName": "tom", "fromTimestamp": 1748926809383, "groupId": 1, "groupMsg": "go to study rust"}
```

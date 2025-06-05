## 集群聊天服务器

### 项目说明

- 基于 C++ 开发集群聊天服务器

### 项目运行

- 1. 启动 MySQL、Nginx、Redis 服务

- 2. 启动集群聊天服务端程序
    - 第一个聊天服务端程序：`chat_server 127.0.0.1 6000`
    - 第二个聊天服务端程序：`chat_server 127.0.0.1 6002`

- 3. 启动集群聊天客户端程序
    - 第一个聊天客户端程序：`chat_client 127.0.0.1 8000`，连接 Nginx 的 TCP 负载均衡器
    - 第二个聊天客户端程序：`chat_client 127.0.0.1 8000`，连接 Nginx 的 TCP 负载均衡器

### 接口测试

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

## 业务优化

- 添加好友
    - 添加好友之前，判断好友是否真实存在
    - 添加好友之前，判断好友是否已经添加过

- 加入群组
    - 用户加入群组之前，判断群组是否真实存在
    - 用户加入群组之前，判断群组是否已经加入过

- 一对一聊天
    - 一对一聊天之前，判断是否已经添加对方为好友

- 用户交互
    - 在发送一对一聊天消息、群聊消息、添加好友消息后，需要返回服务端的处理结果给客户端，最终效果类似登录 / 注册业务一样

## 集群聊天服务器

### 项目说明

- 基于 C++ 开发集群聊天服务器

### 接口测试

- 用户注册

``` json
{"msgType": 3, "name": "jim", "password": "123456"}

{"msgType": 3, "name": "tom", "password": "123456"}
```

- 用户登录

``` json
{"msgType": 1, "name": "jim", "password": "123456"}

{"msgType": 1, "name": "tom", "password": "123456"}
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

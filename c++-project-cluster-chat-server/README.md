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
{"msgType": 1, "id": 22, "password": "123456"}

{"msgType": 1, "id": 23, "password": "123456"}
```

- 一对一聊天

``` json
{"msgType": 5, "fromId": 22, "fromMsg": "hello", "toId": 23}

{"msgType": 5, "fromId": 23, "fromMsg": "hello", "toId": 22}
```

- 添加好友

``` json
{"msgType": 6, "friendid": 23}

{"msgType": 6, "friendid": 22}
```

- 创建群组

``` json
{"msgType": 8, "groupname": "c++", "groupdesc": "c++ study"}
```

- 加入群组

``` json
{"msgType": 10, "groupid": 1}
```

- 发送群聊消息

``` json
{"msgType": 12, "groupid": 1, "groupmsg": "go to study c++"}
```

## 业务优化

- 添加好友
    - 添加好友之前，判断好友是否已经添加过

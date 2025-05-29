## 集群聊天服务器

### 项目说明

- 基于 C++ 开发集群聊天服务器

### 接口测试

- 用户注册

``` json
{"msgType": 3, "name": "jim", "password": "123456"}
```

- 用户登录

``` json
{"msgType": 1, "id": 22, "password": "123456"}
```

- 一对一聊天

``` json
{"msgType": 5, "fromId": 22, "fromName": "jim", "fromMsg": "hello", "toId": 24}

{"msgType": 5, "fromId": 24, "fromName": "peter", "fromMsg": "hello", "toId": 22}
```

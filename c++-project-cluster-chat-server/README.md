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

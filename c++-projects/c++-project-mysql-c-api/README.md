## C++ 使用 MySQL C API 连接 MySQL

### 博客地址

- [C++ 使用 MySQL C API 连接 MySQL](https://techgrow.cn/posts/c9e38d0.html)

### 开发工具

| 软件                       | 版本        | 说明                                                        |
| -------------------------- | ----------- | ----------------------------------------------------------- |
| C++                        | `11`        |                                                             |
| MySQL C API（Connector/C） | `8.4.5`     |                                                             |
| MySQL Server               | `8.4.5`     |                                                             |
| Linux System               | `Debian 12` | MySQL C API（Connector/C）同时适用于 Linux 和 Windows 系统 |

### 项目编译

> 注意：在编译项目之前，请务必在本地 Linux 操作系统中安装好 MySQL C API（Connector/C）库，否则项目编译会失败。

``` sh
# 进入项目根目录
cd c++-project-mysql-c-api

# 脚本文件授权执行
chmod +x autobuild.sh

# 执行一键编译构建脚本
./autobuild.sh
```

### 项目运行

``` sh
# 运行可执行文件
./bin/mysql_c_api_test
```

# 基于 C++ 手写 Muduo 高性能网络库

## 博客教程

- [基于 C++ 手写 Muduo 高性能网络库](https://www.techgrow.cn/posts/dbb10768.html)

## 项目介绍

基于 C++ 开发一个类似 [Muduo](https://github.com/chenshuo/muduo) 的高性能网络库，项目代码大部分是从 Muduo 移值过来，同时去掉 Boost 依赖，并使用 C++ 11 进行代码重构，重点是学习 Muduo 的底层设计思想。

### 项目结构

| 目录名称          | 目录说明                                                            |
| ----------------- | ------------------------------------------------------------------- |
| `build`           | CMake 编译构建项目的目录（项目首次编译后才会有）                    |
| `bin`             | 存放项目编译生成的可执行文件的目录（项目首次编译后才会有）          |
| `lib`             | 存放项目编译生成的 MyMuduo 动态链接库的目录（项目首次编译后才会有） |
| `src`             | MyMuduo 网络框架的源码                                              |
| `test`            | MyMuduo 网络框架的的测试代码                                        |
| `example`         | 各种案例代码                                                          |
| `example/epoll`   | epoll 的使用案例代码                                                |
| `example/mymuduo` | MyMuduo 网络框架的使用案例代码                                      |
| `autobuild.sh`    | 项目一键编译构建的脚本文件                                          |

### 项目技术栈

- 单例设计模式
- epoll 等 I/O 多路复用技术
- Linux 网络编程基础（`socket`、`bind`、`listen`、`accept` 等）
- C++ 11 多线程编程（`std::thread`、`std::mutex`、`std::condition_variable` 等）
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

# 执行自动构建脚本
./autobuild.sh
```

## 项目测试

``` sh
# 进入项目根目录
cd c++-project-mymuduo

# 执行 MyMuduo 网络框架使用案例的可执行文件
./bin/mymuduo_example

# 执行 telnet 命令连接 TCP 服务器（成功连接后，输入任意字符，按回车键即可发送消息给服务器）
telnet 127.0.0.1 6000
```

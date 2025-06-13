## 章节概览

- 第一部分学习内容

```
C++ 从基础到进阶（王建伟 - 80 集）
└── day01
    ├── demo01          C++ 语言课程详细介绍
    ├── demo02          语言特性、工程构成、可移植性
    ├── demo03          auto、头文件防卫、引用、常量
    ├── demo04          命名空间简介、基本输入输出精解
    ├── demo05          范围for、new内存动态分配、nullptr
```

## 常用命令

### Linux 编译与运行

``` shell
# 编译（可同时指定多个".cpp"文件，不需要指定".h"文件）
$ g++ helloworld.cpp -o helloworld

# 运行
$ ./helloworld
```

### Windows 编译与运行

在 Windows 系统的开始菜单栏里，找到 `Developer Command Prompt for VS 2019` 应用程序，双击运行后，在 `Command` 窗口内执行以下命令来编译 C++ 源文件：

```
# 编译（可同时指定多个".cpp"文件，不需要指定".h"文件）
> cl helloworld.cpp /EHsc

# 运行
> helloworld
```

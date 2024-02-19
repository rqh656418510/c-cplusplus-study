## 章节概览

```
└── day01
    ├── demo01          第一个 C++ 程序
    ├── demo02          双冒号作用域限定运算符
    ├── demo03          命名空间的使用
    ├── demo04          using 声明与 using 编译指令
    ├── demo05          const 关键字增强
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

## 章节概览

```
└── day01
    ├── demo01          从编译器角度理解C++代码的编译和链接原理
    ├── demo02          从指令角度掌握函数调用堆栈详细过程
    ├── demo03          掌握进程虚拟地址空间区域划分
    ├── demo04          const、指针、引用的结合使用
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

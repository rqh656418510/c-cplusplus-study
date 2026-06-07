## 章节概览

- 第一部分学习内容

```
C++ 从基础到进阶（王建伟 - 80 集）
└── day01
    ├── demo01          auto、头文件防卫、引用、常量
    ├── demo02          命名空间简介、基本输入输出精解
    ├── demo03          范围for、new内存动态分配、nullptr
    ├── demo04          结构体、权限修饰符、类简介
    ├── demo05          函数新特性、内联函数、const详解
    ├── demo06          string类型介绍
    ├── demo07          vector类型介绍
    ├── demo08          迭代器精彩演绎，失效分析及弥补、实战
    ├── demo09          类型转换：static_cast等
└── day02
    ├── demo01          成员函数、对象拷贝、私有成员
    ├── demo02          构造函数详解，explicit，初始化列表
    ├── demo03          inline、const、mutable、this、static
    ├── demo04          类内初始化、默认构造函数、=default
    ├── demo05          拷贝构造函数
    ├── demo06          重载运算符、析构函数
    ├── demo07          派生类、调用顺序、访问等级、函数遮蔽
    ├── demo08          基类指针、虚函数、纯虚函数、多态性、虚析构
    ├── demo09          友元函数、友元类、友元成员函数
    ├── demo10          RTTI、dynamic_cast、typeid、虚函数表
    ├── demo11          基类与派生类关系的详细再探讨
└── day03
    ├── demo01          左值、右值、左值引用、右值引用、move
    ├── demo02          临时对象深入探讨、解析，提高性能手段
    ├── demo03          对象移动、移动构造函数、移动赋值运算符
    ├── demo04          继承的构造函数、多重继承、虚继承
    ├── demo05          类型转换构造函数、类型转换运算符
    ├── demo06          类成员指针使用
    ├── demo07          模板概念，函数模板定义、调用
    ├── demo08          类模板概念，类模板定义、使用
    ├── demo09          typename场合、默认模板参数、趣味写法分析
    ├── demo10          成员函数模板，显式实例化、声明
    ├── demo11          using定义别名模板，显式指定模板参数
    ├── demo12          模板全特化、偏特化(局部特化)
    ├── demo13          可变参模板
    ├── demo14          可变参模板****续、模板模板参数
└── day04
    ├── demo01          直接内存管理(new-delete)、观察内存泄漏
    ├── demo02          new、delete探秘，智能指针概述、shared_ptr
    ├── demo03          shared_ptr常用操作、计数、自定义删除器等等
    ├── demo04          weak_ptr概述、weak_ptr常用操作、尺寸
    ├── demo05          shared_ptr使用场景、陷阱、性能分析、使用建议
    ├── demo06          unique_ptr概述、常用操作
    ├── demo07          返回unique_ptr、删除器、尺寸、智能指针
└── day05
    ├── demo01          并发基本概念及实现，进程、线程基本概念
    ├── demo02          线程启动、结束，创建线程多法、join，detach
    ├── demo03          线程传参详解，detach()大坑，成员函数做线程函数
```

## 常用命令

### Linux 单个源文件编译与运行

``` shell
# 编译（可同时指定多个".cpp"文件，不需要指定".h"文件）
$ g++ helloworld.cpp -o helloworld

# 运行
$ ./helloworld
```

### Windows 单个源文件编译与运行

在 Windows 系统的开始菜单栏里，找到 `Developer Command Prompt for VS 2019` 应用程序，双击运行后，在 `Command` 窗口内执行以下命令来编译 C++ 源文件：

```
# 编译（可同时指定多个".cpp"文件，不需要指定".h"文件）
> cl helloworld.cpp /EHsc

# 运行
> helloworld
```

## 章节概览

```
C++ 开发工程师基础进阶课程 - 夯实 C++ 基础核心内容（施磊 - 55集）
└── day01
    ├── demo01          从编译器角度理解C++代码的编译和链接原理
    ├── demo02          从指令角度掌握函数调用堆栈详细过程
    ├── demo03          掌握进程虚拟地址空间区域划分
    ├── demo04          const、指针、引用的结合使用
    ├── demo05          全面掌握const的用法
    ├── demo06          深入理解C++的new和delete
    ├── demo07          掌握const和一二级指针的结合应用
    ├── demo08          掌握C++的左值引用和初识右值引用
    ├── demo09          掌握形参带默认值的函数
    ├── demo10          掌握inline内联函数
    ├── demo11          详解函数重载
└── day02
    ├── demo01          类和对象、this指针
    ├── demo02          指向类成员的指针
    ├── demo03          掌握构造函数和析构函数
    ├── demo04          掌握对象的深拷贝和浅拷贝
    ├── demo05          掌握构造函数的初始化列表
    ├── demo06          类和对象代码应用实践
    ├── demo07          掌握类的各种成员方法以及区别
└── day03
    ├── demo01          理解函数模板
    ├── demo02          理解类模板
    ├── demo03          实现C++ STL向量容器vector代码
    ├── demo04          理解容器空间配置器allocator的重要性
└── day04
    ├── demo01          学习复数类CComplex
    ├── demo02          模拟实现C++的string类代码
    ├── demo03          string字符串对象的迭代器iterator实现
    ├── demo04          vector容器的迭代器iterator实现
    ├── demo05          什么是容器的迭代器失效问题
    ├── demo06          深入理解new的delete的原理
    ├── demo07          重载new和delete运算符来实现对象池
└── day05
    ├── demo01          继承的基本意义
    ├── demo02          派生类的构造过程
    ├── demo03          重载、重写、隐藏
    ├── demo04          虚函数、静态绑定和动态绑定
    ├── demo05          再谈动态绑定
    ├── demo06          虚析构函数
    ├── demo07          理解多态到底是什么
    ├── demo08          理解抽象类
    ├── demo09          继承多态笔试题实战分析
└── day06
    ├── demo01          理解虚基类和虚继承
    ├── demo02          菱形继承的问题
    ├── demo03          C++的四种类型转换
└── day07
    ├── demo01          vector容器
    ├── demo02          无序关联容器
    ├── demo03          有序关联容器
    ├── demo04          详解容器适配器
    ├── demo05          迭代器iterator
    ├── demo06          函数对象
    ├── demo07          泛型算法和绑定器
└── day08
    ├── demo01          大厂C++开发工程师面试问题讲解
```

```
C++ 开发工程师高级进阶课程 - 提升 C++ 面试和开发能力（施磊 - 56集）
└── day09
    ├── demo01          CMyString的代码问题
    ├── demo02          添加带右值引用参数的拷贝构造和赋值函数
    ├── demo03          CMyString在vector上的应用          
    ├── demo04          move移动语义和forward类型完美转发
    ├── demo05          对象使用过程中背后调用了哪些方法
    ├── demo06          函数调用过程中对象背后调用的方法太多
    ├── demo07          总结三条对象优化的规则
└── day10
    ├── demo01          智能指针基础知识
    ├── demo02          不带引用计数的智能指针
    ├── demo03          实现带引用计数的智能指针          
    ├── demo04          shared_ptr的交叉引用问题
    ├── demo05          多线程访问共享对象的线程安全问题
    ├── demo06          自定义删除器
└── day11
    ├── demo01          function函数对象类型的应用示例
    ├── demo02          function的实现原理
    ├── demo03          bind和function实现线程池
    ├── demo04          bind1st和bind2nd什么时候会用到
    ├── demo05          bind1st和bind2nd的底层实现原理
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

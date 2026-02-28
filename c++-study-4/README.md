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
```

## 常用命令

### Linux 编译与运行

``` shell
# 编译（可同时指定多个".cpp"文件，不需要指定".h"文件）
$ g++ helloworld.cpp -o helloworld

# 运行
$ ./**helloworld**
```

### Windows 编译与运行

在 Windows 系统的开始菜单栏里，找到 `Developer Command Prompt for VS 2019` 应用程序，双击运行后，在 `Command` 窗口内执行以下命令来编译 C++ 源文件：

```
# 编译（可同时指定多个".cpp"文件，不需要指定".h"文件）
> cl helloworld.cpp /EHsc

# 运行
> helloworld
```

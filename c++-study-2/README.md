## 章节概览

```
└── day01
    ├── demo01          第一个 C++ 程序
    ├── demo02          双冒号作用域限定运算符
    ├── demo03          命名空间的使用
    ├── demo04          using 声明与 using 编译指令的使用
    ├── demo05          C++ 对 const 关键字的增强
    ├── demo06          C++ 中的引用
    ├── demo07          C++ 中对数组建立引用
    ├── demo08          C++ 中引用作函数参数
    ├── demo09          C++ 中引用的注意事项
    ├── demo10          C++ 中引用的本质
    ├── demo11          C++ 中的指针引用
    ├── demo12          C++ 中的常量引用
└── day02
    ├── demo01          作业案例-设计圆类
    ├── demo02          作业案例-设计学生类
    ├── demo03          内联函数的使用
    ├── demo04          函数默认参数与函数占位参数
    ├── demo05          函数重载
    ├── demo06          extern 关键字浅析
    ├── demo07          C 语言封装与 C++ 封装的区别
└── day03
    ├── demo01          面向对象设计案例 - 设计立方体类
    ├── demo02          面向对象设计案例 - 点和圆的关系
    ├── demo03          构造函数和析构函数的使用
    ├── demo04          构造函数的分类及调用
    ├── demo05          拷贝构造函数的调用时机
    ├── demo06          构造函数的调用规则
    ├── demo07          深拷贝与浅拷贝
    ├── demo08          构造函数的初始化列表
    ├── demo09          类对象作为类成员的案例
    ├── demo10          explicit 关键字的作用
    ├── demo11          new 运算符的使用
└── day04
    ├── demo01          静态成员变量
    ├── demo02          静态成员函数
    ├── demo03          单例模式使用案例之一
    ├── demo04          单例模式使用案例之二
    ├── demo05          成员变量和成员属性分开处理
    ├── demo06          this 指针的使用
    ├── demo07          空指针访问成员函数
    ├── demo08          常函数与常对象的使用
    ├── demo09          全局函数作为友元函数
    ├── demo10          类模板的分文件编写的问题以及解决方案
    ├── demo11          整个类作为友元类
    ├── demo12          成员函数作为友元函数
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

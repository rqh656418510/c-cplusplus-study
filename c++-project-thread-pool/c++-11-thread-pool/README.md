## 手写线程池项目

基于 C++ 11 手写一个线程池，并自行实现 `make_unique()`、`any` 类型、信号量类型。

### 博客教程

- [基于 C++ 手写线程池](https://www.techgrow.cn/posts/585aa296.html)

### 编译动态链接库

> 使用的 `g++` 版本是 `4.8.5`，CMake 版本是 `3.27.7`；若版本过低，可能会出现线程池代码编译失败的问题

#### CMake 编译

- 项目的编译构建

``` sh
# 进入项目的源码根目录
cd c++-11-thread-pool

# 编译生成动态链接库和可执行测试程序
cmake -S . -B build && cmake --build build
```

- 动态链接库的安装（可选），如果不安装，第三方程序在运行时可能会遇到找不到动态链接库的问题

``` sh
# 进入项目的源码根目录
cd c++-11-thread-pool

# 将头文件和编译生成的动态链接库安装到系统中
sudo cmake --install build

# 创建系统的动态链接库配置文件
sudo echo "/usr/local/lib" > /etc/ld.so.conf.d/custom.conf

# 重载系统的动态链接库配置
sudo ldconfig
```

#### G++ 编译

- 项目的编译构建

``` sh
# 进入项目的源码根目录
cd c++-11-thread-pool

# 编译生成动态链接库
g++ -fPIC -Iinclude -shared src/thread_pool.cpp -o libthread_pool.so -pthread -std=c++11

# 编译生成可执行测试程序
g++ -Iinclude src/thread_pool.cpp src/test.cpp -o thread_pool_test -pthread -std=c++11
```

- 动态链接库的安装（可选），如果不安装，第三方程序在运行时可能会遇到找不到动态链接库的问题

``` sh
# 进入项目的源码根目录
cd c++-11-thread-pool

# 将头文件安装到系统中
sudo cp ./include/* /usr/local/include

# 将编译生成的动态链接库安装到系统中
sudo cp libthread_pool.so /usr/local/lib

# 创建系统的动态链接库配置文件
sudo echo "/usr/local/lib" > /etc/ld.so.conf.d/custom.conf

# 重载系统的动态链接库配置
sudo ldconfig
```

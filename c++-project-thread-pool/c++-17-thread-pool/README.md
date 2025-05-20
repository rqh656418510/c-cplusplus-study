## 手写线程池项目

基于 C++ 17 手写一个线程池

### 博客教程

- [基于 C++ 手写线程池](https://www.techgrow.cn/posts/585aa296.html)

### 编译动态链接库

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
sudo mv ./include/* /usr/local/include

# 将编译生成的动态链接库安装到系统中
sudo mv libthread_pool.so /usr/local/lib

# 创建系统的动态链接库配置文件
sudo echo "/usr/local/lib" > /etc/ld.so.conf.d/custom.conf

# 重载系统的动态链接库配置
sudo ldconfig
```


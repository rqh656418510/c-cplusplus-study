## 手写线程池项目

基于 C++ 17 手写一个线程池，使用了可变参数模板、`make_unique()`、`packaged_task`、`future` 特性。

### 博客教程

- [基于 C++ 手写线程池](https://www.techgrow.cn/posts/585aa296.html)

### 编译构建

> 使用的 `g++` 版本是 `4.8.5`，CMake 版本是 `3.25.1`；若版本过低，可能会出现线程池代码编译失败的问题

#### CMake 编译

``` sh
# 进入项目的源码根目录
cd c++-17-thread-pool

# 编译生成可执行测试程序
cmake -S . -B build && cmake --build build

# 将头文件安装到系统中（可选）
sudo cmake --install build
```

#### G++ 编译

``` sh
# 进入项目的源码根目录
cd c++-17-thread-pool

# 编译生成可执行测试程序
g++ -Iinclude src/test.cpp -o thread_pool_test -pthread -std=c++17

# 将头文件安装到系统中（可选）
sudo cp ./include/* /usr/local/include
```

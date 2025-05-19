## 手写线程池项目

基于 C++ 11 手写一个线程池

### 博客教程

- [基于 C++ 手写线程池](https://www.techgrow.cn/posts/585aa296.html)

### 编译动态链接库

- 第一种方法：cmake 编译

``` sh
# 进入项目的源码根目录
cd c++-11-thread-pool

# 编译生成动态链接库和可执行测试程序
cmake -S . -B build && cmake --build build
```

- 第二种方法：g++ 编译

``` sh
# 进入项目的源码根目录
cd c++-11-thread-pool

# 编译生成动态链接库
g++ -fPIC -Iinclude -shared src/thread_pool.cpp -o libthread_pool.so -pthread -std=c++11

# 编译生成可执行测试程序
g++ -Iinclude src/thread_pool.cpp src/test.cpp -o thread_pool_test -pthread -std=c++11
```

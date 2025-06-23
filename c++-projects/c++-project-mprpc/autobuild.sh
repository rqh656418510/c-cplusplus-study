#!/bin/bash

set -x

# 配置项目，生成构建文件
cmake -S . -B build

# 编译项目，生成可执行文件
cmake --build build

# 拷贝 RPC 框架的头文件到 lib 目录下（提供给第三方调用 RPC 框架的静态库）
cp -rf `pwd`/src/include `pwd`/lib

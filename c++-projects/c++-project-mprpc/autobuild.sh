#!/bin/bash

set -x

# 清理 bin 输出目录下的所有文件
rm -rf `pwd`/bin/*

# 清理 lib 输出目录下的所有文件
rm -rf `pwd`/lib/*

# 清理 Protobuf 自动生成的源文件
rm -rf `pwd`/src/generated/*
rm -rf `pwd`/example/generated/*
rm -rf `pwd`/test/protobuf/generated/*

# 配置项目，生成构建文件
cmake -S . -B build

# 编译项目，生成可执行文件
cmake --build build

# 拷贝 RPC 框架的头文件到 lib 目录下（提供给第三方调用 RPC 框架的静态库）
cp -rf `pwd`/src/include `pwd`/lib

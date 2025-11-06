#!/bin/bash

set -x

# 清理 bin 输出目录下的所有文件
rm -rf `pwd`/bin/*

# 清理 lib 输出目录下的所有文件
rm -rf `pwd`/lib/*

# 配置项目，生成构建文件
cmake -S . -B build

# 编译项目，生成可执行文件
cmake --build build

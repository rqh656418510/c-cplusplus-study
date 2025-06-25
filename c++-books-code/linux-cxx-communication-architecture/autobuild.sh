#!/bin/bash

set -x

# 清理 bin 目录
rm -rf `pwd`/bin/*

# 生成构建文件
cmake -S . -B build

# 执行编译构建
cmake --build build

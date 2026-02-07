#!/bin/bash

set -x

# 清理编译生成的文件
rm -rf `pwd`/bin/*
rm -rf `pwd`/build/*

# 配置项目，生成构建文件
cmake -S . -B build

# 编译项目，生成可执行文件
cmake --build build

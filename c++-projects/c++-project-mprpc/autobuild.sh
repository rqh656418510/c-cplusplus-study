#!/bin/bash

set -x

# 配置项目，生成构建文件
cmake -S . -B build

# 编译项目，生成可执行文件
cmake --build build

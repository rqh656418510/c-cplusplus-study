#!/bin/bash

# 获取脚本所在目录的绝对路径
SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
PROJECT_ROOT="${SCRIPT_DIR}/.."

# 配置项目，生成构建文件（例如 Makefile 或 Ninja 文件）
cmake -S "${PROJECT_ROOT}" -B "${PROJECT_ROOT}/build"

# 编译项目，生成可执行文件
cmake --build "${PROJECT_ROOT}/build"

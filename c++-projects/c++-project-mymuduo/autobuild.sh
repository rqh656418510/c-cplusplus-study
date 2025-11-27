#!/bin/bash

set -x

TARGET_LIB_DIR=/usr/lib/
TARGET_HEAD_DIR=/usr/include/mymuduo/

# 清理 bin 输出目录下的所有文件
rm -rf `pwd`/bin/*

# 清理 lib 输出目录下的所有文件
rm -rf `pwd`/lib/*

# 配置项目，生成构建文件
cmake -S . -B build

# 编译项目，生成可执行文件
cmake --build build

# 创建存放头文件的系统目录
if [ ! -d $TARGET_HEAD_DIR ]; then 
    mkdir -p $TARGET_HEAD_DIR
fi

# 拷贝头文件到系统目录
cp `pwd`/src/include/*.h $TARGET_HEAD_DIR

# 拷贝动态库到系统目录
cp `pwd`/lib/libmymuduo.so $TARGET_LIB_DIR

# 更新系统缓存
ldconfig

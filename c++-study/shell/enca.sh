#!/bin/bash

########################################################################
#####             批量将项目里所有文件的字符集编码转换为UTF-8
#####       此脚本必须在项目的 shell 目录下执行，建议使用普通用户的权限
########################################################################

# 判断 enca 工具是否已安装
if ! hash enca 2>/dev/null; then
  echo "enca not found"
  exit 0
fi

# 进入项目的根目录
cd ..

# 转换字符集编码为UTF-8
find . -type f -iname "*.h" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.c" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.sh" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.md" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.sql" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.ini" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.txt" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.log" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.dtd" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.xml" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.cpp" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname "*.json" | xargs enca -L zh_CN -x UTF-8
find . -type f -iname ".gitignore" | xargs enca -L zh_CN -x UTF-8
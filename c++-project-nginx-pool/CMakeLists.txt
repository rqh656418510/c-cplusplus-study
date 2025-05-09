cmake_minimum_required(VERSION 3.15)

project(Nginx_Pool)

# C++ 版本
set(CMAKE_CXX_STANDARD 11)

# 构建模式
set(CMAKE_BUILD_TYPE Debug)

# 指定源文件
file(GLOB SRC_FILES src/*.cpp)

# 编译并链接
add_executable(Nginx_Pool ${SRC_FILES})

# 引入头文件
target_include_directories(Nginx_Pool PRIVATE ${CMAKE_SOURCE_DIR}/include)
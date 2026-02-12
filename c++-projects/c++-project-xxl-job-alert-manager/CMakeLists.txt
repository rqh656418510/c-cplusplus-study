# 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.15)

# 指定项目名称
project(alert-manager)

# 指定C++版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定构建模式（Debug模式可用于GDB调试程序）
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 指定可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 指定系统的头文件，如 MySQL C API 的头文件
include_directories(
    /usr/include
    /usr/local/include
)

# 指定项目中的核心头文件
include_directories(
    ${CMAKE_SOURCE_DIR}/third_party/json
    ${CMAKE_SOURCE_DIR}/include/base
    ${CMAKE_SOURCE_DIR}/include/net
    ${CMAKE_SOURCE_DIR}/include/config
    ${CMAKE_SOURCE_DIR}/include/db
    ${CMAKE_SOURCE_DIR}/include/alert
    ${CMAKE_SOURCE_DIR}/include/job
)

# 加载 CMake 子目录
add_subdirectory(src)
add_subdirectory(test)

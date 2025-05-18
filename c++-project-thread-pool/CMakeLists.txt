cmake_minimum_required(VERSION 3.15)

project(Thread_Pool)

# C++ 版本
set(CMAKE_CXX_STANDARD 14)

# 构建模式
set(CMAKE_BUILD_TYPE Debug)

# 指定源文件
file(GLOB SRC_FILES src/*.cpp)

# 编译并链接
add_executable(Thread_Pool ${SRC_FILES})

# 引入头文件
target_include_directories(Thread_Pool PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 添加链接标志
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(Thread_Pool PRIVATE pthread)
endif ()

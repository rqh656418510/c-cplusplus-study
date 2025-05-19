cmake_minimum_required(VERSION 3.15)

project(CXX_17_Thread_Pool)

# C++ 版本
set(CMAKE_CXX_STANDARD 17)

# 构建模式
set(CMAKE_BUILD_TYPE Debug)

# 指定源文件
file(GLOB SRC_FILES src/*.cpp)

# 编译并链接
add_executable(CXX_17_Thread_Pool ${SRC_FILES})

# 引入头文件
target_include_directories(CXX_17_Thread_Pool PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 添加链接标志
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(CXX_17_Thread_Pool PRIVATE pthread)
endif ()

cmake_minimum_required(VERSION 3.15)

project(SGI_STL_Allocator)

# C++ 版本
set(CMAKE_CXX_STANDARD 11)

# 构建模式
set(CMAKE_BUILD_TYPE Debug)

# 指定源文件
file(GLOB SRC_FILES src/*.cpp)

# 编译生成可执行测试程序
add_executable(SGI_STL_Allocator_Test ${SRC_FILES})

# 引入头文件
target_include_directories(SGI_STL_Allocator_Test PRIVATE ${CMAKE_SOURCE_DIR}/include)

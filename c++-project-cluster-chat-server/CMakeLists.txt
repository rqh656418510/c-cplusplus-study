cmake_minimum_required(VERSION 3.15)

project(cluster_chat_server)

# C++ 版本
set(CMAKE_CXX_STANDARD 11)

# 构建模式
set(CMAKE_BUILD_TYPE Debug)

# 指定源文件
file(GLOB SRC_FILES src/*.cpp)

# 编译生成可执行测试文件
add_executable(${PROJECT_NAME}_test ${SRC_FILES})

# 引入头文件
target_include_directories(${PROJECT_NAME}_test PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/thirdparty)

cmake_minimum_required(VERSION 3.15)

project(cluster_chat_server)

# C++ 版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 构建模式
set(CMAKE_BUILD_TYPE Debug)

# 指定项目源文件
file(GLOB SRC_FILES src/*.cpp)

# 编译生成可执行测试文件
add_executable(${PROJECT_NAME}_test ${SRC_FILES})

# 指定头文件
target_include_directories(${PROJECT_NAME}_test
    PRIVATE
    # 项目的头文件
    ${CMAKE_SOURCE_DIR}/include
    # 项目的第三方头文件
    ${CMAKE_SOURCE_DIR}/thirdparty
    # 系统的头文件，如 Muduo 头文件
    /usr/local/include
)

# 链接依赖的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(${PROJECT_NAME}_test
    muduo_net
    muduo_http
    muduo_inspect
    muduo_base
    pthread
)
# 指定CMake最低版本
cmake_minimum_required(VERSION 3.15)

# 指定项目名称
project(cluster_chat_server)

# 指定C++版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定构建模式（Debug模式可用于GDB调试程序）
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 指定可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 指定项目源文件
file(GLOB SRC_FILES src/*.cpp)

# 指定编译生成可执行测试文件
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

# 指定可执行测试文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(${PROJECT_NAME}_test
    muduo_net
    muduo_http
    muduo_inspect
    muduo_base
    pthread
)

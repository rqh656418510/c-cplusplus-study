# 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.15)

# 指定项目名称
project(cluster_chat)

# 指定C++版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定构建模式（Debug模式可用于GDB调试程序）
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 指定可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 指定项目的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/public)
include_directories(${PROJECT_SOURCE_DIR}/include/client)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/dao)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)

# 指定项目的第三方头文件
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

# 指定系统的头文件，如 Muduo 头文件
include_directories(/usr/local/include)

# 指定 MySQL 的静态或动态库
link_directories(/usr/lib/x86_64-linux-gnu)

# 加载 CMake 子目录
add_subdirectory(src)

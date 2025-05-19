cmake_minimum_required(VERSION 3.15)

# 项目名称和语言
project(thread_pool VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 版本
set(CMAKE_CXX_STANDARD 11)

# 设置构建模式
set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)

# 设置头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 设置源文件
file(GLOB SRC_FILES src/*.cpp)

# 编译生成动态链接库
add_library(thread_pool SHARED ${SRC_FILES})

# 设置动态链接库的文件名称
set_target_properties(thread_pool PROPERTIES
        OUTPUT_NAME "thread_pool"
        PREFIX "lib"
        SUFFIX ".so"
        POSITION_INDEPENDENT_CODE ON
)

# 设置动态链接库的链接标志
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(thread_pool PRIVATE pthread)
endif ()

# 编译生成可执行测试程序
add_executable(thread_pool_test ${SRC_FILES})

# 设置可执行测试程序的链接标志
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(thread_pool_test PRIVATE pthread)
endif ()

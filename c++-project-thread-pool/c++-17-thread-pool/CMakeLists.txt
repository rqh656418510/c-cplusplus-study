cmake_minimum_required(VERSION 3.15)

# 项目名称和语言
project(cxx_17_thread_pool VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 版本
set(CMAKE_CXX_STANDARD 17)

# 设置构建模式
set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)

# 设置头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 设置源文件
file(GLOB SRC_FILES src/*.cpp)

# 编译生成可执行测试程序
add_executable(thread_pool_test ${SRC_FILES})

# 设置可执行测试程序的链接标志
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(thread_pool_test PRIVATE pthread)
endif ()

# 设置默认的安装前缀路径
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install path prefix." FORCE)
endif()

# 将头文件安装到指定位置（可选）
install(DIRECTORY include/ DESTINATION include)

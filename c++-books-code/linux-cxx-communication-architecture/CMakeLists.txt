# 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.15)

# 指定项目名称
project(linux_cxx_commu_arch)

# 指定 C++ 版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定构建模式（Debug模式可用于GDB调试程序）
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 指定项目可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 指定项目头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

# 指定项目源文件
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 编译生成可执行文件
add_executable(linux_cxx_commu_arch ${SRC_FILES})

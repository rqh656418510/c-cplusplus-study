# 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.15)

# 指定项目名称
project(mprpc)

# 指定 C++ 版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定构建模式（Debug模式可用于GDB调试程序）
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 指定项目库文件的输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 指定项目可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 指定系统的头文件，如 Muduo、Protobuf 头文件
include_directories(/usr/local/include)

# 指定项目头文件
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# 查找并加载 Protobuf 动态库
find_package(Protobuf REQUIRED)

# 打印 Protobuf 信息
message(STATUS "Using Protobuf ${Protobuf_VERSION}")
message(STATUS "Protobuf include dir: ${Protobuf_INCLUDE_DIRS}")
message(STATUS "Protobuf libraries: ${Protobuf_LIBRARIES}")

# 链接 Protobuf 动态库
link_directories(${Protobuf_LIBRARIES})

# 加载 CMake 子目录
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)

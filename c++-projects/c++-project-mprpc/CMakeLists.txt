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
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# 指定项目可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 每次编译之后清理可执行文件的输出目录
add_custom_target(clean_bin ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${EXECUTABLE_OUTPUT_PATH}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${EXECUTABLE_OUTPUT_PATH}
    COMMENT "Cleaning bin directory"
)

# 每次编译之后拷贝所有配置文件到可执行文件的输出目录
add_custom_command(
    TARGET clean_bin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/conf
    ${EXECUTABLE_OUTPUT_PATH}
    COMMENT "Copying config files to bin directory"
)

# 指定系统的头文件，如 ZooKeeper、Muduo、Protobuf 头文件
include_directories(/usr/include)
include_directories(/usr/local/include)

# 指定项目头文件
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# 加载 CMake 子目录
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)

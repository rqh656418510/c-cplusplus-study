# 指定项目名称，并设定使用 C 语言
project(linux_c_comm_arch C)

# 指定 C 标准版本
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 指定构建模式（如 Debug 模式）
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

# 指定可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 查找源文件（递归查找 .c 文件）
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

# 编译生成可执行文件
add_executable(linux_c_comm_arch ${SRC_FILES})

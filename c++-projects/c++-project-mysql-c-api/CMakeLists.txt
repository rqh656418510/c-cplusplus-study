# 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.15)

# 指定项目名称
project(mysql_c_api_test)

# 指定C++版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定构建模式（Debug模式可用于GDB调试程序）
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 指定可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 指定项目中的源文件
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# 指定编译生成可执行文件
add_executable(mysql_c_api_test ${SRC_FILES})

# 指定项目中的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

# 指定系统的头文件，如 MySQL C API 的头文件
include_directories(/usr/local/include)

# 搜索 MySQL C API 的静态库或动态库
find_library(MYSQL_LIBRARY
    NAMES mysqlclient
    PATHS /usr/lib /usr/local/lib /usr/lib64/mysql /usr/lib/x86_64-linux-gnu
    REQUIRED
)

# 指定可执行文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(mysql_c_api_test PRIVATE
    ${MYSQL_LIBRARY}
)
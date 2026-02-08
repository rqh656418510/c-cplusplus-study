# 定义 CMake 的版本
cmake_minimum_required(VERSION 3.15)

# 定义项目信息
project(db_connection_pool)

# 定义 C++ 的版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定构建输出的目录
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Boost 库的选择开关
option(USE_CUSTOM_BOOST "Use custom compiled Boost" OFF)

# 指定 Boost 库
set(CUSTOM_BOOST_ROOT "/usr/local/boost" CACHE PATH "Custom Boost install by root")
if (USE_CUSTOM_BOOST)
    message(STATUS "Using custom Boost from: ${CUSTOM_BOOST_ROOT}")
    set(Boost_ROOT ${CUSTOM_BOOST_ROOT})
    set(Boost_NO_SYSTEM_PATHS ON)
else()
    message(STATUS "Using system Boost")
endif()

# 指定 MySQL Connector 库
set(PATH_TO_MYSQL_CONNECTOR ${PROJECT_SOURCE_DIR}/libs/mysql-connector)
include_directories(${PATH_TO_MYSQL_CONNECTOR}/include)
link_directories(${PATH_TO_MYSQL_CONNECTOR}/lib)

# 查找第三方库
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

# 引入项目里的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

# 搜索项目里的源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src MAIN_SOURCES)

# 指定可执行文件
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

# 链接项目里的静态库或动态链接库
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Boost::filesystem
        Boost::system
        Threads::Threads
        OpenSSL::SSL
        OpenSSL::Crypto
        mysqlcppconn
)

# 构建前清理 bin 目录
add_custom_target(clean_bin ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${EXECUTABLE_OUTPUT_PATH}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${EXECUTABLE_OUTPUT_PATH}
    COMMENT "Cleaning bin directory before build"
)

# 构建后拷贝 MySQL 配置文件
add_custom_command(
    TARGET clean_bin
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/config/mysql.ini
            ${EXECUTABLE_OUTPUT_PATH}/mysql.ini
    COMMENT "Copying mysql.ini to bin directory before build"
)
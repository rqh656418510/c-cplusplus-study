# 定义 CMake 的版本
cmake_minimum_required(VERSION 3.15)

# 定义第三方库的目录路径
set(PATH_TO_BOOST /usr/local/boost)
set(PATH_TO_MYSQL_CONNECTOR ./libs/mysql-connector)

# 定义项目信息
project(db_connection_pool)

# 定义 C++ 的版本
set(CMAKE_CXX_STANDARD 11)

# 指定构建输出的目录
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

# 指定可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 自定义目标，每次编译之前清理可执行文件的输出目录
add_custom_target(clean_bin ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${EXECUTABLE_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${EXECUTABLE_OUTPUT_PATH}
        COMMENT "Cleaning bin directory before build"
        )

# 自定义命令，每次编译之前拷贝 MySQL 配置文件到可执行文件的输出目录
add_custom_command(
        TARGET clean_bin
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config/mysql.ini
        ${EXECUTABLE_OUTPUT_PATH}/mysql.ini
        COMMENT "Copying mysql.ini to bin directory before build"
)

# 引入项目里的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

# 搜索项目里的源文件，并将文件名保存到 MAIN_SOURCES 变量
aux_source_directory(${PROJECT_SOURCE_DIR}/src MAIN_SOURCES)

# 引入第三方库的头文件
include_directories(${PATH_TO_BOOST}/include ${PATH_TO_MYSQL_CONNECTOR}/include)

# 指定项目里静态库和动态链接库的目录
link_directories(${PATH_TO_BOOST}/lib ${PATH_TO_MYSQL_CONNECTOR}/lib)

# 指定可执行文件的名称和项目里的所有源文件
add_executable(${PROJECT_NAME}_test ${MAIN_SOURCES})

# 指定编译参数，比如包括链接库文件：pthread、ssl、crypto、boost
set(CMAKE_CXX_FLAGS "-lpthread -lssl -lcrypto -lboost_system -lboost_filesystem")

# 链接项目里的静态库和动态链接库
target_link_libraries(${PROJECT_NAME}_test ssl.so crypto.so mysqlcppconn.so)

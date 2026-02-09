# 指定项目源文件
file(GLOB_RECURSE SRC_FILES *.cpp)

# 搜索 OpenSSL
find_package(OpenSSL REQUIRED)

# 搜索 MySQL C API 的静态库或动态库
find_library(MYSQL_LIBRARY
    NAMES mysqlclient
    PATHS /usr/lib /usr/local/lib /usr/lib64/mysql /usr/lib/x86_64-linux-gnu
    REQUIRED
)

# 指定编译生成可执行文件
add_executable(xxl_job_alert_manager ${SRC_FILES})

# 每次编译之后拷贝所有配置文件到可执行文件的输出目录
add_custom_command(
    TARGET xxl_job_alert_manager
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/config
            ${EXECUTABLE_OUTPUT_PATH}
    COMMENT "Copying config files to bin directory after build"
)

# 指定可执行文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(xxl_job_alert_manager PRIVATE
    pthread
    OpenSSL::SSL 
    OpenSSL::Crypto
    ${MYSQL_LIBRARY}
)
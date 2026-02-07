# 指定项目源文件
file(GLOB_RECURSE TEST_SRC_FILES *.cpp)
file(GLOB_RECURSE MAIN_SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(FILTER MAIN_SRC_FILES EXCLUDE REGEX ".*main\\.cpp$")

# 搜索 OpenSSL
find_package(OpenSSL REQUIRED)

# 搜索 MySQL C API 的静态库或动态库
find_library(MYSQL_LIBRARY
    NAMES mysqlclient
    PATHS /usr/lib /usr/local/lib /usr/lib64/mysql /usr/lib/x86_64-linux-gnu
    REQUIRED
)

# 指定编译生成可执行文件
add_executable(xxl_job_alert_manager_test ${TEST_SRC_FILES} ${MAIN_SRC_FILES})

# 指定可执行文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(xxl_job_alert_manager_test PRIVATE
    pthread
    OpenSSL::SSL 
    OpenSSL::Crypto
    ${MYSQL_LIBRARY}
)
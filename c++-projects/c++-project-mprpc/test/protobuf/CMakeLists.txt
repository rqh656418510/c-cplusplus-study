# 指定项目名称
project(proto_test)

# 查找并加载 Protobuf 动态库
find_package(Protobuf REQUIRED)

# 创建存放 Protobuf 自动生成 C++ 源文件的目录
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/generated)

# 指定项目中的 .proto 文件
file(GLOB_RECURSE PROTO_FILES *.proto)

# 编译 .proto 文件，自动生成 C++ 源文件
add_custom_target(proto_test_build ALL
    COMMENT "Cleaning Protobuf C++ files"
    COMMAND rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/generated/*
    COMMENT "Generating Protobuf C++ files"
    COMMAND protoc
        --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/proto
        ${PROTO_FILES}
        --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/generated
)

# 指定项目头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/generated)

# 指定项目源文件
file(GLOB_RECURSE SRC_FILES *.cc)

# 编译生成可执行文件
add_executable(proto_test ${SRC_FILES})

# 保证先让 Protobuf 自动生成 C++ 源文件
add_dependencies(proto_test proto_test_build)

# 指定可执行文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(proto_test
    protobuf
    absl_hash
    absl_log_internal_check_op 
    absl_log_internal_message 
    absl_log_internal_nullguard
)

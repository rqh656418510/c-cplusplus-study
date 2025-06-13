# 指定项目的源文件
file(GLOB_RECURSE SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
    ${PROJECT_SOURCE_DIR}/src/*.cc
    ${PROJECT_SOURCE_DIR}/example/generated/*.cc
)

# 编译生成可执行文件
add_executable(example_rpc_consumer ${SRC_FILES})

# 指定可执行文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(example_rpc_consumer
    protobuf
    absl_hash
    absl_log_internal_check_op 
    absl_log_internal_message 
    absl_log_internal_nullguard
)

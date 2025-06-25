# 指定项目的源文件
file(GLOB_RECURSE SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
    ${CMAKE_SOURCE_DIR}/example/generated/*.cc
)

# 指定项目库文件的搜索路径
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 编译生成可执行文件
add_executable(example_rpc_consumer ${SRC_FILES})

# 指定可执行文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(example_rpc_consumer
    mprpc
    zookeeper_mt
    protobuf
    absl_hash
    absl_log_internal_check_op 
    absl_log_internal_message 
    absl_log_internal_nullguard
)

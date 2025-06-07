# 查找并加载 Protobuf 动态库
find_package(Protobuf REQUIRED)

# 创建存放 Protobuf 自动生成 C++ 源文件的目录
set(PROTO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated)
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

# 指定项目中的 .proto 文件
file(GLOB_RECURSE PROTO_FILES *.proto)

# 编译 .proto 文件，自动生成 C++ 源文件
execute_process(COMMAND protoc
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/proto
    --cpp_out=${PROTO_GEN_DIR}
    ${PROTO_FILES}
)

# 指定 Protobuf 自动生成的 C++ 头文件
include_directories(${PROTO_GEN_DIR})

# 指定项目头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 指定项目源文件
file(GLOB_RECURSE SRC_FILES *.cc)

# 指定编译生成静态库
add_library(mprpc STATIC ${SRC_FILES})

# 指定可执行文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(mprpc
    zookeeper_mt
    muduo_net
    muduo_base
    pthread
    protobuf
    absl_hash
    absl_log_internal_check_op 
    absl_log_internal_message 
    absl_log_internal_nullguard
)
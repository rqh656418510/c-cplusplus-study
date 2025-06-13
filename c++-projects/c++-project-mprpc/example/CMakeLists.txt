# 指定项目名称
project(example_rpc)

# 查找并加载 Protobuf 动态库
find_package(Protobuf REQUIRED)

# 创建存放 Protobuf 自动生成 C++ 源文件的目录
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/generated)

# 指定项目中的 .proto 文件
file(GLOB_RECURSE PROTO_FILES *.proto)

# 编译 .proto 文件，自动生成 C++ 源文件
add_custom_target(example_rpc_protobuf_build ALL
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

# 加载 CMake 子目录
add_subdirectory(callee)
add_subdirectory(caller)

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

# 加载 CMake 子目录
add_subdirectory(provider)
add_subdirectory(consumer)

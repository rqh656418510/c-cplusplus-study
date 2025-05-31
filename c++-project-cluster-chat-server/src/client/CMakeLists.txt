# 指定项目源文件
file(GLOB_RECURSE SRC_FILES *.cpp)

# 指定编译生成可执行文件
add_executable(cluster_chat_client ${SRC_FILES})

# 指定可执行文件链接的静态库或者动态库（必须注意顺序，从上到下链接）
target_link_libraries(cluster_chat_client
    pthread
)

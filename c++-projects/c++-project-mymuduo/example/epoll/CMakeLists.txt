# 指定项目源文件
file(GLOB_RECURSE SRC_FILES *.cc)

# 编译生成可执行文件
add_executable(epoll_example ${SRC_FILES})

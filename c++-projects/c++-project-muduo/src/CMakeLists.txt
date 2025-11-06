# 指定项目源文件
file(GLOB_RECURSE SRC_FILES *.cc)

# 指定编译生成动态库
add_library(mymuduo SHARED ${SRC_FILES})

# cmake_minimum_required(VERSION <specify CMake version here>)
project(c_study C)

set(CMAKE_C_STANDARD 99)

# day01
add_executable(day00-demo-01-hello day00/demo01/hello.c)
add_executable(day00-demo-02-data-type day00/demo02/data-type.c)
add_executable(day00-demo-02-data-type2 day00/demo02/data-type-2.c)
add_executable(day00-demo-02-data-type3 day00/demo02/data-type-3.c)
add_executable(day00-demo-03-program-desgin day00/demo03/program-desgin.c)
add_executable(day00-demo-04-branch-struct day00/demo04/branch-struct.c)
add_executable(day00-demo-05-branch-struct day00/demo05/loop-struct.c)
add_executable(day00-demo-06-array day00/demo06/array.c)
add_executable(day00-homework-01 day00/homework01/homework.c)
add_executable(day00-homework-02 day00/homework02/homework.c)

# day02
add_executable(day01-demo-01 day01/demo01/main.c)
add_executable(day01-demo-02 day01/demo02/main.c)

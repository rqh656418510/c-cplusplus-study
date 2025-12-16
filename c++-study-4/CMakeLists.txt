cmake_minimum_required(VERSION 3.15)
project(c___study_4)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "-lpthread")
endif()

add_executable(day01-demo01 day01/demo01/main.cpp)
add_executable(day01-demo02 day01/demo02/main.cpp)
add_executable(day01-demo03 day01/demo03/main.cpp)
add_executable(day01-demo04 day01/demo04/main.cpp)
add_executable(day01-demo04-2 day01/demo04/main2.cpp)
add_executable(day01-demo05 day01/demo05/main.cpp)
add_executable(day01-demo06 day01/demo06/main.cpp)
add_executable(day01-demo07 day01/demo07/main.cpp)
add_executable(day01-demo08 day01/demo08/main.cpp)

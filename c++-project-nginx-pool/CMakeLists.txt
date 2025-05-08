cmake_minimum_required(VERSION 3.15)
project(c___study_3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "-lpthread")
endif()

add_executable(ngx_pool_demo src/main.cpp)

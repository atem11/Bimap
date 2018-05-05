cmake_minimum_required(VERSION 3.9)
project(BIMAP)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined")
add_executable(BIMAP main.cpp bimap.h)
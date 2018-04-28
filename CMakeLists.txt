cmake_minimum_required(VERSION 3.9)
project(BIGINT)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address")
add_executable(BIGINT main.cpp bimap.h)
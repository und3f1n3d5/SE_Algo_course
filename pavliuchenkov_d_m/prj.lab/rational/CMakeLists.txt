cmake_minimum_required(VERSION 3.17)
project(rational)

set(CMAKE_CXX_STANDARD 20)

add_library(rational rational.h rational.cpp)
add_executable(rational_test rational_test.cpp)

target_link_libraries(rational_test rational)

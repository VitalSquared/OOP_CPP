cmake_minimum_required(VERSION 3.14)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)

include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)

add_executable(lab1 main.cpp RNA.cpp RNA.h test.cpp)

target_link_libraries(lab1 gtest gtest_main)
target_link_libraries(lab1 gmock gmock_main)

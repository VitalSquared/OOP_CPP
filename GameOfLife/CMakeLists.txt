cmake_minimum_required(VERSION 3.16)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_EXE_LINKER_FLAGS "-static")

add_subdirectory(lib/googletest-master)

include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)

add_executable(GameOfLife main.cpp CommandParser.cpp CommandParser.h GameModel.cpp GameModel.h Interface.cpp Interface.h test.cpp)

target_link_libraries(GameOfLife gtest gtest_main)
target_link_libraries(GameOfLife gmock gmock_main)
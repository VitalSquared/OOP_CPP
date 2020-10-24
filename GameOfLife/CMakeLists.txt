cmake_minimum_required(VERSION 3.17)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(GameOfLife main.cpp)
cmake_minimum_required(VERSION 3.17)
project(Robots)

set(CMAKE_CXX_STANDARD 14)

add_executable(Robots main.cpp Mode.cpp Mode.h Robot.cpp Robot.h GameView.cpp GameView.h Command.cpp Command.h)
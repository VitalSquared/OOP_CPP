cmake_minimum_required(VERSION 3.16)
project(Robots)

set(CMAKE_CXX_STANDARD 14)

add_executable(Robots main.cpp Mode.cpp Mode.h Robot.cpp Robot.h GameView.h Command.cpp Command.h Field.cpp Field.h Utils.cpp Utils.h ConsoleView.cpp ConsoleView.h)
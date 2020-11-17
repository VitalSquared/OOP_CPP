cmake_minimum_required(VERSION 3.16)
project(Robots)

set(CMAKE_CXX_STANDARD 14)

include_directories(commands)
include_directories(gameview)
include_directories(modes)
include_directories(robots)
include_directories(field)
include_directories(utils)

add_executable(Robots main.cpp modes/Mode.cpp modes/Mode.h robots/Robot.h gameview/GameView.h commands/Command.cpp commands/Command.h field/Field.cpp field/Field.h utils/Utils.cpp utils/Utils.h gameview/ConsoleView.cpp gameview/ConsoleView.h robots/Collector.cpp robots/Collector.h robots/Sapper.cpp robots/Sapper.h modes/ManualMode.cpp modes/ManualMode.h modes/ScanMode.cpp modes/ScanMode.h modes/AutoMode.cpp modes/AutoMode.h)
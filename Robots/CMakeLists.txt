cmake_minimum_required(VERSION 3.16)
project(Robots)

set(CMAKE_CXX_STANDARD 14)

add_executable(Robots main.cpp IRobot.h ICommand.h IGameView.h Collector.cpp Collector.h Sapper.cpp Sapper.h ConsoleView.cpp ConsoleView.h IMode.h Game.cpp Game.h ChangeModeCommand.cpp ChangeModeCommand.h MoveCommand.cpp MoveCommand.h ScanCommand.cpp ScanCommand.h GrabCommand.cpp GrabCommand.h ToggleSapperCommand.cpp ToggleSapperCommand.h ManualMode.cpp ManualMode.h AutoMode.cpp AutoMode.h ScanMode.cpp ScanMode.h Utils.cpp Utils.h Map.cpp Map.h Repeater.cpp Repeater.h Texture.cpp Texture.h)
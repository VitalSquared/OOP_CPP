# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Workshop\CLionProjects\OOOP\Robots

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Robots.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Robots.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Robots.dir\flags.make

CMakeFiles\Robots.dir\main.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Robots.dir/main.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\main.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\main.cpp
<<

CMakeFiles\Robots.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/main.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\main.cpp
<<

CMakeFiles\Robots.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/main.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\main.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\main.cpp
<<

CMakeFiles\Robots.dir\Collector.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\Collector.cpp.obj: ..\Collector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Robots.dir/Collector.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\Collector.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\Collector.cpp
<<

CMakeFiles\Robots.dir\Collector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/Collector.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\Collector.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\Collector.cpp
<<

CMakeFiles\Robots.dir\Collector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/Collector.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\Collector.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\Collector.cpp
<<

CMakeFiles\Robots.dir\Sapper.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\Sapper.cpp.obj: ..\Sapper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Robots.dir/Sapper.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\Sapper.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\Sapper.cpp
<<

CMakeFiles\Robots.dir\Sapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/Sapper.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\Sapper.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\Sapper.cpp
<<

CMakeFiles\Robots.dir\Sapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/Sapper.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\Sapper.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\Sapper.cpp
<<

CMakeFiles\Robots.dir\ConsoleView.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\ConsoleView.cpp.obj: ..\ConsoleView.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Robots.dir/ConsoleView.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\ConsoleView.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\ConsoleView.cpp
<<

CMakeFiles\Robots.dir\ConsoleView.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/ConsoleView.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\ConsoleView.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\ConsoleView.cpp
<<

CMakeFiles\Robots.dir\ConsoleView.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/ConsoleView.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\ConsoleView.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\ConsoleView.cpp
<<

CMakeFiles\Robots.dir\Game.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\Game.cpp.obj: ..\Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Robots.dir/Game.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\Game.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\Game.cpp
<<

CMakeFiles\Robots.dir\Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/Game.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\Game.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\Game.cpp
<<

CMakeFiles\Robots.dir\Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/Game.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\Game.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\Game.cpp
<<

CMakeFiles\Robots.dir\ChangeModeCommand.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\ChangeModeCommand.cpp.obj: ..\ChangeModeCommand.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Robots.dir/ChangeModeCommand.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\ChangeModeCommand.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\ChangeModeCommand.cpp
<<

CMakeFiles\Robots.dir\ChangeModeCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/ChangeModeCommand.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\ChangeModeCommand.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\ChangeModeCommand.cpp
<<

CMakeFiles\Robots.dir\ChangeModeCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/ChangeModeCommand.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\ChangeModeCommand.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\ChangeModeCommand.cpp
<<

CMakeFiles\Robots.dir\MoveCommand.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\MoveCommand.cpp.obj: ..\MoveCommand.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Robots.dir/MoveCommand.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\MoveCommand.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\MoveCommand.cpp
<<

CMakeFiles\Robots.dir\MoveCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/MoveCommand.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\MoveCommand.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\MoveCommand.cpp
<<

CMakeFiles\Robots.dir\MoveCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/MoveCommand.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\MoveCommand.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\MoveCommand.cpp
<<

CMakeFiles\Robots.dir\ScanCommand.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\ScanCommand.cpp.obj: ..\ScanCommand.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Robots.dir/ScanCommand.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\ScanCommand.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\ScanCommand.cpp
<<

CMakeFiles\Robots.dir\ScanCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/ScanCommand.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\ScanCommand.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\ScanCommand.cpp
<<

CMakeFiles\Robots.dir\ScanCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/ScanCommand.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\ScanCommand.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\ScanCommand.cpp
<<

CMakeFiles\Robots.dir\GrabCommand.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\GrabCommand.cpp.obj: ..\GrabCommand.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Robots.dir/GrabCommand.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\GrabCommand.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\GrabCommand.cpp
<<

CMakeFiles\Robots.dir\GrabCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/GrabCommand.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\GrabCommand.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\GrabCommand.cpp
<<

CMakeFiles\Robots.dir\GrabCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/GrabCommand.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\GrabCommand.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\GrabCommand.cpp
<<

CMakeFiles\Robots.dir\ToggleSapperCommand.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\ToggleSapperCommand.cpp.obj: ..\ToggleSapperCommand.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Robots.dir/ToggleSapperCommand.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\ToggleSapperCommand.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\ToggleSapperCommand.cpp
<<

CMakeFiles\Robots.dir\ToggleSapperCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/ToggleSapperCommand.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\ToggleSapperCommand.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\ToggleSapperCommand.cpp
<<

CMakeFiles\Robots.dir\ToggleSapperCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/ToggleSapperCommand.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\ToggleSapperCommand.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\ToggleSapperCommand.cpp
<<

CMakeFiles\Robots.dir\ManualMode.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\ManualMode.cpp.obj: ..\ManualMode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Robots.dir/ManualMode.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\ManualMode.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\ManualMode.cpp
<<

CMakeFiles\Robots.dir\ManualMode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/ManualMode.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\ManualMode.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\ManualMode.cpp
<<

CMakeFiles\Robots.dir\ManualMode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/ManualMode.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\ManualMode.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\ManualMode.cpp
<<

CMakeFiles\Robots.dir\AutoMode.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\AutoMode.cpp.obj: ..\AutoMode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Robots.dir/AutoMode.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\AutoMode.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\AutoMode.cpp
<<

CMakeFiles\Robots.dir\AutoMode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/AutoMode.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\AutoMode.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\AutoMode.cpp
<<

CMakeFiles\Robots.dir\AutoMode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/AutoMode.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\AutoMode.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\AutoMode.cpp
<<

CMakeFiles\Robots.dir\ScanMode.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\ScanMode.cpp.obj: ..\ScanMode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Robots.dir/ScanMode.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\ScanMode.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\ScanMode.cpp
<<

CMakeFiles\Robots.dir\ScanMode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/ScanMode.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\ScanMode.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\ScanMode.cpp
<<

CMakeFiles\Robots.dir\ScanMode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/ScanMode.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\ScanMode.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\ScanMode.cpp
<<

CMakeFiles\Robots.dir\Utils.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\Utils.cpp.obj: ..\Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Robots.dir/Utils.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\Utils.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\Utils.cpp
<<

CMakeFiles\Robots.dir\Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/Utils.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\Utils.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\Utils.cpp
<<

CMakeFiles\Robots.dir\Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/Utils.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\Utils.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\Utils.cpp
<<

CMakeFiles\Robots.dir\Map.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\Map.cpp.obj: ..\Map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Robots.dir/Map.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\Map.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\Map.cpp
<<

CMakeFiles\Robots.dir\Map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/Map.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\Map.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\Map.cpp
<<

CMakeFiles\Robots.dir\Map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/Map.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\Map.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\Map.cpp
<<

CMakeFiles\Robots.dir\Repeater.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\Repeater.cpp.obj: ..\Repeater.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/Robots.dir/Repeater.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\Repeater.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\Repeater.cpp
<<

CMakeFiles\Robots.dir\Repeater.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/Repeater.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\Repeater.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\Repeater.cpp
<<

CMakeFiles\Robots.dir\Repeater.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/Repeater.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\Repeater.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\Repeater.cpp
<<

CMakeFiles\Robots.dir\Texture.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\Texture.cpp.obj: ..\Texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/Robots.dir/Texture.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\Texture.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\Texture.cpp
<<

CMakeFiles\Robots.dir\Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/Texture.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\Texture.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\Texture.cpp
<<

CMakeFiles\Robots.dir\Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/Texture.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\Texture.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\Texture.cpp
<<

CMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.obj: CMakeFiles\Robots.dir\flags.make
CMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.obj: ..\SwitchCollectorCommand.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/Robots.dir/SwitchCollectorCommand.cpp.obj"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.obj /FdCMakeFiles\Robots.dir\ /FS -c D:\Workshop\CLionProjects\OOOP\Robots\SwitchCollectorCommand.cpp
<<

CMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robots.dir/SwitchCollectorCommand.cpp.i"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" > CMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Workshop\CLionProjects\OOOP\Robots\SwitchCollectorCommand.cpp
<<

CMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robots.dir/SwitchCollectorCommand.cpp.s"
	"D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.s /c D:\Workshop\CLionProjects\OOOP\Robots\SwitchCollectorCommand.cpp
<<

# Object files for target Robots
Robots_OBJECTS = \
"CMakeFiles\Robots.dir\main.cpp.obj" \
"CMakeFiles\Robots.dir\Collector.cpp.obj" \
"CMakeFiles\Robots.dir\Sapper.cpp.obj" \
"CMakeFiles\Robots.dir\ConsoleView.cpp.obj" \
"CMakeFiles\Robots.dir\Game.cpp.obj" \
"CMakeFiles\Robots.dir\ChangeModeCommand.cpp.obj" \
"CMakeFiles\Robots.dir\MoveCommand.cpp.obj" \
"CMakeFiles\Robots.dir\ScanCommand.cpp.obj" \
"CMakeFiles\Robots.dir\GrabCommand.cpp.obj" \
"CMakeFiles\Robots.dir\ToggleSapperCommand.cpp.obj" \
"CMakeFiles\Robots.dir\ManualMode.cpp.obj" \
"CMakeFiles\Robots.dir\AutoMode.cpp.obj" \
"CMakeFiles\Robots.dir\ScanMode.cpp.obj" \
"CMakeFiles\Robots.dir\Utils.cpp.obj" \
"CMakeFiles\Robots.dir\Map.cpp.obj" \
"CMakeFiles\Robots.dir\Repeater.cpp.obj" \
"CMakeFiles\Robots.dir\Texture.cpp.obj" \
"CMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.obj"

# External object files for target Robots
Robots_EXTERNAL_OBJECTS =

Robots.exe: CMakeFiles\Robots.dir\main.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\Collector.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\Sapper.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\ConsoleView.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\Game.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\ChangeModeCommand.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\MoveCommand.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\ScanCommand.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\GrabCommand.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\ToggleSapperCommand.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\ManualMode.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\AutoMode.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\ScanMode.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\Utils.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\Map.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\Repeater.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\Texture.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\SwitchCollectorCommand.cpp.obj
Robots.exe: CMakeFiles\Robots.dir\build.make
Robots.exe: CMakeFiles\Robots.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking CXX executable Robots.exe"
	"D:\CLion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Robots.dir --rc="D:\Windows Kits\10\bin\10.0.18362.0\x86\rc.exe" --mt="D:\Windows Kits\10\bin\10.0.18362.0\x86\mt.exe" --manifests  -- "D:\Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\bin\Hostx86\x86\link.exe" /nologo @CMakeFiles\Robots.dir\objects1.rsp @<<
 /out:Robots.exe /implib:Robots.lib /pdb:D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\Robots.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Robots.dir\build: Robots.exe

.PHONY : CMakeFiles\Robots.dir\build

CMakeFiles\Robots.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Robots.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Robots.dir\clean

CMakeFiles\Robots.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Workshop\CLionProjects\OOOP\Robots D:\Workshop\CLionProjects\OOOP\Robots D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug D:\Workshop\CLionProjects\OOOP\Robots\cmake-build-debug\CMakeFiles\Robots.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Robots.dir\depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Chess1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Chess1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Chess1.dir/flags.make

CMakeFiles/Chess1.dir/main.c.obj: CMakeFiles/Chess1.dir/flags.make
CMakeFiles/Chess1.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Chess1.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Chess1.dir\main.c.obj   -c C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\main.c

CMakeFiles/Chess1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Chess1.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\main.c > CMakeFiles\Chess1.dir\main.c.i

CMakeFiles/Chess1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Chess1.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\main.c -o CMakeFiles\Chess1.dir\main.c.s

CMakeFiles/Chess1.dir/main.c.obj.requires:

.PHONY : CMakeFiles/Chess1.dir/main.c.obj.requires

CMakeFiles/Chess1.dir/main.c.obj.provides: CMakeFiles/Chess1.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\Chess1.dir\build.make CMakeFiles/Chess1.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/Chess1.dir/main.c.obj.provides

CMakeFiles/Chess1.dir/main.c.obj.provides.build: CMakeFiles/Chess1.dir/main.c.obj


CMakeFiles/Chess1.dir/GameBoard.c.obj: CMakeFiles/Chess1.dir/flags.make
CMakeFiles/Chess1.dir/GameBoard.c.obj: ../GameBoard.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Chess1.dir/GameBoard.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Chess1.dir\GameBoard.c.obj   -c C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\GameBoard.c

CMakeFiles/Chess1.dir/GameBoard.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Chess1.dir/GameBoard.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\GameBoard.c > CMakeFiles\Chess1.dir\GameBoard.c.i

CMakeFiles/Chess1.dir/GameBoard.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Chess1.dir/GameBoard.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\GameBoard.c -o CMakeFiles\Chess1.dir\GameBoard.c.s

CMakeFiles/Chess1.dir/GameBoard.c.obj.requires:

.PHONY : CMakeFiles/Chess1.dir/GameBoard.c.obj.requires

CMakeFiles/Chess1.dir/GameBoard.c.obj.provides: CMakeFiles/Chess1.dir/GameBoard.c.obj.requires
	$(MAKE) -f CMakeFiles\Chess1.dir\build.make CMakeFiles/Chess1.dir/GameBoard.c.obj.provides.build
.PHONY : CMakeFiles/Chess1.dir/GameBoard.c.obj.provides

CMakeFiles/Chess1.dir/GameBoard.c.obj.provides.build: CMakeFiles/Chess1.dir/GameBoard.c.obj


CMakeFiles/Chess1.dir/consoleUI.c.obj: CMakeFiles/Chess1.dir/flags.make
CMakeFiles/Chess1.dir/consoleUI.c.obj: ../consoleUI.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Chess1.dir/consoleUI.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Chess1.dir\consoleUI.c.obj   -c C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\consoleUI.c

CMakeFiles/Chess1.dir/consoleUI.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Chess1.dir/consoleUI.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\consoleUI.c > CMakeFiles\Chess1.dir\consoleUI.c.i

CMakeFiles/Chess1.dir/consoleUI.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Chess1.dir/consoleUI.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\consoleUI.c -o CMakeFiles\Chess1.dir\consoleUI.c.s

CMakeFiles/Chess1.dir/consoleUI.c.obj.requires:

.PHONY : CMakeFiles/Chess1.dir/consoleUI.c.obj.requires

CMakeFiles/Chess1.dir/consoleUI.c.obj.provides: CMakeFiles/Chess1.dir/consoleUI.c.obj.requires
	$(MAKE) -f CMakeFiles\Chess1.dir\build.make CMakeFiles/Chess1.dir/consoleUI.c.obj.provides.build
.PHONY : CMakeFiles/Chess1.dir/consoleUI.c.obj.provides

CMakeFiles/Chess1.dir/consoleUI.c.obj.provides.build: CMakeFiles/Chess1.dir/consoleUI.c.obj


CMakeFiles/Chess1.dir/xmlGame.c.obj: CMakeFiles/Chess1.dir/flags.make
CMakeFiles/Chess1.dir/xmlGame.c.obj: ../xmlGame.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Chess1.dir/xmlGame.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Chess1.dir\xmlGame.c.obj   -c C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\xmlGame.c

CMakeFiles/Chess1.dir/xmlGame.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Chess1.dir/xmlGame.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\xmlGame.c > CMakeFiles\Chess1.dir\xmlGame.c.i

CMakeFiles/Chess1.dir/xmlGame.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Chess1.dir/xmlGame.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\xmlGame.c -o CMakeFiles\Chess1.dir\xmlGame.c.s

CMakeFiles/Chess1.dir/xmlGame.c.obj.requires:

.PHONY : CMakeFiles/Chess1.dir/xmlGame.c.obj.requires

CMakeFiles/Chess1.dir/xmlGame.c.obj.provides: CMakeFiles/Chess1.dir/xmlGame.c.obj.requires
	$(MAKE) -f CMakeFiles\Chess1.dir\build.make CMakeFiles/Chess1.dir/xmlGame.c.obj.provides.build
.PHONY : CMakeFiles/Chess1.dir/xmlGame.c.obj.provides

CMakeFiles/Chess1.dir/xmlGame.c.obj.provides.build: CMakeFiles/Chess1.dir/xmlGame.c.obj


CMakeFiles/Chess1.dir/GameState.c.obj: CMakeFiles/Chess1.dir/flags.make
CMakeFiles/Chess1.dir/GameState.c.obj: ../GameState.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Chess1.dir/GameState.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Chess1.dir\GameState.c.obj   -c C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\GameState.c

CMakeFiles/Chess1.dir/GameState.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Chess1.dir/GameState.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\GameState.c > CMakeFiles\Chess1.dir\GameState.c.i

CMakeFiles/Chess1.dir/GameState.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Chess1.dir/GameState.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\GameState.c -o CMakeFiles\Chess1.dir\GameState.c.s

CMakeFiles/Chess1.dir/GameState.c.obj.requires:

.PHONY : CMakeFiles/Chess1.dir/GameState.c.obj.requires

CMakeFiles/Chess1.dir/GameState.c.obj.provides: CMakeFiles/Chess1.dir/GameState.c.obj.requires
	$(MAKE) -f CMakeFiles\Chess1.dir\build.make CMakeFiles/Chess1.dir/GameState.c.obj.provides.build
.PHONY : CMakeFiles/Chess1.dir/GameState.c.obj.provides

CMakeFiles/Chess1.dir/GameState.c.obj.provides.build: CMakeFiles/Chess1.dir/GameState.c.obj


CMakeFiles/Chess1.dir/MiniMax.c.obj: CMakeFiles/Chess1.dir/flags.make
CMakeFiles/Chess1.dir/MiniMax.c.obj: ../MiniMax.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Chess1.dir/MiniMax.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Chess1.dir\MiniMax.c.obj   -c C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\MiniMax.c

CMakeFiles/Chess1.dir/MiniMax.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Chess1.dir/MiniMax.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\MiniMax.c > CMakeFiles\Chess1.dir\MiniMax.c.i

CMakeFiles/Chess1.dir/MiniMax.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Chess1.dir/MiniMax.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\MiniMax.c -o CMakeFiles\Chess1.dir\MiniMax.c.s

CMakeFiles/Chess1.dir/MiniMax.c.obj.requires:

.PHONY : CMakeFiles/Chess1.dir/MiniMax.c.obj.requires

CMakeFiles/Chess1.dir/MiniMax.c.obj.provides: CMakeFiles/Chess1.dir/MiniMax.c.obj.requires
	$(MAKE) -f CMakeFiles\Chess1.dir\build.make CMakeFiles/Chess1.dir/MiniMax.c.obj.provides.build
.PHONY : CMakeFiles/Chess1.dir/MiniMax.c.obj.provides

CMakeFiles/Chess1.dir/MiniMax.c.obj.provides.build: CMakeFiles/Chess1.dir/MiniMax.c.obj


# Object files for target Chess1
Chess1_OBJECTS = \
"CMakeFiles/Chess1.dir/main.c.obj" \
"CMakeFiles/Chess1.dir/GameBoard.c.obj" \
"CMakeFiles/Chess1.dir/consoleUI.c.obj" \
"CMakeFiles/Chess1.dir/xmlGame.c.obj" \
"CMakeFiles/Chess1.dir/GameState.c.obj" \
"CMakeFiles/Chess1.dir/MiniMax.c.obj"

# External object files for target Chess1
Chess1_EXTERNAL_OBJECTS =

Chess1.exe: CMakeFiles/Chess1.dir/main.c.obj
Chess1.exe: CMakeFiles/Chess1.dir/GameBoard.c.obj
Chess1.exe: CMakeFiles/Chess1.dir/consoleUI.c.obj
Chess1.exe: CMakeFiles/Chess1.dir/xmlGame.c.obj
Chess1.exe: CMakeFiles/Chess1.dir/GameState.c.obj
Chess1.exe: CMakeFiles/Chess1.dir/MiniMax.c.obj
Chess1.exe: CMakeFiles/Chess1.dir/build.make
Chess1.exe: CMakeFiles/Chess1.dir/linklibs.rsp
Chess1.exe: CMakeFiles/Chess1.dir/objects1.rsp
Chess1.exe: CMakeFiles/Chess1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable Chess1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Chess1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Chess1.dir/build: Chess1.exe

.PHONY : CMakeFiles/Chess1.dir/build

CMakeFiles/Chess1.dir/requires: CMakeFiles/Chess1.dir/main.c.obj.requires
CMakeFiles/Chess1.dir/requires: CMakeFiles/Chess1.dir/GameBoard.c.obj.requires
CMakeFiles/Chess1.dir/requires: CMakeFiles/Chess1.dir/consoleUI.c.obj.requires
CMakeFiles/Chess1.dir/requires: CMakeFiles/Chess1.dir/xmlGame.c.obj.requires
CMakeFiles/Chess1.dir/requires: CMakeFiles/Chess1.dir/GameState.c.obj.requires
CMakeFiles/Chess1.dir/requires: CMakeFiles/Chess1.dir/MiniMax.c.obj.requires

.PHONY : CMakeFiles/Chess1.dir/requires

CMakeFiles/Chess1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Chess1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Chess1.dir/clean

CMakeFiles/Chess1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug C:\Users\Dror\CLionProjects\SoftwareProject\FinalProject\cmake-build-debug\CMakeFiles\Chess1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Chess1.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/build"

# Include any dependencies generated for this target.
include CMakeFiles/FileTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FileTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FileTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FileTest.dir/flags.make

CMakeFiles/FileTest.dir/src/basic.cpp.o: CMakeFiles/FileTest.dir/flags.make
CMakeFiles/FileTest.dir/src/basic.cpp.o: ../src/basic.cpp
CMakeFiles/FileTest.dir/src/basic.cpp.o: CMakeFiles/FileTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FileTest.dir/src/basic.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FileTest.dir/src/basic.cpp.o -MF CMakeFiles/FileTest.dir/src/basic.cpp.o.d -o CMakeFiles/FileTest.dir/src/basic.cpp.o -c "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/basic.cpp"

CMakeFiles/FileTest.dir/src/basic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FileTest.dir/src/basic.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/basic.cpp" > CMakeFiles/FileTest.dir/src/basic.cpp.i

CMakeFiles/FileTest.dir/src/basic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FileTest.dir/src/basic.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/basic.cpp" -o CMakeFiles/FileTest.dir/src/basic.cpp.s

# Object files for target FileTest
FileTest_OBJECTS = \
"CMakeFiles/FileTest.dir/src/basic.cpp.o"

# External object files for target FileTest
FileTest_EXTERNAL_OBJECTS =

FileTest: CMakeFiles/FileTest.dir/src/basic.cpp.o
FileTest: CMakeFiles/FileTest.dir/build.make
FileTest: CMakeFiles/FileTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FileTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FileTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FileTest.dir/build: FileTest
.PHONY : CMakeFiles/FileTest.dir/build

CMakeFiles/FileTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FileTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FileTest.dir/clean

CMakeFiles/FileTest.dir/depend:
	cd "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine" "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine" "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/build" "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/build" "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/build/CMakeFiles/FileTest.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/FileTest.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/master/prak7/task2/TestGen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/master/prak7/task2/TestGen/build

# Include any dependencies generated for this target.
include CMakeFiles/TestGen.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestGen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestGen.dir/flags.make

CMakeFiles/TestGen.dir/main.cpp.o: CMakeFiles/TestGen.dir/flags.make
CMakeFiles/TestGen.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/master/prak7/task2/TestGen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestGen.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestGen.dir/main.cpp.o -c /home/master/prak7/task2/TestGen/main.cpp

CMakeFiles/TestGen.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestGen.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/master/prak7/task2/TestGen/main.cpp > CMakeFiles/TestGen.dir/main.cpp.i

CMakeFiles/TestGen.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestGen.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/master/prak7/task2/TestGen/main.cpp -o CMakeFiles/TestGen.dir/main.cpp.s

# Object files for target TestGen
TestGen_OBJECTS = \
"CMakeFiles/TestGen.dir/main.cpp.o"

# External object files for target TestGen
TestGen_EXTERNAL_OBJECTS =

TestGen: CMakeFiles/TestGen.dir/main.cpp.o
TestGen: CMakeFiles/TestGen.dir/build.make
TestGen: CMakeFiles/TestGen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/master/prak7/task2/TestGen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestGen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestGen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestGen.dir/build: TestGen

.PHONY : CMakeFiles/TestGen.dir/build

CMakeFiles/TestGen.dir/clean:
	$(CMAKE_COMMAND) -calcProbability CMakeFiles/TestGen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestGen.dir/clean

CMakeFiles/TestGen.dir/depend:
	cd /home/master/prak7/task2/TestGen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/master/prak7/task2/TestGen /home/master/prak7/task2/TestGen /home/master/prak7/task2/TestGen/build /home/master/prak7/task2/TestGen/build /home/master/prak7/task2/TestGen/build/CMakeFiles/TestGen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestGen.dir/depend


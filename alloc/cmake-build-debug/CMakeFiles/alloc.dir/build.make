# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Users/ekaterina/Desktop/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Users/ekaterina/Desktop/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ekaterina/alloc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ekaterina/alloc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/alloc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/alloc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/alloc.dir/flags.make

CMakeFiles/alloc.dir/main.c.o: CMakeFiles/alloc.dir/flags.make
CMakeFiles/alloc.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ekaterina/alloc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/alloc.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alloc.dir/main.c.o   -c /Users/ekaterina/alloc/main.c

CMakeFiles/alloc.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alloc.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ekaterina/alloc/main.c > CMakeFiles/alloc.dir/main.c.i

CMakeFiles/alloc.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alloc.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ekaterina/alloc/main.c -o CMakeFiles/alloc.dir/main.c.s

CMakeFiles/alloc.dir/main.c.o.requires:

.PHONY : CMakeFiles/alloc.dir/main.c.o.requires

CMakeFiles/alloc.dir/main.c.o.provides: CMakeFiles/alloc.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/alloc.dir/build.make CMakeFiles/alloc.dir/main.c.o.provides.build
.PHONY : CMakeFiles/alloc.dir/main.c.o.provides

CMakeFiles/alloc.dir/main.c.o.provides.build: CMakeFiles/alloc.dir/main.c.o


# Object files for target alloc
alloc_OBJECTS = \
"CMakeFiles/alloc.dir/main.c.o"

# External object files for target alloc
alloc_EXTERNAL_OBJECTS =

alloc: CMakeFiles/alloc.dir/main.c.o
alloc: CMakeFiles/alloc.dir/build.make
alloc: CMakeFiles/alloc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ekaterina/alloc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable alloc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alloc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/alloc.dir/build: alloc

.PHONY : CMakeFiles/alloc.dir/build

CMakeFiles/alloc.dir/requires: CMakeFiles/alloc.dir/main.c.o.requires

.PHONY : CMakeFiles/alloc.dir/requires

CMakeFiles/alloc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/alloc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/alloc.dir/clean

CMakeFiles/alloc.dir/depend:
	cd /Users/ekaterina/alloc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ekaterina/alloc /Users/ekaterina/alloc /Users/ekaterina/alloc/cmake-build-debug /Users/ekaterina/alloc/cmake-build-debug /Users/ekaterina/alloc/cmake-build-debug/CMakeFiles/alloc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/alloc.dir/depend


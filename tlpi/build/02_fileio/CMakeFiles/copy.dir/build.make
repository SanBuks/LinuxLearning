# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/bin/cmake3

# The command to remove a file.
RM = /usr/bin/cmake3 -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/LinuxLearning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/LinuxLearning/build

# Include any dependencies generated for this target.
include 02_fileio/CMakeFiles/copy.dir/depend.make

# Include the progress variables for this target.
include 02_fileio/CMakeFiles/copy.dir/progress.make

# Include the compile flags for this target's objects.
include 02_fileio/CMakeFiles/copy.dir/flags.make

02_fileio/CMakeFiles/copy.dir/copy.cc.o: 02_fileio/CMakeFiles/copy.dir/flags.make
02_fileio/CMakeFiles/copy.dir/copy.cc.o: ../02_fileio/copy.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/LinuxLearning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 02_fileio/CMakeFiles/copy.dir/copy.cc.o"
	cd /home/LinuxLearning/build/02_fileio && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/copy.dir/copy.cc.o -c /home/LinuxLearning/02_fileio/copy.cc

02_fileio/CMakeFiles/copy.dir/copy.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/copy.dir/copy.cc.i"
	cd /home/LinuxLearning/build/02_fileio && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/LinuxLearning/02_fileio/copy.cc > CMakeFiles/copy.dir/copy.cc.i

02_fileio/CMakeFiles/copy.dir/copy.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/copy.dir/copy.cc.s"
	cd /home/LinuxLearning/build/02_fileio && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/LinuxLearning/02_fileio/copy.cc -o CMakeFiles/copy.dir/copy.cc.s

# Object files for target copy
copy_OBJECTS = \
"CMakeFiles/copy.dir/copy.cc.o"

# External object files for target copy
copy_EXTERNAL_OBJECTS =

02_fileio/copy: 02_fileio/CMakeFiles/copy.dir/copy.cc.o
02_fileio/copy: 02_fileio/CMakeFiles/copy.dir/build.make
02_fileio/copy: lib/libtlpi_header.so
02_fileio/copy: 02_fileio/CMakeFiles/copy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/LinuxLearning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable copy"
	cd /home/LinuxLearning/build/02_fileio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/copy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
02_fileio/CMakeFiles/copy.dir/build: 02_fileio/copy

.PHONY : 02_fileio/CMakeFiles/copy.dir/build

02_fileio/CMakeFiles/copy.dir/clean:
	cd /home/LinuxLearning/build/02_fileio && $(CMAKE_COMMAND) -P CMakeFiles/copy.dir/cmake_clean.cmake
.PHONY : 02_fileio/CMakeFiles/copy.dir/clean

02_fileio/CMakeFiles/copy.dir/depend:
	cd /home/LinuxLearning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/LinuxLearning /home/LinuxLearning/02_fileio /home/LinuxLearning/build /home/LinuxLearning/build/02_fileio /home/LinuxLearning/build/02_fileio/CMakeFiles/copy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 02_fileio/CMakeFiles/copy.dir/depend

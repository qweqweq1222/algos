# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/anreydron/CLionProjects/520_B/algos/dron_a_a

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build

# Include any dependencies generated for this target.
include prj.lab/m3i/CMakeFiles/test_m3i.dir/depend.make

# Include the progress variables for this target.
include prj.lab/m3i/CMakeFiles/test_m3i.dir/progress.make

# Include the compile flags for this target's objects.
include prj.lab/m3i/CMakeFiles/test_m3i.dir/flags.make

prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o: prj.lab/m3i/CMakeFiles/test_m3i.dir/flags.make
prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o: ../prj.lab/m3i/m3i_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o"
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/m3i && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_m3i.dir/m3i_test.cpp.o -c /home/anreydron/CLionProjects/520_B/algos/dron_a_a/prj.lab/m3i/m3i_test.cpp

prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_m3i.dir/m3i_test.cpp.i"
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/m3i && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anreydron/CLionProjects/520_B/algos/dron_a_a/prj.lab/m3i/m3i_test.cpp > CMakeFiles/test_m3i.dir/m3i_test.cpp.i

prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_m3i.dir/m3i_test.cpp.s"
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/m3i && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anreydron/CLionProjects/520_B/algos/dron_a_a/prj.lab/m3i/m3i_test.cpp -o CMakeFiles/test_m3i.dir/m3i_test.cpp.s

prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o.requires:

.PHONY : prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o.requires

prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o.provides: prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o.requires
	$(MAKE) -f prj.lab/m3i/CMakeFiles/test_m3i.dir/build.make prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o.provides.build
.PHONY : prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o.provides

prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o.provides.build: prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o


# Object files for target test_m3i
test_m3i_OBJECTS = \
"CMakeFiles/test_m3i.dir/m3i_test.cpp.o"

# External object files for target test_m3i
test_m3i_EXTERNAL_OBJECTS =

prj.lab/m3i/test_m3i: prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o
prj.lab/m3i/test_m3i: prj.lab/m3i/CMakeFiles/test_m3i.dir/build.make
prj.lab/m3i/test_m3i: prj.lab/m3i/libm3i.a
prj.lab/m3i/test_m3i: prj.lab/m3i/CMakeFiles/test_m3i.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_m3i"
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/m3i && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_m3i.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
prj.lab/m3i/CMakeFiles/test_m3i.dir/build: prj.lab/m3i/test_m3i

.PHONY : prj.lab/m3i/CMakeFiles/test_m3i.dir/build

prj.lab/m3i/CMakeFiles/test_m3i.dir/requires: prj.lab/m3i/CMakeFiles/test_m3i.dir/m3i_test.cpp.o.requires

.PHONY : prj.lab/m3i/CMakeFiles/test_m3i.dir/requires

prj.lab/m3i/CMakeFiles/test_m3i.dir/clean:
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/m3i && $(CMAKE_COMMAND) -P CMakeFiles/test_m3i.dir/cmake_clean.cmake
.PHONY : prj.lab/m3i/CMakeFiles/test_m3i.dir/clean

prj.lab/m3i/CMakeFiles/test_m3i.dir/depend:
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anreydron/CLionProjects/520_B/algos/dron_a_a /home/anreydron/CLionProjects/520_B/algos/dron_a_a/prj.lab/m3i /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/m3i /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/m3i/CMakeFiles/test_m3i.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : prj.lab/m3i/CMakeFiles/test_m3i.dir/depend


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
include prj.lab/rational/CMakeFiles/rational.dir/depend.make

# Include the progress variables for this target.
include prj.lab/rational/CMakeFiles/rational.dir/progress.make

# Include the compile flags for this target's objects.
include prj.lab/rational/CMakeFiles/rational.dir/flags.make

prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o: prj.lab/rational/CMakeFiles/rational.dir/flags.make
prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o: ../prj.lab/rational/rational.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o"
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/rational && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rational.dir/rational.cpp.o -c /home/anreydron/CLionProjects/520_B/algos/dron_a_a/prj.lab/rational/rational.cpp

prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rational.dir/rational.cpp.i"
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/rational && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anreydron/CLionProjects/520_B/algos/dron_a_a/prj.lab/rational/rational.cpp > CMakeFiles/rational.dir/rational.cpp.i

prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rational.dir/rational.cpp.s"
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/rational && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anreydron/CLionProjects/520_B/algos/dron_a_a/prj.lab/rational/rational.cpp -o CMakeFiles/rational.dir/rational.cpp.s

prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o.requires:

.PHONY : prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o.requires

prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o.provides: prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o.requires
	$(MAKE) -f prj.lab/rational/CMakeFiles/rational.dir/build.make prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o.provides.build
.PHONY : prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o.provides

prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o.provides.build: prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o


# Object files for target rational
rational_OBJECTS = \
"CMakeFiles/rational.dir/rational.cpp.o"

# External object files for target rational
rational_EXTERNAL_OBJECTS =

prj.lab/rational/librational.a: prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o
prj.lab/rational/librational.a: prj.lab/rational/CMakeFiles/rational.dir/build.make
prj.lab/rational/librational.a: prj.lab/rational/CMakeFiles/rational.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librational.a"
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/rational && $(CMAKE_COMMAND) -P CMakeFiles/rational.dir/cmake_clean_target.cmake
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/rational && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rational.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
prj.lab/rational/CMakeFiles/rational.dir/build: prj.lab/rational/librational.a

.PHONY : prj.lab/rational/CMakeFiles/rational.dir/build

prj.lab/rational/CMakeFiles/rational.dir/requires: prj.lab/rational/CMakeFiles/rational.dir/rational.cpp.o.requires

.PHONY : prj.lab/rational/CMakeFiles/rational.dir/requires

prj.lab/rational/CMakeFiles/rational.dir/clean:
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/rational && $(CMAKE_COMMAND) -P CMakeFiles/rational.dir/cmake_clean.cmake
.PHONY : prj.lab/rational/CMakeFiles/rational.dir/clean

prj.lab/rational/CMakeFiles/rational.dir/depend:
	cd /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anreydron/CLionProjects/520_B/algos/dron_a_a /home/anreydron/CLionProjects/520_B/algos/dron_a_a/prj.lab/rational /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/rational /home/anreydron/CLionProjects/520_B/algos/dron_a_a/build/prj.lab/rational/CMakeFiles/rational.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : prj.lab/rational/CMakeFiles/rational.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /snap/cmake/1315/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1315/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bobliew/gitTest/day2/3d-bpp-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bobliew/gitTest/day2/3d-bpp-cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/cubeBpptest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cubeBpptest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cubeBpptest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cubeBpptest.dir/flags.make

CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o: CMakeFiles/cubeBpptest.dir/flags.make
CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o: /home/bobliew/gitTest/day2/3d-bpp-cpp/test/bppCube.cc
CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o: CMakeFiles/cubeBpptest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bobliew/gitTest/day2/3d-bpp-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o -MF CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o.d -o CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o -c /home/bobliew/gitTest/day2/3d-bpp-cpp/test/bppCube.cc

CMakeFiles/cubeBpptest.dir/test/bppCube.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cubeBpptest.dir/test/bppCube.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bobliew/gitTest/day2/3d-bpp-cpp/test/bppCube.cc > CMakeFiles/cubeBpptest.dir/test/bppCube.cc.i

CMakeFiles/cubeBpptest.dir/test/bppCube.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cubeBpptest.dir/test/bppCube.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bobliew/gitTest/day2/3d-bpp-cpp/test/bppCube.cc -o CMakeFiles/cubeBpptest.dir/test/bppCube.cc.s

# Object files for target cubeBpptest
cubeBpptest_OBJECTS = \
"CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o"

# External object files for target cubeBpptest
cubeBpptest_EXTERNAL_OBJECTS = \
"/home/bobliew/gitTest/day2/3d-bpp-cpp/build/cubeBpp/CMakeFiles/cubeBpp.dir/objects/objects.cc.o" \
"/home/bobliew/gitTest/day2/3d-bpp-cpp/build/cubeBpp/CMakeFiles/cubeBpp.dir/algorithms/cubeGenAlgorithm.cc.o"

cubeBpptest: CMakeFiles/cubeBpptest.dir/test/bppCube.cc.o
cubeBpptest: cubeBpp/CMakeFiles/cubeBpp.dir/objects/objects.cc.o
cubeBpptest: cubeBpp/CMakeFiles/cubeBpp.dir/algorithms/cubeGenAlgorithm.cc.o
cubeBpptest: CMakeFiles/cubeBpptest.dir/build.make
cubeBpptest: /usr/local/lib/libboost_thread.so.1.82.0
cubeBpptest: CMakeFiles/cubeBpptest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/bobliew/gitTest/day2/3d-bpp-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cubeBpptest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cubeBpptest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cubeBpptest.dir/build: cubeBpptest
.PHONY : CMakeFiles/cubeBpptest.dir/build

CMakeFiles/cubeBpptest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cubeBpptest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cubeBpptest.dir/clean

CMakeFiles/cubeBpptest.dir/depend:
	cd /home/bobliew/gitTest/day2/3d-bpp-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bobliew/gitTest/day2/3d-bpp-cpp /home/bobliew/gitTest/day2/3d-bpp-cpp /home/bobliew/gitTest/day2/3d-bpp-cpp/build /home/bobliew/gitTest/day2/3d-bpp-cpp/build /home/bobliew/gitTest/day2/3d-bpp-cpp/build/CMakeFiles/cubeBpptest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cubeBpptest.dir/depend


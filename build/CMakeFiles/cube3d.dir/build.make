# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/matthias/development/ogl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matthias/development/ogl/build

# Include any dependencies generated for this target.
include CMakeFiles/cube3d.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cube3d.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cube3d.dir/flags.make

CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o: CMakeFiles/cube3d.dir/flags.make
CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o: ../mgl/source/GLSLProgram.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matthias/development/ogl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o"
	/usr/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o -c /home/matthias/development/ogl/mgl/source/GLSLProgram.cpp

CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.i"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matthias/development/ogl/mgl/source/GLSLProgram.cpp > CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.i

CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.s"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matthias/development/ogl/mgl/source/GLSLProgram.cpp -o CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.s

CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o.requires:

.PHONY : CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o.requires

CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o.provides: CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o.requires
	$(MAKE) -f CMakeFiles/cube3d.dir/build.make CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o.provides.build
.PHONY : CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o.provides

CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o.provides.build: CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o


CMakeFiles/cube3d.dir/Main.cpp.o: CMakeFiles/cube3d.dir/flags.make
CMakeFiles/cube3d.dir/Main.cpp.o: ../Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matthias/development/ogl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cube3d.dir/Main.cpp.o"
	/usr/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cube3d.dir/Main.cpp.o -c /home/matthias/development/ogl/Main.cpp

CMakeFiles/cube3d.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cube3d.dir/Main.cpp.i"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matthias/development/ogl/Main.cpp > CMakeFiles/cube3d.dir/Main.cpp.i

CMakeFiles/cube3d.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cube3d.dir/Main.cpp.s"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matthias/development/ogl/Main.cpp -o CMakeFiles/cube3d.dir/Main.cpp.s

CMakeFiles/cube3d.dir/Main.cpp.o.requires:

.PHONY : CMakeFiles/cube3d.dir/Main.cpp.o.requires

CMakeFiles/cube3d.dir/Main.cpp.o.provides: CMakeFiles/cube3d.dir/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/cube3d.dir/build.make CMakeFiles/cube3d.dir/Main.cpp.o.provides.build
.PHONY : CMakeFiles/cube3d.dir/Main.cpp.o.provides

CMakeFiles/cube3d.dir/Main.cpp.o.provides.build: CMakeFiles/cube3d.dir/Main.cpp.o


# Object files for target cube3d
cube3d_OBJECTS = \
"CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o" \
"CMakeFiles/cube3d.dir/Main.cpp.o"

# External object files for target cube3d
cube3d_EXTERNAL_OBJECTS =

cube3d: CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o
cube3d: CMakeFiles/cube3d.dir/Main.cpp.o
cube3d: CMakeFiles/cube3d.dir/build.make
cube3d: CMakeFiles/cube3d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matthias/development/ogl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable cube3d"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cube3d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cube3d.dir/build: cube3d

.PHONY : CMakeFiles/cube3d.dir/build

CMakeFiles/cube3d.dir/requires: CMakeFiles/cube3d.dir/mgl/source/GLSLProgram.cpp.o.requires
CMakeFiles/cube3d.dir/requires: CMakeFiles/cube3d.dir/Main.cpp.o.requires

.PHONY : CMakeFiles/cube3d.dir/requires

CMakeFiles/cube3d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cube3d.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cube3d.dir/clean

CMakeFiles/cube3d.dir/depend:
	cd /home/matthias/development/ogl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matthias/development/ogl /home/matthias/development/ogl /home/matthias/development/ogl/build /home/matthias/development/ogl/build /home/matthias/development/ogl/build/CMakeFiles/cube3d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cube3d.dir/depend

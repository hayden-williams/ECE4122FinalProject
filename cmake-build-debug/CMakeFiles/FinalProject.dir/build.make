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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/FinalProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FinalProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FinalProject.dir/flags.make

CMakeFiles/FinalProject.dir/graphics.cpp.o: CMakeFiles/FinalProject.dir/flags.make
CMakeFiles/FinalProject.dir/graphics.cpp.o: ../graphics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FinalProject.dir/graphics.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FinalProject.dir/graphics.cpp.o -c /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/graphics.cpp

CMakeFiles/FinalProject.dir/graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FinalProject.dir/graphics.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/graphics.cpp > CMakeFiles/FinalProject.dir/graphics.cpp.i

CMakeFiles/FinalProject.dir/graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FinalProject.dir/graphics.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/graphics.cpp -o CMakeFiles/FinalProject.dir/graphics.cpp.s

CMakeFiles/FinalProject.dir/graphics.cpp.o.requires:

.PHONY : CMakeFiles/FinalProject.dir/graphics.cpp.o.requires

CMakeFiles/FinalProject.dir/graphics.cpp.o.provides: CMakeFiles/FinalProject.dir/graphics.cpp.o.requires
	$(MAKE) -f CMakeFiles/FinalProject.dir/build.make CMakeFiles/FinalProject.dir/graphics.cpp.o.provides.build
.PHONY : CMakeFiles/FinalProject.dir/graphics.cpp.o.provides

CMakeFiles/FinalProject.dir/graphics.cpp.o.provides.build: CMakeFiles/FinalProject.dir/graphics.cpp.o


CMakeFiles/FinalProject.dir/main.cpp.o: CMakeFiles/FinalProject.dir/flags.make
CMakeFiles/FinalProject.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FinalProject.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FinalProject.dir/main.cpp.o -c /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/main.cpp

CMakeFiles/FinalProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FinalProject.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/main.cpp > CMakeFiles/FinalProject.dir/main.cpp.i

CMakeFiles/FinalProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FinalProject.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/main.cpp -o CMakeFiles/FinalProject.dir/main.cpp.s

CMakeFiles/FinalProject.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/FinalProject.dir/main.cpp.o.requires

CMakeFiles/FinalProject.dir/main.cpp.o.provides: CMakeFiles/FinalProject.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/FinalProject.dir/build.make CMakeFiles/FinalProject.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/FinalProject.dir/main.cpp.o.provides

CMakeFiles/FinalProject.dir/main.cpp.o.provides.build: CMakeFiles/FinalProject.dir/main.cpp.o


# Object files for target FinalProject
FinalProject_OBJECTS = \
"CMakeFiles/FinalProject.dir/graphics.cpp.o" \
"CMakeFiles/FinalProject.dir/main.cpp.o"

# External object files for target FinalProject
FinalProject_EXTERNAL_OBJECTS =

FinalProject: CMakeFiles/FinalProject.dir/graphics.cpp.o
FinalProject: CMakeFiles/FinalProject.dir/main.cpp.o
FinalProject: CMakeFiles/FinalProject.dir/build.make
FinalProject: /usr/local/lib/libGLEW.dylib
FinalProject: /usr/local/Cellar/glfw/3.2.1/lib/libglfw.dylib
FinalProject: /usr/local/lib/libSOIL.dylib
FinalProject: CMakeFiles/FinalProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable FinalProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FinalProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FinalProject.dir/build: FinalProject

.PHONY : CMakeFiles/FinalProject.dir/build

CMakeFiles/FinalProject.dir/requires: CMakeFiles/FinalProject.dir/graphics.cpp.o.requires
CMakeFiles/FinalProject.dir/requires: CMakeFiles/FinalProject.dir/main.cpp.o.requires

.PHONY : CMakeFiles/FinalProject.dir/requires

CMakeFiles/FinalProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FinalProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FinalProject.dir/clean

CMakeFiles/FinalProject.dir/depend:
	cd /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/cmake-build-debug /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/cmake-build-debug /Users/elizabethrobelo/Documents/ECE4122/ECE4122FinalProject/cmake-build-debug/CMakeFiles/FinalProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FinalProject.dir/depend


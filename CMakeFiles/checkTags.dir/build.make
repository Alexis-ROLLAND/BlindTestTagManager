# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/arolland/LooCpp/BlindTestTagManager

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arolland/LooCpp/BlindTestTagManager

# Include any dependencies generated for this target.
include CMakeFiles/checkTags.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/checkTags.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/checkTags.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/checkTags.dir/flags.make

CMakeFiles/checkTags.dir/src/checkTags.cpp.o: CMakeFiles/checkTags.dir/flags.make
CMakeFiles/checkTags.dir/src/checkTags.cpp.o: src/checkTags.cpp
CMakeFiles/checkTags.dir/src/checkTags.cpp.o: CMakeFiles/checkTags.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/arolland/LooCpp/BlindTestTagManager/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/checkTags.dir/src/checkTags.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/checkTags.dir/src/checkTags.cpp.o -MF CMakeFiles/checkTags.dir/src/checkTags.cpp.o.d -o CMakeFiles/checkTags.dir/src/checkTags.cpp.o -c /home/arolland/LooCpp/BlindTestTagManager/src/checkTags.cpp

CMakeFiles/checkTags.dir/src/checkTags.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/checkTags.dir/src/checkTags.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arolland/LooCpp/BlindTestTagManager/src/checkTags.cpp > CMakeFiles/checkTags.dir/src/checkTags.cpp.i

CMakeFiles/checkTags.dir/src/checkTags.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/checkTags.dir/src/checkTags.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arolland/LooCpp/BlindTestTagManager/src/checkTags.cpp -o CMakeFiles/checkTags.dir/src/checkTags.cpp.s

CMakeFiles/checkTags.dir/src/tagManager.cpp.o: CMakeFiles/checkTags.dir/flags.make
CMakeFiles/checkTags.dir/src/tagManager.cpp.o: src/tagManager.cpp
CMakeFiles/checkTags.dir/src/tagManager.cpp.o: CMakeFiles/checkTags.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/arolland/LooCpp/BlindTestTagManager/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/checkTags.dir/src/tagManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/checkTags.dir/src/tagManager.cpp.o -MF CMakeFiles/checkTags.dir/src/tagManager.cpp.o.d -o CMakeFiles/checkTags.dir/src/tagManager.cpp.o -c /home/arolland/LooCpp/BlindTestTagManager/src/tagManager.cpp

CMakeFiles/checkTags.dir/src/tagManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/checkTags.dir/src/tagManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arolland/LooCpp/BlindTestTagManager/src/tagManager.cpp > CMakeFiles/checkTags.dir/src/tagManager.cpp.i

CMakeFiles/checkTags.dir/src/tagManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/checkTags.dir/src/tagManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arolland/LooCpp/BlindTestTagManager/src/tagManager.cpp -o CMakeFiles/checkTags.dir/src/tagManager.cpp.s

# Object files for target checkTags
checkTags_OBJECTS = \
"CMakeFiles/checkTags.dir/src/checkTags.cpp.o" \
"CMakeFiles/checkTags.dir/src/tagManager.cpp.o"

# External object files for target checkTags
checkTags_EXTERNAL_OBJECTS =

checkTags: CMakeFiles/checkTags.dir/src/checkTags.cpp.o
checkTags: CMakeFiles/checkTags.dir/src/tagManager.cpp.o
checkTags: CMakeFiles/checkTags.dir/build.make
checkTags: /usr/local/lib/libtag.a
checkTags: /usr/lib/x86_64-linux-gnu/libz.so
checkTags: CMakeFiles/checkTags.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/arolland/LooCpp/BlindTestTagManager/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable checkTags"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/checkTags.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/checkTags.dir/build: checkTags
.PHONY : CMakeFiles/checkTags.dir/build

CMakeFiles/checkTags.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/checkTags.dir/cmake_clean.cmake
.PHONY : CMakeFiles/checkTags.dir/clean

CMakeFiles/checkTags.dir/depend:
	cd /home/arolland/LooCpp/BlindTestTagManager && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arolland/LooCpp/BlindTestTagManager /home/arolland/LooCpp/BlindTestTagManager /home/arolland/LooCpp/BlindTestTagManager /home/arolland/LooCpp/BlindTestTagManager /home/arolland/LooCpp/BlindTestTagManager/CMakeFiles/checkTags.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/checkTags.dir/depend


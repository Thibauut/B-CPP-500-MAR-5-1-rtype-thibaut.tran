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
CMAKE_SOURCE_DIR = /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/build

# Include any dependencies generated for this target.
include CMakeFiles/r-type_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/r-type_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/r-type_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/r-type_client.dir/flags.make

CMakeFiles/r-type_client.dir/client/main.cpp.o: CMakeFiles/r-type_client.dir/flags.make
CMakeFiles/r-type_client.dir/client/main.cpp.o: ../client/main.cpp
CMakeFiles/r-type_client.dir/client/main.cpp.o: CMakeFiles/r-type_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/r-type_client.dir/client/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/r-type_client.dir/client/main.cpp.o -MF CMakeFiles/r-type_client.dir/client/main.cpp.o.d -o CMakeFiles/r-type_client.dir/client/main.cpp.o -c /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/client/main.cpp

CMakeFiles/r-type_client.dir/client/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/r-type_client.dir/client/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/client/main.cpp > CMakeFiles/r-type_client.dir/client/main.cpp.i

CMakeFiles/r-type_client.dir/client/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/r-type_client.dir/client/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/client/main.cpp -o CMakeFiles/r-type_client.dir/client/main.cpp.s

# Object files for target r-type_client
r__type_client_OBJECTS = \
"CMakeFiles/r-type_client.dir/client/main.cpp.o"

# External object files for target r-type_client
r__type_client_EXTERNAL_OBJECTS =

../r-type_client: CMakeFiles/r-type_client.dir/client/main.cpp.o
../r-type_client: CMakeFiles/r-type_client.dir/build.make
../r-type_client: libs/SFML/lib/libsfml-graphics.so.2.6.0
../r-type_client: libs/SFML/lib/libsfml-window.so.2.6.0
../r-type_client: libs/SFML/lib/libsfml-audio.so.2.6.0
../r-type_client: libs/SFML/lib/libsfml-system.so.2.6.0
../r-type_client: CMakeFiles/r-type_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../r-type_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/r-type_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/r-type_client.dir/build: ../r-type_client
.PHONY : CMakeFiles/r-type_client.dir/build

CMakeFiles/r-type_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/r-type_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/r-type_client.dir/clean

CMakeFiles/r-type_client.dir/depend:
	cd /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/build /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/build /home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/build/CMakeFiles/r-type_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/r-type_client.dir/depend


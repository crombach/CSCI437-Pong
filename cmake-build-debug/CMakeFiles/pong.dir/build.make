# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/cullen/Programs/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/cullen/Programs/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cullen/Code/school/pong

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cullen/Code/school/pong/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pong.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pong.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pong.dir/flags.make

CMakeFiles/pong.dir/bin/pong.cpp.o: CMakeFiles/pong.dir/flags.make
CMakeFiles/pong.dir/bin/pong.cpp.o: ../bin/pong.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cullen/Code/school/pong/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pong.dir/bin/pong.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pong.dir/bin/pong.cpp.o -c /home/cullen/Code/school/pong/bin/pong.cpp

CMakeFiles/pong.dir/bin/pong.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pong.dir/bin/pong.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cullen/Code/school/pong/bin/pong.cpp > CMakeFiles/pong.dir/bin/pong.cpp.i

CMakeFiles/pong.dir/bin/pong.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pong.dir/bin/pong.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cullen/Code/school/pong/bin/pong.cpp -o CMakeFiles/pong.dir/bin/pong.cpp.s

CMakeFiles/pong.dir/bin/pong.cpp.o.requires:

.PHONY : CMakeFiles/pong.dir/bin/pong.cpp.o.requires

CMakeFiles/pong.dir/bin/pong.cpp.o.provides: CMakeFiles/pong.dir/bin/pong.cpp.o.requires
	$(MAKE) -f CMakeFiles/pong.dir/build.make CMakeFiles/pong.dir/bin/pong.cpp.o.provides.build
.PHONY : CMakeFiles/pong.dir/bin/pong.cpp.o.provides

CMakeFiles/pong.dir/bin/pong.cpp.o.provides.build: CMakeFiles/pong.dir/bin/pong.cpp.o


CMakeFiles/pong.dir/src/Paddle.cpp.o: CMakeFiles/pong.dir/flags.make
CMakeFiles/pong.dir/src/Paddle.cpp.o: ../src/Paddle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cullen/Code/school/pong/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pong.dir/src/Paddle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pong.dir/src/Paddle.cpp.o -c /home/cullen/Code/school/pong/src/Paddle.cpp

CMakeFiles/pong.dir/src/Paddle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pong.dir/src/Paddle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cullen/Code/school/pong/src/Paddle.cpp > CMakeFiles/pong.dir/src/Paddle.cpp.i

CMakeFiles/pong.dir/src/Paddle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pong.dir/src/Paddle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cullen/Code/school/pong/src/Paddle.cpp -o CMakeFiles/pong.dir/src/Paddle.cpp.s

CMakeFiles/pong.dir/src/Paddle.cpp.o.requires:

.PHONY : CMakeFiles/pong.dir/src/Paddle.cpp.o.requires

CMakeFiles/pong.dir/src/Paddle.cpp.o.provides: CMakeFiles/pong.dir/src/Paddle.cpp.o.requires
	$(MAKE) -f CMakeFiles/pong.dir/build.make CMakeFiles/pong.dir/src/Paddle.cpp.o.provides.build
.PHONY : CMakeFiles/pong.dir/src/Paddle.cpp.o.provides

CMakeFiles/pong.dir/src/Paddle.cpp.o.provides.build: CMakeFiles/pong.dir/src/Paddle.cpp.o


CMakeFiles/pong.dir/src/Ball.cpp.o: CMakeFiles/pong.dir/flags.make
CMakeFiles/pong.dir/src/Ball.cpp.o: ../src/Ball.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cullen/Code/school/pong/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/pong.dir/src/Ball.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pong.dir/src/Ball.cpp.o -c /home/cullen/Code/school/pong/src/Ball.cpp

CMakeFiles/pong.dir/src/Ball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pong.dir/src/Ball.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cullen/Code/school/pong/src/Ball.cpp > CMakeFiles/pong.dir/src/Ball.cpp.i

CMakeFiles/pong.dir/src/Ball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pong.dir/src/Ball.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cullen/Code/school/pong/src/Ball.cpp -o CMakeFiles/pong.dir/src/Ball.cpp.s

CMakeFiles/pong.dir/src/Ball.cpp.o.requires:

.PHONY : CMakeFiles/pong.dir/src/Ball.cpp.o.requires

CMakeFiles/pong.dir/src/Ball.cpp.o.provides: CMakeFiles/pong.dir/src/Ball.cpp.o.requires
	$(MAKE) -f CMakeFiles/pong.dir/build.make CMakeFiles/pong.dir/src/Ball.cpp.o.provides.build
.PHONY : CMakeFiles/pong.dir/src/Ball.cpp.o.provides

CMakeFiles/pong.dir/src/Ball.cpp.o.provides.build: CMakeFiles/pong.dir/src/Ball.cpp.o


CMakeFiles/pong.dir/src/ScoreLabel.cpp.o: CMakeFiles/pong.dir/flags.make
CMakeFiles/pong.dir/src/ScoreLabel.cpp.o: ../src/ScoreLabel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cullen/Code/school/pong/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/pong.dir/src/ScoreLabel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pong.dir/src/ScoreLabel.cpp.o -c /home/cullen/Code/school/pong/src/ScoreLabel.cpp

CMakeFiles/pong.dir/src/ScoreLabel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pong.dir/src/ScoreLabel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cullen/Code/school/pong/src/ScoreLabel.cpp > CMakeFiles/pong.dir/src/ScoreLabel.cpp.i

CMakeFiles/pong.dir/src/ScoreLabel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pong.dir/src/ScoreLabel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cullen/Code/school/pong/src/ScoreLabel.cpp -o CMakeFiles/pong.dir/src/ScoreLabel.cpp.s

CMakeFiles/pong.dir/src/ScoreLabel.cpp.o.requires:

.PHONY : CMakeFiles/pong.dir/src/ScoreLabel.cpp.o.requires

CMakeFiles/pong.dir/src/ScoreLabel.cpp.o.provides: CMakeFiles/pong.dir/src/ScoreLabel.cpp.o.requires
	$(MAKE) -f CMakeFiles/pong.dir/build.make CMakeFiles/pong.dir/src/ScoreLabel.cpp.o.provides.build
.PHONY : CMakeFiles/pong.dir/src/ScoreLabel.cpp.o.provides

CMakeFiles/pong.dir/src/ScoreLabel.cpp.o.provides.build: CMakeFiles/pong.dir/src/ScoreLabel.cpp.o


CMakeFiles/pong.dir/src/CollisionUtils.cpp.o: CMakeFiles/pong.dir/flags.make
CMakeFiles/pong.dir/src/CollisionUtils.cpp.o: ../src/CollisionUtils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cullen/Code/school/pong/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/pong.dir/src/CollisionUtils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pong.dir/src/CollisionUtils.cpp.o -c /home/cullen/Code/school/pong/src/CollisionUtils.cpp

CMakeFiles/pong.dir/src/CollisionUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pong.dir/src/CollisionUtils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cullen/Code/school/pong/src/CollisionUtils.cpp > CMakeFiles/pong.dir/src/CollisionUtils.cpp.i

CMakeFiles/pong.dir/src/CollisionUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pong.dir/src/CollisionUtils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cullen/Code/school/pong/src/CollisionUtils.cpp -o CMakeFiles/pong.dir/src/CollisionUtils.cpp.s

CMakeFiles/pong.dir/src/CollisionUtils.cpp.o.requires:

.PHONY : CMakeFiles/pong.dir/src/CollisionUtils.cpp.o.requires

CMakeFiles/pong.dir/src/CollisionUtils.cpp.o.provides: CMakeFiles/pong.dir/src/CollisionUtils.cpp.o.requires
	$(MAKE) -f CMakeFiles/pong.dir/build.make CMakeFiles/pong.dir/src/CollisionUtils.cpp.o.provides.build
.PHONY : CMakeFiles/pong.dir/src/CollisionUtils.cpp.o.provides

CMakeFiles/pong.dir/src/CollisionUtils.cpp.o.provides.build: CMakeFiles/pong.dir/src/CollisionUtils.cpp.o


CMakeFiles/pong.dir/src/TextUtils.cpp.o: CMakeFiles/pong.dir/flags.make
CMakeFiles/pong.dir/src/TextUtils.cpp.o: ../src/TextUtils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cullen/Code/school/pong/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/pong.dir/src/TextUtils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pong.dir/src/TextUtils.cpp.o -c /home/cullen/Code/school/pong/src/TextUtils.cpp

CMakeFiles/pong.dir/src/TextUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pong.dir/src/TextUtils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cullen/Code/school/pong/src/TextUtils.cpp > CMakeFiles/pong.dir/src/TextUtils.cpp.i

CMakeFiles/pong.dir/src/TextUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pong.dir/src/TextUtils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cullen/Code/school/pong/src/TextUtils.cpp -o CMakeFiles/pong.dir/src/TextUtils.cpp.s

CMakeFiles/pong.dir/src/TextUtils.cpp.o.requires:

.PHONY : CMakeFiles/pong.dir/src/TextUtils.cpp.o.requires

CMakeFiles/pong.dir/src/TextUtils.cpp.o.provides: CMakeFiles/pong.dir/src/TextUtils.cpp.o.requires
	$(MAKE) -f CMakeFiles/pong.dir/build.make CMakeFiles/pong.dir/src/TextUtils.cpp.o.provides.build
.PHONY : CMakeFiles/pong.dir/src/TextUtils.cpp.o.provides

CMakeFiles/pong.dir/src/TextUtils.cpp.o.provides.build: CMakeFiles/pong.dir/src/TextUtils.cpp.o


# Object files for target pong
pong_OBJECTS = \
"CMakeFiles/pong.dir/bin/pong.cpp.o" \
"CMakeFiles/pong.dir/src/Paddle.cpp.o" \
"CMakeFiles/pong.dir/src/Ball.cpp.o" \
"CMakeFiles/pong.dir/src/ScoreLabel.cpp.o" \
"CMakeFiles/pong.dir/src/CollisionUtils.cpp.o" \
"CMakeFiles/pong.dir/src/TextUtils.cpp.o"

# External object files for target pong
pong_EXTERNAL_OBJECTS =

pong: CMakeFiles/pong.dir/bin/pong.cpp.o
pong: CMakeFiles/pong.dir/src/Paddle.cpp.o
pong: CMakeFiles/pong.dir/src/Ball.cpp.o
pong: CMakeFiles/pong.dir/src/ScoreLabel.cpp.o
pong: CMakeFiles/pong.dir/src/CollisionUtils.cpp.o
pong: CMakeFiles/pong.dir/src/TextUtils.cpp.o
pong: CMakeFiles/pong.dir/build.make
pong: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
pong: /usr/lib/x86_64-linux-gnu/libsfml-window.so
pong: /usr/lib/x86_64-linux-gnu/libsfml-system.so
pong: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
pong: /usr/lib/x86_64-linux-gnu/libsfml-network.so
pong: libpong_core.a
pong: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
pong: /usr/lib/x86_64-linux-gnu/libsfml-window.so
pong: /usr/lib/x86_64-linux-gnu/libsfml-system.so
pong: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
pong: /usr/lib/x86_64-linux-gnu/libsfml-network.so
pong: CMakeFiles/pong.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cullen/Code/school/pong/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable pong"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pong.dir/link.txt --verbose=$(VERBOSE)
	/home/cullen/Programs/clion-2017.2.2/bin/cmake/bin/cmake -E copy_directory /home/cullen/Code/school/pong/resources /home/cullen/Code/school/pong/cmake-build-debug/resources

# Rule to build all files generated by this target.
CMakeFiles/pong.dir/build: pong

.PHONY : CMakeFiles/pong.dir/build

CMakeFiles/pong.dir/requires: CMakeFiles/pong.dir/bin/pong.cpp.o.requires
CMakeFiles/pong.dir/requires: CMakeFiles/pong.dir/src/Paddle.cpp.o.requires
CMakeFiles/pong.dir/requires: CMakeFiles/pong.dir/src/Ball.cpp.o.requires
CMakeFiles/pong.dir/requires: CMakeFiles/pong.dir/src/ScoreLabel.cpp.o.requires
CMakeFiles/pong.dir/requires: CMakeFiles/pong.dir/src/CollisionUtils.cpp.o.requires
CMakeFiles/pong.dir/requires: CMakeFiles/pong.dir/src/TextUtils.cpp.o.requires

.PHONY : CMakeFiles/pong.dir/requires

CMakeFiles/pong.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pong.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pong.dir/clean

CMakeFiles/pong.dir/depend:
	cd /home/cullen/Code/school/pong/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cullen/Code/school/pong /home/cullen/Code/school/pong /home/cullen/Code/school/pong/cmake-build-debug /home/cullen/Code/school/pong/cmake-build-debug /home/cullen/Code/school/pong/cmake-build-debug/CMakeFiles/pong.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pong.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Desktop\Workspace\comp-477-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Desktop\Workspace\comp-477-project\cmake-build-release

# Include any dependencies generated for this target.
include lib/glfw/tests/CMakeFiles/opacity.dir/depend.make

# Include the progress variables for this target.
include lib/glfw/tests/CMakeFiles/opacity.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw/tests/CMakeFiles/opacity.dir/flags.make

lib/glfw/tests/CMakeFiles/opacity.dir/opacity.c.obj: lib/glfw/tests/CMakeFiles/opacity.dir/flags.make
lib/glfw/tests/CMakeFiles/opacity.dir/opacity.c.obj: lib/glfw/tests/CMakeFiles/opacity.dir/includes_C.rsp
lib/glfw/tests/CMakeFiles/opacity.dir/opacity.c.obj: ../lib/glfw/tests/opacity.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Desktop\Workspace\comp-477-project\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/glfw/tests/CMakeFiles/opacity.dir/opacity.c.obj"
	cd /d D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\opacity.dir\opacity.c.obj   -c D:\Desktop\Workspace\comp-477-project\lib\glfw\tests\opacity.c

lib/glfw/tests/CMakeFiles/opacity.dir/opacity.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opacity.dir/opacity.c.i"
	cd /d D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Desktop\Workspace\comp-477-project\lib\glfw\tests\opacity.c > CMakeFiles\opacity.dir\opacity.c.i

lib/glfw/tests/CMakeFiles/opacity.dir/opacity.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opacity.dir/opacity.c.s"
	cd /d D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Desktop\Workspace\comp-477-project\lib\glfw\tests\opacity.c -o CMakeFiles\opacity.dir\opacity.c.s

lib/glfw/tests/CMakeFiles/opacity.dir/__/deps/glad.c.obj: lib/glfw/tests/CMakeFiles/opacity.dir/flags.make
lib/glfw/tests/CMakeFiles/opacity.dir/__/deps/glad.c.obj: lib/glfw/tests/CMakeFiles/opacity.dir/includes_C.rsp
lib/glfw/tests/CMakeFiles/opacity.dir/__/deps/glad.c.obj: ../lib/glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Desktop\Workspace\comp-477-project\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/glfw/tests/CMakeFiles/opacity.dir/__/deps/glad.c.obj"
	cd /d D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\opacity.dir\__\deps\glad.c.obj   -c D:\Desktop\Workspace\comp-477-project\lib\glfw\deps\glad.c

lib/glfw/tests/CMakeFiles/opacity.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/opacity.dir/__/deps/glad.c.i"
	cd /d D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Desktop\Workspace\comp-477-project\lib\glfw\deps\glad.c > CMakeFiles\opacity.dir\__\deps\glad.c.i

lib/glfw/tests/CMakeFiles/opacity.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/opacity.dir/__/deps/glad.c.s"
	cd /d D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Desktop\Workspace\comp-477-project\lib\glfw\deps\glad.c -o CMakeFiles\opacity.dir\__\deps\glad.c.s

# Object files for target opacity
opacity_OBJECTS = \
"CMakeFiles/opacity.dir/opacity.c.obj" \
"CMakeFiles/opacity.dir/__/deps/glad.c.obj"

# External object files for target opacity
opacity_EXTERNAL_OBJECTS =

lib/glfw/tests/opacity.exe: lib/glfw/tests/CMakeFiles/opacity.dir/opacity.c.obj
lib/glfw/tests/opacity.exe: lib/glfw/tests/CMakeFiles/opacity.dir/__/deps/glad.c.obj
lib/glfw/tests/opacity.exe: lib/glfw/tests/CMakeFiles/opacity.dir/build.make
lib/glfw/tests/opacity.exe: lib/glfw/src/libglfw3.a
lib/glfw/tests/opacity.exe: lib/glfw/tests/CMakeFiles/opacity.dir/linklibs.rsp
lib/glfw/tests/opacity.exe: lib/glfw/tests/CMakeFiles/opacity.dir/objects1.rsp
lib/glfw/tests/opacity.exe: lib/glfw/tests/CMakeFiles/opacity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Desktop\Workspace\comp-477-project\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable opacity.exe"
	cd /d D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\opacity.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw/tests/CMakeFiles/opacity.dir/build: lib/glfw/tests/opacity.exe

.PHONY : lib/glfw/tests/CMakeFiles/opacity.dir/build

lib/glfw/tests/CMakeFiles/opacity.dir/clean:
	cd /d D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests && $(CMAKE_COMMAND) -P CMakeFiles\opacity.dir\cmake_clean.cmake
.PHONY : lib/glfw/tests/CMakeFiles/opacity.dir/clean

lib/glfw/tests/CMakeFiles/opacity.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Desktop\Workspace\comp-477-project D:\Desktop\Workspace\comp-477-project\lib\glfw\tests D:\Desktop\Workspace\comp-477-project\cmake-build-release D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests D:\Desktop\Workspace\comp-477-project\cmake-build-release\lib\glfw\tests\CMakeFiles\opacity.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw/tests/CMakeFiles/opacity.dir/depend


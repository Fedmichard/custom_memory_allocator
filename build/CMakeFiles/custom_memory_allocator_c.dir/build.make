# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\build

# Include any dependencies generated for this target.
include CMakeFiles/custom_memory_allocator_c.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/custom_memory_allocator_c.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/custom_memory_allocator_c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/custom_memory_allocator_c.dir/flags.make

CMakeFiles/custom_memory_allocator_c.dir/src/main.c.obj: CMakeFiles/custom_memory_allocator_c.dir/flags.make
CMakeFiles/custom_memory_allocator_c.dir/src/main.c.obj: CMakeFiles/custom_memory_allocator_c.dir/includes_C.rsp
CMakeFiles/custom_memory_allocator_c.dir/src/main.c.obj: C:/Users/franc/Documents/Personal_Projects/custom_memory_allocator/src/main.c
CMakeFiles/custom_memory_allocator_c.dir/src/main.c.obj: CMakeFiles/custom_memory_allocator_c.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/custom_memory_allocator_c.dir/src/main.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/custom_memory_allocator_c.dir/src/main.c.obj -MF CMakeFiles\custom_memory_allocator_c.dir\src\main.c.obj.d -o CMakeFiles\custom_memory_allocator_c.dir\src\main.c.obj -c C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\src\main.c

CMakeFiles/custom_memory_allocator_c.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/custom_memory_allocator_c.dir/src/main.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\src\main.c > CMakeFiles\custom_memory_allocator_c.dir\src\main.c.i

CMakeFiles/custom_memory_allocator_c.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/custom_memory_allocator_c.dir/src/main.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\src\main.c -o CMakeFiles\custom_memory_allocator_c.dir\src\main.c.s

# Object files for target custom_memory_allocator_c
custom_memory_allocator_c_OBJECTS = \
"CMakeFiles/custom_memory_allocator_c.dir/src/main.c.obj"

# External object files for target custom_memory_allocator_c
custom_memory_allocator_c_EXTERNAL_OBJECTS =

custom_memory_allocator_c.exe: CMakeFiles/custom_memory_allocator_c.dir/src/main.c.obj
custom_memory_allocator_c.exe: CMakeFiles/custom_memory_allocator_c.dir/build.make
custom_memory_allocator_c.exe: CMakeFiles/custom_memory_allocator_c.dir/linkLibs.rsp
custom_memory_allocator_c.exe: CMakeFiles/custom_memory_allocator_c.dir/objects1.rsp
custom_memory_allocator_c.exe: CMakeFiles/custom_memory_allocator_c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable custom_memory_allocator_c.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\custom_memory_allocator_c.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/custom_memory_allocator_c.dir/build: custom_memory_allocator_c.exe
.PHONY : CMakeFiles/custom_memory_allocator_c.dir/build

CMakeFiles/custom_memory_allocator_c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\custom_memory_allocator_c.dir\cmake_clean.cmake
.PHONY : CMakeFiles/custom_memory_allocator_c.dir/clean

CMakeFiles/custom_memory_allocator_c.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\build C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\build C:\Users\franc\Documents\Personal_Projects\custom_memory_allocator\build\CMakeFiles\custom_memory_allocator_c.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/custom_memory_allocator_c.dir/depend

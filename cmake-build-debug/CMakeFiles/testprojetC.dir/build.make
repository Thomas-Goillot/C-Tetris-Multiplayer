# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = C:\Users\joshua\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\joshua\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CLionProjects\2_eme_annee\testprojetC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CLionProjects\2_eme_annee\testprojetC\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/testprojetC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testprojetC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testprojetC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testprojetC.dir/flags.make

CMakeFiles/testprojetC.dir/main.c.obj: CMakeFiles/testprojetC.dir/flags.make
CMakeFiles/testprojetC.dir/main.c.obj: D:/CLionProjects/2_eme_annee/testprojetC/main.c
CMakeFiles/testprojetC.dir/main.c.obj: CMakeFiles/testprojetC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionProjects\2_eme_annee\testprojetC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/testprojetC.dir/main.c.obj"
	C:\Mingw\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/testprojetC.dir/main.c.obj -MF CMakeFiles\testprojetC.dir\main.c.obj.d -o CMakeFiles\testprojetC.dir\main.c.obj -c D:\CLionProjects\2_eme_annee\testprojetC\main.c

CMakeFiles/testprojetC.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testprojetC.dir/main.c.i"
	C:\Mingw\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\CLionProjects\2_eme_annee\testprojetC\main.c > CMakeFiles\testprojetC.dir\main.c.i

CMakeFiles/testprojetC.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testprojetC.dir/main.c.s"
	C:\Mingw\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\CLionProjects\2_eme_annee\testprojetC\main.c -o CMakeFiles\testprojetC.dir\main.c.s

# Object files for target testprojetC
testprojetC_OBJECTS = \
"CMakeFiles/testprojetC.dir/main.c.obj"

# External object files for target testprojetC
testprojetC_EXTERNAL_OBJECTS =

testprojetC.exe: CMakeFiles/testprojetC.dir/main.c.obj
testprojetC.exe: CMakeFiles/testprojetC.dir/build.make
testprojetC.exe: CMakeFiles/testprojetC.dir/linklibs.rsp
testprojetC.exe: CMakeFiles/testprojetC.dir/objects1.rsp
testprojetC.exe: CMakeFiles/testprojetC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionProjects\2_eme_annee\testprojetC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable testprojetC.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\testprojetC.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testprojetC.dir/build: testprojetC.exe
.PHONY : CMakeFiles/testprojetC.dir/build

CMakeFiles/testprojetC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\testprojetC.dir\cmake_clean.cmake
.PHONY : CMakeFiles/testprojetC.dir/clean

CMakeFiles/testprojetC.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionProjects\2_eme_annee\testprojetC D:\CLionProjects\2_eme_annee\testprojetC D:\CLionProjects\2_eme_annee\testprojetC\cmake-build-debug D:\CLionProjects\2_eme_annee\testprojetC\cmake-build-debug D:\CLionProjects\2_eme_annee\testprojetC\cmake-build-debug\CMakeFiles\testprojetC.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testprojetC.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /cygdrive/c/Users/sbruno/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/sbruno/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/CatchUnitTesting.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CatchUnitTesting.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CatchUnitTesting.dir/flags.make

CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.o: CMakeFiles/CatchUnitTesting.dir/flags.make
CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.o: ../CIniFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.o -c "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/CIniFile.cpp"

CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/CIniFile.cpp" > CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.i

CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/CIniFile.cpp" -o CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.s

CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.o: CMakeFiles/CatchUnitTesting.dir/flags.make
CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.o: ../TestCIniFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.o -c "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/TestCIniFile.cpp"

CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/TestCIniFile.cpp" > CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.i

CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/TestCIniFile.cpp" -o CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.s

# Object files for target CatchUnitTesting
CatchUnitTesting_OBJECTS = \
"CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.o" \
"CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.o"

# External object files for target CatchUnitTesting
CatchUnitTesting_EXTERNAL_OBJECTS =

CatchUnitTesting.exe: CMakeFiles/CatchUnitTesting.dir/CIniFile.cpp.o
CatchUnitTesting.exe: CMakeFiles/CatchUnitTesting.dir/TestCIniFile.cpp.o
CatchUnitTesting.exe: CMakeFiles/CatchUnitTesting.dir/build.make
CatchUnitTesting.exe: CMakeFiles/CatchUnitTesting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable CatchUnitTesting.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CatchUnitTesting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CatchUnitTesting.dir/build: CatchUnitTesting.exe

.PHONY : CMakeFiles/CatchUnitTesting.dir/build

CMakeFiles/CatchUnitTesting.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CatchUnitTesting.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CatchUnitTesting.dir/clean

CMakeFiles/CatchUnitTesting.dir/depend:
	cd "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject" "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject" "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/cmake-build-debug" "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/cmake-build-debug" "/cygdrive/c/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/cmake-build-debug/CMakeFiles/CatchUnitTesting.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/CatchUnitTesting.dir/depend


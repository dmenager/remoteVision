# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc"

# Include any dependencies generated for this target.
include CMakeFiles/remoteVision.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/remoteVision.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/remoteVision.dir/flags.make

CMakeFiles/remoteVision.dir/main.cpp.o: CMakeFiles/remoteVision.dir/flags.make
CMakeFiles/remoteVision.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/remoteVision.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/remoteVision.dir/main.cpp.o -c "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/main.cpp"

CMakeFiles/remoteVision.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remoteVision.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/main.cpp" > CMakeFiles/remoteVision.dir/main.cpp.i

CMakeFiles/remoteVision.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remoteVision.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/main.cpp" -o CMakeFiles/remoteVision.dir/main.cpp.s

CMakeFiles/remoteVision.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/remoteVision.dir/main.cpp.o.requires

CMakeFiles/remoteVision.dir/main.cpp.o.provides: CMakeFiles/remoteVision.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/remoteVision.dir/build.make CMakeFiles/remoteVision.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/remoteVision.dir/main.cpp.o.provides

CMakeFiles/remoteVision.dir/main.cpp.o.provides.build: CMakeFiles/remoteVision.dir/main.cpp.o

CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o: CMakeFiles/remoteVision.dir/flags.make
CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o: ../avcaptureremote.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o -c "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/avcaptureremote.cpp"

CMakeFiles/remoteVision.dir/avcaptureremote.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remoteVision.dir/avcaptureremote.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/avcaptureremote.cpp" > CMakeFiles/remoteVision.dir/avcaptureremote.cpp.i

CMakeFiles/remoteVision.dir/avcaptureremote.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remoteVision.dir/avcaptureremote.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/avcaptureremote.cpp" -o CMakeFiles/remoteVision.dir/avcaptureremote.cpp.s

CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o.requires:
.PHONY : CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o.requires

CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o.provides: CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o.requires
	$(MAKE) -f CMakeFiles/remoteVision.dir/build.make CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o.provides.build
.PHONY : CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o.provides

CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o.provides.build: CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o

CMakeFiles/remoteVision.dir/dmfunctions.cpp.o: CMakeFiles/remoteVision.dir/flags.make
CMakeFiles/remoteVision.dir/dmfunctions.cpp.o: ../dmfunctions.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc/CMakeFiles" $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/remoteVision.dir/dmfunctions.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/remoteVision.dir/dmfunctions.cpp.o -c "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/dmfunctions.cpp"

CMakeFiles/remoteVision.dir/dmfunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remoteVision.dir/dmfunctions.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/dmfunctions.cpp" > CMakeFiles/remoteVision.dir/dmfunctions.cpp.i

CMakeFiles/remoteVision.dir/dmfunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remoteVision.dir/dmfunctions.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/dmfunctions.cpp" -o CMakeFiles/remoteVision.dir/dmfunctions.cpp.s

CMakeFiles/remoteVision.dir/dmfunctions.cpp.o.requires:
.PHONY : CMakeFiles/remoteVision.dir/dmfunctions.cpp.o.requires

CMakeFiles/remoteVision.dir/dmfunctions.cpp.o.provides: CMakeFiles/remoteVision.dir/dmfunctions.cpp.o.requires
	$(MAKE) -f CMakeFiles/remoteVision.dir/build.make CMakeFiles/remoteVision.dir/dmfunctions.cpp.o.provides.build
.PHONY : CMakeFiles/remoteVision.dir/dmfunctions.cpp.o.provides

CMakeFiles/remoteVision.dir/dmfunctions.cpp.o.provides.build: CMakeFiles/remoteVision.dir/dmfunctions.cpp.o

CMakeFiles/remoteVision.dir/dataReader.cpp.o: CMakeFiles/remoteVision.dir/flags.make
CMakeFiles/remoteVision.dir/dataReader.cpp.o: ../dataReader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc/CMakeFiles" $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/remoteVision.dir/dataReader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/remoteVision.dir/dataReader.cpp.o -c "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/dataReader.cpp"

CMakeFiles/remoteVision.dir/dataReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remoteVision.dir/dataReader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/dataReader.cpp" > CMakeFiles/remoteVision.dir/dataReader.cpp.i

CMakeFiles/remoteVision.dir/dataReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remoteVision.dir/dataReader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/dataReader.cpp" -o CMakeFiles/remoteVision.dir/dataReader.cpp.s

CMakeFiles/remoteVision.dir/dataReader.cpp.o.requires:
.PHONY : CMakeFiles/remoteVision.dir/dataReader.cpp.o.requires

CMakeFiles/remoteVision.dir/dataReader.cpp.o.provides: CMakeFiles/remoteVision.dir/dataReader.cpp.o.requires
	$(MAKE) -f CMakeFiles/remoteVision.dir/build.make CMakeFiles/remoteVision.dir/dataReader.cpp.o.provides.build
.PHONY : CMakeFiles/remoteVision.dir/dataReader.cpp.o.provides

CMakeFiles/remoteVision.dir/dataReader.cpp.o.provides.build: CMakeFiles/remoteVision.dir/dataReader.cpp.o

CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o: CMakeFiles/remoteVision.dir/flags.make
CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o: ../neuralNetwork.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc/CMakeFiles" $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o -c "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/neuralNetwork.cpp"

CMakeFiles/remoteVision.dir/neuralNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remoteVision.dir/neuralNetwork.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/neuralNetwork.cpp" > CMakeFiles/remoteVision.dir/neuralNetwork.cpp.i

CMakeFiles/remoteVision.dir/neuralNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remoteVision.dir/neuralNetwork.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/neuralNetwork.cpp" -o CMakeFiles/remoteVision.dir/neuralNetwork.cpp.s

CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o.requires:
.PHONY : CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o.requires

CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o.provides: CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o.requires
	$(MAKE) -f CMakeFiles/remoteVision.dir/build.make CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o.provides.build
.PHONY : CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o.provides

CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o.provides.build: CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o

CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o: CMakeFiles/remoteVision.dir/flags.make
CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o: ../neuralNetworkTrainer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc/CMakeFiles" $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o -c "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/neuralNetworkTrainer.cpp"

CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/neuralNetworkTrainer.cpp" > CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.i

CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/neuralNetworkTrainer.cpp" -o CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.s

CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o.requires:
.PHONY : CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o.requires

CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o.provides: CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o.requires
	$(MAKE) -f CMakeFiles/remoteVision.dir/build.make CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o.provides.build
.PHONY : CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o.provides

CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o.provides.build: CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o

# Object files for target remoteVision
remoteVision_OBJECTS = \
"CMakeFiles/remoteVision.dir/main.cpp.o" \
"CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o" \
"CMakeFiles/remoteVision.dir/dmfunctions.cpp.o" \
"CMakeFiles/remoteVision.dir/dataReader.cpp.o" \
"CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o" \
"CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o"

# External object files for target remoteVision
remoteVision_EXTERNAL_OBJECTS =

sdk/bin/remoteVision: CMakeFiles/remoteVision.dir/main.cpp.o
sdk/bin/remoteVision: CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o
sdk/bin/remoteVision: CMakeFiles/remoteVision.dir/dmfunctions.cpp.o
sdk/bin/remoteVision: CMakeFiles/remoteVision.dir/dataReader.cpp.o
sdk/bin/remoteVision: CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o
sdk/bin/remoteVision: CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o
sdk/bin/remoteVision: CMakeFiles/remoteVision.dir/build.make
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalaudio.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalvision.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalextractor.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalproxies.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalproxies.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalcommon.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalsoap.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/librttools.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalthread.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_signals-mt.a
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_program_options-mt.a
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalvalue.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libtinyxml.so
sdk/bin/remoteVision: /usr/lib/x86_64-linux-gnu/librt.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libqi.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_filesystem-mt.a
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_thread-mt.a
sdk/bin/remoteVision: /usr/lib/x86_64-linux-gnu/libpthread.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_system-mt.a
sdk/bin/remoteVision: /usr/lib/x86_64-linux-gnu/libdl.so
sdk/bin/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalerror.so
sdk/bin/remoteVision: /usr/local/lib/libopencv_highgui.so
sdk/bin/remoteVision: /usr/local/lib/libopencv_imgproc.so
sdk/bin/remoteVision: /usr/local/lib/libopencv_core.so
sdk/bin/remoteVision: CMakeFiles/remoteVision.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sdk/bin/remoteVision"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/remoteVision.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/remoteVision.dir/build: sdk/bin/remoteVision
.PHONY : CMakeFiles/remoteVision.dir/build

# Object files for target remoteVision
remoteVision_OBJECTS = \
"CMakeFiles/remoteVision.dir/main.cpp.o" \
"CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o" \
"CMakeFiles/remoteVision.dir/dmfunctions.cpp.o" \
"CMakeFiles/remoteVision.dir/dataReader.cpp.o" \
"CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o" \
"CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o"

# External object files for target remoteVision
remoteVision_EXTERNAL_OBJECTS =

CMakeFiles/CMakeRelink.dir/remoteVision: CMakeFiles/remoteVision.dir/main.cpp.o
CMakeFiles/CMakeRelink.dir/remoteVision: CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o
CMakeFiles/CMakeRelink.dir/remoteVision: CMakeFiles/remoteVision.dir/dmfunctions.cpp.o
CMakeFiles/CMakeRelink.dir/remoteVision: CMakeFiles/remoteVision.dir/dataReader.cpp.o
CMakeFiles/CMakeRelink.dir/remoteVision: CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o
CMakeFiles/CMakeRelink.dir/remoteVision: CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o
CMakeFiles/CMakeRelink.dir/remoteVision: CMakeFiles/remoteVision.dir/build.make
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalaudio.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalvision.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalextractor.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalproxies.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalproxies.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalcommon.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalsoap.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/librttools.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalthread.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_signals-mt.a
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_program_options-mt.a
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalvalue.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libtinyxml.so
CMakeFiles/CMakeRelink.dir/remoteVision: /usr/lib/x86_64-linux-gnu/librt.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libqi.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_filesystem-mt.a
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_thread-mt.a
CMakeFiles/CMakeRelink.dir/remoteVision: /usr/lib/x86_64-linux-gnu/libpthread.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libboost_system-mt.a
CMakeFiles/CMakeRelink.dir/remoteVision: /usr/lib/x86_64-linux-gnu/libdl.so
CMakeFiles/CMakeRelink.dir/remoteVision: /home/dmenager/NAO/SDK/naoqi-sdk-1.14.5-linux64/lib/libalerror.so
CMakeFiles/CMakeRelink.dir/remoteVision: /usr/local/lib/libopencv_highgui.so
CMakeFiles/CMakeRelink.dir/remoteVision: /usr/local/lib/libopencv_imgproc.so
CMakeFiles/CMakeRelink.dir/remoteVision: /usr/local/lib/libopencv_core.so
CMakeFiles/CMakeRelink.dir/remoteVision: CMakeFiles/remoteVision.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable CMakeFiles/CMakeRelink.dir/remoteVision"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/remoteVision.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
CMakeFiles/remoteVision.dir/preinstall: CMakeFiles/CMakeRelink.dir/remoteVision
.PHONY : CMakeFiles/remoteVision.dir/preinstall

CMakeFiles/remoteVision.dir/requires: CMakeFiles/remoteVision.dir/main.cpp.o.requires
CMakeFiles/remoteVision.dir/requires: CMakeFiles/remoteVision.dir/avcaptureremote.cpp.o.requires
CMakeFiles/remoteVision.dir/requires: CMakeFiles/remoteVision.dir/dmfunctions.cpp.o.requires
CMakeFiles/remoteVision.dir/requires: CMakeFiles/remoteVision.dir/dataReader.cpp.o.requires
CMakeFiles/remoteVision.dir/requires: CMakeFiles/remoteVision.dir/neuralNetwork.cpp.o.requires
CMakeFiles/remoteVision.dir/requires: CMakeFiles/remoteVision.dir/neuralNetworkTrainer.cpp.o.requires
.PHONY : CMakeFiles/remoteVision.dir/requires

CMakeFiles/remoteVision.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/remoteVision.dir/cmake_clean.cmake
.PHONY : CMakeFiles/remoteVision.dir/clean

CMakeFiles/remoteVision.dir/depend:
	cd "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision" "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision" "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc" "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc" "/home/dmenager/NAO/AE 756 Worktree/remoteVision/RemoteVision/build-tc/CMakeFiles/remoteVision.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/remoteVision.dir/depend


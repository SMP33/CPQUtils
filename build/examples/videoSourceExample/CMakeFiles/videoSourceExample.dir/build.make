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
CMAKE_COMMAND = C:\Qt\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Qt\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mikha\source\repos\CPQUtils

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mikha\source\repos\CPQUtils\build

# Include any dependencies generated for this target.
include examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/depend.make

# Include the progress variables for this target.
include examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/progress.make

# Include the compile flags for this target's objects.
include examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/flags.make

examples/videoSourceExample/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp: ../examples/videoSourceExample/resources.qrc
examples/videoSourceExample/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp: examples/videoSourceExample/CMakeFiles/videoSourceExample_autogen.dir/AutoRcc_resources_EWIEGA46WW_Info.json
examples/videoSourceExample/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp: ../examples/videoSourceExample/index.html
examples/videoSourceExample/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp: C:/Qt/5.12.2/mingw73_64/bin/rcc.exe
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\mikha\source\repos\CPQUtils\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for resources.qrc"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\CMake_64\bin\cmake.exe -E cmake_autorcc C:/Users/mikha/source/repos/CPQUtils/build/examples/videoSourceExample/CMakeFiles/videoSourceExample_autogen.dir/AutoRcc_resources_EWIEGA46WW_Info.json Debug

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.obj: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/flags.make
examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.obj: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/includes_CXX.rsp
examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.obj: examples/videoSourceExample/videoSourceExample_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mikha\source\repos\CPQUtils\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.obj"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\videoSourceExample.dir\videoSourceExample_autogen\mocs_compilation.cpp.obj -c C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample\videoSourceExample_autogen\mocs_compilation.cpp

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.i"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample\videoSourceExample_autogen\mocs_compilation.cpp > CMakeFiles\videoSourceExample.dir\videoSourceExample_autogen\mocs_compilation.cpp.i

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.s"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample\videoSourceExample_autogen\mocs_compilation.cpp -o CMakeFiles\videoSourceExample.dir\videoSourceExample_autogen\mocs_compilation.cpp.s

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.obj: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/flags.make
examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.obj: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/includes_CXX.rsp
examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.obj: ../examples/videoSourceExample/videoSourceExample.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mikha\source\repos\CPQUtils\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.obj"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\videoSourceExample.dir\videoSourceExample.cpp.obj -c C:\Users\mikha\source\repos\CPQUtils\examples\videoSourceExample\videoSourceExample.cpp

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.i"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mikha\source\repos\CPQUtils\examples\videoSourceExample\videoSourceExample.cpp > CMakeFiles\videoSourceExample.dir\videoSourceExample.cpp.i

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.s"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\mikha\source\repos\CPQUtils\examples\videoSourceExample\videoSourceExample.cpp -o CMakeFiles\videoSourceExample.dir\videoSourceExample.cpp.s

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.obj: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/flags.make
examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.obj: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/includes_CXX.rsp
examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.obj: examples/videoSourceExample/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mikha\source\repos\CPQUtils\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.obj"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\videoSourceExample.dir\videoSourceExample_autogen\EWIEGA46WW\qrc_resources.cpp.obj -c C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample\videoSourceExample_autogen\EWIEGA46WW\qrc_resources.cpp

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.i"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample\videoSourceExample_autogen\EWIEGA46WW\qrc_resources.cpp > CMakeFiles\videoSourceExample.dir\videoSourceExample_autogen\EWIEGA46WW\qrc_resources.cpp.i

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.s"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && C:\Qt\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample\videoSourceExample_autogen\EWIEGA46WW\qrc_resources.cpp -o CMakeFiles\videoSourceExample.dir\videoSourceExample_autogen\EWIEGA46WW\qrc_resources.cpp.s

# Object files for target videoSourceExample
videoSourceExample_OBJECTS = \
"CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.obj" \
"CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.obj"

# External object files for target videoSourceExample
videoSourceExample_EXTERNAL_OBJECTS =

examples/videoSourceExample/videoSourceExample.exe: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/mocs_compilation.cpp.obj
examples/videoSourceExample/videoSourceExample.exe: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample.cpp.obj
examples/videoSourceExample/videoSourceExample.exe: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp.obj
examples/videoSourceExample/videoSourceExample.exe: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/build.make
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_gapi420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_stitching420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_aruco420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_bgsegm420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_bioinspired420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_ccalib420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dnn_objdetect420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dnn_superres420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dpm420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_face420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_fuzzy420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_hfs420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_img_hash420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_line_descriptor420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_quality420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_reg420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_rgbd420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_saliency420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_stereo420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_structured_light420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_superres420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_surface_matching420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_tracking420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_videostab420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_xfeatures2d420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_xobjdetect420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_xphoto420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: C:/Qt/5.12.2/mingw73_64/lib/libQt5Networkd.a
examples/videoSourceExample/videoSourceExample.exe: src/Web/libWeb.a
examples/videoSourceExample/videoSourceExample.exe: src/Vision/libVision.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_shape420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_highgui420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_datasets420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_plot420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_text420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dnn420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_ml420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_phase_unwrapping420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_optflow420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_ximgproc420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_video420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_videoio420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_imgcodecs420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_objdetect420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_calib3d420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_features2d420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_flann420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_photo420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_imgproc420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_core420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: C:/Qt/5.12.2/mingw73_64/lib/libQt5Cored.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_gapi420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_stitching420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_aruco420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_bgsegm420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_bioinspired420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_ccalib420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dnn_objdetect420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dnn_superres420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dpm420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_highgui420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_face420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_fuzzy420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_hfs420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_img_hash420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_line_descriptor420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_quality420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_reg420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_rgbd420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_saliency420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_stereo420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_structured_light420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_phase_unwrapping420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_superres420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_optflow420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_surface_matching420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_tracking420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_datasets420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_plot420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_text420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_dnn420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_videostab420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_videoio420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_xfeatures2d420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_ml420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_shape420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_ximgproc420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_video420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_xobjdetect420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_imgcodecs420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_objdetect420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_calib3d420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_features2d420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_flann420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_xphoto420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_photo420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_imgproc420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: D:/opencv/build/install/x64/mingw/lib/libopencv_core420d.dll.a
examples/videoSourceExample/videoSourceExample.exe: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/linklibs.rsp
examples/videoSourceExample/videoSourceExample.exe: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/objects1.rsp
examples/videoSourceExample/videoSourceExample.exe: examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\mikha\source\repos\CPQUtils\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable videoSourceExample.exe"
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\videoSourceExample.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/build: examples/videoSourceExample/videoSourceExample.exe

.PHONY : examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/build

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/clean:
	cd /d C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample && $(CMAKE_COMMAND) -P CMakeFiles\videoSourceExample.dir\cmake_clean.cmake
.PHONY : examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/clean

examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/depend: examples/videoSourceExample/videoSourceExample_autogen/EWIEGA46WW/qrc_resources.cpp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\mikha\source\repos\CPQUtils C:\Users\mikha\source\repos\CPQUtils\examples\videoSourceExample C:\Users\mikha\source\repos\CPQUtils\build C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample C:\Users\mikha\source\repos\CPQUtils\build\examples\videoSourceExample\CMakeFiles\videoSourceExample.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/videoSourceExample/CMakeFiles/videoSourceExample.dir/depend


message("")
message("========== Library Vision ==========")

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Eigen3)
find_package(OpenCV)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Eigen3_INCLUDE_DIRS})

message("  OpenCV_FOUND: ${OpenCV_FOUND}")
message("  Eigen3_FOUND: ${Eigen3_FOUND}")

if(NO_OPENCV) #Build without CV
    add_compile_definitions(NO_OPENCV)
    message(WARNING "OpenCV was not found!"
        "The project will be built, but some functions will not be available")
else() #Build with CV
    if(NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV was not found!"
            "If you want to build project with OpenCV you must install it"
            "If you don't want to build a project with OpenCV run cmake with option -DNO_OPENCV=ON")
    endif()
    if(NOT Eigen3_FOUND)
        message(FATAL_ERROR "Eigen3 was not found!"
            "You can install it from here: https://gitlab.com/libeigen/eigen"
            "If you want to build project with OpenCV you must install it")
    endif()
endif()
cpq_glob_cpp()
add_library(Vision ${SOURCE_CPP})
target_link_libraries(Vision PUBLIC ${OpenCV_LIBS})

message("")



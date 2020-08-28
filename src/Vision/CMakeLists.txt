message("")
message("========== Library Vision ==========")
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Eigen3)
find_package(OpenCV)

include_directories(${Qt5Core_INCLUDE_DIRS})

message("  OpenCV_FOUND: ${OpenCV_FOUND}")
message("  Eigen3_FOUND: ${Eigen3_FOUND}")

if(OpenCV_FOUND)#Build with CV
    if(NOT Eigen3_FOUND)
#        message(FATAL_ERROR "Eigen3 was not found!\r\n"
#            "You can install it from here: https://gitlab.com/libeigen/eigen")
    endif()
else()#Build without CV
    message(WARNING "OpenCV was not found!\r\n"
        "The project will be built, but some functions will not be available")
    add_definitions(-DBUILD_WITH_OPENCV)
endif()

add_library(Vision VideoSource.cpp)

message("")



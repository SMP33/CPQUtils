message("")
message("========== Library Core ==========")

find_package(Qt5 REQUIRED COMPONENTS Core Network)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

message("  Eigen3_FOUND: ${Eigen3_FOUND}")

    if(NOT Eigen3_FOUND)
       message(FATAL_ERROR "Eigen3 was not found!"
       "You can install it from here: https://gitlab.com/libeigen/eigen")
    endif()

cpq_glob_cpp()
add_library(Core ${SOURCE_CPP})



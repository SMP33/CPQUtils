message("")
message("========== Library Core ==========")

find_package(Qt5 REQUIRED COMPONENTS Core Network)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

cpq_glob_cpp()
add_library(Core ${SOURCE_CPP})



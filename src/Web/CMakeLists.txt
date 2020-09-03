message("")
message("========== Library Web ==========")

find_package(Qt5 REQUIRED COMPONENTS Core Network)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

cpq_glob_cpp()
add_library(Web ${SOURCE_CPP})



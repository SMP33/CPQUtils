message("")
message("Library Web:")

find_package(Qt5 REQUIRED COMPONENTS Core Network)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_CPP "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(FILTER SOURCE_CPP EXCLUDE REGEX ".*/examples/.*.cpp")

message("  SOURCE_CPP:")

foreach(S ${SOURCE_CPP})
    message("    ${S}")
endforeach()
message("")

add_library(Web STATIC ${SOURCE_CPP} "../Web.h")


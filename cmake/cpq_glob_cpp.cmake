macro(cpq_glob_cpp)

file(GLOB_RECURSE SOURCE_CPP "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
message("  Source files:")

foreach(S ${SOURCE_CPP})
    message("    ${S}")
endforeach()

endmacro()

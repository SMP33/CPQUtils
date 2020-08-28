message("Examples dir: ${CMAKE_CURRENT_SOURCE_DIR}")

SUBDIRLIST(examplesSubdirs ${CMAKE_CURRENT_SOURCE_DIR})
message("Examples list:")

foreach(dir ${examplesSubdirs})
    message("  ${dir}")
    add_subdirectory(${dir})
endforeach()

message("")

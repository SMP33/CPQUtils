cmake_minimum_required(VERSION 3.1.0)

project(CPQUtils LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network)

include("cmake/subdirList.cmake")
include("cmake/cpq_install_headers.cmake")
include("cmake/cpq_glob_cpp.cmake")

add_subdirectory("src")
add_subdirectory("examples")

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "uninstall.cmake"
    )
configure_file(cmake/uninstall.cmake uninstall.cmake @ONLY)

install(TARGETS
    Web Vision
    EXPORT Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    )

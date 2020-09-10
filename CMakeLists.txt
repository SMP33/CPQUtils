cmake_minimum_required(VERSION 3.1.0)

project(CPQUtils LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)

set(CPQUtils_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include)

find_package(Qt5 REQUIRED COMPONENTS Core Network)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIR})

message("${EIGEN3_INCLUDE_DIR}")

include("cmake/subdirList.cmake")
include("cmake/cpq_install_headers.cmake")
include("cmake/cpq_glob_cpp.cmake")
#include("cmake/doxyCmake.cmake")

add_subdirectory("src")
add_subdirectory("examples")

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "uninstall.cmake"
    )

    
#SET(DOXY_OUTPUT_LANGUAGE "Russian")
#SET(DOXY_INPUT ${PROJECT_SOURCE_DIR}/src)
#ADD_DOCUMENTATION(doc Doxyfile)


configure_file(cmake/uninstall.cmake uninstall.cmake @ONLY)

configure_file(cmake/CPQUtilsConfig.cmake CPQUtilsConfig.cmake)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/${CMAKE_PROJECT_NAME}
)

install(TARGETS
        Web Vision Core
        EXPORT Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

install(EXPORT Targets
        FILE Targets.cmake
        NAMESPACE CPQUtils::
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/CPQUtils
         )

export(PACKAGE CPQUtils)

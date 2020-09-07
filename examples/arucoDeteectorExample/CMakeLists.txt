find_package(Qt5 REQUIRED COMPONENTS Core Network)
find_package(OpenCV)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

if(OpenCV_FOUND)
add_executable(arucoDetectorExample arucoDetectorExample.cpp resources.qrc)

target_link_libraries(arucoDetectorExample
    Web
    Vision
    ${OpenCV_LIBS}
    Qt5::Core
    Qt5::Network

    )
endif()
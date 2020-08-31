find_package(Qt5 REQUIRED COMPONENTS Core Network)
find_package(OpenCV )

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

add_executable(videoSourceExample videoSourceExample.cpp resources.qrc)

target_link_libraries(videoSourceExample
    Web
    Vision
    ${OpenCV_LIBS}
    Qt5::Core
    Qt5::Network

    )

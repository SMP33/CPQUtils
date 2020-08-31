find_package(Qt5 REQUIRED COMPONENTS Core Network)
find_package(OpenCV REQUIRED)

add_executable(videoSourceExample videoSourceExample.cpp resources.qrc)

target_link_libraries(videoSourceExample
    ${OpenCV_LIBS}
    Qt5::Core
    Qt5::Network
    Web
    Vision
    )

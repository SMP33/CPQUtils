find_package(Qt5 REQUIRED COMPONENTS Core Network)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

add_executable(simpleHttpServer simpleHttpServer.cpp)

target_link_libraries(simpleHttpServer
    Web
    Qt5::Core
    Qt5::Network)

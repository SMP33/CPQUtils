add_executable(simpleHttpServer simpleHttpServer.cpp)

target_link_libraries(simpleHttpServer
    Web
    Qt5::Core
    Qt5::Network)

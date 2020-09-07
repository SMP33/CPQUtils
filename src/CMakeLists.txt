add_subdirectory("Core")
add_subdirectory("Web")
add_subdirectory("Vision")

message("========== Headers to install ==========")
cpq_install_headers()
message("")

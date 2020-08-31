MACRO(cpq_install_headers)
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
list(FILTER HEADERS EXCLUDE REGEX ".*_private.h")
message("Exclude regex: \".*_private.h\"")

foreach(H ${HEADERS})
    message("    ${H} ->")
    get_filename_component(DEST ${H} DIRECTORY)
    string(REPLACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_INSTALL_PREFIX}/include"
        DEST
        ${DEST}
        )
    message("      ${DEST};")
    install(FILES ${H} DESTINATION ${DEST})
endforeach()
ENDMACRO()

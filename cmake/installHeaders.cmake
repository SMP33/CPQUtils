MACRO(installHeaders)
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
foreach(H ${HEADERS})
    message("    ${H} =>")
    get_filename_component(DEST ${H} DIRECTORY)
    string(REPLACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_INSTALL_PREFIX}/include"
        DEST
        ${DEST}
        )
    message("      ${DEST}")
    install(FILES ${H} DESTINATION ${DEST})
endforeach()
ENDMACRO()

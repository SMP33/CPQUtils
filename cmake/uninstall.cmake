set(MANIFEST ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt)

message(${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt)

if(NOT EXISTS ${MANIFEST})
    message("Cannot find install manifest: '${MANIFEST}'")
    message(STATUS "Skip uninstalling")
else()
    file(STRINGS ${MANIFEST} files)
    foreach(file ${files})
        if(EXISTS ${file})
            message(STATUS "Removing file: '${file}'")

            execute_process(COMMAND cmake -E remove ${file}
                OUTPUT_VARIABLE result)

            message(STATUS ${result})
        endif()
    endforeach(file)
endif()



if (SCU)
    set(SOURCES
        ${SOURCES}
        "${CMAKE_CURRENT_SOURCE_DIR}/SCU.cpp"
        PARENT_SCOPE)
else ()
    add_subdirectory(gui)
    add_subdirectory(samples)

    set( SOURCES ${SOURCES} PARENT_SCOPE )
endif ()

set( HEADERS ${HEADERS} PARENT_SCOPE )

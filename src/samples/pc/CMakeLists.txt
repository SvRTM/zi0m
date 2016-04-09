if (WIN32)
    add_subdirectory(win)
elseif (`"${CMAKE_SYSTEM}" MATCHES "Linux")
    add_subdirectory(linux)
endif ()

set(SOURCES
    ${SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EmuLcd.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EmuTouch.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    PARENT_SCOPE
)

set(HEADERS
    ${HEADERS}
    "${CMAKE_CURRENT_SOURCE_DIR}/Application.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/EmuLcd.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/EmuTouch.h"
    PARENT_SCOPE
)

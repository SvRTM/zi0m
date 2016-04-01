add_subdirectory (system)
add_subdirectory (font)

set (SOURCES
    ${SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/additional.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ApplicationBase.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Button.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/InputDevice.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Label.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MonitorDevice.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/TextCharacters.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Widget.cpp"
    PARENT_SCOPE
)

set (HEADERS
    ${HEADERS}
    "${CMAKE_CURRENT_SOURCE_DIR}/additional.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ApplicationBase.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Button.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/common.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/InputDevice.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Label.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/MonitorDevice.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/TextCharacters.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Widget.h"
    PARENT_SCOPE
)

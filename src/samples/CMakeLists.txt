add_subdirectory(pc)

set(SOURCES
    ${SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/AnotherWindow.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp"
    PARENT_SCOPE
)

set(HEADERS
    ${HEADERS}
    "${CMAKE_CURRENT_SOURCE_DIR}/AnotherWindow.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h"
    PARENT_SCOPE
)

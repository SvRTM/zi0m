add_subdirectory(pc)

set(SOURCES
    ${SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/Buttons.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GroupBoxs.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Labels.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp"
    PARENT_SCOPE
)

set(HEADERS
    ${HEADERS}
    "${CMAKE_CURRENT_SOURCE_DIR}/AbstractBody.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Buttons.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/GroupBoxs.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Labels.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h"
    PARENT_SCOPE
)

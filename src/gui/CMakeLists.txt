add_subdirectory(io)
add_subdirectory(kernel)
add_subdirectory(text)
add_subdirectory(widgets)

set(SOURCES ${SOURCES} PARENT_SCOPE)

set(HEADERS
    ${HEADERS}
    "${CMAKE_CURRENT_SOURCE_DIR}/common.h"
    PARENT_SCOPE
)

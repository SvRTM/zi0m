cmake_minimum_required (VERSION 3.2)

project (zi0m)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)


if (WIN32)
    set (libraries gdi32)
else()
    include (FindX11)
    if (X11_FOUND)
       include_directories (${X11_INCLUDE_DIR})
       #set (libraries ${libraries} ${X11_LIBRARIES})
       set (libraries ${libraries} X11)
    else()
       message (" *****************************************************************************")
       message (" *** X11 DEVELOPMENT LIBRARIES NOT FOUND                       ***")
       message (" *** Make sure libx11 is installed if you want GUI support.         ***")
       message (" *****************************************************************************")
       message (FATAL_ERROR "X11 DEVELOPMENT LIBRARIES NOT FOUND")
    endif()
endif()

if (MSVC)
        add_definitions (/W4)
elseif (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions (-Wall -pedantic)
else ()
        message ("Unknown compiler")
endif ()


set (HEADERS)
set (SOURCES )

include_directories ("src")
add_subdirectory (src)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT_NAME} ${libraries})
set_target_properties (${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")

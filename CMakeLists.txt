cmake_minimum_required (VERSION 3.2)

project(zi0m)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE OFF)

if (NOT DEFINED COLOR_DEPTH)
    set(COLOR_DEPTH RGB565)
endif ()

if (WIN32)
    set(PLATFORM "WIN32")

    set(libraries gdi32)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(PLATFORM "LINUX")

    include(FindX11)
    if (X11_FOUND)
       include_directories(${X11_INCLUDE_DIR})
       #set(libraries ${libraries} ${X11_LIBRARIES})
       set(libraries ${libraries} X11)
    else ()
       message(" *****************************************************************************")
       message(" *** X11 DEVELOPMENT LIBRARIES NOT FOUND                       ***")
       message(" *** Make sure libx11 is installed if you want GUI support.         ***")
       message(" *****************************************************************************")
       message(FATAL_ERROR "X11 DEVELOPMENT LIBRARIES NOT FOUND")
    endif ()
else ()
    message(FATAL_ERROR "Unknown OS")
endif ()

if (MSVC)
        add_definitions(/W4)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -pedantic)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native")

    if (CMAKE_BUILD_TYPE MATCHES Release)
        set(CMAKE_EXE_LINKER_FLAGS "-s")
    endif ()
else ()
        message("Unknown compiler")
endif ()

configure_file(src/config.h.in ${PROJECT_BINARY_DIR}/config.h)
include_directories("${PROJECT_BINARY_DIR}")

set(HEADERS)
set(SOURCES )

include_directories("src")
add_subdirectory(src)

source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${libraries})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" DEBUG_POSTFIX "_d")

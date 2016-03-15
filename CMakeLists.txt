cmake_minimum_required(VERSION 3.2)

project(zi0m)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (WIN32)
    set (libraries gdi32)
else()
    #add_definitions(-DLINUX)
    #find_library(pthreadlib pthread)
    #set (libraries ${pthreadlib})

    include(FindX11)
    if (X11_FOUND)
       include_directories(${X11_INCLUDE_DIR})
       #set (libraries ${libraries} ${X11_LIBRARIES})
       set (libraries ${libraries} X11)
    else()
       message(" *****************************************************************************")
       message(" *** DLIB GUI SUPPORT DISABLED BECAUSE X11 DEVELOPMENT LIBRARIES NOT FOUND ***")
       message(" *** Make sure libx11-dev is installed if you want GUI support.            ***")
       message(" *** On Ubuntu run: sudo apt-get install libx11-dev                        ***")
       message(" *****************************************************************************")
       set(DLIB_NO_GUI_SUPPORT ON CACHE STRING ${DLIB_NO_GUI_SUPPORT_STR} FORCE )
    endif()

#    include(FindOpenGL)
#    if (OPENGL_FOUND)
#        include_directories(${OPENGL_INCLUDE_DIR})
#        set (libraries ${libraries} ${OPENGL_LIBRARIES})
#    else()
#        message(" *****************************************************************************")
#        message(" *** DLIB GUI SUPPORT DISABLED BECAUSE X11 DEVELOPMENT LIBRARIES NOT FOUND ***")
#        message(" *** Make sure libGL is installed if you want GUI support.            ***")
#        message(" *** On Ubuntu run: sudo apt-get install libx11-dev                        ***")
#        message(" *****************************************************************************")
#        set(DLIB_NO_GUI_SUPPORT ON CACHE STRING ${DLIB_NO_GUI_SUPPORT_STR} FORCE )
#    endif()
endif()

if (MSVC)
        add_definitions (/W4)
        #add_definitions(-DWIN32)
elseif (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions (-Wall -pedantic)
else ()
        message ("Unknown compiler")
endif ()



#set (HEADERS)
#set (SOURCES )

include_directories("src")
add_subdirectory(src)

#source_group ("Header Files" FILES ${HEADERS})
#source_group ("Source Files" FILES ${SOURCES})



#message(${libraries})
#message(${HEADERS})
#message(${SOURCES})

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries (${PROJECT_NAME} ${libraries})



#set(CMAKE_USE_RELATIVE_PATHS true)

#if(MSVC)
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /MP")
#elseif(CMAKE_COMPILER_IS_GNUCXX)
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")
#endif()


#aux_source_directory(. SRC_LIST)
#find_package(x11)
#if(x11)

#    message("x11 are found")
#else()
#    message("x11 not found")
#endif()

#add_definitions("-Wpedantic -Wall -std=c++11 -O3")


#add_executable(${PROJECT_NAME} ${SRC_LIST})


#include_directories(./include)
#file(GLOB_RECURSE ${APPLICATION_NAME}_HEADERS "include/*.h")
#file(GLOB_RECURSE ${APPLICATION_NAME}_SOURCE  "src/*.cpp")

#set(PROJECT_FILES)
#list(APPEND PROJECT_FILES ${${APPLICATION_NAME}_HEADERS} ${${APPLICATION_NAME}_SOURCE})

#add_executable(${APPLICATION_NAME} ${PROJECT_FILES})
#target_link_libraries(${APPLICATION_NAME})
#set_target_properties(${APPLICATION_NAME} PROPERTIES DEBUG_POSTFIX "_d")

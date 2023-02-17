cmake_minimum_required(VERSION 3.22)
project(sdl_template C)

set(CMAKE_C_STANDARD 99)

# region SDL2 generic configuration
set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/x64")
    set(SDL2_DYNAMIC_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/bin/x64")
else ()
    set(SDL2_LIBRARIES_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/x86")
    set(SDL2_DYNAMIC_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/bin/x86")
endif ()

set(SDL2_LIBRARIES SDL2main SDL2)
set(SDL2_DYNAMIC_LIB "SDL2.dll")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
#endregion

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARIES_DIR})
link_libraries(mingw32 ${SDL2_LIBRARIES})

add_executable(sdl_1_create_window 1_create_window.c)
add_executable(sdl_2_manage_events 2_manage_events.c)
add_executable(sdl_3_drawing_rects 3_drawing_rects.c)
add_executable(sdl_4_pong 4_pong.c)

# Copy the right DLL into the cmake-build-debug folder
add_custom_command(TARGET sdl_1_create_window
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_DYNAMIC_LIB_DIR}/${SDL2_DYNAMIC_LIB}" ${CMAKE_BINARY_DIR}/.
        )
cmake_minimum_required(VERSION 3.15)
project(eog VERSION 0.0.1 LANGUAGES C)
set(CMAKE_C_COMPILER gcc)
string(APPEND CMAKE_C_FLAGS "-Wall -Wextra -Wno-unused-parameter")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_executable(eog ${PROJECT_SOURCE_DIR}/src/main.c)

target_link_libraries(eog allegro_dialog
                          allegro_acodec
                          allegro_audio
                          allegro_image
                          allegro_font
                          allegro_primitives
                          allegro_ttf
                          allegro
)

set(CPACK_GENERATOR "TGZ")
include(CPack)
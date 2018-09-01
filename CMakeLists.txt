cmake_minimum_required(VERSION 3.5)

project(eog VERSION 0.0.1 LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_executable(eog ${PROJECT_SOURCE_DIR}/source/main.c)

target_link_libraries(eog allegro_dialog
                          allegro_image
                          allegro_font
                          allegro_ttf
                          allegro
)
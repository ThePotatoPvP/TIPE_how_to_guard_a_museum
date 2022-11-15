cmake_minimum_required(VERSION 3.24)
project(TIPE_how_to_guard_a_museum C)

set(CMAKE_C_STANDARD 23)

include_directories(.)

add_executable(tipe
        code.c
        code.h
        geometry.c
        geometry.h operator.c operator.h structures.c structures.h)

target_link_libraries(tipe X11 m)
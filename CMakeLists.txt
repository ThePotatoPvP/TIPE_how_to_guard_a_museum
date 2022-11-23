cmake_minimum_required(VERSION 3.24)
project(TIPE_how_to_guard_a_museum C)

set(CMAKE_C_STANDARD 23)

include_directories(.)

add_executable(tipe
        src/c_src/code.c
        src/c_src/code.h
        src/c_src/geometry.c
        src/c_src/geometry.h src/c_src/operator.c src/c_src/operator.h src/c_src/structures.c src/c_src/structures.h)

target_link_libraries(tipe X11 m)
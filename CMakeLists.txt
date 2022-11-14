cmake_minimum_required(VERSION 3.24)
project(TIPE_how_to_guard_a_museum C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TIPE_how_to_guard_a_museum
        code.c
        code.h)

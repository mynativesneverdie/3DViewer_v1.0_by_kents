cmake_minimum_required(VERSION 3.24)
project(3DViewer_v1_0_by_kents C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(3DViewer_v1_0_by_kents
        src/parcer_obj.c
        src/parcer_obj.h)

cmake_minimum_required(VERSION 3.29)
project(CyEnedis C)

set(CMAKE_C_STANDARD 11)

include_directories(
        include/
)

add_executable(CyEnedis src/main.c
        include/avl.h
        include/station.h
        src/station.c
        src/avl.c
        include/maths.h
        src/maths.c)

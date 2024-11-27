cmake_minimum_required(VERSION 3.29)
project(CyEnedis C)

set(CMAKE_C_STANDARD 11)

include_directories(
        include/
)

add_executable(CyEnedis src/main.c
        include/avl.h
        src/avl.c
        include/maths.h
        src/maths.c
        include/application_settings.h
        src/application_settings.c
        include/csv_parser.h
        src/csv_parser.c
        include/result_generator.h
        src/result_generator.c)

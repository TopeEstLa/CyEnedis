cmake_minimum_required(VERSION 3.29)
project(CyEnedis C)

set(CMAKE_C_STANDARD 11)

include_directories(
        include/
)

add_executable(CyEnedis

        src/main.c
        include/avl.h
        src/avl.c
        include/maths.h
        src/maths.c
        include/application_settings.h
        src/application_settings.c
        include/csv_parser.h
        src/csv_parser.c
        include/result_generator.h
        src/result_generator.c
        include/csv_output.h
        src/csv_output.c
        include/qsort.h
        src/qsort.c
        include/application_test.h
        src/application_test.c
        include/benchmark.h
        src/benchmark.c
        include/waiting_scene.h
        src/waiting_scene.c
        include/memleak_check.h
        src/memleak_check.c
)

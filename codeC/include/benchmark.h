#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#elif __linux__
#include <sys/resource.h>
#endif

/**
enable benchmark method
 */
void set_benchmark_enabled(bool enabled);

/**
get the current time in millis
 */
long long current_time_in_ms();

/**
mark the start of a benchmark
 */
void mark_benchmark_start();

/**
mark the end of a benchmark
 */
void mark_benchmark_end();

/**
mark the end of settings time process
 */
void mark_setting_time();

/**
mark the end of the build time process
 */
void mark_build_time();
/**
mark the end of the collect time process
 */
void mark_collect_time();
/*
mark the end of the sort time process
*/
void mark_sort_time();
/**
mark the end of the write time process
 */
void mark_write_time();

/**
pretty print of the benchmark result
 */
void benchmark_result();

/**
print the memory usage of the program
 */
void print_memory_usage();

#endif //BENCHMARK_H

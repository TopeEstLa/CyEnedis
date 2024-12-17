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
 * @brief Set the benchmark status
 * @param enabled
 */
void set_benchmark_enabled(bool enabled);

/**
 * @brief Get the current time in milliseconds
 * @return the current time in milliseconds
 */
long long current_time_in_ms();

/**
 * @brief mark the start of a benchmark
 */
void mark_benchmark_start();

/**
 * @brief mark the end of a benchmark
 */
void mark_benchmark_end();

/**
 * @brief mark the end of the setting time process
 */
void mark_setting_time();

/**
 * @brief mark the end of the build time process
 */
void mark_build_time();

/**
 * @brief mark the end of the collect time process
 */
void mark_collect_time();

/**
 * @brief mark the end of the sort time process
 */
void mark_sort_time();

/**
 * @brief mark the end of the write time process
 */
void mark_write_time();

/**
 * @brief print the benchmark result
 */
void benchmark_result();

/**
 * @brief print the memory usage
 */
void print_memory_usage();

#endif //BENCHMARK_H

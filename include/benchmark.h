#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

void set_benchmark_enabled(bool enabled);

long long current_time_in_ms();

void mark_benchmark_start();

void mark_benchmark_end();

void mark_setting_time();
void mark_build_time();
void mark_collect_time();
void mark_sort_time();
void mark_write_time();

void benchmark_result();

#endif //BENCHMARK_H

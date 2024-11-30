#include <benchmark.h>
#include <stdbool.h>

bool enable_benchmark = false;

long long start_time = 0;
long long setting_time = 0;
long long processing_time = 0;
long long collect_time = 0;
long long sort_time = 0;
long long write_time = 0;
long long end_time = 0;

long long current_time_in_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000LL) + (ts.tv_nsec / 1000000);
}

void set_benchmark_enabled(bool enabled) {
    enable_benchmark = enabled;
}

void mark_benchmark_start() {
    if (!enable_benchmark) return;
    start_time = current_time_in_ms();
}

void mark_benchmark_end() {
    if (!enable_benchmark) return;
    end_time = current_time_in_ms();
}

void mark_setting_time() {
    if (!enable_benchmark) return;
    setting_time = current_time_in_ms();
}

void mark_build_time() {
    if (!enable_benchmark) return;
    processing_time = current_time_in_ms();
}

void mark_collect_time() {
    if (!enable_benchmark) return;
    collect_time = current_time_in_ms();
}

void mark_sort_time() {
    if (!enable_benchmark) return;
    sort_time = current_time_in_ms();
}

void mark_write_time() {
    if (!enable_benchmark) return;
    write_time = current_time_in_ms();
}

void benchmark_result() {
    if (!enable_benchmark) return;
    printf("======================BENCHMARK======================\n");
    printf("Settings elapsed time: %lld ms\n", setting_time - start_time);
    printf("Processing elapsed time: %lld ms\n", processing_time - setting_time);
    printf("Collect elapsed time: %lld ms\n", collect_time - processing_time);
    printf("Sort elapsed time: %lld ms\n", sort_time - collect_time);
    printf("Write elapsed time: %lld ms\n", write_time - sort_time);
    printf("Total elapsed time: %lld ms\n", end_time - start_time);
}
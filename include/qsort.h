#ifndef QSORT_H
#define QSORT_H

#include <avl.h>
#include <result_generator.h>

void swap(StationResult **a, StationResult **b);

int capacity_partition(StationResult **results, int low, int high);

int load_partition(StationResult **results, int low, int high);

void capacity_quick_sort(StationResult **results, int low, int high);

void load_quick_sort(StationResult **results, int low, int high);

void qsort_by_capacity(StationResult **results, int count);

void qsort_by_load(StationResult **results, int count);

#endif //QSORT_H

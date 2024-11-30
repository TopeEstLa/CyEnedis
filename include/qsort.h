#ifndef QSORT_H
#define QSORT_H

#include <avl.h>
#include <result_generator.h>

//Implementation of quick sort algorithm

/**
 * Swap pointer of StationResult
 * @param a First pointer
 * @param b Second pointer
 */
void swap(StationResult **a, StationResult **b);

/**
 * Partition the array by capacity
 * @param results Array of StationResult
 * @param low  Low index
 * @param high High index
 * @return Partition index
 */
int capacity_partition(StationResult **results, int low, int high);

/**
 * Partition the array by load
 * @param results Array of StationResult
 * @param low Low index
 * @param high High index
 * @return Partition index
 */
int load_partition(StationResult **results, int low, int high);

/**
 * Quick sort by capacity
 * @param results Array of StationResult
 * @param low Low index
 * @param high High index
 */
void capacity_quick_sort(StationResult **results, int low, int high);

/**
 * Quick sort by load
 * @param results Array of StationResult
 * @param low Low index
 * @param high High index
 */
void load_quick_sort(StationResult **results, int low, int high);

/**
 * Facade function to quick sort by capacity
 * @param results Array of StationResult
 * @param count Number of results
 */
void qsort_by_capacity(StationResult **results, int count);

/**
 * Facade function to quick sort by load
 * @param results Array of StationResult
 * @param count Number of results
 */
void qsort_by_load(StationResult **results, int count);

#endif //QSORT_H

#include <qsort.h>

void swap(StationResult **a, StationResult **b) {
    StationResult *temp = *a;
    *a = *b;
    *b = temp;
}

int capacity_partition(StationResult **results, int low, int high) {
    int pivot = results[high]->capacity;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (results[j]->capacity < pivot) {
            i++;
            swap(&results[i], &results[j]);
        }
    }
    swap(&results[i + 1], &results[high]);
    return i + 1;
}

int load_partition(StationResult **results, int low, int high) {
    int pivot = results[high]->load;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (results[j]->load < pivot) {
            i++;
            swap(&results[i], &results[j]);
        }
    }
    swap(&results[i + 1], &results[high]);
    return i + 1;
}

void capacity_quick_sort(StationResult **results, int low, int high) {
    if (low < high) {
        int pi = capacity_partition(results, low, high);
        capacity_quick_sort(results, low, pi - 1);
        capacity_quick_sort(results, pi + 1, high);
    }
}

void load_quick_sort(StationResult **results, int low, int high) {
    if (low < high) {
        int pi = load_partition(results, low, high);
        load_quick_sort(results, low, pi - 1);
        load_quick_sort(results, pi + 1, high);
    }
}

void qsort_by_capacity(StationResult **results, int count) {
    capacity_quick_sort(results, 0, count - 1);
}

void qsort_by_load(StationResult **results, int count) {
    load_quick_sort(results, 0, count - 1);
}

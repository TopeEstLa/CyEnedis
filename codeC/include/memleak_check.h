#ifndef MEMLEAK_CHECK_H
#define MEMLEAK_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Structure to track all allocation
 */
typedef struct Allocation {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct Allocation *next;
} Allocation;

/**
 * @brief add a new allocation to the tracking list
 * @param ptr pointer to the allocation
 * @param size size of the allocation
 * @param file file that made the allocation
 * @param line line in the file that made the allocation
 */
void add_allocation(void *ptr, size_t size, const char *file, int line);

/**
 * @brief remove an allocation from the tracking list
 * @param ptr pointer to the allocation
 */
void remove_allocation(void *ptr);

/**
 * @brief check all allocation and print the one that are not free
 */
void check_leaks();

/**
 * @brief a wrapper for malloc function to track all allocation
 * @param size size of the requested allocation
 * @param file file that made the allocation
 * @param line line in the file that made the allocation
 * @return
 */
void *malloc_wrapper(size_t size, const char *file, int line);

/**
 * @brief a wrapper for free function to track all allocation
 * @param ptr pointer to the allocation to free
 */
void free_wrapper(void *ptr);

#endif //MEMLEAK_CHECK_H

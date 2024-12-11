#ifndef MEMLEAK_CHECK_H
#define MEMLEAK_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* @brief structure representing allocation tracking
 */
typedef struct Allocation {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct Allocation *next;
} Allocation;

/**
* @brief add new allocation to track
 */ 
void add_allocation(void *ptr, size_t size, const char *file, int line);

/**
* @brief remove tracked allocation
 */
void remove_allocation(void *ptr);

/**
* @brief check if all tracked allocation as been removed
 */
void check_leaks();

/**
* @brief a wrapper for malloc function to track all alocation
 */
void *malloc_wrapper(size_t size, const char *file, int line);

/**
* @brief a wrapper for free function to track all alocation remove
 */
void free_wrapper(void *ptr);

#endif //MEMLEAK_CHECK_H

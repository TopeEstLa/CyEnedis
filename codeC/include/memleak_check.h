#ifndef MEMLEAK_CHECK_H
#define MEMLEAK_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Allocation {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct Allocation *next;
} Allocation;

void add_allocation(void *ptr, size_t size, const char *file, int line);

void remove_allocation(void *ptr);

void check_leaks();

void *malloc_wrapper(size_t size, const char *file, int line);

void free_wrapper(void *ptr);

#endif //MEMLEAK_CHECK_H

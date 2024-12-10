#include <memleak_check.h>


Allocation *allocations = NULL;

void add_allocation(void *ptr, size_t size, const char *file, int line) {
    Allocation *new_alloc = (Allocation *)malloc(sizeof(Allocation));
    new_alloc->ptr = ptr;
    new_alloc->size = size;
    new_alloc->file = file;
    new_alloc->line = line;
    new_alloc->next = allocations;
    allocations = new_alloc;
}

void remove_allocation(void *ptr) {
    Allocation **current = &allocations;
    while (*current) {
        if ((*current)->ptr == ptr) {
            Allocation *to_free = *current;
            *current = to_free->next;
            free(to_free);
            return;
        }
        current = &(*current)->next;
    }

    fprintf(stderr, "Trying to free a NULL pointer : %p\n", ptr);
}

void check_leaks() {
    Allocation *current = allocations;
    if (current) {
        printf("Mem Leak :\n");
        long long total_size = 0;
        while (current) {
            printf("Non Free : %p (taille : %zu, file : %s, ligne : %d)\n",
                   current->ptr, current->size, current->file, current->line);
            current = current->next;
            total_size += current->size;
        }
        printf("Full : %lld octets not free\n", total_size);
    } else {
        printf("No mem leak !\n");
    }
}

void *malloc_wrapper(size_t size, const char *file, int line) {
    //printf("Allocating %zu bytes from %s:%d\n", size, file, line);
    void *ptr = malloc(size);
    if (ptr) {
        add_allocation(ptr, size, file, line);
    }
    return ptr;
}

void free_wrapper(void *ptr) {
    //printf("Freeing %p\n", ptr);
    if (ptr) {
        remove_allocation(ptr);
    }
    free(ptr);
}
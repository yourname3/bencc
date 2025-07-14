#ifndef BENCC_ALLOC_H
#define BENCC_ALLOC_H

#include <stdlib.h>
#include <stdio.h>

static inline void*
reallocate(void *ptr, size_t new_size) {
    void *result = NULL;
    if(!ptr) {
        result = malloc(new_size);
    }
    else {
        result = realloc(ptr, new_size);
    }

    if(!result) {
        /* TODO: Do we want to longjmp or something? */
        printf("Error: Compiler ran out of memory\n");
        exit(-1);
    }

    return result;
}

#endif
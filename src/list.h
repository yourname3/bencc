#ifndef BENCC_LIST_H
#define BENCC_LIST_H

#include <stddef.h>

#include "alloc.h"

#define list_of(Ty) struct { \
    Ty *at; \
    size_t length; \
    size_t allocated; \
}

#define list_init(list_ptr) do { \
    (list_ptr)->at = NULL; \
    (list_ptr)->length = 0; \
    (list_ptr)->allocated = 0; \
} while(0)

static inline size_t
list_compute_size(size_t wanted, size_t current) {
    if(current < 8) current = 8;
    while(current < wanted) current *= 2;
    return current;
}

#define list_reserve_at_least(list_ptr, size) do { \
    if((list_ptr)->allocated < (size)) { \
        (list_ptr)->allocated = list_compute_size((size), (list_ptr)->allocated); \
        (list_ptr)->at = reallocate((list_ptr)->at, (list_ptr)->allocated * sizeof(*((list_ptr)->at))); \
    } \
} while(0)

#define list_push(list_ptr, object) do { \
    list_reserve_at_least(list_ptr, (list_ptr)->length + 1); \
    (list_ptr)->at[(list_ptr)->length++] = object; \
} while(0)

#define list_foreach(list_ptr, idx) \
for(size_t idx = 0; idx < (list_ptr)->length; ++idx)

#endif
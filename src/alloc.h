#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

void *bt_malloc(size_t size);
void *bt_realloc(void *ptr, size_t size);
void bt_free(void *ptr);

/* malloc stuff */
#define MALLOC_BYTES(type, bytes)           ((type *)bt_malloc(bytes))
#define MALLOC_ARRAY(type, n)               MALLOC_BYTES(type, sizeof(type) * n)
#define MALLOC(type)                        MALLOC_ARRAY(type, 1)

/* memory reallocation */
#define REALLOC_BYTES(type, ptr, bytes)     ((type *)bt_realloc(ptr, bytes))
#define REALLOC_ARRAY(type, ptr, n)         REALLOC_BYTES(type, ptr, \
                                                          sizeof(type) * n)
#define REALLOC(type, ptr, bytes)           REALLOC_BYTES(type, ptr, bytes)

/* don't forget it: free :-) */
#define FREE(ptr)                   bt_free(ptr)

#endif

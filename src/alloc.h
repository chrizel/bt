#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

void *bt_malloc(size_t size);
void bt_free(void *ptr);

#define MALLOC_BYTES(type, bytes)   ((type)bt_malloc(bytes))
#define MALLOC_ARRAY(type, n)       MALLOC_BYTES(type, sizeof(type) * n)
#define MALLOC(type)                MALLOC_ARRAY(type, 1)
#define FREE(ptr)                   bt_free(ptr)

#endif

#include <stdlib.h>
#include <stdio.h>

#include "alloc.h"
#include "error.h"

void *bt_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        error("Out of memory!\n");

    return ptr;
}

void *bt_realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

void bt_free(void *ptr)
{
    free(ptr);
}

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

void bt_free(void *ptr)
{
    free(ptr);
}

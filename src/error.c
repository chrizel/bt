#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error.h"

void error(char *text, ...)
{
    va_list args;

    va_start(args, text);
    fprintf(stderr, "error: ");
    vfprintf(stderr, text, args);
    fprintf(stderr, "\n");
    va_end(args);

    exit(1);
}

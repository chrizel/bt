/* Bermuda Triangle - action adventure game
   Copyright (C) 2004 Christian Zeller <chrizel@gmx.net>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

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

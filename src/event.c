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

#include <string.h>

#include "event.h"
#include "error.h"
#include "alloc.h"


/* static t_evl_item functions */
static t_evl_item *evl_item_new()
{
    t_evl_item *item = MALLOC(t_evl_item);
    memset(item, 0, sizeof(t_evl_item));
}

static void evl_item_reg(t_evl_item *item, t_func func)
{
    /* if we don't have any functions yet... */
    if (item->count == 0)
        /* ...initialize functions array */
        item->funcs = MALLOC_ARRAY(t_func, MAX_EV_FUNCS);
    else if (item->count == MAX_EV_FUNCS)
        /* if this happens, you should increase MAX_EV_FUNCS */
        error("evl_item_reg: item->count == MAX_EV_FUNCS");

    /* now we can assume, that we can do the job */
    item->funcs[item->count] = func;
    item->count++;
}

static void evl_item_call(t_evl_item *item)
{
    int i;
    for (i = 0; i < item->count; i++)
        item->funcs[i]();
}

static void evl_item_free(t_evl_item *item)
{
    FREE(item->funcs);
    FREE(item);
}

t_evl *evl_new(int count)
{
    t_evl *list = MALLOC(t_evl);

    list->count = count;
    list->items = MALLOC_ARRAY(t_evl_item *, count);

    /* set item stuff to NULL - it will be filled in evl_reg */
    memset(list->items, 0, sizeof(t_evl_item *) * count);

    return list;
}

void evl_reg(t_evl *list, int event, t_func func)
{
    /* check if all is ok... */
    if (!list) {
        warning("evl_reg: list is NULL");
        return;
    }

    if (!func) {
        warning("evl_reg: func is NULL");
        return;
    }

    if (event >= list->count) {
        warning("evl_reg: event >= list->count");
        return;
    }

    /* no let's check if list->items[event] is already allocated,
     * if not, create it. */
    if (list->items[event] == NULL)
        list->items[event] = evl_item_new();

    /* register function */
    evl_item_reg(list->items[event], func);
}

void evl_call(t_evl *list, int event)
{
    /* error checking */
    if (!list) {
        warning("evl_call: list is NULL");
        return;
    }

    if (event >= list->count) {
        warning("evl_call: event >= list->count");
        return;
    }

    /* do the job */
    if (list->items[event])
        evl_item_call(list->items[event]);
}

void evl_free(t_evl *list)
{
    while (--(list->count))
        evl_item_free(list->items[list->count]);

    FREE(list->items);
    FREE(list);
}
#include <string.h>

#include "event.h"
#include "error.h"
#include "alloc.h"


/* static t_evl_item functions */
static t_evl_item *evl_item_new()
{
    t_evl_item *item = MALLOC(t_evl_item);
    memset(item, 0, sizeof(t_evl_item));
}

static void evl_item_reg(t_evl_item *item, t_func func)
{
    /* if we don't have any functions yet... */
    if (item->count == 0)
        /* ...initialize functions array */
        item->funcs = MALLOC_ARRAY(t_func, MAX_EV_FUNCS);
    else if (item->count == MAX_EV_FUNCS)
        /* if this happens, you should increase MAX_EV_FUNCS */
        error("evl_item_reg: item->count == MAX_EV_FUNCS");

    /* now we can assume, that we can do the job */
    item->funcs[item->count] = func;
    item->count++;
}

static void evl_item_call(t_evl_item *item)
{
    int i;
    for (i = 0; i < item->count; i++)
        item->funcs[i]();
}

static void evl_item_free(t_evl_item *item)
{
    FREE(item->funcs);
    FREE(item);
}

t_evl *evl_new(int count)
{
    t_evl *list = MALLOC(t_evl);

    list->count = count;
    list->items = MALLOC_ARRAY(t_evl_item *, count);

    /* set item stuff to NULL - it will be filled in evl_reg */
    memset(list->items, 0, sizeof(t_evl_item *) * count);

    return list;
}

void evl_reg(t_evl *list, int event, t_func func)
{
    /* check if all is ok... */
    if (!list) {
        warning("evl_reg: list is NULL");
        return;
    }

    if (!func) {
        warning("evl_reg: func is NULL");
        return;
    }

    if (event >= list->count) {
        warning("evl_reg: event >= list->count");
        return;
    }

    /* no let's check if list->items[event] is already allocated,
     * if not, create it. */
    if (list->items[event] == NULL)
        list->items[event] = evl_item_new();

    /* register function */
    evl_item_reg(list->items[event], func);
}

void evl_call(t_evl *list, int event)
{
    /* error checking */
    if (!list) {
        warning("evl_call: list is NULL");
        return;
    }

    if (event >= list->count) {
        warning("evl_call: event >= list->count");
        return;
    }

    /* do the job */
    if (list->items[event])
        evl_item_call(list->items[event]);
}

void evl_free(t_evl *list)
{
    while (--(list->count))
        evl_item_free(list->items[list->count]);

    FREE(list->items);
    FREE(list);
}

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

#ifndef EVENT_H
#define EVENT_H

typedef void (*t_func)();

typedef struct {
    int count;
    t_func *funcs;
} t_evl_item;

typedef struct {
    int count;
    t_evl_item **items;
} t_evl;

t_evl *evl_new(int count);
void evl_reg(t_evl *list, int event, t_func func);
void evl_call(t_evl *list, int event);
void evl_free(t_evl *list);

/* increase this, if needed! */
#define MAX_EV_FUNCS 16

#endif

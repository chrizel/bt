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

#ifndef MEGA_H
#define MEGA_H 

#include "console.h"
#include "sdl_events.h"

#define FPS 30

struct _player {
    int x;
    int y;
} player;

SDL_Surface *screen;

int editor_mode;
int editor_pen;
int *editor_pg;
int editor_pg_y;
int editor_pg_x;

void bt_exit();
void bt_pen(void);

void bt_editor();
void bt_pg(void);
void bt_write(void);
void bt_load(void);
void bt_fill(void);
void bt_put(void);
void bt_new(void);

#endif

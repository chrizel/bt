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

#ifndef BT_H
#define BT_H

#include "console.h"
#include "sdl_events.h"
#include "map.h"
#include "game.h"

#define SCREEN_W 800
#define SCREEN_H 600

#define FPS 30
#define BPP 16

#if(BPP == 8)
#define USE_8BIT
#else
#define USE_16BIT
#endif

extern SDL_Surface *screen;
extern SDL_Surface *minilogo;

#ifdef DO_FRAMETEST
extern int frames;
extern int ticks_begin, ticks_end;
#endif

id bt;

void bt_exit();
void bt_pen(void);

void bt_editor();
void bt_pg(void);
void bt_write(void);
void bt_load(void);
void bt_fill(void);
void bt_put(void);
void bt_new(void);

#ifdef DO_FRAMETEST
void fps_output();
#endif

#endif

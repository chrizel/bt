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

#ifndef MAP_H
#define MAP_H

#include "objc/Object.h"
//#include "eventhandler.h"

/* Map Format enums */
enum {
    MF_ID = (1 << 17) - 1,
    MF_ANIM = 1 << 17,
};

/* static map information */
#define TILE_SIZE 20
#define XTILES 40 /* tiles per row on screen */
#define YTILES 30 /* tiles per col on screen */

@interface Map: Object
{
    SDL_Surface *stocks;
    Uint32 xoffset;
    Uint32 yoffset;
    Uint32 prev_ticker; 
    Uint32 version;

    /* head data */
    Uint32 width;
    Uint32 height;
    Uint32 anim_count;

    /* animation data */
    Uint32 *anims;

    /* map data itself */
    Uint32 *data;

    SDL_Rect srcrect;

    Uint32 anim_ticker;
    Uint32 anim_ticks;
    Uint32 switch_palette;

    Uint32 destTicks;
}

- (id)initWithWidth:(Uint32)w height:(Uint32)h animCount:(Uint32)ac animTicks:(Uint32)at;

+ (id)newWithFile:(char *)file;
+ (id)newWithWidth:(Uint32)w height:(Uint32)h animCount:(Uint32)ac animTicks:(Uint32)at;

/*
    virtual ~Map();
*/

- save:(char *)file;
- open:(char *)file;

- fill:(int)id;
- fillWithID:(int)id;
- putID:(int)id xT:(int)xt yT:(int)yt;

- onEvent:(SDL_Event *)event;
- onDraw:(SDL_Surface *)sfc;
- onIdle;

- incAnimTicker;

@end

#endif

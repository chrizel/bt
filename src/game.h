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

#ifndef GAME_H
#define GAME_H 

#include <SDL.h>
#include <objc/Object.h>

//#include "editor.h"

@interface Game: Object
{
    char *title;

    id map;
    id console;
    id player;
    id editor;
    id audio;
    id python;

    int music;
    int chunk;

    SDL_Rect ppos;

    Uint32 xOffset;
    Uint32 yOffset;
}

- initSDL;
- eventLoop;
- printGPL;

+ (id)newWithTitle:(char *)t;
- (id)initWithTitle:(char *)t;
- free;

- run;

- print:(char *)t;
- printLine:(char *)t;

- (id)getConsole;
- (id)getMap;
- (id)getPlayer;
- getPython;

@end

#endif

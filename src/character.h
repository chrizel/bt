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

#ifndef CHARACTER_H
#define CHARACTER_H

#include "sprite.h"

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

@interface Character: Sprite
{
    BOOL going;
    int direction;
    int tick;

    Uint32 destTicks;
}

- initWithSfcName:(char *)sfc_name position:(SDL_Rect *)prect;
- free;

- (BOOL)isGoing;
- (int)getDirection;
- setDirection:(int)dir;

- setTick:(int)t;
- (int)getTick;
- switchTick;

- onIdle;

@end

#endif

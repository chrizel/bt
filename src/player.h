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

#ifndef PLAYER_H
#define PLAYER_H

#include <objc/Object.h>

@interface Player: Object
{
    SDL_Surface *my_sfc;
    SDL_Rect pos;
    SDL_Rect cur_shape;
    BOOL blink;
}

+ (id)new;
- (id)init;
// virtual ~Player();

- onDraw:(SDL_Surface *)sfc;
- (BOOL)switchBlink;
- (BOOL)getBlink;

@end

#endif

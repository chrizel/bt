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

#include <SDL.h>

#include "player.h"

#include "bt.h"
#include "sdl_events.h"
#include "bmpl.h"

@implementation Player

static SDL_Rect wider_rect(SDL_Rect *rect, int border)
{
    static SDL_Rect wrect;
    
    //printf("%d,%d,%d,%d\n", rect->x, rect->y, rect->w, rect->h);

    wrect.x = rect->x - border;
    wrect.y = rect->y - border;
    wrect.w = rect->w + border * 2;
    wrect.h = rect->h + border * 2;

    return wrect;
}

+ (id)new
{
    return [[super new] init];
}

- (id)init
{
    blink = NO;
    my_sfc = bmpl_get("player.player1");

    pos.w = 80;
    pos.h = 100;

    pos.x = 600;
    pos.y = 400;

    cur_shape.w = 80;
    cur_shape.h = 100;
    cur_shape.x = 0;
    cur_shape.y = 0;

    return self;
}

- onDraw:(SDL_Surface *)sfc;
{
    if (blink)
	cur_shape.x = 80;
    else
	cur_shape.x = 0;

    SDL_BlitSurface(my_sfc, &cur_shape, sfc, &pos);
    PUSH_UR(wider_rect(&pos, 10));
}

- (BOOL)switchBlink
{
    printf("blink\n");
    blink = !blink;
    return blink;
}

- (BOOL)getBlink
{
    return blink;
}

- onIdle
{
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (keystate[SDLK_UP])
	pos.y -= 10;
    else if (keystate[SDLK_DOWN])
	pos.y += 10;

    if (keystate[SDLK_LEFT])
	pos.x -= 10;
    else if (keystate[SDLK_RIGHT])
	pos.x += 10;
}

@end

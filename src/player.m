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

#define PW 48
#define PH 64
#define MPW(x) x * PW
#define MPH(y) y * PH

#define TICK_COUNT 3
#define PLAYER_RECT(x, y) playerMap[y * TICK_COUNT + x]
#define SET_PRECT(x, y) cur_shape = &PLAYER_RECT(x, y)

static SDL_Rect playerMap[] = {
    {MPW(0), MPH(0), PW, PH},
    {MPW(1), MPH(0), PW, PH},
    {MPW(2), MPH(0), PW, PH},
    {MPW(0), MPH(1), PW, PH},
    {MPW(1), MPH(1), PW, PH},
    {MPW(2), MPH(1), PW, PH},
    {MPW(0), MPH(2), PW, PH},
    {MPW(1), MPH(2), PW, PH},
    {MPW(2), MPH(2), PW, PH},
    {MPW(0), MPH(3), PW, PH},
    {MPW(1), MPH(3), PW, PH},
    {MPW(2), MPH(3), PW, PH},
};

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

    pos.w = 48;
    pos.h = 64;

    pos.x = 600;
    pos.y = 400;

    going = NO;
    tick_dir = YES;
    direction = SOUTH;
    tick = 1;

    SET_PRECT(1, 2);

    destTicks = SDL_GetTicks();

    return self;
}

- onDraw:(SDL_Surface *)sfc;
{
    /*
    if (blink)
	cur_shape.x = 48;
    else
        cur_shape.x = 0;
    */
    SET_PRECT(tick, direction);

    SDL_BlitSurface(my_sfc, cur_shape, sfc, &pos);
    //whole_redraw = YES;
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

- (BOOL)isGoing
{
    return going;
}

- (int)getDirection
{
    return direction;
}

- setDirection:(int)dir
{
    direction = dir;
}

- (int)getTick
{
    return tick;
}

- setTick:(int)t
{
    tick = t;
}

- switchTick
{
    if (tick)
	tick = 0;
    else
	tick = 2;
}

- onIdle
{
    /*** Input ***/
    Uint8 *keystate = SDL_GetKeyState(NULL);

    going = keystate[SDLK_UP] || keystate[SDLK_DOWN] ||
	keystate[SDLK_LEFT] || keystate[SDLK_RIGHT];

    if (keystate[SDLK_UP]) {
	pos.y -= 10;
	direction = NORTH;
    } else if (keystate[SDLK_DOWN]) {
	pos.y += 10;
	direction = SOUTH;
    }

    if (keystate[SDLK_LEFT]) {
	pos.x -= 10;
	direction = WEST;
    } else if (keystate[SDLK_RIGHT]) {
	pos.x += 10;
	direction = EAST;
    }

    /*** Animation calculations ***/
    if (SDL_GetTicks() >= destTicks) {
	/* Do animation */
	if(going)
	    [self switchTick];
	else
	    [self setTick:1];

	/* Calculate next tick time */
	destTicks = SDL_GetTicks() + 100;
    }
}

@end

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

#include "game.h"

#include "player.h"

#include "sdl_events.h"
#include "bmpl.h"

#define PW 48
#define PH 64
#define MPW(x) x * PW
#define MPH(y) y * PH

#define TICK_COUNT 3
#define PLAYER_RECT(x, y) playerMap[y * TICK_COUNT + x]
#define SET_PRECT(x, y) src_rect = &PLAYER_RECT(x, y)

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

Player::Player(char *sfc_name, SDL_Rect *prect) : Character(sfc_name, prect)
{
    going = false;
    direction = SOUTH;
    tick = 1;

    SET_PRECT(1, 2);
}

Player::~Player()
{
}

void Player::draw(SDL_Surface *dst_sfc, int xo, int yo)
{
    SET_PRECT(tick, direction);
    Character::draw(dst_sfc, xo, yo);
}

void Player::switchTick()
{
    if (tick)
        tick = 0;
    else
        tick = 2;
}

void Player::playerGo(int xo, int yo)
{
    if (xo != 0) {
        if ( (pos.x < 100) || (pos.x > 700) ) {
            game->getMap()->updateOffset(xo / 20, 0);
            pos.x -= xo;
        } else {
            pos.x += xo;
        }
    }

    if (yo != 0) {
        if ( (pos.y < 100) || (pos.y > 500) ) {
            game->getMap()->updateOffset(0, yo / 20);
            pos.y -= yo;
        } else {
            pos.y += yo;
        }
    }
}

void Player::onIdle()
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

    if (going) {
        /*** Animation calculations ***/
        if (SDL_GetTicks() >= destTicks) {
            /* Do animation */
            switchTick();

            /* Calculate next tick time */
            destTicks = SDL_GetTicks() + 100;
        }
    } else {
        tick = 1;
    }
}

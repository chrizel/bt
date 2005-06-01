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
    SDL_Rect scroll_rect;
    scroll_rect.x = scroll_rect.y = 100;
    scroll_rect.w = game->getWidth() - scroll_rect.x - 100;
    scroll_rect.h = game->getHeight() - scroll_rect.y - 100;

    if (xo != 0) {
        if ( pos.x < scroll_rect.x ) {
            if ( xo < 0 ) {
                if ( game->getMap()->getXPos() > 0 ) {
                    game->getMap()->updateOffset(xo, 0);
                } else {
                    pos.x += xo;
                }
            } else {
                pos.x += xo;
            }
        } else if ( pos.x > scroll_rect.w ) {
            if ( xo > 0 ) {
                game->getMap()->updateOffset(xo, 0);
            } else {
                pos.x += xo;
            }
        } else {
            pos.x += xo;
        }
    }

    if (yo != 0) {
        if ( pos.y < scroll_rect.y ) {
            if ( yo < 0 ) {
                if ( game->getMap()->getYPos() > 0) {
                    game->getMap()->updateOffset(0, yo);
                } else {
                    pos.y += yo;
                }
            } else {
                pos.y += yo;
            }
        } else if ( pos.y > scroll_rect.h ) {
            if ( yo > 0 ) {
                game->getMap()->updateOffset(0, yo);
            } else { 
                pos.y += yo;
            }
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
        playerGo(0, -10);
        direction = NORTH;
    } else if (keystate[SDLK_DOWN]) {
        playerGo(0, 10);
        direction = SOUTH;
    }

    if (keystate[SDLK_LEFT]) {
        playerGo(-10, 0);
        direction = WEST;
    } else if (keystate[SDLK_RIGHT]) {
        playerGo(10, 0);
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

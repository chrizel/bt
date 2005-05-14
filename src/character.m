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

#include "character.h"

Character::Character(char *sfc_name, SDL_Rect *prect) : Sprite(sfc_name, prect)
{
    going = false;
    tick = 0;
    destTicks = SDL_GetTicks();
}

Character::~Character()
{
}

void Character::switchTick()
{
    tick = 0; //TODO: tick-count attribute, so i can calc this tick stuff
}

bool Character::isGoing()
{
    return going;
}

int Character::getDirection()
{
    return direction;
}

void Character::setDirection(int dir)
{
    direction = dir;
}

int Character::getTick()
{
    return tick;
}

void Character::setTick(int t)
{
    tick = t;
}

void Character::onIdle()
{
    if (going) {
	/*** Animation calculations ***/
	if (SDL_GetTicks() >= destTicks) {
	    /* Do animation */
	    switchTick();

	    /* Calculate next tick time */
	    destTicks = SDL_GetTicks() + 100; //TODO: speed attribute
	}
    } else {
	tick = 1;
    }
}

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

#include <glSDL.h>
#include <SDL_endian.h>

#include "Python.h"

#include "editor.h"
#include "map.h"
#include "bt.h"

@implementation Editor

- init
{
    active = YES;
    pen = 0;
    pg = NULL;
}

- free
{
    [super free];
}

- (BOOL)isActive
{
    return active;
}

- setActive:(BOOL)value
{
    active = value;
}

- (int)getPen
{
    return pen;
}

- (int)setPen:(int)value
{
    pen = value;
    return pen;
}

- setTID:(int)tid onX:(int)x andY:(int)y
{
    [[bt getMap] setTID:tid onX:x andY:y];
}

- onEvent:(SDL_Event *)event
{
}

- onDraw:(SDL_Surface *)sfc;
{
}

- saveMap:(char *)file
{
    [[bt getMap] save:file];
}

- openMap:(char *)file
{
    [[bt getMap] open:file];
}

- onIdle
{
    if (active) {
	int x, y, xt, yt;
        Uint8 mousestate = SDL_GetMouseState(&x, &y);

        xt = (x - (x % TILE_SIZE)) / TILE_SIZE;
        yt = (y - (y % TILE_SIZE)) / TILE_SIZE;

        if (mousestate & SDL_BUTTON(1)) {
	    [self setTID:pen onX:xt andY:yt];
	    whole_redraw = 1;
        } else if (mousestate & SDL_BUTTON(3)) {
	    [self setTID:0 onX:xt andY:yt];
	    whole_redraw = 1;
	}

    }
}

- updateGUI
{
    // Update the TK GUI
    PyRun_SimpleString("updateGUI()");
}

@end

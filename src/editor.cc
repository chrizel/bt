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
#include <SDL_endian.h>
#include <iostream>

#include "bmpl.h"
#include "game.h"
#include "sdl_events.h"
#include "editor.h"
#include "map.h"

Editor::Editor()
{
    active = true;
    pen = 0;
    pg = NULL;
}

Editor::~Editor()
{
}

bool Editor::isActive()
{
    return active;
}

void Editor::setActive(bool value)
{
    active = value;
}

int Editor::getPen()
{
    return pen;
}

int Editor::setPen(int value)
{
    pen = value;
    return pen;
}

void Editor::setTID(int tid, int x, int y)
{
    game->getMap()->setTID(tid, x, y);
}

void Editor::onEvent(SDL_Event *event)
{
}

void Editor::onDraw(SDL_Surface *sfc)
{
    SDL_Surface *stocks = game->getMap()->getStocks();
    SDL_Rect srcrect = { 0, 0, TILE_SIZE, TILE_SIZE };
    SDL_Rect dstrect = { 10, 10, TILE_SIZE, TILE_SIZE };

    const int stockRowTiles = 40;
    srcrect.x = (pen % stockRowTiles) * TILE_SIZE;
    srcrect.y = ((pen - (pen % stockRowTiles)) / stockRowTiles) * TILE_SIZE;

    SDL_BlitSurface( stocks, &srcrect, screen, &dstrect );
    PUSH_UR(dstrect);
}

void Editor::saveMap(char *file)
{
    game->getMap()->save(file);
}

void Editor::openMap(char *file)
{
    game->getMap()->open(file);
}

void Editor::incPen(int x)
{
    pen += x;
    std::cout << pen << std::endl;
}

void Editor::decPen(int x)
{
    if ((pen - x) >= 0)
        pen -= x;
    std::cout << pen << std::endl;
}

void Editor::onIdle()
{
    if (active) {
	int x, y, xt, yt;
        Uint8 mousestate = SDL_GetMouseState(&x, &y);

        x += game->getMap()->getXPos();
        y += game->getMap()->getYPos();
        xt = (x - (x % TILE_SIZE)) / TILE_SIZE;
        yt = (y - (y % TILE_SIZE)) / TILE_SIZE;

        if (mousestate & SDL_BUTTON(1)) {
	    setTID(pen, xt, yt);
	    whole_redraw = 1;
        } else if (mousestate & SDL_BUTTON(3)) {
	    setTID(0, xt, yt);
	    whole_redraw = 1;
	}
    }
}

void Editor::updateGUI()
{
}

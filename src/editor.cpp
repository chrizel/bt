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

#include "editor.h"
#include "map.h"
#include "bt.h"

Editor::Editor(Map *aMap)
{
    mode = 1;
    pen = 0;
    pg = NULL;
    
    map = aMap;
}

Editor::~Editor()
{
}

void Editor::writeInt(FILE *fp, Uint32 num)
{
    SDL_RWops *area;
    area = SDL_RWFromFP(fp, 0);
    SDL_WriteLE32(area, num);
    SDL_FreeRW(area);
}

Uint32 Editor::readInt(FILE *fp)
{
    int num;

    SDL_RWops *area;
    area = SDL_RWFromFP(fp, 0);
    num = SDL_ReadLE32(area);
    SDL_FreeRW(area);

    return num;
}

bool Editor::getMode()
{
    return mode;
}

bool Editor::setMode(bool value)
{
    mode = value;
    return mode;
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

int Editor::setTile(int id, int x, int y)
{
    map->put(id, x, y);
}

void Editor::saveMap(char *file)
{
    map->save(file);
}

void Editor::openMap(char *file)
{
    map->open(file);
}

void Editor::newMap(Uint32 width, Uint32 height, Uint32 anim_count, Uint32 anim_ticks)
{
}

void Editor::onEvent(SDL_Event *event)
{
}

void Editor::onDraw(SDL_Surface *sfc)
{
}

void Editor::onIdle()
{
    /*
    if (bt->getConsole()->isVisible())
	return;

    if (mode) {
	int x, y, xt, yt;
        Uint8 mousestate = SDL_GetMouseState(&x, &y);

        xt = (x - (x % TILE_SIZE)) / TILE_SIZE;
        yt = (y - (y % TILE_SIZE)) / TILE_SIZE;

        if (mousestate & SDL_BUTTON(1)) {
            map->put(1, xt, yt);
	    whole_redraw = 1;
        } else if (mousestate & SDL_BUTTON(3)) {
            map->put(0, xt, yt);
	    whole_redraw = 1;
	}

    }
    */
}

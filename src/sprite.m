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

#include "sprite.h"
#include "bmpl.h"
#include "bt.h"

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

Sprite::Sprite(char *sfc_name, SDL_Rect *prect)
{
    sfc = bmpl_get(sfc_name);
    pos = *prect;
    
    // Init defautl src_rect
    def_src_rect.y = def_src_rect.x = 0;
    def_src_rect.w = pos.w;
    def_src_rect.h = pos.h;
    src_rect = &def_src_rect;
}

Sprite::~Sprite()
{
}

void Sprite::draw(SDL_Surface *dst_sfc, int xo, int yo)
{
    // Offset check
    if ((pos.x + pos.w > xo) && (pos.y + pos.h > yo) &&
        (pos.x < xo + SCREEN_W) && (pos.y < yo + SCREEN_H)) {
        SDL_BlitSurface(sfc, src_rect, dst_sfc, &pos);
        PUSH_UR(wider_rect(&pos, 10));
    }
}


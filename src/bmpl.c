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

#include <stdio.h>
#include <string.h>

#include "bt.h"
#include "bmpl.h"
#include "bitmaps.h"
#include "colors.h"

static SDL_Surface *load_bitmap(t_bmpl_item *item);
static t_bmpl_item *item_lookup(char *id);

SDL_Surface *bmpl_get(char *id)
{
    t_bmpl_item *item = item_lookup(id);

    if (!item)
        error("bmpl_get: id not found!");

    if (item->sfc == NULL)
        item->sfc = load_bitmap(item);

    return item->sfc;
}

static t_bmpl_item *item_lookup(char *id)
{
    int i;
    for (i = 0; bmpl_list[i].id; i++) {
        if (strcmp(bmpl_list[i].id, id) == 0)
            return &bmpl_list[i];
    }

    return NULL;
}

static SDL_Surface *load_bitmap(t_bmpl_item *item)
{
    SDL_Surface *temp, *surf;

    /* Load */
    temp = IMG_Load(item->file);
    if (!temp)
        error("Can't load bitmap: %s", item->file);

    SDL_SetColors(temp, colors, 0, n_colors);

    /* ColorKey... */
    if (item->flags & BL_COLORKEY) {
      if (SDL_SetColorKey (temp, SDL_SRCCOLORKEY, 141))
            error("Can't set colorkey %s", item->file);
    }
    
    /* Convert */
    /*
    surf = SDL_DisplayFormat(temp);
    if (!surf)
        error("Can't convert %s", item->file);
        */


    //SDL_FreeSurface(temp);

    return temp;
}

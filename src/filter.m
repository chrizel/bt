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
#include <string.h>

#include "bt.h"
#include "filter.h"
#include "console.h"
#include "colors.h"

#define DNUM 50
#define DARKER(value) ((value - DNUM) < 0 ? 0 : value - DNUM)

t_func cur_filter;

static void night_filter()
{
    int i;

    printf("n_colors = %d\n", n_colors);
    for (i = 0; i < n_colors; i++) {
        /* Decrease color with DNUM... */
        colors[i].r = DARKER(orig_colors[i].r);  
        colors[i].g = DARKER(orig_colors[i].g);  
        colors[i].b = DARKER(orig_colors[i].b);  
    }

    /* Set palette... */
    SDL_SetColors(screen, colors, 0, n_colors);

    cur_filter = NULL;
}

static void day_filter()
{
    int i;

    for (i = 0; i < n_colors; i++) {
        /* Decrease color with DNUM... */
        colors[i].r = orig_colors[i].r;  
        colors[i].g = orig_colors[i].g;  
        colors[i].b = orig_colors[i].b;  
    }

    /* Set palette... */
    SDL_SetColors(screen, colors, 0, n_colors);

    cur_filter = NULL;
}

void con_switch_filter()
{
  if (!bt->getConsole()->getLastParam())
        return;

  if (strcmp(bt->getConsole()->getLastParam(), "night") == 0) {
        cur_filter = night_filter;
        bt->print("cur_filter = night");
  } else if (strcmp(bt->getConsole()->getLastParam(), "day") == 0) {
        cur_filter = day_filter;
        bt->print("cur_filter = day");
    } else {
        cur_filter = NULL;
        bt->print("cur_filter = NULL");
    }
}

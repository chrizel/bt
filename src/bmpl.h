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

/*
 * bmpl.h - Bitmap Loader
 */
#ifndef BMPL_H
#define BMPL_H

#include <SDL.h>
#include <SDL_image.h>

enum {
    BL_COLORKEY = (1 << 0),
};

typedef struct {
    char *id;
    char *file;
    SDL_Surface *sfc;
    int flags;
} t_bmpl_item;

SDL_Surface *bmpl_get(char *id);

#endif

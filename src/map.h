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

#ifndef MAP_H
#define MAP_H

/* Map Format enums */
enum {
    MF_ID = (1 << 17) - 1,
    MF_ANIM = 1 << 17,
};

/* static map information */
#define TILE_SIZE 20
#define XTILES 40 /* tiles per row on screen */
#define YTILES 30 /* tiles per col on screen */

/*
 * Map structure
 * Create a map with map_new(...)
 * Free it with map_free(...)
 */
typedef struct {

    /*
     * ATTRIBUTES
     */
    SDL_Surface *stocks;
    Uint32 xoffset;
    Uint32 yoffset;
    Uint32 anim_ticker;
    Uint32 version;
    Uint32 switch_palette;

    /* head data */
    Uint32 width;
    Uint32 height;
    Uint32 anim_count;
    Uint32 anim_ticks;

    /* animation data */
    Uint32 *anims;

    /* map data itself */
    Uint32 *data; 
} t_map;

/*
 * FUNCTIONS
 */
t_map *map_new(char *file);
t_map *map_new_empty(Uint32 width, Uint32 height, Uint32 anim_count, Uint32 anim_ticks);
void map_free(t_map *map);

void map_save(t_map *map, char *file);
t_map *map_open(char *file);

void map_fill(t_map *map, int id);
void map_put(t_map *map, int id, int xt, int yt);

void map_draw(t_map *map, SDL_Surface *sfc);
void map_idle(t_map *map);

#endif

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

typedef struct _map_data {
    /* head data */
    unsigned int width;
    unsigned int height;
    unsigned int anim_count;
    unsigned int anim_ticks;

    /* animation data */
    unsigned int *anims;

    /* map data itself */
    unsigned int *data; 
} map_data;

void init_map();
void write_map(char *filename);
void read_map(char *filename);
void fill_map(int id);
void map_put(int id, int xt, int yt);
void map_new(unsigned int width, unsigned int height, unsigned int anim_count, unsigned int anim_ticks);

#endif
#ifndef MAP_H
#define MAP_H

/* Map Format enums */
enum {
    MF_ID = (1 << 17) - 1,
    MF_ANIM = 1 << 17,
};

typedef struct _map_data {
    /* head data */
    unsigned int width;
    unsigned int height;
    unsigned int anim_count;
    unsigned int anim_ticks;

    /* animation data */
    unsigned int *anims;

    /* map data itself */
    unsigned int *data; 
} map_data;

void init_map();
void write_map(char *filename);
void read_map(char *filename);
void fill_map(int id);
void map_put(int id, int xt, int yt);
void map_new(unsigned int width, unsigned int height, unsigned int anim_count, unsigned int anim_ticks);

#endif

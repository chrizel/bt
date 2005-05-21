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

class Map
{
private:
    SDL_Surface *stocks;
    Uint32 xoffset;
    Uint32 yoffset;
    Uint32 prev_ticker; 
    Uint32 version;

    /* head data */
    Uint32 width;
    Uint32 height;
    Uint32 anim_count;

    /* animation data */
    Uint32 *anims;

    /* map data itself */
    Uint32 *data;

    SDL_Rect srcrect;

    Uint32 anim_ticker;
    Uint32 anim_ticks;
    Uint32 switch_palette;

    Uint32 destTicks;
public:
    Map(Uint32 w, Uint32 h, Uint32 ac, Uint32 at);;
    Map(char *file);
    virtual ~Map();

    void init(Uint32 w, Uint32 h, Uint32 ac, Uint32 at);

    void save(char *file);
    void open(char *file);

    void fill(int id);
    void fillWithID(int id);
    void setTID(int id, int x, int y);

    void onEvent(SDL_Event *event);
    void onDraw(SDL_Surface *sfc);
    void onIdle();

    void incAnimTicker();

    int getXTiles();
    int getYTiles();

    void updateOffset(int xo, int yo);
};

#endif

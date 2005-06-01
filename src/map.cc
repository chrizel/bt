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

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_endian.h>

#include "game.h"
#include "console.h"
#include "bmpl.h"
#include "sdl_events.h"
#include "alloc.h"

#include "error.h"

/*
#define SET_STOCK_ID(map, xt, yt, tid) \
    map->data[(yt + map->yoffset) * map->width + (xt + map->xoffset)] = tid;
*/

static void writeInt(FILE *fp, Uint32 num)
{
    SDL_RWops *area;
    area = SDL_RWFromFP(fp, 0);
    SDL_WriteLE32(area, num);
    SDL_FreeRW(area);
}

static Uint32 readInt(FILE *fp)
{
    int num;

    SDL_RWops *area;
    area = SDL_RWFromFP(fp, 0);
    num = SDL_ReadLE32(area);
    SDL_FreeRW(area);

    return num;
}

void Map::incAnimTicker()
{
    anim_ticker++;
    if (anim_ticker == anim_ticks)
	anim_ticker = 0;
}

Map::Map(Uint32 w, Uint32 h, Uint32 ac, Uint32 at)
{
    init(w, h, ac, at);
}

Map::Map(char *file)
{
    open(file);
}

Map::~Map()
{
}

void Map::init(Uint32 w, Uint32 h, Uint32 ac, Uint32 at)
{
    this->stocks = bmpl_get("map.stock_default");
    
    /* allocate anims and raw data arrays */
    this->anims = MALLOC_ARRAY(Uint32, ac * at);
    this->data  = MALLOC_ARRAY(Uint32, w * h);

    /* set data attributes */
    this->width      = w;
    this->height     = h;
    this->anim_count = ac;
    this->anim_ticks = at;

    /* set other attributes */
    this->xpos           = 0;
    this->ypos           = 0;
    this->anim_ticker    = 0;
    this->prev_ticker    = 1;
    this->version        = 1;
    this->switch_palette = 0;

    destTicks = SDL_GetTicks();

    srcrect.w = srcrect.h = TILE_SIZE;
}

void Map::save(char *file)
{
    int anim, tick, x, y, i;
    FILE *fp;

    fp = fopen(file, "w");

    // write header...
    fprintf(fp, "MAP:%u,%u,%u,%u,%u\n", 
	    this->version, this->width, this->height, 
	    this->anim_count, this->anim_ticks);

    // write anim data
    for (anim = 0; anim < this->anim_count; anim++)
        for (tick = 0; tick < this->anim_ticks; tick++)
            fprintf(fp, "%u.", this->anims[anim * this->anim_count + tick]);

    fputc('\n', fp);

    // write map data
    for (y = 0; y < this->height; y++)
        for (x = 0; x < this->width; x++)
	    writeInt(fp, this->data[this->width * y + x]);

    fclose(fp);
    game->print("ok\n");
}

void Map::open(char *file)
{
    int anim, tick, x, y, i, v;
    int w, h, ac, at;
    FILE *fp;

    game->print("read map...");
    fp = fopen(file, "r");

    // check if file is available...
    if (!fp) {
	    game->print("file not found");
        return;
    }

    // read header...
    fscanf(fp, "MAP:%u,%u,%u,%u,%u\n", &v, &w, &h, &ac, &at);
    //game->print("::%u, %u, %u, %u, %u", v, w, h, ac, at);

    // check v
    // TODO
    /*
      if (v != file_v)
        error("Wrong map version or wrong format.");
    */

    // create map in space
    init(w, h, ac, at);
    
    // read anim data
    for (anim = 0; anim < this->anim_count; anim++)
        for (tick = 0; tick < this->anim_ticks; tick++)
            fscanf(fp, "%u.", 
		   &this->anims[anim * this->anim_count + tick]);

    //if (anim) {
    //game->print("skip anim");
    fseek(fp, 1, SEEK_CUR); // jump over \n
    //}

    // read map data
    //game->print("width: %u height: %u", width, height);
    for (y = 0; y < this->height; y++)
        for (x = 0; x < this->width; x++)
            this->data[this->width * y + x] = readInt(fp);

    fclose(fp);
    //game->print("ok (cur_map->data[0] = %u)", this->data[0]);
    srcrect.w = srcrect.h = TILE_SIZE;

    whole_redraw = 1;
}

void Map::fill(int id)
{
    fillWithID(id);
}

void Map::fillWithID(int id)
{
    int x, y;

    for (y = 0; y < this->height; y++)
        for (x = 0; x < this->width; x++)
            this->data[y * this->width + x] = id;
}

void Map::setTID(int id, int x, int y)
{
    //SET_STOCK_ID(this, x, y, id);
}

void Map::onEvent(SDL_Event *event)
{
}

void Map::onDraw(SDL_Surface *sfc)
{
    // dstrect is the destination rect of the tile on the screen in pixels
    SDL_Rect dstrect;
    dstrect.w = dstrect.h = TILE_SIZE;

    // xpos and ypos are the x/y positions on the map in pixels!
    // now we have to calculate from which tile we have to begin painting
    Uint32 startXTile = (xpos - xpos % TILE_SIZE) / TILE_SIZE;
    Uint32 startYTile = (ypos - ypos % TILE_SIZE) / TILE_SIZE;
    Uint32 endXTile   = startXTile + getXTiles();
    Uint32 endYTile   = startYTile + getYTiles();
    dstrect.y         = 0 - ypos % TILE_SIZE;
    dstrect.x         = 0 - xpos % TILE_SIZE;

    // draw the map...
    for (Uint32 yTile = startYTile; yTile < endYTile; yTile++) {
        Sint32 oldX = dstrect.x;
        for (Uint32 xTile = startXTile; xTile < endXTile; xTile++) {
            int tileData = this->data[yTile * this->width + xTile];

            if (tileData & MF_ANIM) {
                // it's an animation, so we read the current animation tileData
                tileData = this->anims[(tileData & MF_ID) + this->anim_ticker];

                if (this->prev_ticker != this->anim_ticker)
                    PUSH_UR(dstrect);
            }

            // calculate srcrect
            const int stockRowTiles = 40;
            srcrect.x = (tileData % stockRowTiles) * TILE_SIZE;
            srcrect.y = ((tileData - (tileData % stockRowTiles)) / stockRowTiles) * TILE_SIZE;

            SDL_Rect real_dstrect = dstrect;
            SDL_BlitSurface(this->stocks, &srcrect, screen, &real_dstrect);

            dstrect.x = dstrect.x + TILE_SIZE;
        }
        dstrect.x = oldX;
        dstrect.y = dstrect.y + TILE_SIZE;
    }

    this->prev_ticker = this->anim_ticker;
}

void Map::onIdle()
{
    const int inc = 10;

    /*** Input ***/
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if ( keystate[SDLK_KP7] || keystate[SDLK_KP8] || keystate[SDLK_KP9]) {
        if (ypos > 0) {
            ypos -= inc; // this up...
	    whole_redraw = 1;
	}
    }
    if (keystate[SDLK_KP1] || keystate[SDLK_KP2] || keystate[SDLK_KP3]) {
        if ((ypos + getYTiles() * TILE_SIZE) < ((height - 1) * TILE_SIZE)) {
            ypos += inc; // this down...
	    whole_redraw = 1;
	}
    }
    if (keystate[SDLK_KP1] || keystate[SDLK_KP4] || keystate[SDLK_KP7]) {
	if (xpos > 0) {
	    xpos -= inc;	// this left...
	    whole_redraw = 1;
	}
    } 
    if (keystate[SDLK_KP3] || keystate[SDLK_KP6] || keystate[SDLK_KP9]) {
    	if ((xpos + getXTiles() * TILE_SIZE) < ((width - 1) * TILE_SIZE)) {
            xpos += inc;	// this right...
	    whole_redraw = 1;
	}
    }

    /*** Animation calculations ***/
    if (SDL_GetTicks() >= destTicks) {
	/* Do animation */
    incAnimTicker();

	/* Calculate next tick time */
	destTicks = SDL_GetTicks() + 100;
    }
}

int Map::getXTiles()
{
    return game->getWidth() / TILE_SIZE + 1;
}

int Map::getYTiles()
{
    return game->getHeight() / TILE_SIZE + 1;
}

void Map::updateOffset(int xo, int yo)
{
    if (xo != 0) { 
        xpos += xo;
        xpos = xpos < 0 ? 0 : xpos;
        whole_redraw = 1;
    }

    if (yo != 0) {
        ypos += yo;
        ypos = ypos < 0 ? 0 : ypos;
        whole_redraw = 1;
    }
}

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
#include <stdlib.h>
#include <SDL.h>
#include <SDL_endian.h>

#include "game.h"
#include "console.h"
#include "bmpl.h"
#include "sdl_events.h"
#include "alloc.h"

#include "error.h"

#define SET_STOCK_ID(map, xt, yt, tid) \
    map->data[(yt + map->yoffset) * map->width + (xt + map->xoffset)] = tid;

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
    this->xoffset        = 0;
    this->yoffset        = 0;
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
    //int x, y;

    SET_STOCK_ID(this, x, y, id);
    
    /* TODO 
    if (id) {
        SET_STOCK_ID(this, xt, yt, editor_pen);
    } else {
	
        if (editor_pg)
            for (y = 0; y < editor_pg_y; y++)
                for (x = 0; x < editor_pg_x; x++)
                    SET_STOCK_ID(this, xt + x, yt + y, 
				 editor_pg[editor_pg_x * y + x]);
    }
    */
}

void Map::onEvent(SDL_Event *event)
{
}

void Map::onDraw(SDL_Surface *sfc)
{
    int x, y, x2, y2, idx;
    int anim_switched = 0;
    int xtiles, ytiles;
    SDL_Rect rect;

    // TODO: We could do that already in init_map, if srcrect would be global!?
    //srcrect.w = srcrect.h = rect.w = rect.h = TILE_SIZE;
    rect.w = rect.h = TILE_SIZE;

    anim_switched = this->prev_ticker != this->anim_ticker;
    xtiles = getXTiles();
    ytiles = getYTiles();

    /* draw map */
    for (y = 0; y < ytiles; y++) {
        rect.y = TILE_SIZE * y;
	y2 = y + this->yoffset;

        for (x = 0; x < xtiles; x++) {
            rect.x = TILE_SIZE * x;
	    x2 = x + this->xoffset;

            idx = this->data[y2 * this->width + x2];

            if (idx & MF_ANIM) {
                /* it's an animation, so we read the current animation tile */
                idx = this->anims[(idx & MF_ID) + this->anim_ticker];

		// calculate source rect
		srcrect.x = (idx % 40) * TILE_SIZE;
		srcrect.y = ((idx - (idx % 40)) / 40) * TILE_SIZE;

		if (anim_switched)
		    PUSH_UR(rect);
	    } else {
		// calculate source rect
		srcrect.x = (idx % 40) * TILE_SIZE;
		srcrect.y = ((idx - (idx % 40)) / 40) * TILE_SIZE;
	    }

	    SDL_BlitSurface(this->stocks, &srcrect, screen, &rect);
        }
    }

    this->prev_ticker = this->anim_ticker;
}

void Map::onIdle()
{
    /*** Input ***/
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if ( keystate[SDLK_KP7] || keystate[SDLK_KP8] || keystate[SDLK_KP9]) {
        if (yoffset > 0) {
            yoffset--; // this up...
	    whole_redraw = 1;
	}
    }
    if (keystate[SDLK_KP1] || keystate[SDLK_KP2] || keystate[SDLK_KP3]) {
        if ((yoffset + getYTiles()) < (height - 1)) {
            yoffset++; // this down...
	    whole_redraw = 1;
	}
    }
    if (keystate[SDLK_KP1] || keystate[SDLK_KP4] || keystate[SDLK_KP7]) {
	if (xoffset > 0) {
	    xoffset--;	// this left...
	    whole_redraw = 1;
	}
    } 
    if (keystate[SDLK_KP3] || keystate[SDLK_KP6] || keystate[SDLK_KP9]) {
    	if ((xoffset + getXTiles()) < (width - 1)) {
            xoffset++;	// this right...
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
        xoffset += xo;         
        whole_redraw = 1;
    }

    if (yo != 0) {
        xoffset += yo;
        whole_redraw = 1;
    }
}

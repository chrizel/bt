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

#include "bt.h"
#include "bmpl.h"
#include "sdl_events.h"
#include "colors.h"
#include "alloc.h"

#include "error.h"

#include "eventhandler.h"

#define SET_STOCK_ID(map, xt, yt, id) \
    map->data[(yt + map->yoffset) * map->width + (xt + map->xoffset)] = id;

/* global static variables */

/* helper functions */
static Uint32 map_anim_timer(Uint32 interval, void *param);
static void write_int(FILE *fp, Uint32 num);
static Uint32 read_int(FILE *fp);

static void write_int(FILE *fp, Uint32 num)
{
    SDL_RWops *area;
    area = SDL_RWFromFP(fp, 0);
    SDL_WriteLE32(area, num);
    SDL_FreeRW(area);
}

static Uint32 read_int(FILE *fp)
{
    int num;

    SDL_RWops *area;
    area = SDL_RWFromFP(fp, 0);
    num = SDL_ReadLE32(area);
    SDL_FreeRW(area);

    return num;
}

static Uint32 map_anim_timer(Uint32 interval, void *param)
{
    Map *map;
    map = (Map *)param;

    map->anim_ticker++;
    if (map->anim_ticker == map->anim_ticks)
        map->anim_ticker = 0;

    /* TODO */
    map->switch_palette = 1;

    return interval;
}

void Map::create(Uint32 width, Uint32 height, 
			     Uint32 anim_count, Uint32 anim_ticks)
{
    /* load stocks surface */
    this->stocks = bmpl_get("map.stock_default");

    /* allocate anims and raw data arrays */
    this->anims = MALLOC_ARRAY(Uint32, anim_count * anim_ticks);
    this->data  = MALLOC_ARRAY(Uint32, width * height);

    /* set data attributes */
    this->width      = width;
    this->height     = height;
    this->anim_count = anim_count;
    this->anim_ticks = anim_ticks;

    /* set other attributes */
    this->xoffset        = 0;
    this->yoffset        = 0;
    this->anim_ticker    = 0;
    this->prev_ticker    = 1;
    this->version        = 1;
    this->switch_palette = 0;

    /* Add SDL_Time, so we can make tile animations... 
     * map as parameter... :)
     */
    SDL_AddTimer(100, map_anim_timer, (void *)this);
    srcrect.w = srcrect.h = TILE_SIZE;
}

Map::Map(char *file)
{
    open(file);
}

Map::Map(Uint32 width, Uint32 height, Uint32 anim_count, Uint32 anim_ticks)
{
    create(width, height, anim_count, anim_ticks);
    fill(0);
}

Map::~Map()
{
    // TODO    
}

void Map::save(char *file)
{
    int anim, tick, x, y, i;
    FILE *fp;

    fp = fopen(file, "w");

    /* write header... */
    fprintf(fp, "MAP:%u,%u,%u,%u,%u\n", 
	    this->version, this->width, this->height, 
	    this->anim_count, this->anim_ticks);

    /* write anim data */
    for (anim = 0; anim < this->anim_count; anim++)
        for (tick = 0; tick < this->anim_ticks; tick++)
            fprintf(fp, "%u.", this->anims[anim * this->anim_count + tick]);

    fputc('\n', fp);

    /* write map data */
    for (y = 0; y < this->height; y++)
        for (x = 0; x < this->width; x++)
            write_int(fp, this->data[this->width * y + x]);

    fclose(fp);
    printf("ok\n");
}

void Map::open(char *file)
{
    int anim, tick, x, y, i, version;
    int width, height, anim_count, anim_ticks;
    FILE *fp;

    printf("read map...");
    fp = fopen(file, "r");

    /* check if file is available... */
    if (!fp) {
        bt->print("file not found");
        return;
    }

    /* read header... */
    fscanf(fp, "MAP:%u,%u,%u,%u,%u\n", &version, &width, &height, &anim_count, &anim_ticks);

    /* check version */
    /* TODO
    if (version != file_version)
        error("Wrong map version or wrong format.");
    */

    /* create map in space */
    create(width, height, anim_count, anim_ticks);

    /* read anim data */
    for (anim = 0; anim < this->anim_count; anim++)
        for (tick = 0; tick < this->anim_ticks; tick++)
            fscanf(fp, "%u.", 
		   &this->anims[anim * this->anim_count + tick]);

    if (anim)
        fseek(fp, 1, SEEK_CUR); /* jump over \n */

    /* read map data */
    for (y = 0; y < this->height; y++)
        for (x = 0; x < this->width; x++)
            this->data[this->width * y + x] = read_int(fp);

    fclose(fp);
    printf("ok (cur_map->data[0] = %u)\n", this->data[0]);
    srcrect.w = srcrect.h = TILE_SIZE;
}

void Map::fill(int id)
{
    int x, y;

    for (y = 0; y < this->height; y++)
        for (x = 0; x < this->width; x++)
            this->data[y * this->width + x] = id;
}

void Map::put(int id, int xt, int yt)
{
    int x, y;

    if (id) {
        SET_STOCK_ID(this, xt, yt, editor_pen);
    } else {
        if (editor_pg)
            for (y = 0; y < editor_pg_y; y++)
                for (x = 0; x < editor_pg_x; x++)
                    SET_STOCK_ID(this, xt + x, yt + y, 
				 editor_pg[editor_pg_x * y + x]);
    }
}

void Map::onEvent(SDL_Event *event)
{
}

void Map::onDraw(SDL_Surface *sfc)
{
    int x, y, x2, y2, id;
    int anim_switched = 0;
    SDL_Rect rect;

    // TODO: We could do that already in init_map, if srcrect would be global!?
    //srcrect.w = srcrect.h = rect.w = rect.h = TILE_SIZE;
    rect.w = rect.h = TILE_SIZE;

    anim_switched = this->prev_ticker != this->anim_ticker;

    /* draw testmap */
    for (y = 0; y < YTILES; y++) {
        rect.y = TILE_SIZE * y;
	y2 = y + this->yoffset;

        for (x = 0; x < XTILES; x++) {
            rect.x = TILE_SIZE * x;
	    x2 = x + this->xoffset;

            id = this->data[y2 * this->width + x2];

            if (id & MF_ANIM) {
                /* it's an animation, so we read the current animation tile */
                id = this->anims[(id & MF_ID) + this->anim_ticker];

		// calculate source rect
		srcrect.x = (id % XTILES) * TILE_SIZE;
		srcrect.y = ((id - (id % XTILES)) / XTILES) * TILE_SIZE;

		if (anim_switched)
		    PUSH_UR(rect);
	    } else {
		// calculate source rect
		srcrect.x = (id % XTILES) * TILE_SIZE;
		srcrect.y = ((id - (id % XTILES)) / XTILES) * TILE_SIZE;
	    }

	    SDL_BlitSurface(this->stocks, &srcrect, screen, &rect);
        }
    }

    this->prev_ticker = this->anim_ticker;
}

void Map::onIdle()
{
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if (bt->getConsole()->isVisible())
        return;
    /*
    if ( keystate[SDLK_UP]) {
        if (this->yoffset > 0) {
            this->yoffset--; // this up...
	    whole_redraw = 1;
	}
    } else if (keystate[SDLK_DOWN]) {
        if ((this->yoffset + YTILES) < (this->height - 1)) {
            this->yoffset++; // this down...
	    whole_redraw = 1;
	}
    }

    if (keystate[SDLK_LEFT]) {
	if (this->xoffset > 0) {
	    this->xoffset--;	// this left...
	    whole_redraw = 1;
	}
    } else if (keystate[SDLK_RIGHT]) {
    	if ((this->xoffset + XTILES) < (this->width - 1)) {
            this->xoffset++;	// this right...
	    whole_redraw = 1;
	}
    }
    */

    if (editor_mode) {
        int x, y, xt, yt;
        Uint8 mousestate = SDL_GetMouseState(&x, &y);

        xt = (x - (x % TILE_SIZE)) / TILE_SIZE;
        yt = (y - (y % TILE_SIZE)) / TILE_SIZE;

        if (mousestate & SDL_BUTTON(1)) {
            put(1, xt, yt);
	    whole_redraw = 1;
        } else if (mousestate & SDL_BUTTON(3)) {
            put(0, xt, yt);
	    whole_redraw = 1;
	}
    }
}

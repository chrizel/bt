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
//#include "editor.h"

//#include "eventhandler.h"

#define SET_STOCK_ID(map, xt, yt, id) \
    map->data[(yt + map->yoffset) * map->width + (xt + map->xoffset)] = id;

/* global static variables */

@implementation Map

/* helper functions */
static Uint32 map_anim_timer(Uint32 interval, void *param);

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

- (id)initWithWidth:(Uint32)width height:(Uint32)height animCount:(Uint32)anim_count animTicks:(Uint32)anim_ticks
{
    self->stocks = bmpl_get("map.stock_default");
    
    /* allocate anims and raw data arrays */
    self->anims = MALLOC_ARRAY(Uint32, anim_count * anim_ticks);
    self->data  = MALLOC_ARRAY(Uint32, width * height);

    /* set data attributes */
    self->width      = width;
    self->height     = height;
    self->anim_count = anim_count;
    self->anim_ticks = anim_ticks;

    /* set other attributes */
    self->xoffset        = 0;
    self->yoffset        = 0;
    self->anim_ticker    = 0;
    self->prev_ticker    = 1;
    self->version        = 1;
    self->switch_palette = 0;

    /* Add SDL_Time, so we can make tile animations... 
     * map as parameter... :)
     */
    SDL_AddTimer(100, map_anim_timer, (void *)this);
    srcrect.w = srcrect.h = TILE_SIZE;

    return self;
}

+ (id)newWithFile:(char *)file
{
    return [[super new] open:file];
}

+ (id)newWithWidth:(Uint32)width height:(Uint32)height animCount:(Uint32) anim_count animTicks:(Uint32)anim_ticks
{
    id me = [super new];
    me = [me initWithWidth:width height:height animCount:anim_count animTicks:anim_ticks];
    [me fill:0];
    
    return me;
}

- save:(char *)file
{
    int anim, tick, x, y, i;
    FILE *fp;

    fp = fopen(file, "w");

    // write header...
    fprintf(fp, "MAP:%u,%u,%u,%u,%u\n", 
	    self->version, self->width, self->height, 
	    self->anim_count, self->anim_ticks);

    // write anim data
    for (anim = 0; anim < self->anim_count; anim++)
        for (tick = 0; tick < self->anim_ticks; tick++)
            fprintf(fp, "%u.", self->anims[anim * self->anim_count + tick]);

    fputc('\n', fp);

    // write map data
    for (y = 0; y < self->height; y++)
        for (x = 0; x < self->width; x++)
	    writeInt(fp, self->data[self->width * y + x]);

    fclose(fp);
    printf("ok\n");
}

- open:(char *)file
{
    int anim, tick, x, y, i, version;
    int width, height, anim_count, anim_ticks;
    FILE *fp;

    printf("read map...");
    fp = fopen(file, "r");

    // check if file is available...
    if (!fp) {
        bt->print("file not found");
        return;
    }

    // read header...
    fscanf(fp, "MAP:%u,%u,%u,%u,%u\n", &version, &width, &height, &anim_count, &anim_ticks);

    // check version
    // TODO
    /*
      if (version != file_version)
        error("Wrong map version or wrong format.");
    */

    // create map in space
    create(width, height, anim_count, anim_ticks);
    
    // read anim data
    for (anim = 0; anim < self->anim_count; anim++)
        for (tick = 0; tick < self->anim_ticks; tick++)
            fscanf(fp, "%u.", 
		   &self->anims[anim * self->anim_count + tick]);

    if (anim)
        fseek(fp, 1, SEEK_CUR); // jump over \n

    // read map data
    for (y = 0; y < self->height; y++)
        for (x = 0; x < self->width; x++)
            self->data[self->width * y + x] = Editor::readInt(fp);

    fclose(fp);
    printf("ok (cur_map->data[0] = %u)\n", self->data[0]);
    srcrect.w = srcrect.h = TILE_SIZE;
}

- fill:(int)id
{
    [self fillWithID:id];
}

- fillWithID:(int)id
{
    int x, y;

    for (y = 0; y < self->height; y++)
        for (x = 0; x < self->width; x++)
            self->data[y * self->width + x] = id;
}

- putID:(int)id xT:(int)xt yT:(int)yt;
{
    int x, y;

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

- onEvent:(SDL_Event *)event
{
}

- onDraw:(SDL_Surface *)sfc
{
    int x, y, x2, y2, id;
    int anim_switched = 0;
    SDL_Rect rect;

    // TODO: We could do that already in init_map, if srcrect would be global!?
    //srcrect.w = srcrect.h = rect.w = rect.h = TILE_SIZE;
    rect.w = rect.h = TILE_SIZE;

    anim_switched = self->prev_ticker != self->anim_ticker;

    /* draw testmap */
    for (y = 0; y < YTILES; y++) {
        rect.y = TILE_SIZE * y;
	y2 = y + self->yoffset;

        for (x = 0; x < XTILES; x++) {
            rect.x = TILE_SIZE * x;
	    x2 = x + self->xoffset;

            id = self->data[y2 * self->width + x2];

            if (id & MF_ANIM) {
                /* it's an animation, so we read the current animation tile */
                id = self->anims[(id & MF_ID) + self->anim_ticker];

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

	    SDL_BlitSurface(self->stocks, &srcrect, screen, &rect);
        }
    }

    self->prev_ticker = self->anim_ticker;
}

- onIdle
{
    Uint8 *keystate = SDL_GetKeyState(NULL);

    /*
    if (bt->getConsole()->isVisible())
        return;
    */
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
}

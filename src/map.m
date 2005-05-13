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

#define SET_STOCK_ID(map, xt, yt, tid) \
    map->data[(yt + map->yoffset) * map->width + (xt + map->xoffset)] = tid;

/* global static variables */

@implementation Map

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

- incAnimTicker
{
    anim_ticker++;
    if (anim_ticker == anim_ticks)
	anim_ticker = 0;
}

- (id)initWithWidth:(Uint32)w height:(Uint32)h animCount:(Uint32)ac animTicks:(Uint32)at
{
    self->stocks = bmpl_get("map.stock_default");
    
    /* allocate anims and raw data arrays */
    self->anims = MALLOC_ARRAY(Uint32, ac * at);
    self->data  = MALLOC_ARRAY(Uint32, w * h);

    /* set data attributes */
    self->width      = w;
    self->height     = h;
    self->anim_count = ac;
    self->anim_ticks = at;

    /* set other attributes */
    self->xoffset        = 0;
    self->yoffset        = 0;
    self->anim_ticker    = 0;
    self->prev_ticker    = 1;
    self->version        = 1;
    self->switch_palette = 0;

    destTicks = SDL_GetTicks();

    srcrect.w = srcrect.h = TILE_SIZE;

    return self;
}

+ (id)newWithFile:(char *)file
{
    printf("+ newWithFile\n");
    id me = [super new];
    [me open:file];
    return me;
}

+ (id)newWithWidth:(Uint32)w height:(Uint32)h animCount:(Uint32)ac animTicks:(Uint32)at
{
    id me = [super new];
    me = [me initWithWidth:w height:h animCount:ac animTicks:at];
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
    int anim, tick, x, y, i, v;
    int w, h, ac, at;
    FILE *fp;

    printf("read map...");
    fp = fopen(file, "r");

    // check if file is available...
    if (!fp) {
	[bt printLine:"file not found"];
        return nil;
    }

    // read header...
    fscanf(fp, "MAP:%u,%u,%u,%u,%u\n", &v, &w, &h, &ac, &at);
    printf("::%u, %u, %u, %u, %u\n", v, w, h, ac, at);

    // check v
    // TODO
    /*
      if (v != file_v)
        error("Wrong map version or wrong format.");
    */

    // create map in space
    [self initWithWidth:w height:h animCount:ac animTicks:at];
    
    // read anim data
    for (anim = 0; anim < self->anim_count; anim++)
        for (tick = 0; tick < self->anim_ticks; tick++)
            fscanf(fp, "%u.", 
		   &self->anims[anim * self->anim_count + tick]);

    //if (anim) {
    printf("skip anim\n");
    fseek(fp, 1, SEEK_CUR); // jump over \n
    //}

    // read map data
    printf("width: %u height: %u\n", width, height);
    for (y = 0; y < self->height; y++)
        for (x = 0; x < self->width; x++)
            self->data[self->width * y + x] = readInt(fp);

    fclose(fp);
    printf("ok (cur_map->data[0] = %u)\n", self->data[0]);
    srcrect.w = srcrect.h = TILE_SIZE;

    whole_redraw = 1;
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

- setTID:(int)tid onX:(int)x andY:(int)y;
{
    //int x, y;

    SET_STOCK_ID(self, x, y, tid);
    
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
    int x, y, x2, y2, idx;
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

            idx = self->data[y2 * self->width + x2];

            if (idx & MF_ANIM) {
                /* it's an animation, so we read the current animation tile */
                idx = self->anims[(idx & MF_ID) + self->anim_ticker];

		// calculate source rect
		srcrect.x = (idx % XTILES) * TILE_SIZE;
		srcrect.y = ((idx - (idx % XTILES)) / XTILES) * TILE_SIZE;

		if (anim_switched)
		    PUSH_UR(rect);
	    } else {
		// calculate source rect
		srcrect.x = (idx % XTILES) * TILE_SIZE;
		srcrect.y = ((idx - (idx % XTILES)) / XTILES) * TILE_SIZE;
	    }

	    SDL_BlitSurface(self->stocks, &srcrect, screen, &rect);
        }
    }

    self->prev_ticker = self->anim_ticker;
}

- onIdle
{
    /*** Input ***/
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if ([[bt getConsole] isVisible])
        return nil;

    if ( keystate[SDLK_KP7] || keystate[SDLK_KP8] || keystate[SDLK_KP9]) {
        if (yoffset > 0) {
            yoffset--; // this up...
	    whole_redraw = 1;
	}
    }
    if (keystate[SDLK_KP1] || keystate[SDLK_KP2] || keystate[SDLK_KP3]) {
        if ((yoffset + YTILES) < (height - 1)) {
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
    	if ((xoffset + XTILES) < (width - 1)) {
            xoffset++;	// this right...
	    whole_redraw = 1;
	}
    }

    /*** Animation calculations ***/
    if (SDL_GetTicks() >= destTicks) {
	/* Do animation */
	[self incAnimTicker];

	/* Calculate next tick time */
	destTicks = SDL_GetTicks() + 100;
    }
}

@end

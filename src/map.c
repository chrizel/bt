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

#include "bt.h"
#include "bmpl.h"
#include "sdl_events.h"
#include "testmap.h"
#include "colors.h"
#include "alloc.h"

#include "error.h"

#define SET_STOCK_ID(map, xt, yt, id) \
    map->data[(yt + map->yoffset) * map->width + (xt + map->xoffset)] = id;

/* global static variables */
static SDL_Rect srcrect;

/* helper functions */
static t_map *map_new_internal(Uint32 width, Uint32 height, 
			       Uint32 anim_count, Uint32 anim_ticks);
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
    t_map *map;
    map = (t_map *)param;

    map->anim_ticker++;
    if (map->anim_ticker == map->anim_ticks)
	map->anim_ticker = 0;

    /* TODO */
    map->switch_palette = 1;

    return interval;
}

static t_map *map_new_internal(Uint32 width, Uint32 height, 
			       Uint32 anim_count, Uint32 anim_ticks)
{
    t_map *map;

    /* first of all: create space for our map structure */
    map = MALLOC(t_map);

    /* load stocks surface */
    map->stocks = bmpl_get("map.stock_default");

    /* allocate anims and raw data arrays */
    map->anims = MALLOC_ARRAY(int, anim_count * anim_ticks);
    map->data  = MALLOC_ARRAY(int, width * height);

    /* set data attributes */
    map->width      = width;
    map->height     = height;
    map->anim_count = anim_count;
    map->anim_ticks = anim_ticks;

    /* set other attributes */
    map->xoffset        = 0;
    map->yoffset        = 0;
    map->anim_ticker    = 0;
    map->version        = 1;
    map->switch_palette = 0;

    /* Add SDL_Time, so we can make tile animations... 
     * map as parameter... :)
     */
    SDL_AddTimer(100, map_anim_timer, (void *)map);

    return map;
}

t_map *map_new(char *file)
{
    t_map *map;
    map = map_open(file);
    return map;
}

t_map *map_new_empty(Uint32 width, Uint32 height, Uint32 anim_count, Uint32 anim_ticks)
{
    t_map *map;

    map = map_new_internal(width, height, anim_count, anim_ticks);
    map_fill(map, 0);

    return map;
}

void map_free(t_map *map)
{
    /* TODO */
}

void map_save(t_map *map, char *file)
{
    int anim, tick, x, y, i;
    FILE *fp;

    fp = fopen(file, "w");

    /* write header... */
    fprintf(fp, "MAP:%u,%u,%u,%u,%u\n", 
	    map->version, map->width, map->height, 
	    map->anim_count, map->anim_ticks);

    /* write anim data */
    for (anim = 0; anim < map->anim_count; anim++)
        for (tick = 0; tick < map->anim_ticks; tick++)
            fprintf(fp, "%u.", map->anims[anim * map->anim_count + tick]);

    fputc('\n', fp);

    /* write map data */
    for (y = 0; y < map->height; y++)
        for (x = 0; x < map->width; x++)
            write_int(fp, map->data[map->width * y + x]);

    fclose(fp);
    printf("ok\n");
}

t_map *map_open(char *file)
{
    int anim, tick, x, y, i, version;
    int width, height, anim_count, anim_ticks;
    FILE *fp;
    t_map *map;

    printf("read map...");
    fp = fopen(file, "r");

    /* check if file is available... */
    if (!fp) {
        CON_Out(btConsole, "file not found");
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
    map = map_new_internal(width, height, anim_count, anim_ticks);

    /* read anim data */
    for (anim = 0; anim < map->anim_count; anim++)
        for (tick = 0; tick < map->anim_ticks; tick++)
            fscanf(fp, "%u.", 
		   &map->anims[anim * map->anim_count + tick]);

    if (anim)
        fseek(fp, 1, SEEK_CUR); /* jump over \n */

    /* read map data */
    for (y = 0; y < map->height; y++)
        for (x = 0; x < map->width; x++)
            map->data[map->width * y + x] = read_int(fp);

    fclose(fp);
    printf("ok (cur_map->data[0] = %u)\n", map->data[0]);

    return map;
}

void map_fill(t_map *map, int id)
{
    int x, y;

    for (y = 0; y < map->height; y++)
        for (x = 0; x < map->width; x++)
            map->data[y * map->width + x] = id;
}

void map_put(t_map *map, int id, int xt, int yt)
{
    int x, y;

    if (id) {
        SET_STOCK_ID(map, xt, yt, editor_pen);
    } else {
        if (editor_pg)
            for (y = 0; y < editor_pg_y; y++)
                for (x = 0; x < editor_pg_x; x++)
                    SET_STOCK_ID(map, xt + x, yt + y, 
				 editor_pg[editor_pg_x * y + x]);
    }
}

void map_draw(t_map *map, SDL_Surface *sfc)
{
    int x, y, x2, y2, id;
    SDL_Rect rect;

    if (!map)
	return;

    // TODO: We could do that already in init_map, if srcrect would be global!?
    srcrect.w = TILE_SIZE;
    srcrect.h = TILE_SIZE;

    /* draw testmap */
    for (y = 0; y < YTILES; y++) {
        rect.y = TILE_SIZE * y;
	y2 = y + map->yoffset;

        for (x = 0; x < XTILES; x++) {
            rect.x = TILE_SIZE * x;
	    x2 = x + map->xoffset;

            id = map->data[y2 * map->width + x2];

            if (id & MF_ANIM)
                /* it's an animation, so we read the current animation tile */
                id = map->anims[(id & MF_ID) + map->anim_ticker];

            // calculate source rect
            srcrect.x = (id % XTILES) * TILE_SIZE;
            srcrect.y = ((id - (id % XTILES)) / XTILES) * TILE_SIZE;

            SDL_BlitSurface(map->stocks, &srcrect, screen, &rect);
        }
    }
}

void map_idle(t_map *map)
{
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if (CON_isVisible(btConsole))
        return;

    if ( keystate[SDLK_UP]) {
	if (map->yoffset > 0)
	    map->yoffset--; // map up...
    } else if (keystate[SDLK_DOWN]) {
	if ((map->yoffset + YTILES) < (map->height - 1))
	    map->yoffset++; // map down...
    }

    if (keystate[SDLK_LEFT]) {
	if (map->xoffset > 0)
	    map->xoffset--;	// map left...
    } else if (keystate[SDLK_RIGHT]) {
	if ((map->xoffset + XTILES) < (map->width - 1))
	    map->xoffset++;	// map right...
    }

    if (editor_mode) {
        int x, y, xt, yt;
        Uint8 mousestate = SDL_GetMouseState(&x, &y);

        xt = (x - (x % TILE_SIZE)) / TILE_SIZE;
        yt = (y - (y % TILE_SIZE)) / TILE_SIZE;

        if (mousestate & SDL_BUTTON(1))
            map_put(map, 1, xt, yt);
        else if (mousestate & SDL_BUTTON(3))
            map_put(map, 0, xt, yt);
    }
}

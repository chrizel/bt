#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "bt.h"
#include "bmpl.h"
#include "sdl_events.h"
#include "map.h"
#include "testmap.h"
#include "colors.h"

#define TILE_SIZE 20
#define XTILES 40 /* tiles per row */
#define YTILES 30 /* tiles per col */

static SDL_Surface **stocks;
static SDL_Surface *wallpaper;
static int xoffset = 0, yoffset = 0;
static int anim_ticker = 0;
static int file_version = 1;
static map_data *cur_map = NULL;
static union _utile {
    int as_int;
    char as_char[4];
} utile;

static void draw_map();
static void on_idle();
static void load_stocks(char *id, int xcount, int ycount);
static SDL_Surface *get_tile(SDL_Surface *src, int x, int y);
static Uint32 switch_anim_ticker(Uint32 interval, void *param);

static void write_map(char *filename);
static void read_map(char *filename);

void init_map()
{
    load_stocks("map.stock1", 3, 4); 
    evl_reg(sdl_evl, EV_SDL_PAINT, draw_map);
    evl_reg(sdl_evl, EV_SDL_IDLE, on_idle);

    /* TODO: load map */
    /*
    cur_map.width      = TM_WIDTH;
    cur_map.height     = TM_HEIGHT;
    cur_map.anim_count = TM_ANIMS;
    cur_map.anim_ticks = TM_TICKS;
    cur_map.anims      = test_anims;
    cur_map.data       = test_map;
    */
    //read_map("main.map");

    //write_map("main.map");
    read_map("main.map");

    SDL_AddTimer(250, switch_anim_ticker, NULL);
}

static void write_map(char *filename)
{
    int anim, tick, x, y, i;
    FILE *fp;

    if(!cur_map)
        return;

    printf("write map...");
    fp = fopen(filename, "w");
    
    /* write header... */
    fprintf(fp, "MAP:%d,%d,%d,%d,%d\n", file_version, cur_map->width, cur_map->height, cur_map->anim_count, cur_map->anim_ticks);

    /* write anim data */
    for (anim = 0; anim < cur_map->anim_count; anim++) {
        for (tick = 0; tick < cur_map->anim_ticks; tick++) {
            fprintf(fp, "%d.", cur_map->anims[anim * cur_map->anim_count + tick]);
        }
    }
    fputc('\n', fp);

    /* write map data */
    for (y = 0; y < cur_map->height; y++) {
        for (x = 0; x < cur_map->width; x++) {
            /* put tile data into union */
            utile.as_int = cur_map->data[y * cur_map->width + x];

            /* write int as 4 chars */
            for (i = 0; i < 4; i++)
                fputc(utile.as_char[i], fp);
        }
    }

    fclose(fp);
    printf("ok\n");
}

static void read_map(char *filename)
{
    int anim, tick, x, y, i, version;
    FILE *fp;

    printf("read map...");
    fp = fopen(filename, "r");

    /* check if cur_map is null */
    if (cur_map == NULL)
        cur_map = (map_data *)malloc(sizeof(map_data));

    /* read header... */
    fscanf(fp, "MAP:%d,%d,%d,%d,%d\n", &version, &cur_map->width, &cur_map->height, &cur_map->anim_count, &cur_map->anim_ticks);

    /* check version */
    if (version != file_version)
        error("Wrong map version.");

    /* ok, now it's important to reserve enough space for our map! */
    cur_map->anims = (int *)malloc(cur_map->anim_count * cur_map->anim_ticks * sizeof(int));
    cur_map->data  = (int *)malloc(cur_map->width * cur_map->height * sizeof(int));

    /* read anim data */
    for (anim = 0; anim < cur_map->anim_count; anim++) {
        for (tick = 0; tick < cur_map->anim_ticks; tick++) {
            fscanf(fp, "%d.", &cur_map->anims[anim * cur_map->anim_count + tick]);
        }
    }
    fseek(fp, 1, SEEK_CUR); /* jump over \n */

    /* read map data */
    for (y = 0; y < cur_map->height; y++) {
        for (x = 0; x < cur_map->width; x++) {
            /* put tile data into union */
            for (i = 0; i < 4; i++)
                utile.as_char[i] = (unsigned char) fgetc(fp);

            /* write tile data into our struct */
            cur_map->data[y * cur_map->width + x] = utile.as_int;
        }
    }

    fclose(fp);
    printf("ok\n");
}

static Uint32 switch_anim_ticker(Uint32 interval, void *param)
{
    anim_ticker = !anim_ticker;
    return interval;
}

static void draw_map()
{
    int x, y, x2, y2, id;
    SDL_Rect rect;

    if (cur_map == NULL) {
        /*
        rect.x = 0;
        rect.y = 0;
        SDL_BlitSurface(wallpaper, NULL, screen, &rect);
        */
        return;
    }

    /* consider offsets */
    if (xoffset < 0)
        xoffset = cur_map->width - (cur_map->width % abs(xoffset));

    if (yoffset < 0)
        yoffset = cur_map->height - (cur_map->height % abs(yoffset));

    /* draw testmap */
    for (y = 0; y < YTILES; y++) {
        rect.y = TILE_SIZE * y;
        for (x = 0; x < XTILES; x++) {
            rect.x = TILE_SIZE * x;

            //printf("%d\n", yoffset);

            if ((y + yoffset) >= cur_map->height)
                y2 = y + (yoffset - cur_map->height);
            else
                y2 = y + yoffset;

            if ((x + xoffset) >= cur_map->width)
                x2 = x + (xoffset - cur_map->width);
            else
                x2 = x + xoffset;

            id = cur_map->data[y2 * cur_map->width + x2];
            if (id & MF_ANIM) {
                /* it's an animation, so we read the current animation tile */
                id = cur_map->anims[(id & MF_ID) + anim_ticker];
            } 

            SDL_BlitSurface(stocks[id], NULL, screen, &rect);
        }
    }
}

static void on_idle()
{
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if (CON_isVisible(btConsole))
        return;

    if (keystate[SDLK_r]) {
        if (!cur_map)
            read_map("main.map");
    } else if (keystate[SDLK_w]) {
        write_map("main.map");
    }
    
    if (cur_map) {
        if ( keystate[SDLK_UP]) {
            // map up...
            if (yoffset < 1)
                yoffset = cur_map->height - 1;
            else
                yoffset--;
        } else if (keystate[SDLK_DOWN]) {
            // map down...
            if (yoffset >= cur_map->height)
                yoffset = 0;
            else
                yoffset++;
        }

        if (keystate[SDLK_LEFT]) {
            // map left...
            if (xoffset < 1)
                xoffset = cur_map->width - 1;
            else
                xoffset--;
        } else if (keystate[SDLK_RIGHT]) {
            // map right...
            if (xoffset >= cur_map->width)
                xoffset = 0;
            else
                xoffset++;
        }
    }
}

static void load_stocks(char *id, int xcount, int ycount)
{
    SDL_Surface *tmp;
    /* first we create space for our stocks array */
    stocks = (SDL_Surface**) malloc(sizeof (SDL_Surface*) * xcount * ycount);
    
    /* then we load the stock bitmap */
    tmp = bmpl_get(id);

    /* now we copy create one surface per tile ... copy it from tmp */
    {
        int x, y, i = 0;

        for (y = 0; y < ycount; y++)
            for (x = 0; x < xcount; x++)
               stocks[i++] = get_tile(tmp, x, y);
    }

    SDL_FreeSurface(tmp);
}

static SDL_Surface *get_tile(SDL_Surface *src, int x, int y)
{
    SDL_Surface *tile;
    SDL_Rect srcrect; 

    tile = SDL_CreateRGBSurface(SDL_SWSURFACE, TILE_SIZE, TILE_SIZE, 8, 0, 0, 0, 0); 
    SDL_SetColors(tile, colors, 0, n_colors);

    srcrect.x = x * TILE_SIZE;
    srcrect.y = y * TILE_SIZE;
    srcrect.w = srcrect.x + TILE_SIZE;
    srcrect.h = srcrect.y + TILE_SIZE;

    SDL_BlitSurface (src, &srcrect, tile, NULL);

    return tile;
}

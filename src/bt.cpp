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
#include <stdarg.h>
#include <string.h>

#include <SDL.h>

#include <iostream>

#include "bt.h"
#include "error.h"
#include "event.h"
#include "rotozoom/SDL_rotozoom.h"
#include "m_math.h"
#include "colors.h"
#include "textshow.h"
#include "input.h"
#include "filter.h"
#include "map.h"
#include "bmpl.h"
#include "game.h"

SDL_Surface *screen;
SDL_Surface *minilogo;

int editor_mode;
int editor_pen;
int *editor_pg;
int editor_pg_y;
int editor_pg_x;

int frames;
int ticks_begin, ticks_end;


Game *bt;

static void keydown();
static void quit();

int main(int argc, char *argv[])
{
    editor_mode = 1;
    editor_pen = 0;
    editor_pg = NULL;
    cur_filter = NULL;

    puts(GPL_TEXT);

    bt = new Game("Bermuda Triangle");

    // init_sdl_events();

    minilogo = bmpl_get("main.minilogo");

    // evl_reg(evl_sdl, EV_SDL_KEYDOWN, keydown);

    bt->run();

    return 0;
}

static void keydown()
{
  if (sdl_ev->key.keysym.sym == SDLK_q)
    bt_exit();
}

static void quit()
{
    bt_exit();
}

void bt_exit()
{
    /* TODO: cleanup all surfaces, etc. */

    printf("Bye :)\n");
    exit(0);
}

/*
Yes, that sprintf stuff is all very quick and dirty, but we will change this in future...
*/
void bt_editor(void)
{
    char buf[100];

    editor_mode = !editor_mode;
    sprintf(buf, "editor_mode = %d", editor_mode);

    bt->print(buf);
}

void bt_pen(void)
{
    int buf[100], id;
    sscanf(bt->getConsole()->getLastParam(), "%s %d", buf, &id);

    editor_pen = id;
}

void bt_pg(void)
{
    int i, j, len, pos;
    char buf1[512], buf2[512];
    sscanf(bt->getConsole()->getLastParam(), "%s %d %d %[^a-z]", buf1, &editor_pg_x, &editor_pg_y, buf2);

    if (editor_pg)
        FREE(editor_pg);

    editor_pg = MALLOC_ARRAY(int, editor_pg_x * editor_pg_y);

    j = 0;
    pos = 0;
    //printf("\nbuf2: %s\n", buf2);
    for (i = 0; (i <= strlen(buf2)) && (pos < editor_pg_x * editor_pg_y); i++) {
        //printf("%d: %c\n", i, buf2[i]);
        buf1[j] = buf2[i];

        if ((buf1[j] == ' ') || (i == strlen(buf2))) {
            buf1[j] = '\0';
            //printf("New item (%d): %s\n", j, buf1);
            editor_pg[pos] = atoi(buf1);
            pos++;
            j = 0;
        } else
            j++;
    }

    bt->print("set pg");

    /*
    printf("\npg:\t%d\n", editor_pg_x * editor_pg_y);
    for (i = 0; i < editor_pg_x * editor_pg_y; i++)
        printf("\t%d\n", editor_pg[i]);
        */
}

void bt_write(void)
{
    char buf1[100], buf2[100];
    sscanf(bt->getConsole()->getLastParam(), "%s %s", buf1, buf2);

    bt->getMap()->save(buf2);
}

void bt_load(void)
{
    char buf1[100], buf2[100];
    sscanf(bt->getConsole()->getLastParam(), "%s %s", buf1, buf2);

    std::cout << "Not implemented.";
    /* TODO
    delete map;
    map = new Map(buf2);
    */
}

void bt_fill(void)
{
    char buf1[100];
    int id;
    sscanf(bt->getConsole()->getLastParam(), "%s %d", buf1, &id);

    bt->getMap()->fill(id);
}

void bt_put(void)
{
    char buf1[100];
    int id, x, y;
    sscanf(bt->getConsole()->getLastParam(), "%s %d %d %d", buf1, &id, &x, &y);

    bt->getMap()->put(id, x, y);
}

void bt_new(void)
{
    char buf1[100];
    int width, height, anim_count, anim_ticks;

    sscanf(bt->getConsole()->getLastParam(), "%s %d %d %d %d %d", buf1, &width, &height, &anim_count, &anim_ticks);

    std::cout << "Not implemented.";
    /* TODO
    delete map;
    map = new Map(width, height, anim_count, anim_ticks);
    */
}

#ifdef DO_FRAMETEST
void fps_output()
{
    ticks_end = SDL_GetTicks();
    //    printf("Frame statistic:\n");
    //  printf("----------------\n");
    // printf("Frames: %i\n", frames);
    //printf("Milliseconds: %i\n", ticks_end - ticks_begin);
    printf("FPS: %i\n", (1000 * frames) / (ticks_end - ticks_begin));
    ticks_begin = SDL_GetTicks();
    frames = 0;
}
#endif

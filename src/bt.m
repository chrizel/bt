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

#include "glSDL.h"

//#include <iostream>

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

int frames;
int ticks_begin, ticks_end;


//Game *bt;

int main(int argc, char *argv[])
{
    bt_argc = argc;
    bt_argv = argv;

    cur_filter = NULL;
    printf("create bt...\n");
    bt = [Game newWithTitle:"Bermuda Triangle"];

    // register quit function for cleanup
    atexit(btQuit);

    minilogo = bmpl_get("main.minilogo");

    printf("run...\n");
    [bt run];

    return 0;
}

void btQuit()
{
    printf("Call bt free...\n");
    [bt free];

    printf("Bye :)\n");
}

/*
Yes, that sprintf stuff is all very quick and dirty, but we will change this in future...
*/
/*
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

    TODO:
    delete map;
    map = new Map(buf2);
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

    TODO:
    delete map;
    map = new Map(width, height, anim_count, anim_ticks);
}
*/

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

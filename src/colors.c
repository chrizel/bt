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
#include "colors.h"

static int load_gimp_palette(char *file);

void init_colors()
{
    printf("load color palette...");
    /* Load GIMP palette */
    load_gimp_palette("data/palette3.gpl");
    clone_colors();
    printf("ok\n");

    /* Set palette */
    SDL_SetColors(screen, colors, 0, n_colors);
}

void clone_colors()
{
    int i;
    for (i = 0; i < n_colors; i++) {
        orig_colors[i].r = colors[i].r;
        orig_colors[i].g = colors[i].g;
        orig_colors[i].b = colors[i].b;
    }
}

static int load_gimp_palette(char *file)
{
    FILE *fp;
    int i;
    char buf[100];
    int rgb[3];

    fp = fopen(file, "r");

    if (!fp)
        error("GIMP palette not found.");

    /* goto line 5... */
    fgets(buf, 100, fp);
    fgets(buf, 100, fp);
    fgets(buf, 100, fp);
    fgets(buf, 100, fp);

    n_colors = 0;
    for (i = 0; i < 255; i++) {
        /* read numbers */
        fscanf(fp, "%d %d %d", &rgb[0], &rgb[1], &rgb[2]);

        /* Set colors */
        colors[i].r = rgb[0];
        colors[i].g = rgb[1];
        colors[i].b = rgb[2];

        //printf("%d,%d,%d\n", rgb[0], rgb[1], rgb[2]);

        /* goto next line... */
        fgets(buf, 100, fp);

        n_colors++;

        if (feof(fp))
            break;
    }

    fclose(fp);
}
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "colors.h"

static int load_gimp_palette(char *file);

void init_colors()
{
    printf("load color palette...");
    /* Load GIMP palette */
    load_gimp_palette("data/palette3.gpl");
    clone_colors();
    printf("ok\n");

    /* Set palette */
    SDL_SetColors(screen, colors, 0, n_colors);
}

void clone_colors()
{
    int i;
    for (i = 0; i < n_colors; i++) {
        orig_colors[i].r = colors[i].r;
        orig_colors[i].g = colors[i].g;
        orig_colors[i].b = colors[i].b;
    }
}

static int load_gimp_palette(char *file)
{
    FILE *fp;
    int i;
    char buf[100];
    int rgb[3];

    fp = fopen(file, "r");

    if (!fp)
        error("GIMP palette not found.");

    /* goto line 5... */
    fgets(buf, 100, fp);
    fgets(buf, 100, fp);
    fgets(buf, 100, fp);
    fgets(buf, 100, fp);

    n_colors = 0;
    for (i = 0; i < 255; i++) {
        /* read numbers */
        fscanf(fp, "%d %d %d", &rgb[0], &rgb[1], &rgb[2]);

        /* Set colors */
        colors[i].r = rgb[0];
        colors[i].g = rgb[1];
        colors[i].b = rgb[2];

        //printf("%d,%d,%d\n", rgb[0], rgb[1], rgb[2]);

        /* goto next line... */
        fgets(buf, 100, fp);

        n_colors++;

        if (feof(fp))
            break;
    }

    fclose(fp);
}

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "colors.h"

static int load_gimp_palette(char *file);

void init_colors()
{
    /* Load GIMP palette */
    load_gimp_palette("data/palette2.gpl");

    /* Set palette */
    SDL_SetColors(screen, colors, 0, n_colors);
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

        printf("%d,%d,%d\n", rgb[0], rgb[1], rgb[2]);

        /* goto next line... */
        fgets(buf, 100, fp);

        n_colors++;

        if (feof(fp))
            break;
    }

    fclose(fp);
}

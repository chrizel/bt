#include <SDL.h>
#include <string.h>

#include "bt.h"
#include "filter.h"
#include "console.h"
#include "colors.h"

#define DNUM 50
#define DARKER(value) ((value - DNUM) < 0 ? 0 : value - DNUM)

static void night_filter()
{
    int i;

    printf("n_colors = %d\n", n_colors);
    for (i = 0; i < n_colors; i++) {
        /* Decrease color with DNUM... */
        colors[i].r = DARKER(orig_colors[i].r);  
        colors[i].g = DARKER(orig_colors[i].g);  
        colors[i].b = DARKER(orig_colors[i].b);  
    }

    /* Set palette... */
    SDL_SetColors(screen, colors, 0, n_colors);

    cur_filter = NULL;
}

static void day_filter()
{
    int i;

    for (i = 0; i < n_colors; i++) {
        /* Decrease color with DNUM... */
        colors[i].r = orig_colors[i].r;  
        colors[i].g = orig_colors[i].g;  
        colors[i].b = orig_colors[i].b;  
    }

    /* Set palette... */
    SDL_SetColors(screen, colors, 0, n_colors);

    cur_filter = NULL;
}

void con_switch_filter()
{
    if (!con_last_param)
        return;

    if (strcmp(con_last_param, "night") == 0) {
        cur_filter = night_filter;
        CON_Out(btConsole, "cur_filter = night");
    } else if (strcmp(con_last_param, "day") == 0) {
        cur_filter = day_filter;
        CON_Out(btConsole, "cur_filter = day");
    } else {
        cur_filter = NULL;
        CON_Out(btConsole, "cur_filter = NULL");
    }
}

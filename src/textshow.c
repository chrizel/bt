#include "rotozoom/SDL_rotozoom.h"
#include "event.h"
#include "bt.h"

SDL_Surface *background;

static void textshow_paint()
{
    SDL_BlitSurface(background, NULL, screen, NULL);
}

int init_textshow()
{
    reg_func(textshow_paint, EH_PAINT);
    background = bmpl_get("font.bg.test");
    if(background == NULL)
        printf("Warning: Failed to load image\n");
    //background = zoomSurface(background, 
    //        (double)screen->w/640.0, (double)screen->w/640.0, 0);
}

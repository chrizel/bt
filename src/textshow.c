#include "rotozoom/SDL_rotozoom.h"
#include "sdl_events.h"
#include "bt.h"

SDL_Surface *background;

static void textshow_paint()
{
    /* Nononono... we won't blit this :-D
       SDL_BlitSurface(background, NULL, screen, NULL); */
}

int init_textshow()
{
    evl_reg(sdl_evl, EV_SDL_PAINT, textshow_paint);

    background = (SDL_Surface *) bmpl_get("font.bg.test");
    if(background == NULL)
        printf("Warning: Failed to load image\n");
    //background = zoomSurface(background, 
    //        (double)screen->w/640.0, (double)screen->w/640.0, 0);
}

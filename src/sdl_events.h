#ifndef SDL_EVENTS_H
#define SDL_EVENTS_H

#include <SDL.h>
#include "event.h"

t_evl *evl_sdl;
SDL_Event *sdl_ev;

/* event hooks */
enum {
    EV_SDL_IDLE,
    EV_SDL_PAINT,
    EV_SDL_KEYDOWN,
    EV_SDL_KEYUP,
    EV_SDL_JOYBUTTONDOWN,
    EV_SDL_JOYBUTTONUP,
    EV_SDL_JOYAXIS,

    EV_SDL_LAST, /* has to be the last! */
};

void init_sdl_events(void);
void sdl_event_loop(void);

#endif

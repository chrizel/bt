#include <SDL.h>
#include <SDL_ttf.h>

#include "bt.h"
#include "alloc.h"
#include "event.h"
#include "sdl_events.h"

void init_sdl_events(void)
{
    sdl_ev  = MALLOC(SDL_Event);
    evl_sdl = evl_new(EV_SDL_LAST);
}

void sdl_event_loop(void)
{
    // Handle fps
    int done = 0;
    Uint32 ticks = SDL_GetTicks();

    while (!done) {
        while(SDL_GetTicks() <= ticks)
            ;
        ticks = SDL_GetTicks() + (1000 / FPS);

        while (SDL_PollEvent(sdl_ev)) {

            if (CON_isVisible(btConsole)) {
                if (!CON_Events(sdl_ev))
                    continue;
            } else {
                /* call event hooks... */
                switch(sdl_ev->type) {
                case SDL_KEYDOWN: 
                    if (sdl_ev->key.keysym.sym == SDLK_F1) {
                        if (!CON_isVisible(btConsole))
                            CON_Show(btConsole);
                        break;
                    }

                    evl_call(evl_sdl, EV_SDL_KEYDOWN);
                    break;
                case SDL_KEYUP:
                    evl_call(evl_sdl, EV_SDL_KEYUP);
                    break;
                case SDL_JOYBUTTONDOWN:
                    evl_call(evl_sdl, EV_SDL_JOYBUTTONDOWN);
                    break;
                case SDL_JOYBUTTONUP:
                    evl_call(evl_sdl, EV_SDL_JOYBUTTONUP);
                    break;
                case SDL_JOYAXISMOTION:
                    evl_call(evl_sdl, EV_SDL_JOYAXIS);
                    break;
                }
            }
        }

        evl_call(evl_sdl, EV_SDL_IDLE);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        evl_call(evl_sdl, EV_SDL_PAINT);
        CON_DrawConsole(btConsole);
        
        SDL_Flip(screen);
    }
}


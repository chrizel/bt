#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <SDL.h>

#include "bt.h"
#include "error.h"
#include "event.h"
#include "rotozoom/SDL_rotozoom.h"
#include "m_math.h"
#include "colors.h"
#include "textshow.h"
#include "input.h"
#include "filter.h"


static void init_sdl(void);
static void keydown();
static void quit();

int main(int argc, char *argv[])
{
    cur_filter = NULL;
    con_last_param = NULL;

    init_sdl();
    init_colors();
    init_sdl_events();

    init_console();
    init_map();
    init_textshow();
    init_input();

    evl_reg(evl_sdl, EV_SDL_KEYDOWN, keydown);

    /* start main loop */
    sdl_event_loop();

    CON_Destroy(btConsole);

    return 0;
}

static void keydown()
{
    if (sdl_ev->key.keysym.sym == SDLK_ESCAPE)
        bt_exit();
}

static void quit()
{
    bt_exit();
}

void bt_exit()
{
    /* TODO: cleanup all surfaces, etc. */
    printf("Ende :)\n");
    exit(0);
}

static void init_sdl(void)
{
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error("Couldn't initialize SDL: %s", SDL_GetError());

    /* Initialize SDL_TIMER */
    if (SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
        error("Couldn't initialize SDL: %s", SDL_GetError());

    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
      error("Couldn't initialize support of joystick in SDL: %s", 
	    SDL_GetError());

    /* Clean up on exit */
    atexit(SDL_Quit);

    /* VideoMode... */
    screen = SDL_SetVideoMode(800, 600, 8, SDL_DOUBLEBUF | SDL_HWPALETTE);
    if (!screen)
        error("Couldn't set VideoMode: %s", SDL_GetError());

    if ((screen->flags & SDL_HWSURFACE))
        printf("* Using Hardware Surface\n");
    else
        printf("* Using Software Surface\n");

    SDL_WM_SetCaption( "Bermuda Triangle", NULL);
}



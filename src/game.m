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

#include <SDL.h>
#include <stdlib.h>

#include "game.h"
#include "bt.h"
#include "sdl_events.h"
#include "error.h"
#include "console.h"
/*
#include "editor.h"
*/
#include "player.h"
#include "audio.h"

@implementation Game

static Uint32 blink_anim_timer(Uint32 interval, void *param)
{
    if ([(id)param switchBlink])
	return 200;
    else
	return 5000;
}

+ (id)newWithTitle:(char *)t
{
    return [[super new] initWithTitle:t];
}

- (id)initWithTitle:(char *)t
{
    title = t;
    [self initSDL];
  
#ifdef USE_8BIT
    init_colors();
#endif

    printf("make map...\n");
    map = [Map newWithFile:"main.map"];
    //editor = [Editor new];
    console = [Console new];
    player = [Player new];

    printf("make audio...\n");
    audio = [Audio new];

    printf("addMusic...\n");
    music = [audio addMusic:"data/penguinplanet.ogg"];

    printf("addChunk...\n");
    chunk = [audio addChunk:"data/sound.wav"];

    printf("play music...\n");
    [audio playMusic:music];

    return self;
}

/*
Game::~Game()
{
    delete player;
    delete console;
    delete map;
    delete audio;
}
*/

- initSDL
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
    screen = SDL_SetVideoMode(800, 600, BPP, SDL_DOUBLEBUF | SDL_HWPALETTE);

    if (!screen)
        error("Couldn't set VideoMode: %s", SDL_GetError());

    if ((screen->flags & SDL_HWSURFACE))
        printf("> Using hardware surface\n");
    else
        printf("> Using software surface\n");

    SDL_WM_SetCaption(title, NULL);
}

- run
{
    printf("inside run\n");

    // Handle fps
    int done = 0;
    Uint32 ticks = SDL_GetTicks();
    SDL_Rect ml_rect;

    static SDL_Event ev;
    sdl_ev = &ev;

    ml_rect.x = 800 - 100;
    ml_rect.y = 600 - 60;
    
    whole_redraw = 1;

    SDL_AddTimer(2500, blink_anim_timer, (void *)player);

#ifdef DO_FRAMETEST
    ticks_begin = SDL_GetTicks();
    ticks_end = ticks_begin;
#endif

    printf("before while...\n");
    while (!done) {
	ur_count = 0;
#ifdef DO_FRAMETEST
	frames++;
	ticks_end = SDL_GetTicks();
	if ( (ticks_end - ticks_begin) >= 4000) 
	    fps_output();
#endif
	
        while(SDL_GetTicks() <= ticks)
            ;
        ticks = SDL_GetTicks() + (1000 / FPS);

	//printf("before PollEvent...\n");
        while (SDL_PollEvent(sdl_ev)) {
	    //printf("inside PollEvent\n");

	    if ([console isVisible]) {
		[console onEvent:sdl_ev];
            } else {
                /* call event hooks... */
	        switch(sdl_ev->type) {
                case SDL_KEYDOWN: 
                    if (sdl_ev->key.keysym.sym == SDLK_c) {
			if (![console isVisible])
			    [console show];
			  
                        break;
                    } else if (sdl_ev->key.keysym.sym == SDLK_q) {
			//std::cout << "Bye :)" << std::endl;
			exit(0);
		    } else if (sdl_ev->key.keysym.sym == SDLK_s) {
			[audio playChunk:chunk];
		    }
                    break;
                case SDL_KEYUP:
                    // evl_call(evl_sdl, EV_SDL_KEYUP);
                    break;
		case SDL_JOYBUTTONDOWN:
                    // evl_call(evl_sdl, EV_SDL_JOYBUTTONDOWN);
                    break;
                case SDL_JOYBUTTONUP:
                    // evl_call(evl_sdl, EV_SDL_JOYBUTTONUP);
                    break;
                case SDL_JOYAXISMOTION:
                    // evl_call(evl_sdl, EV_SDL_JOYAXIS);
                    break;
                }
	    }
	}

	/*
	  {
	  Uint8 *keystate = SDL_GetKeyState(NULL);
	  if (keystate[SDLK_UP])
	  player.pos.y -= 10;
	  else if (keystate[SDLK_DOWN])
	  player.pos.y += 10;

	  if (keystate[SDLK_LEFT])
	  player.pos.x -= 10;
	  else if (keystate[SDLK_RIGHT])
	  player.pos.x += 10;
	  }
	*/

        //map->onIdle();
	//printf("Map onIdle\n");
	[map onIdle];
	//editor->onIdle();
        
	//printf("Map onDraw\n");
	[map onDraw:screen];
	[player onDraw:screen];
	//[editor onDraw:screen];
	[console draw];

        /* Execute surface filter... */
        // if (cur_filter)
	// cur_filter();

	//printf("BlitSurface\n");
	SDL_BlitSurface(minilogo, NULL, screen, &ml_rect);

        //bt->getConsole()->draw();
        
	//printf("whole_redraw\n");
	if (whole_redraw || [console isVisible]) {
	    // printf("whole_redraw\n");
	    SDL_Flip(screen);
	    whole_redraw = 0;
	} else {
	    if (ur_count) {
		// printf("update_rects: %d\n", ur_count);
		SDL_UpdateRects(screen, ur_count, update_rects);
	    }
	}
    }
}

- eventLoop
{
}

- printGPL
{
    static char GPL_TEXT[] =  
	"Bermuda Triangle, Copyright (C) 2004 Christian Zeller and Simon Goller\n"
	"Bermuda Triangle comes with ABSOLUTELY NO WARRANTY. This is free software,\n" 
	"and you are welcome to redistribute it under certain conditions; see\n"
	"LICENSE file for details.\n\n";

    puts(GPL_TEXT);

}

- print:(char *)t
{
    [self printLine:t];
}

- printLine:(char *)t
{
    // stdout...
    puts(t);

    // and console
    [console printLine:t];
}

- (id)getConsole
{
    //return console;
}

- (id)getMap
{
    return map;
}

- (id)getPlayer
{
    //return player;
}

@end

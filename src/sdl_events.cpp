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
#include <SDL_ttf.h>

#include "bt.h"
#include "alloc.h"
#include "event.h"
#include "sdl_events.h"
#include "filter.h"
#include "map.h"
#include "game.h"

t_evl *evl_sdl;
SDL_Event *sdl_ev;

SDL_Rect update_rects[MAX_RECTS];
int ur_count;
int whole_redraw;

Map *tmp_map;

SDL_Rect wider_rect(SDL_Rect *rect, int border)
{
    static SDL_Rect wrect;
    
    //printf("%d,%d,%d,%d\n", rect->x, rect->y, rect->w, rect->h);

    wrect.x = rect->x - border;
    wrect.y = rect->y - border;
    wrect.w = rect->w + border * 2;
    wrect.h = rect->h + border * 2;

    return wrect;
}

static Uint32 blink_anim_timer(Uint32 interval, void *param)
{
    player.blink = !player.blink;

    if (player.blink)
	return 200;
    else
	return 5000;
}

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
    SDL_Rect ml_rect;

    ml_rect.x = 800 - 100;
    ml_rect.y = 600 - 60;
    
    whole_redraw = 1;

    SDL_AddTimer(2500, blink_anim_timer, 0);

#ifdef DO_FRAMETEST
    ticks_begin = SDL_GetTicks();
    ticks_end = ticks_begin;
#endif

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

        while (SDL_PollEvent(sdl_ev)) {

	  if (bt->getConsole()->isVisible()) {
                /*
                if (!CON_Events(sdl_ev))
                    continue;
                    */
	    bt->getConsole()->onEvent(sdl_ev);
            } else {
                /* call event hooks... */
                switch(sdl_ev->type) {
                case SDL_KEYDOWN: 
                    if (sdl_ev->key.keysym.sym == SDLK_c) {
		      if (!bt->getConsole()->isVisible())
			bt->getConsole()->show();
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

        tmp_map->onIdle();
        evl_call(evl_sdl, EV_SDL_IDLE);

        //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        tmp_map->onDraw(screen);
        evl_call(evl_sdl, EV_SDL_PAINT);

        /* Execute surface filter... */
        // if (cur_filter)
	// cur_filter();

	if (player.blink)
	    player.cur_shape.x = 80;
	else
	    player.cur_shape.x = 0;

	SDL_BlitSurface(player.sfc, &player.cur_shape, screen, &player.pos);
	PUSH_UR(wider_rect(&player.pos, 10));

	SDL_BlitSurface(minilogo, NULL, screen, &ml_rect);

        bt->getConsole()->draw();
        
	if (whole_redraw || bt->getConsole()->isVisible()) {
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


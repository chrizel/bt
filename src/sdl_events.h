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

#ifndef SDL_EVENTS_H
#define SDL_EVENTS_H

#include <SDL.h>
#include "map.h"

extern SDL_Event *sdl_ev;

void init_sdl_events(void);
void sdl_event_loop(void);

#define MAX_RECTS 2048
extern SDL_Rect update_rects[MAX_RECTS];
extern int ur_count;
extern int whole_redraw;

extern Map *tmp_map;

#define INTERCEPT_CHECK(rect) do {		\
	if (rect.x < 0)				\
	    rect.x = 0;				\
	else if (rect.x >= game->getWidth())		\
	    rect.x = game->getWidth();			\
	if (rect.y < 0)				\
	    rect.y = 0;				\
	else if (rect.y >= game->getHeight())		\
	    rect.y = game->getHeight();			\
	if ((rect.x + rect.w) >= game->getWidth())	\
	    rect.w = game->getWidth() - rect.x;		\
	if ((rect.y + rect.h) >= game->getHeight())	\
	    rect.h = game->getHeight() - rect.y;		\
    } while(0);


#define PUSH_UR(rect)					\
	if (!whole_redraw && ur_count < MAX_RECTS) {	\
	    update_rects[ur_count] = rect;		\
	    INTERCEPT_CHECK(update_rects[ur_count]);	\
	    ur_count++;					\
	} else {					\
	    whole_redraw = 1;				\
	}


#endif

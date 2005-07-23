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
#include <iostream>

#include "game.h"
#include "window.h"
#include "bmpl.h"
#include "sdl_events.h"

Window::Window()
{
    sfc = bmpl_get("window");
    rect.x = rect.y = 10;
    rect.w = rect.h = 200;
}

Window::~Window()
{
}

void Window::draw()
{
    /*
    SDL_Rect src, dst;

    // draw top left
    src.x = src.y = 0;
    dst.x = rect.x;
    dst.y = rect.y;
    dst.w = src.w = 25;
    dst.h = src.h = 20;
    SDL_BlitSurface( sfc, &src, screen, &dst );

    // draw top line
    src.x = 25;
    src.y = 0;
    dst.x = rect.x + 25;
    dst.y = rect.y;
    dst.w = src.w = 1;
    dst.h = src.h = 20;
    for (int i = 25; i < (rect.w - 10); i++) {
        SDL_Rect tmp = dst;
        SDL_BlitSurface( sfc, &src, screen, &tmp );
        dst.x++;
    }

    // draw top right
    src.x = 90;
    src.y = 0;
    dst.x = rect.w - 10;
    dst.y = rect.y;
    dst.w = src.w = 10;
    dst.h = src.h = 20;
    SDL_BlitSurface( sfc, &src, screen, &dst );

    // draw left
    src.x = 0;
    src.y = 20;
    dst.x = rect.x;
    dst.y = rect.y + 20;
    dst.w = src.w = 5;
    dst.h = src.h = 1;
    for (int i = 20; i < (rect.h - 5); i++) {
        SDL_Rect tmp = dst;
        SDL_BlitSurface( sfc, &src, screen, &tmp );
        dst.y++;        
    }

    // draw middle...
    src.x = 5;
    src.y = 20;
    dst.y = rect.y + 20;
    dst.w = src.w = 1;
    dst.h = src.h = 1;
    for (int y = 20; y < (rect.h - 5); y++) {
        dst.x = rect.x + 5;
        for (int x = 5; x < (rect.w - 5); x++) {
            SDL_Rect tmp = dst;
            SDL_BlitSurface( sfc, &src, screen, &tmp );
            dst.x++;
        }
        dst.y++;
    }

    PUSH_UR(rect);
*/
}

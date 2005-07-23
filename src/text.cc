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

#include <string.h>

#include "game.h"
#include "error.h"
#include "sdl_events.h"
#include "text.h"

Text::Text(char *aFontFile, int aSize, SDL_Color aColor)
{
    fontfile = aFontFile;
    size = aSize;
    color = aColor;
    charmap = 0;
    shadows = 0;

    bakeCharmap();
}

Text::~Text()
{
}

void Text::bakeCharmap()
{
    Uint32 rmask, gmask, bmask, amask;

    // Load font
    TTF_Font *font = TTF_OpenFont(fontfile, size);
    if (!font)
        error("TTF_OpenFont: %s", TTF_GetError());

    // Make space for our charmap...
    charmap = new SDL_Surface*[256];
    shadows = new SDL_Surface*[256];
    for (int i = 0; i < 256; i++) {
        char buffer[2];
        buffer[0] = (unsigned char)i;
        buffer[1] = '\0';

        charmap[i] = TTF_RenderText_Blended(font, buffer, color);
        SDL_Color scolor = {0, 0, 0};
        shadows[i] = TTF_RenderText_Blended(font, buffer, scolor);
        /*
        // Calculate rendered character size...
        int w, h;
        TTF_SizeText(font, buffer, &w, &h);

        w += 1;
        h += 1;

        // Create our char surface for rendering...
        charmap[i] = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, w, h, 
                                          screen->format->BitsPerPixel,
                                          screen->format->Rmask, 
                                          screen->format->Gmask,
                                          screen->format->Bmask,
                                          screen->format->Amask);
        //charmap[i] = SDL_DisplayFormatAlpha(charmap[i]);

        // fill it transparent
        SDL_Rect fillrect = {0, 0, w, h};
        SDL_FillRect(charmap[i], &fillrect, SDL_MapRGBA(charmap[i]->format, 255, 255, 255, 0));

        // Blit background font
        SDL_Color bgcolor = {0, 0, 0, 0};
        SDL_Rect dstrect = {1, 1, 0, 0};
        SDL_Surface *background = TTF_RenderText_Blended(font, buffer, bgcolor);
        SDL_BlitSurface(background, NULL, charmap[i], &dstrect);

        // Blit foreground font
        SDL_Surface *foreground = TTF_RenderText_Blended(font, buffer, color);
        SDL_BlitSurface(foreground, NULL, charmap[i], NULL);

        */
    }
}

int Text::drawChar(char aChar, int x, int y)
{
    SDL_Rect dstrect = {x, y, 0, 0};
    SDL_Rect shdwrect = {x + 1, y + 1, 0, 0};

    SDL_Surface *sfc = charmap[aChar];
    SDL_Surface *shdw = shadows[aChar];

    SDL_BlitSurface(shdw, NULL, screen, &shdwrect);
    SDL_BlitSurface(sfc, NULL, screen, &dstrect);

    return sfc->w;
}

int Text::drawString(char *aString, int x, int y)
{
    int pos = x;
    for (int i = 0; i < strlen( aString ); i++) {
        pos = pos + drawChar( aString[i], pos, y );
    }
    SDL_Rect arect = {x, y, pos - x, y + size};
    PUSH_UR(arect);
}

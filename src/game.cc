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
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <stdarg.h>

#include "game.h"
#include "sdl_events.h"
#include "error.h"
#include "player.h"
#include "bmpl.h"
#include "editor.h"
#include "window.h"
#include "text.h"

Game *game;

SDL_Surface *screen;

int frames;
int ticks_begin, ticks_end;

static void btQuit()
{
    game->print("Bye...");
    delete game;
}

Game::Game(char *aTitle)
{
    width = DEFAULT_SCREEN_W;
    height = DEFAULT_SCREEN_H;
    xOffset = 0;
    yOffset = 0;
    title = aTitle;
    fpsstr = new char[20];
    fpsstr[0] = '\0';

    initSDL();

    print("init game...");

    map = new Map("main.map");
    editor = new Editor();
    window = new Window();

    SDL_Color color = {255, 255, 255};
    bigtext = new Text("data/font/Vera.ttf", 30, color);
    text = new Text("data/font/Vera.ttf", 20, color);
    systext = new Text("data/font/Vera.ttf", 12, color);

    SDL_Color blue = {0, 0, 255};
    bluetext = new Text("data/font/Vera.ttf", 20, blue);

    ppos.x = 400;
    ppos.y = 300;
    ppos.w = 48;
    ppos.h = 92;
    player = new Player("player.player1", &ppos);

    bubble = bmpl_get("bubble");
}

Game::~Game()
{
    map->save("main.map");

    delete player;
    delete editor;
    delete window;
    delete map;
    delete text;
    delete bigtext;
    delete bluetext;
    delete systext;
    delete fpsstr;
}

void Game::initSDL()
{
    print("init sdl...");

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error("Couldn't initialize SDL: %s", SDL_GetError());

    /* Initialize SDL_TIMER */
    if (SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
        error("Couldn't initialize SDL: %s", SDL_GetError());

    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
        error("Couldn't initialize support of joystick in SDL: %s", 
              SDL_GetError());

    if (TTF_Init() == -1)
        error("TTF_Init: %s", TTF_GetError());

    /* Clean up on exit */
    atexit(SDL_Quit);

    /* VideoMode... */
    screen = SDL_SetVideoMode(width, height, BPP, SDL_DOUBLEBUF | SDL_RESIZABLE);

    if (!screen)
        error("Couldn't set VideoMode: %s", SDL_GetError());

    if ((screen->flags & SDL_HWSURFACE))
        print("Using hardware surface");
    else
        print("Using software surface");

    SDL_WM_SetCaption(title, NULL);

    // register quit function for cleanup
    atexit(btQuit);
}

void Game::run()
{
    // Handle fps
    int done = 0;
    Uint32 ticks = SDL_GetTicks();
    SDL_Rect ml_rect;

    static SDL_Event ev;
    sdl_ev = &ev;

    ml_rect.x = 800 - 100;
    ml_rect.y = 600 - 60;
    
    whole_redraw = 1;

    ticks_begin = SDL_GetTicks();
    ticks_end = ticks_begin;

    while (!done) {
	ur_count = 0;

	frames++;
	ticks_end = SDL_GetTicks();
	if ( (ticks_end - ticks_begin) >= 1000) 
	    fpsOutput();
	
        while(SDL_GetTicks() <= ticks)
            ;
        ticks = SDL_GetTicks() + (1000 / MAX_FPS);

        while (SDL_PollEvent(sdl_ev)) {

            switch(sdl_ev->type) {
            case SDL_KEYDOWN: 
                if (sdl_ev->key.keysym.sym == SDLK_c) {
                    break;
                } else if (sdl_ev->key.keysym.sym == SDLK_q) {
                    //std::cout << "Bye :)" << std::endl;
                    exit(0);
                } else if (sdl_ev->key.keysym.sym == SDLK_KP_PLUS) {
                    editor->incPen(1);
                } else if (sdl_ev->key.keysym.sym == SDLK_KP_MINUS) {
                    editor->decPen(1);
                } else if (sdl_ev->key.keysym.sym == SDLK_KP_MULTIPLY) {
                    editor->incPen(40);
                } else if (sdl_ev->key.keysym.sym == SDLK_KP_DIVIDE) {
                    editor->decPen(40);
                }
                    
                break;
            case SDL_VIDEORESIZE:
                width = sdl_ev->resize.w;
                height = sdl_ev->resize.h;
                print("Resize: %d, %d", width, height);

                screen = SDL_SetVideoMode(width, height, BPP, SDL_DOUBLEBUF | SDL_RESIZABLE);
                whole_redraw = 1;
                break;
            }
	}

        //map->onIdle();
        map->onIdle();
        player->onIdle();
        editor->onIdle();
        
	//print("Map onDraw");
	//[map draw:screen xOffset:xOffset yOffset:yOffset];
        map->onDraw(screen);
        editor->onDraw(screen);
        player->draw(screen, xOffset, yOffset);
        window->draw();

        /* Execute surface filter... */
        // if (cur_filter)
	// cur_filter();

	//print("BlitSurface");
	//SDL_BlitSurface(minilogo, NULL, screen, &ml_rect);
        SDL_Rect dstrect = {175, 180, 0, 0};
        //SDL_BlitSurface(bubble, NULL, screen, &dstrect);

        //text->drawChar('B', 100, 100);
        bigtext->drawString("Bermuda Triangle", 10, 10);
        text->drawString("The Future Depends On You", 10, 45);
        //text->drawString("I wish you what!", 10, 40);

        bluetext->drawString("^^ Blau oh blaudiblau blau blau -.-", 200, 200);

        text->drawString("Das ist ein Test: !@#$!(*()_@(%?><}|{)_)(l;,..", 10, 550);

        systext->drawString(fpsstr, 10, 80);

	//print("whole_redraw");
	if (whole_redraw) {
	  // print("whole_redraw");
	  SDL_Flip(screen);
	  whole_redraw = 0;
	} else {
	    if (ur_count) {
		// print("update_rects: %d\n", ur_count);
		SDL_UpdateRects(screen, ur_count, update_rects);
	    }
	}
    }
}

void Game::fpsOutput()
{
    ticks_end = SDL_GetTicks();
    print("FPS: %i", (1000 * frames) / (ticks_end - ticks_begin));
    sprintf(fpsstr, "FPS: %i", (1000 * frames) / (ticks_end - ticks_begin));
    ticks_begin = SDL_GetTicks();
    frames = 0;
}

void Game::printGPL()
{
    static char GPL_TEXT[] =  
	"Bermuda Triangle, Copyright (C) 2005 Christian Zeller and Simon Goller\n"
	"Bermuda Triangle comes with ABSOLUTELY NO WARRANTY. This is free software,\n" 
	"and you are welcome to redistribute it under certain conditions; see\n"
	"LICENSE file for details.\n\n";

    puts(GPL_TEXT);

}

void Game::print(char *text, ...)
{
    va_list args;

    va_start(args, text);
    vfprintf(stdout, text, args);
    fprintf(stdout, "\n");

    va_end(args);
}

Map* Game::getMap()
{
    return map;
}

Player* Game::getPlayer()
{
    return player;
}

int Game::getWidth()
{
    return width;
}

int Game::getHeight()
{
    return height;
}

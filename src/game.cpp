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

#include <iostream>

#include "game.h"
#include "bt.h"
#include "sdl_events.h"
#include "error.h"
#include "console.h"
#include "player.h"

Game::Game(char *title)
{ 
    this->title = title;
    this->initSDL();

    #ifdef USE_8BIT
    init_colors();
    #endif

    map = new Map("main.map");
    console = new Console();
    player = new Player();

    tmp_map = map;
}

Game::~Game()
{
    delete player;
    delete console;
    delete map;
}

void Game::initSDL()
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

    SDL_WM_SetCaption(this->title, NULL);
}

void Game::run()
{
    sdl_event_loop();
}

void Game::eventLoop()
{
}

void Game::printGPL()
{
    std::cout << GPL_TEXT;
}

void Game::print(char *text)
{
    console->print(text);
}

Console *Game::getConsole()
{
    return console;
}

Map *Game::getMap()
{
    return map;
}

Player *Game::getPlayer()
{
    return player;
}

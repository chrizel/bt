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

#ifndef GAME_H
#define GAME_H 

#include <SDL.h>

class Player;
class Console;
class Editor;
class Map;
class Audio;

class Game
{
private:
    char *title;

    Map *map;
    Console *console;
    Player *player;
    Editor *editor;
    Audio *audio;

    int music;
    int chunk;

    SDL_Rect ppos;

    Uint32 xOffset;
    Uint32 yOffset;

    int width;
    int height;

public:
    Game(char *aTitle);
    virtual ~Game();

    void initSDL();
    void eventLoop();
    void printGPL();

    void run();

    void print(char *aText);
    void printLine(char *aText);

    int getWidth();
    int getHeight();

    Console* getConsole();
    Map* getMap();
    Player* getPlayer();
};

#endif

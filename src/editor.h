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

#ifndef EDITOR_H
#define EDITOR_H

#include "eventhandler.h"

class Map;

class Editor : public EventHandler {
private:
    int mode;
    int pen;
    int *pg;
    int pg_y;
    int pg_x;
    Map *map;

public:
    Editor(Map *aMap);
    virtual ~Editor();

    /* Attribute access routines */
    bool getMode();
    bool setMode(bool value);

    int getPen();
    int setPen(int value);

    int setTile(int id, int x, int y);

    void saveMap(char *file);
    void openMap(char *file);
    void newMap(Uint32 width, Uint32 height, Uint32 anim_count, Uint32 anim_ticks);

    /* Event handling */
    void onEvent(SDL_Event *event);
    void onDraw(SDL_Surface *sfc);
    void onIdle();

    static void writeInt(FILE *fp, Uint32 num);
    static Uint32 readInt(FILE *fp);
};

#endif

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

class Editor
{
private:
    bool active;

    int pen;
    int *pg;
    int pg_y;
    int pg_x;
public:
    Editor();
    virtual ~Editor();

    bool isActive();
    void setActive(bool value);

    int getPen();
    int setPen(int value);

    void setTID(int tid, int x, int y);

    void onEvent(SDL_Event *event);
    void onDraw(SDL_Surface *sfc);
    void onIdle();

    void saveMap(char *file);
    void openMap(char *file);

    void updateGUI();
};

#endif

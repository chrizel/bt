/* Bermuda Triangle - action adventure game
   Copyright (C) 2004 Simon Goller <ladldadl@yahoo.de>

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

#include <stdio.h>
#include "joystick.h"

SDL_Joystick **joysticks;

void init_joystick()
{
    int joynum, i;

    // Loading all joysticks
    joynum = SDL_NumJoysticks();
    if (joynum == 0)
        printf("No joysticks found.\n");
    else
        printf("%i joysticks found:\n", joynum);

    joysticks = (SDL_Joystick **)malloc(sizeof(SDL_Joystick *) * joynum);

    for (i = 0; i < joynum; i++) {
        printf("%i. %s\n", i, SDL_JoystickName(i));
        joysticks[i] = SDL_JoystickOpen(i);
        printf("    Number of Axes: %i\n", 
           SDL_JoystickNumAxes(joysticks[i]));
        printf("    Number of Buttons: %i\n", 
           SDL_JoystickNumButtons(joysticks[i]));
    }
}

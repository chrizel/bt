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

#include <stdio.h>
#include <string.h>

#include "bt.h"
#include "console.h"
#include "filter.h"
#include "error.h"

static void CommandHandler(ConsoleInformation *console, char *command);

Console::Console()
{
    SDL_Rect conRect;

    printf("+++ init console\n");

    /* setup rect */
    conRect.x = 10;
    conRect.y = 0;
    conRect.w = 780;
    conRect.h = 195;

    /* init console */
    console = CON_Init("data/ConsoleFont.bmp", screen, 200, conRect);

    if (!console)
        error("Can not init console!");

    CON_SetExecuteFunction(console, CommandHandler);
    //CON_Alpha(console, 150);
    CON_SetPrompt(console, ">>> ");
    CON_Topmost(console);
    //CON_Show(console);
}

Console::~Console()
{
    printf("--- free console\n");
    CON_Hide(console);
    CON_Destroy(console);
}

void Console::print(char *str)
{
    CON_Out(console, str);
}

bool Console::isVisible()
{
    return CON_isVisible(console);
}

bool Console::isClosing()
{
    return console->Visible == CON_CLOSING;
}

void Console::onEvent(SDL_Event *event)
{
    CON_Events(event);
}

void Console::show()
{
    CON_Show(console);
}

void Console::hide()
{
    CON_Hide(console);
}

void Console::draw()
{
    CON_DrawConsole(console);
}

static void CommandHandler(ConsoleInformation *console, char *command)
{
}


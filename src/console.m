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
#include "console/SDL_console.h"
#include "filter.h"
#include "error.h"

@implementation Console

typedef struct {
    char *command;
    void (*func)();
} t_command;

t_command commands[] = {
    {"exit", bt_exit},
    //{"editor", bt_editor},
    {"night", con_switch_filter},
    {"day", con_switch_filter},
    /*
    {"pen", bt_pen},
    {"pg", bt_pg},
    {"write", bt_write},
    {"read", bt_load},
    {"load", bt_load},
    {"fill", bt_fill},
    {"put", bt_put},
    {"new", bt_new},
    */
    {NULL, NULL},
};

static id curConsole = NULL;
static void CommandHandler(ConsoleInformation *console, char *command);

+ (id)new
{
    return [[super new] init];
}

- (id)init
{
    SDL_Rect conRect;

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
    CON_SetPrompt(console, "console> ");
    CON_Topmost(console);
    //CON_Show(console);
    
    curConsole = self;
}

/*
Console::~Console()
{
    CON_Hide(this->console);
    CON_Destroy(this->console);
    curConsole = 0;
}
*/

- handleCommand:(char *)command
{
    int i, found = 0;

    if (command[0] == '<') {
	[self readScript:command + 1];
        return;
    }

    lastParam = command;

    for (i = 0; commands[i].command; ++i) {
        if (strncmp(commands[i].command, command, strlen(commands[i].command)) == 0) {
            commands[i].func();
            lastParam = 0;
            found = 1;
        }
    }

    lastParam = 0;

    if (!found)
	[self print:"Command not found"];
}

- readScript:(char *)filename
{
    char buf[512];
    FILE *fp;

    /* "<filename"... we don't need < */
    //file = file + 1;

    fp = fopen(filename, "r");
    if (fp) {

        while (!feof(fp)) {
            fgets(buf, 512, fp);
            printf("%s\n", buf);
	    [self print:buf];
            CommandHandler(console, buf);
        }

        fclose(fp);
    } else {
        [self print:"file not found"];
        return;
    }
}

- (char *)getLastParam
{
    return lastParam;
}

- print:(char *)str
{
    CON_Out(console, str);
}

- (BOOL)isVisible
{
    return CON_isVisible(console);
}

- onEvent:(SDL_Event *)event
{
    CON_Events(event);
}

- show
{
    CON_Show(console);
}

- hide
{
    CON_Hide(console);
}

- draw
{
    CON_DrawConsole(console);
}

static void CommandHandler(ConsoleInformation *console, char *command)
{
    if (curConsole)
	[curConsole handleCommand:command];
}

@end

#include <stdio.h>
#include <string.h>

#include "bt.h"
#include "console.h"
#include "console/SDL_console.h"
#include "filter.h"

typedef struct {
    char *command;
    void (*func)();
} t_command;

t_command commands[] = {
    {"exit", bt_exit},
    {"night", con_switch_filter},
    {"day", con_switch_filter},
    {NULL, NULL},
};

static void CommandHandler(ConsoleInformation *console, char *command);

void init_console()
{
    SDL_Rect conRect;

    /* setup rect */
    conRect.x = 10;
    conRect.y = 0;
    conRect.w = 780;
    conRect.h = 195;

    /* init console */
    btConsole = CON_Init("data/ConsoleFont.bmp", screen, 200, conRect);

    if (!btConsole)
        error("Can not init console!");

    CON_SetExecuteFunction(btConsole, CommandHandler);
    //CON_Alpha(btConsole, 150);
    CON_SetPrompt(btConsole, "console> ");
    CON_Topmost(btConsole);
    //CON_Show(btConsole);
}

static void CommandHandler(ConsoleInformation *console, char *command)
{
    int i;
    con_last_param = command;

    for (i = 0; commands[i].command; ++i) {
        if (strcmp(commands[i].command, command) == 0) {
            commands[i].func();
            con_last_param = NULL;
            return;
        }
    }

    con_last_param = NULL;
    CON_Out(console, "Command not found");
}

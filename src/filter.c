#include <SDL.h>
#include <string.h>

#include "bt.h"
#include "filter.h"
#include "console.h"

static void night_filter()
{
    //TODO: night filter
}

void con_switch_filter()
{
    if (!con_last_param)
        return;

    if (strcmp(con_last_param, "night") == 0) {
        cur_filter = night_filter;
        CON_Out(btConsole, "cur_filter = night");
    } else {
        cur_filter = NULL;
        CON_Out(btConsole, "cur_filter = NULL");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <SDL.h>

#include "bt.h"
#include "error.h"
#include "event.h"
#include "rotozoom/SDL_rotozoom.h"
#include "m_math.h"
#include "colors.h"
#include "textshow.h"
#include "input.h"
#include "filter.h"
#include "map.h"


static void init_sdl(void);
static void keydown();
static void quit();

int main(int argc, char *argv[])
{
    editor_mode = 1;
    editor_pen = 0;
    editor_pg = NULL;
    cur_filter = NULL;
    con_last_param = NULL;

    init_sdl();
    init_colors();
    init_sdl_events();

    init_console();
    init_map();
    init_textshow();
    init_input();

    evl_reg(evl_sdl, EV_SDL_KEYDOWN, keydown);

    /* start main loop */
    sdl_event_loop();

    CON_Destroy(btConsole);

    return 0;
}

static void keydown()
{
    /*
    if (sdl_ev->key.keysym.sym == SDLK_ESCAPE)
        bt_exit();
        */
}

static void quit()
{
    bt_exit();
}

void bt_exit()
{
    /* TODO: cleanup all surfaces, etc. */
    printf("Ende :)\n");
    exit(0);
}

static void init_sdl(void)
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
    screen = SDL_SetVideoMode(800, 600, 8, SDL_DOUBLEBUF | SDL_HWPALETTE);
    if (!screen)
        error("Couldn't set VideoMode: %s", SDL_GetError());

    if ((screen->flags & SDL_HWSURFACE))
        printf("* Using Hardware Surface\n");
    else
        printf("* Using Software Surface\n");

    SDL_WM_SetCaption( "Bermuda Triangle", NULL);
}

/*
Yes, that sprintf stuff is all very quick and dirty, but we will change this in future...
*/
void bt_editor(void)
{
    char buf[100];

    editor_mode = !editor_mode;
    sprintf(buf, "editor_mode = %d", editor_mode);

    CON_Out(btConsole, buf);
}

void bt_pen(void)
{
    int buf[100], id;
    sscanf(con_last_param, "%s %d", buf, &id);

    editor_pen = id;
}

void bt_pg(void)
{
    int i, j, len, pos;
    char buf1[100], buf2[100];
    sscanf(con_last_param, "%s %d %[^a-z]", buf1, &editor_pg_size, buf2);

    if (editor_pg)
        FREE(editor_pg);

    editor_pg = MALLOC_ARRAY(int, editor_pg_size * editor_pg_size);

    j = 0;
    pos = 0;
    printf("\nbuf2: %s\n", buf2);
    for (i = 0; (i <= strlen(buf2)) && (pos < editor_pg_size * editor_pg_size); i++) {
        printf("%d: %c\n", i, buf2[i]);
        buf1[j] = buf2[i];

        if ((buf1[j] == ' ') || (i == strlen(buf2))) {
            buf1[j] = '\0';
            printf("New item (%d): %s\n", j, buf1);
            editor_pg[pos] = atoi(buf1);
            pos++;
            j = 0;
        } else
            j++;
    }

    printf("\npg:\t%d\n", editor_pg_size);
    for (i = 0; i < editor_pg_size * editor_pg_size; i++)
        printf("\t%d\n", editor_pg[i]);
}

void bt_write(void)
{
    int buf1[100], buf2[100];
    sscanf(con_last_param, "%s %s", buf1, buf2);

    write_map(buf2);
}

void bt_load(void)
{
    int buf1[100], buf2[100];
    sscanf(con_last_param, "%s %s", buf1, buf2);

    read_map(buf2);
}

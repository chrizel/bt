#ifndef MEGA_H
#define MEGA_H 

#include "console.h"
#include "sdl_events.h"

#define FPS 30

struct _player {
    int x;
    int y;
} player;

SDL_Surface *screen;

int editor_mode;
int editor_pen;
int *editor_pg;
int editor_pg_y;
int editor_pg_x;

void bt_exit();
void bt_pen(void);

void bt_editor();
void bt_pg(void);
void bt_write(void);
void bt_load(void);
void bt_fill(void);

#endif

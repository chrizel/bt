#ifndef MEGA_H
#define MEGA_H 

#include "console.h"

#define FPS 30

struct _player {
    int x;
    int y;
} player;

SDL_Surface *screen;

void bt_exit();

#endif

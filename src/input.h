/* This file handles all input devices like keyboard and joystick */

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "alloc.h"
#include "sdl_events.h"
#include "joystick.h"

#define INP_TYPE int

enum {
    INP_TYPE_KEY,
    INP_TYPE_JOYBUTTON,
    INP_TYPE_JOYAXIS,

    INP_TYPE_FREE,
    INP_TYPE_NULL
};

enum {
    EV_INP_RUN,

    EV_INP_NULL
};

typedef struct _inp_item {
    INP_TYPE type;
    t_func func;
    int arg1, arg2, arg3;
    int pressed;
} inp_item;

extern int i_inputs;
extern inp_item *inputs;

void init_input();
void free_input();
void inp_add_key(int key, t_func func);

inp_item *get_inp_item();

#endif



/* This file handles all input devices like keyboard and joystick */

#include <stdio.h>
#include "input.h"

inp_el *inputs;

static void on_key() 
{
    printf("Keydown\n");
}

static void on_joybutton()
{
    printf("Joybuttondown\n");
}

static void on_joyaxis()
{
    printf("Joyaxischanged\n");
}


void init_input()
{
    init_joystick();

    inputs = MALLOC(inp_el);
    inputs->type = INP_TYPE_FREE;

    evl_reg(sdl_evl, EV_SDL_KEYDOWN, on_key);
    evl_reg(sdl_evl, EV_SDL_JOYBUTTONDOWN, on_joybutton);
    evl_reg(sdl_evl, EV_SDL_JOYAXIS, on_joyaxis);
}

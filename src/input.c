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

/* This file handles all input devices like keyboard and joystick */

#include <stdio.h>
#include "input.h"

inp_item *inputs;
int i_inputs;

static void on_key() 
{
    int i;
    inp_item *pointer = inputs;

    for (i = 0; i < i_inputs; i++) {
      //	if (pointer->type == INP_TYPE_KEY &&
      //	    pointer->arg1 == sdl_ev.key.keysym.sym)
      //	    pointer->pressed = 1;
	pointer++;
    }
}

static void on_up()
{
    printf("UP\n");
}

static void on_joybutton()
{
    printf("Joybuttondown\n");
}

static void on_joyaxis()
{
    printf("Joyaxischanged\n");
}

void inp_run()
{
    int i;
    inp_item *pointer = inputs;

    for (i = 0; i < i_inputs; i++) {
	if (pointer->pressed)
	    pointer->func();
	pointer++;
    }
}

void init_input()
{
    init_joystick();

    inputs = MALLOC(inp_item);
    inputs->type = INP_TYPE_FREE;

    inp_add_key(SDLK_UP, on_up);

    evl_reg(evl_sdl, EV_SDL_KEYDOWN, on_key);
    evl_reg(evl_sdl, EV_SDL_JOYBUTTONDOWN, on_joybutton);
    evl_reg(evl_sdl, EV_SDL_JOYAXIS, on_joyaxis);
    evl_reg(evl_sdl, EV_INP_RUN, inp_run);
}

void free_input()
{
    FREE(inputs);
}

void inp_add_key(int key, t_func func)
{
    inp_item *pointer = get_inp_item();

    pointer->type = INP_TYPE_KEY;
    pointer->func = func;
    pointer->arg1 = key;
    pointer->pressed = 0;
}


inp_item *get_inp_item()
{
    int found = 0;
    inp_item *pointer = inputs;

    while (pointer != NULL) {
	if (pointer->type == INP_TYPE_FREE) {
	    found = 1;
	    break;
	}
	pointer++;
    }

    if (found)
	return pointer;
    else {
	i_inputs++;
	inputs = REALLOC_ARRAY(inp_item, inputs, i_inputs);
	pointer = inputs + i_inputs;
	return pointer;
    }
}
/* This file handles all input devices like keyboard and joystick */

#include <stdio.h>
#include "input.h"

inp_item *inputs;
int i_inputs;

static void on_key() 
{
    int i;
    inp_item *pointer = inputs;

    for (i = 0; i < i_inputs; i++) {
      //	if (pointer->type == INP_TYPE_KEY &&
      //	    pointer->arg1 == sdl_ev.key.keysym.sym)
      //	    pointer->pressed = 1;
	pointer++;
    }
}

static void on_up()
{
    printf("UP\n");
}

static void on_joybutton()
{
    printf("Joybuttondown\n");
}

static void on_joyaxis()
{
    printf("Joyaxischanged\n");
}

void inp_run()
{
    int i;
    inp_item *pointer = inputs;

    for (i = 0; i < i_inputs; i++) {
	if (pointer->pressed)
	    pointer->func();
	pointer++;
    }
}

void init_input()
{
    init_joystick();

    inputs = MALLOC(inp_item);
    inputs->type = INP_TYPE_FREE;

    inp_add_key(SDLK_UP, on_up);

    evl_reg(evl_sdl, EV_SDL_KEYDOWN, on_key);
    evl_reg(evl_sdl, EV_SDL_JOYBUTTONDOWN, on_joybutton);
    evl_reg(evl_sdl, EV_SDL_JOYAXIS, on_joyaxis);
    evl_reg(evl_sdl, EV_INP_RUN, inp_run);
}

void free_input()
{
    FREE(inputs);
}

void inp_add_key(int key, t_func func)
{
    inp_item *pointer = get_inp_item();

    pointer->type = INP_TYPE_KEY;
    pointer->func = func;
    pointer->arg1 = key;
    pointer->pressed = 0;
}


inp_item *get_inp_item()
{
    int found = 0;
    inp_item *pointer = inputs;

    while (pointer != NULL) {
	if (pointer->type == INP_TYPE_FREE) {
	    found = 1;
	    break;
	}
	pointer++;
    }

    if (found)
	return pointer;
    else {
	i_inputs++;
	inputs = REALLOC_ARRAY(inp_item, inputs, i_inputs);
	pointer = inputs + i_inputs;
	return pointer;
    }
}

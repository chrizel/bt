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

typedef struct _inp_el {
  INP_TYPE type;
  void (*func)();
  int arg1, arg2, arg3;
} inp_el;

//extern inp_el *inputs = { { INP_TYPE_NULL, NULL, 0, 0, 0 } };

void init_input();
void inp_add_key(int key, void (*func)());

#endif

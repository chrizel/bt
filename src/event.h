#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>

typedef struct _ev {
    int sdl_event;
    int (*func)(SDL_Event *event);
} ev; 

/* event hooks */
enum {
    EH_IDLE,
    EH_PAINT,
    EH_KEYDOWN,
    EH_KEYUP,
    EH_JOYBUTTONDOWN,
    EH_JOYBUTTONUP,
    EH_JOYAXIS,

    EH_LAST, /* has to be the last! */
};

extern SDL_Event event;


SDL_Event *sdl_ev;
void call_hooks(int eh_type);
void reg_func(void (*eh_func)(), int eh_type);
void init_hooks();

void set_major_el(ev *el); /* set major event list */
void set_minor_el(ev *el); /* set minor event list */
void main_loop(void);

#endif

#include <assert.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "bt.h"
#include "event.h"
#include "error.h"

static ev null_ev[] = {{0, 0}}; 
static ev *major_el = null_ev; /* pointer to major event list */
static ev *minor_el = null_ev; /* pointer to minor event list */

#define EH_BUF 16
static void (**eh_list[EH_LAST])();
static int eh_counts[EH_LAST];

SDL_Event event;

static int disp_el(ev *el, SDL_Event *event)
{
    int i;
    for (i = 0; el[i].sdl_event != 0; ++i)
        if (el[i].sdl_event == event->type) {
            if (el[i].func)
                if(el[i].func(event)) 
                    return 1;
                else
                    return 0;
        }

    return 0;
}

static void disp_ev(SDL_Event *event)
{
    if (!disp_el (minor_el, event)) /* dispatch minor event list first... */
        disp_el (major_el, event);  /* if not succeeded... dispatch major one */
}

void set_major_el(ev *el)
{
    major_el = el ? el : null_ev;
}

void set_minor_el(ev *el)
{
    minor_el = el ? el : null_ev;
}

void main_loop(void)
{
    // Handle fps
    int done = 0;
    Uint32 ticks = SDL_GetTicks();

    while (!done) {
        while(SDL_GetTicks() <= ticks)
            ;
        ticks = SDL_GetTicks() + (1000 / FPS);

        while (SDL_PollEvent(&event)) {

            if (CON_isVisible(btConsole)) {
                if (!CON_Events(&event))
                    continue;
            } else {
                sdl_ev = &event;
                disp_ev(&event);

                /* call event hooks... */
                switch(event.type) {
                case SDL_KEYDOWN: 
                    if (event.key.keysym.sym == SDLK_F1) {
                        if (!CON_isVisible(btConsole))
                            CON_Show(btConsole);
                        break;
                    }

                    call_hooks(EH_KEYDOWN);
                    break;
                case SDL_KEYUP:
                    call_hooks(EH_KEYUP);
                    break;
		case SDL_JOYBUTTONDOWN:
		    call_hooks(EH_JOYBUTTONDOWN);
		    break;
		case SDL_JOYBUTTONUP:
		    call_hooks(EH_JOYBUTTONUP);
		    break;
		case SDL_JOYAXISMOTION:
		    call_hooks(EH_JOYAXIS);
		    break;
                }
            }
        }

        call_hooks(EH_IDLE);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        call_hooks(EH_PAINT);
        CON_DrawConsole(btConsole);
        
        SDL_Flip(screen);
    }
}

void call_hooks(int eh_type)
{
    int i;
    for (i = 0; i < eh_counts[eh_type]; i++)
        eh_list[eh_type][i]();
}

void reg_func(void (*eh_func)(), int eh_type)
{
    eh_counts[eh_type]++;
    eh_list[eh_type][eh_counts[eh_type]-1] = eh_func;
}

void init_hooks()
{
    int i;
    for (i = 0; i < EH_LAST; i++) {
        eh_list[i] = (void (**)())malloc(EH_BUF);
        eh_counts[i] = 0;
    }
}

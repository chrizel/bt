#include <stdio.h>
#include "joystick.h"

SDL_Joystick **joysticks;

void init_joystick()
{
    int joynum, i;

    // Loading all joysticks
    joynum = SDL_NumJoysticks();
    if (joynum == 0)
        printf("No joysticks found.\n");
    else
        printf("%i joysticks found:\n", joynum);

    joysticks = (SDL_Joystick **)malloc(sizeof(SDL_Joystick *) * joynum);

    for (i = 0; i < joynum; i++) {
        printf("%i. %s\n", i, SDL_JoystickName(i));
        joysticks[i] = SDL_JoystickOpen(i);
        printf("    Number of Axes: %i\n", 
           SDL_JoystickNumAxes(joysticks[i]));
        printf("    Number of Buttons: %i\n", 
           SDL_JoystickNumButtons(joysticks[i]));
    }
}

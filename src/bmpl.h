/*
 * bmpl.h - Bitmap Loader
 */
#ifndef BMPL_H
#define BMPL_H

#include <SDL.h>
#include <SDL_image.h>

enum {
    BL_COLORKEY = (1 << 0),
};

typedef struct {
    char *id;
    char *file;
    SDL_Surface *sfc;
    int flags;
} t_bmpl_item;

SDL_Surface *bmpl_get(char *id);

#endif

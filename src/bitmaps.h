#ifndef BITMAPS_H
#define BITMAPS_H

#include "bmpl.h"

t_bmpl_item bmpl_list[] = {
    {"map.stock1", "data/tiles/empty_stock.bmp", NULL, 0},
    {"font.bg.test", "data/Speak/test3.bmp", NULL, BL_COLORKEY},

    {NULL, NULL, NULL, 0}, /* the last entry must be NULL! */
};

#endif

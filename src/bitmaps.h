/* Bermuda Triangle - action adventure game
   Copyright (C) 2004 Christian Zeller <chrizel@gmx.net>

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

#ifndef BITMAPS_H
#define BITMAPS_H

#include "bmpl.h"
#include "game.h"

t_bmpl_item bmpl_list[] = {
    {"map.stock_default", RESOURCE_DIR("data/tiles/stock2.png"), NULL, 0},
    {"map.stock1", RESOURCE_DIR("data/tiles/empty_stock.png"), NULL, 0},
    {"map.stock2", RESOURCE_DIR("data/tiles/stock2.png"), NULL, 0},
    {"font.bg.test", RESOURCE_DIR("data/Speak/test3.png"), NULL, BL_COLORKEY},
    {"main.minilogo", RESOURCE_DIR("data/tiles/minilogo.png"), NULL, BL_COLORKEY | BL_ALPHA_50},
    {"player.player1", RESOURCE_DIR("data/player/player4.png"), NULL, BL_ALPHA_50},
    {"btme.control", RESOURCE_DIR("data/btmecontrol.png"), NULL, 0},
    {"window", RESOURCE_DIR("data/window.png"), NULL, 0},
    {"bubble", RESOURCE_DIR("data/bubble.png"), NULL, 0},

    {NULL, NULL, NULL, 0}, /* the last entry must be NULL! */
};

#endif

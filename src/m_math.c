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

#include "m_math.h"

// sin_table:
//    0,  15,  30,  45,  60,  75,
//   90, 105, 120, 135, 150, 165, 
//  180, 195, 210, 225, 240, 255,
//  270, 285, 300, 315, 330, 245

float sin_table[24] = {
	 0.0,  .2588,  .5,     .7071,  .8660,  .9659,
	 1.0,  .9659,  .8660,  .7071,  .5,     .2588,
	-0.0, -.2588, -.5,    -.7071, -.8660, -.9659,
	-1.0, -.9659, -.8660, -.7071, -.5,    -.2588,};

void move(int angle, float v, int *x, int *y)
{
	*x = m_sin(angle) * -v;
	*y = m_cos(angle) * -v;
}

float m_sin(int x)
{
/*    while(x<0)
        x += 360;
    while(x>=360)
        x -= 360;
    return sin_table[x/15];*/
    return sin((double)x*6.2831/360.0);
}

float m_cos(int x)
{
    /*
    x = 90 - x;
    while(x<0)
        x += 360;
    while(x>=360)
        x -= 360;
    return sin_table[x/15];*/
    return cos((double)x*6.2831/360.0);
}
#include "m_math.h"

// sin_table:
//    0,  15,  30,  45,  60,  75,
//   90, 105, 120, 135, 150, 165, 
//  180, 195, 210, 225, 240, 255,
//  270, 285, 300, 315, 330, 245

float sin_table[24] = {
	 0.0,  .2588,  .5,     .7071,  .8660,  .9659,
	 1.0,  .9659,  .8660,  .7071,  .5,     .2588,
	-0.0, -.2588, -.5,    -.7071, -.8660, -.9659,
	-1.0, -.9659, -.8660, -.7071, -.5,    -.2588,};

void move(int angle, float v, int *x, int *y)
{
	*x = m_sin(angle) * -v;
	*y = m_cos(angle) * -v;
}

float m_sin(int x)
{
/*    while(x<0)
        x += 360;
    while(x>=360)
        x -= 360;
    return sin_table[x/15];*/
    return sin((double)x*6.2831/360.0);
}

float m_cos(int x)
{
    /*
    x = 90 - x;
    while(x<0)
        x += 360;
    while(x>=360)
        x -= 360;
    return sin_table[x/15];*/
    return cos((double)x*6.2831/360.0);
}

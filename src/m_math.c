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

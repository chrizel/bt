#ifndef VORWAERZ_H
#define VORWAERZ_H

extern float sin_table[24];

void move(int angle, float v, int *x, int *y);
float m_sin(int x);
float m_cos(int x);

#endif

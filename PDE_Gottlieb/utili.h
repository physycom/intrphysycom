#ifndef utili_h
#define utili_h

#include <math.h>
#include <stdio.h>
#include <time.h>



double segno( double a);
double minimo( double a, double b);
double minmod( int a, int b, double c);
double un( double a, double b,int g);
double Godunov( double u1m, double u1p );
double uu_x(int i,double u[]);
void sleep( clock_t wait );

#endif  // utili_h


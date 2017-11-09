#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

double t, x, xdot, delta;

//-----------------------------------------------------------
void forze(double x_, double t_) { xdot = x_; }
//-----------------------------------------------------------
void next_Eulero() {
  forze(x, t);
  x = x + xdot * delta;
  t = t + delta;
}
//-----------------------------------------------------------
void next_rk2() {
  double xw;
  forze(x, t);
  xw = x + xdot * delta / 2;
  forze(xw, t + delta / 2);
  x = x + xdot * delta;
  t = t + delta;
}
//-----------------------------------------------------------
void next_rk4() {
  double x1, x2, x3;
  double xdot1, xdot2, xdot3, xdot4;

  forze(x, t);
  xdot1 = xdot;
  x1 = x + xdot1 * delta / 2;
  forze(x1, t + delta / 2);
  xdot2 = xdot;
  x2 = x + xdot2 * delta / 2;
  forze(x2, t + delta / 2);
  xdot3 = xdot;
  x3 = x + xdot3 * delta;
  forze(x3, t + delta);
  xdot4 = xdot;

  x = x + (xdot1 + 2 * xdot2 + 2 * xdot3 + xdot4) * delta / 6;
  t = t + delta;
}
//-----------------------------------------------------------
//-----------------------------------------------------------
int main(int argc, char *argv[]) {
  int k, N_STEP; // N_STEP= numero di passi
  double e_teo, e_eulero, e_rk2, e_rk4;

  e_teo = exp(1.0);

  printf("    T    N_STEP        Eulero           RK2           RK4 \n");

  for (N_STEP = 2; N_STEP < 1025; N_STEP *= 2) {
    // N_STEP=100;
    delta = 1.0 / double(N_STEP);

    t = 0, x = 1;
    for (k = 0; k < N_STEP; k++) {
      next_Eulero();
    }
    e_eulero = (x - e_teo) / e_teo;

    t = 0, x = 1;
    for (k = 0; k < N_STEP; k++) {
      next_rk2();
    }
    e_rk2 = (x - e_teo) / e_teo;

    t = 0, x = 1;
    for (k = 0; k < N_STEP; k++) {
      next_rk4();
    }
    e_rk4 = (x - e_teo) / e_teo;
    printf("%5.2lf %9.0d  %15.12lf  %15.12lf  %15.12lf\n", t, N_STEP, e_eulero,
           e_rk2, e_rk4);
  }

  cin.get();
  return 0;
}

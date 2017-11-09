#include "EqLaplace.h"
#include "dati.h"
#include <math.h>
#include <time.h>

double dx, dx2, sigma;
double **u, **f, **e, *x, *y;

//-----------------------------------------------------------------------------
void Start() {
  sigma = 1.9; // 2.0;  Next2
  // sigma= 1.0; // Next
  dx = 2.0 / (NN - 1);
  dx2 = dx * dx;

  x = new double[NN];
  y = new double[NN];
  u = new double *[NN];
  for (int i = 0; i < NN; i++)
    u[i] = new double[NN];
  f = new double *[NN];
  for (int i = 0; i < NN; i++)
    f[i] = new double[NN];
  e = new double *[NN];
  for (int i = 0; i < NN; i++)
    e[i] = new double[NN];

  for (int i = 0; i < NN; i++) {
    x[i] = i * dx - 1.0;
    y[i] = i * dx - 1.0;
  }
  // definisco la condizione iniziale e le condizioni al contorno
  for (int i = 0; i < NN; i++)
    for (int j = 0; j < NN; j++)
      u[i][j] = 0.0;
  // definisco la forzante
  for (int i = 1; i < NN - 1; i++)
    for (int j = 1; j < NN - 1; j++) {
      // f[i][j]= 20*sin(x[i]*PI)*cos(2*PI*y[j]);
      f[i][j] = 10;
    }

  Err();
}
//-----------------------------------------------------------------------------
double Err() {
  static bool prima_volta = true;
  static double e20 = 1.0;
  double ee, e2 = 0;
  for (int i = 1; i < NN - 1; i++)
    for (int j = 1; j < NN - 1; j++) {
      ee = u[i][j] -
           (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1] -
            dx2 * f[i][j]) /
               4;
      e2 += ee * ee;
    }
  e2 /= (NN - 1) * (NN - 1);
  if (prima_volta) {
    prima_volta = false;
    e20 = e2;
  }
  return sqrt(e2 / e20);
}
//-----------------------------------------------------------------------------
void Next() {
  for (int i = 1; i < NN - 1; i++)
    for (int j = 1; j < NN - 1; j++) {
      e[i][j] = u[i][j] -
                (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1] -
                 dx2 * f[i][j]) /
                    4;
    }
  for (int i = 1; i < NN - 1; i++)
    for (int j = 1; j < NN - 1; j++) {
      u[i][j] = u[i][j] - sigma * e[i][j];
    }
}
///-----------------------------------------------------------------------------
void Next2() {
  double ee;
  for (int i = 1; i < NN - 1; i++)
    for (int j = 1; j < NN - 1; j++) {
      ee = u[i][j] -
           (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1] -
            dx2 * f[i][j]) /
               4;
      u[i][j] = u[i][j] - sigma * ee;
    }
}
//-----------------------------------------------------------------------------

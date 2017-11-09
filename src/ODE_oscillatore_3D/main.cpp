// Moto armonico: autovalori debolmente instabili

#include "classi.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define PI 3.1415927
#define N_DIM 1

Stato s(N_DIM);
double t, delta;

//-----------------------------------------------------------
void force(Stato &s) {
  for (int i = 0; i < N_DIM; i++)
    s.a[i] = -s.x[i];
}
//-----------------------------------------------------------
double energy(Stato &s) {
  double sum = 0;
  for (int i = 0; i < N_DIM; i++) {
    sum += s.x[i] * s.x[i]; // 2 energia potenziale
    sum += s.v[i] * s.v[i]; // 2 energia cinetica
  }
  return sum / 2;
}
//-----------------------------------------------------------
void next_rk2() {
  Stato sw(N_DIM);
  force(s);
  for (int i = 0; i < N_DIM; i++) {
    sw.x[i] = s.x[i] + s.v[i] * delta / 2;
    sw.v[i] = s.v[i] + s.a[i] * delta / 2;
  }
  t = t + delta / 2;
  force(sw);
  for (int i = 0; i < N_DIM; i++) {
    s.x[i] = s.x[i] + sw.v[i] * delta;
    s.v[i] = s.v[i] + sw.a[i] * delta;
  }
  t = t + delta / 2;
}
//-----------------------------------------------------------
void next_s2() {

  for (int i = 0; i < N_DIM; i++)
    s.x[i] = s.x[i] + s.v[i] * delta / 2;
  t = t + delta / 2;
  force(s);
  for (int i = 0; i < N_DIM; i++)
    s.v[i] = s.v[i] + s.a[i] * delta;
  for (int i = 0; i < N_DIM; i++)
    s.x[i] = s.x[i] + s.v[i] * delta / 2;
  t = t + delta / 2;
}
//-----------------------------------------------------------
void next_rk4() {

  Stato sw1(N_DIM), sw2(N_DIM), sw3(N_DIM);

  force(s);
  for (int i = 0; i < N_DIM; i++) {
    sw1.x[i] = s.x[i] + s.v[i] * delta / 2;
    sw1.v[i] = s.v[i] + s.a[i] * delta / 2;
  }
  t = t + delta / 2;
  force(sw1);
  for (int i = 0; i < N_DIM; i++) {
    sw2.x[i] = s.x[i] + sw1.v[i] * delta / 2;
    sw2.v[i] = s.v[i] + sw1.a[i] * delta / 2;
  }

  force(sw2);
  for (int i = 0; i < N_DIM; i++) {
    sw3.x[i] = s.x[i] + sw2.v[i] * delta;
    sw3.v[i] = s.v[i] + sw2.a[i] * delta;
  }

  t = t + delta / 2;
  force(sw3);

  for (int i = 0; i < N_DIM; i++) {
    s.x[i] =
        s.x[i] + (s.v[i] + 2 * sw1.v[i] + 2 * sw2.v[i] + sw3.v[i]) * delta / 6;
    s.v[i] =
        s.v[i] + (s.a[i] + 2 * sw1.a[i] + 2 * sw2.a[i] + sw3.a[i]) * delta / 6;
  }
}
//-----------------------------------------------------------
int main(int argc, char *argv[]) {

  int n_rotazioni = 1000000;
  int n_punti_x_rotazione = 100;
  int kmax = n_rotazioni * n_punti_x_rotazione;
  delta = 2 * PI / n_punti_x_rotazione;

  printf("\n      n_rotazioni= %d  n_punti_x_rotazione= %d\n\n", n_rotazioni,
         n_punti_x_rotazione);
  printf("          2E= 1.000000000 x= 1.000000 v= 0.000000  esatto \n");

  s.set(1.0, 0.0);
  t = 0.0;
  for (int k = 0; k < kmax; k++)
    next_s2();
  printf(" t=%6.2lf 2E=%12.9lf x=%9.6lf v=%9.6lf      s2\n", t, 2 * energy(s),
         s.x[0], s.v[0]);

  // s.set(1.0,0.0); t=0.0;
  // for (int k=0; k<kmax; k++) next_rk2();
  // printf(" t=%6.2lf 2E=%12.9lf x=%9.6lf v=%9.6lf
  // rk2\n",t,2*energy(s),s.x[0],s.v[0]);

  // s.set(1.0,0.0); t=0.0;
  // for (int k=0; k<kmax; k++) next_rk4();
  // printf(" t=%6.2lf 2E=%12.9lf x=%9.6lf v=%9.6lf
  // rk4\n",t,2*energy(s),s.x[0],s.v[0]);

  printf("\n  ");
  cin.get();
  return 0;
}

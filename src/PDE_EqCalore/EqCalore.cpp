#include <math.h>
#include <time.h>

#define N 201
#define PI 3.14159265359

int nmax = N, iter_max = 100000;
double t, sigma;
double u[N], u_[N], u__[N];
double a[N], b[N], c[N], d[N], r[N], x[N];

void Tridiag(double *a, double *b, double *c, double *r, double *u, int n);
//-----------------------------------------------------------------------------
void Start() {
  sigma = 50.0; // 0.5 limite  next1
  // sigma= 0.001;        // 0.0 limite  next2
  for (int n = 1; n < N - 1; n++)
    u[n] = 0;
  u[0] = 10.0;
  u[N - 1] = 5.0;
}
//-----------------------------------------------------------------------------
void next1() {

  for (int n = 1; n < N - 1; n++)
    u_[n] = u[n] + sigma * (u[n - 1] - 2 * u[n] + u[n + 1]);
  for (int n = 1; n < N - 1; n++)
    u[n] = u_[n];
}
//-----------------------------------------------------------------------------
void next2() {

  for (int n = 1; n < N - 1; n++)
    u_[n] = u__[n] + 2 * sigma * (u[n - 1] - 2 * u[n] + u[n + 1]);
  for (int n = 1; n < N - 1; n++) {
    u__[n] = u[n];
    u[n] = u_[n];
  }
}
//-----------------------------------------------------------------------------
// per comodita` la condizione al contorno l'ho applicata per n=-1 ed n= N
void next3() {
  for (int n = 0; n < N; n++) {
    a[n] = 1;
    b[n] = -(2 + 1 / sigma);
    c[n] = 1;
    r[n] = -(1 / sigma) * u[n];
  }
  r[0] = -(1 / sigma) * u[0] - u[0];
  r[N - 1] = -(1 / sigma) * u[N - 1] - u[N - 1];
  Tridiag(a, b, c, r, x, N);
  for (int n = 1; n < N - 1; n++)
    u[n] = x[n];
}
//-----------------------------------------------------------------------------
void sleep(clock_t wait) {
  clock_t goal;
  goal = wait + clock();
  while (goal > clock())
    ;
}
//-----------------------------------------------------------------------------
void Tridiag(double *a, double *b, double *c, double *r, double *u, int n) {
  double *gam;
  gam = new double[n];
  if (b[0] == 0.0)
    throw("Error 1 in tridag");
  double bet = b[0];
  u[0] = r[0] / bet;
  for (int j = 1; j < n; j++) {
    gam[j] = c[j - 1] / bet;
    bet = b[j] - a[j] * gam[j];
    if (bet == 0.0)
      throw("Error 2 in tridag");
    u[j] = (r[j] - a[j] * u[j - 1]) / bet;
  }
  for (int j = (n - 2); j >= 0; j--)
    u[j] -= gam[j + 1] * u[j + 1];
}
//-----------------------------------------------------------------------------
void EqCalore() {
  static int iter = 0;
  if (iter++ == 0)
    Start();
  if (iter < iter_max)
    next3();
  // if(iter < iter_max ) next2();
}
//-----------------------------------------------------------------------------

#include "robby.h"
#include "includes.h"
#include <nr.h>
#include <ran.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <vector>

using namespace std;

//------------------------------------------------------------------------

int **A;
int i_robby, j_robby;
// Ran myran(17);    // (Ullong seed)   best
Ranq1 myran(17); // (Ullong seed)   2.5 faster // 1+myran.int64() % N return a
                 // random integer between 1 and N (inclusive)
vector<Robby> robby;
Robby best_robby;
//------------------------------------------------------------------------
bool comp_Robby(const Robby &a, const Robby &b) { return (a.value > b.value); }
//------------------------------------------------------------------------
void setup() {
  A = new int *[Nmax];
  for (int i = 0; i < Nmax; i++)
    A[i] = new int[Nmax];
  for (int j = 0; j < Nmax; j++)
    A[0][j] = A[Nmax - 1][j] = A[j][0] = A[j][Nmax - 1] =
        2; // sulla frontiera A vale 2
  robby.resize(NROBBY);
  for (int n = 0; n < NROBBY; n++)
    for (int i = 0; i < 243; i++)
      robby[n].dna[i] = myran.int64() % 6; // 0-5
}
//------------------------------------------------------------------------
void put_cans() {
  while (true) {
    int i = 1 + myran.int64() % (Nmax - 2);
    int j = 1 + myran.int64() % (Nmax - 2);
    if (A[i][j] == 0) {
      A[i][j] = 1;
      break;
    }
  }
}
//------------------------------------------------------------------------
void valuta_Robby() {
  int value, mean_value;
  for (int n = 0; n < NROBBY; n++) {
    mean_value = 0;
    for (int m = 0; m < NTEST; m++) {
      for (int j = 1; j < Nmax - 1; j++)
        for (int i = 1; i < Nmax - 1; i++)
          A[i][j] = 0;
      for (int k = 0; k < NCANS; k++)
        put_cans();
      value = 0;
      int ir = 1 + myran.int64() % (Nmax - 2);
      int jr = 1 + myran.int64() % (Nmax - 2);
      for (int step = 0; step < NSTEP; step++) {
        int mappa = A[ir][jr] + A[ir - 1][jr] * 3 + A[ir + 1][jr] * 9 +
                    A[ir][jr - 1] * 27 + A[ir][jr + 1] * 81;
        int azione = robby[n].dna[mappa];
        if (azione == 0)
          azione = 1 + myran.int64() % 4;
        switch (
            azione) { // fermo,destra,sinistra,su,giu,raccogli )=(0,1,2,3,4,5)
        case 1:
          if (ir == Nmax - 2)
            value -= 5;
          else
            ir++;
          break;
        case 2:
          if (ir == 1)
            value -= 5;
          else
            ir--;
          break;
        case 3:
          if (jr == Nmax - 2)
            value -= 5;
          else
            jr++;
          break;
        case 4:
          if (jr == 1)
            value -= 5;
          else
            jr--;
          break;
        case 5:
          if (A[ir][jr] == 1) {
            value += 10;
            A[ir][jr] = 0;
          } else
            value -= 1;
          break;
        default:
          cout << " error " << endl;
        }
      }
      mean_value += value;
    }
    robby[n].value = mean_value / NTEST;
    // fprintf(stdout,"n=%8d     value=%8d \n",n,robby[n].value);
  }
}
//------------------------------------------------------------------------
void next() {
  // scegliamo i 10 migliori e li riproduciamo
  int id, i1, i2, icut;
  id = 9;
  while (id < NROBBY - 2) {
    i1 = myran.int64() % 10;
    i2 = i1;
    while (i2 == i1)
      i2 = myran.int64() % 10;
    icut = myran.int64() % 243;
    id++;
    for (int n = 0; n < icut; n++)
      robby[id].dna[n] = robby[i1].dna[n];
    for (int n = icut; n < 243; n++)
      robby[id].dna[n] = robby[i2].dna[n];
    robby[id].dna[myran.int64() % 243] = myran.int64() % 6;
    id++;
    for (int n = 0; n < icut; n++)
      robby[id].dna[n] = robby[i2].dna[n];
    for (int n = icut; n < 243; n++)
      robby[id].dna[n] = robby[i1].dna[n];
    robby[id].dna[myran.int64() % 243] = myran.int64() % 6;
  }
}
//------------------------------------------------------------------------
void segui_robby() {
  static bool prima_volta = true;
  static int value = 0, t;
  if (prima_volta) {
    prima_volta = false;
    for (int j = 1; j < Nmax - 1; j++)
      for (int i = 1; i < Nmax - 1; i++)
        A[i][j] = 0;
    for (int k = 0; k < NCANS; k++)
      put_cans();
    i_robby = 1 + myran.int64() % (Nmax - 2);
    j_robby = 1 + myran.int64() % (Nmax - 2);
    t = 0;
    return;
  }
  int ir = i_robby;
  int jr = j_robby;
  if (t++ >= NSTEP)
    return;
  int mappa = A[ir][jr] + A[ir - 1][jr] * 3 + A[ir + 1][jr] * 9 +
              A[ir][jr - 1] * 27 + A[ir][jr + 1] * 81;
  int azione = best_robby.dna[mappa];
  if (azione == 0)
    azione = 1 + myran.int64() % 4;
  switch (azione) { // fermo,destra,sinistra,su,giu,raccogli )=(0,1,2,3,4,5)
  case 1:
    if (ir == Nmax - 2)
      value -= 5;
    else
      ir++;
    break;
  case 2:
    if (ir == 1)
      value -= 5;
    else
      ir--;
    break;
  case 3:
    if (jr == Nmax - 2)
      value -= 5;
    else
      jr++;
    break;
  case 4:
    if (jr == 1)
      value -= 5;
    else
      jr--;
    break;
  case 5:
    if (A[ir][jr] == 1) {
      value += 10;
      A[ir][jr] = 0;
    } else
      value -= 1;
    break;
  default:
    cout << " error " << endl;
  }
  i_robby = ir;
  j_robby = jr;
}
//------------------------------------------------------------------------
int robby_main() {
  setup();

  for (int t = 0; t < NGEN; t++) {
    valuta_Robby();
    sort(robby.begin(), robby.end(), comp_Robby);
    if (t % 100 == 0)
      fprintf(stdout, "gen %8d max_value=%8d \n", t, robby[0].value);
    next();
  }
  best_robby = robby[0];
  // for( int n=0; n<NROBBY; n++ ) fprintf(stdout,"n=%8d     value=%8d
  // \n",n,robby[n].value); fprintf(stdout,"\n\n\n");
  // for( int n=0; n<243; n++ ) fprintf(stdout,"n=%8d value=%8d
  // \n",n,robby[0].dna[n]);

  return 0;
}
//-----------------------------------------------------------------------

#ifndef AVANZA_HPP
#define AVANZA_HPP

#include "def.h"
#include <FL/gl.h>
#include <FL/glu.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Punto {
public:
  int k;
  double d;
};
class Nodo {
public:
  int n_punti;
  Punto vicino[DIECI];
};

void Forza();
double R_UNI();
void Distanza();
void Stringhe_Distanze();
void Next();
void StartAvanza();

#endif // AVANZA

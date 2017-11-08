#ifndef AVANZA_HPP
#define AVANZA_HPP

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <FL/gl.h>
#include <FL/glu.h>
#include "def.h"

class Punto { public: int k; double d; };
class Nodo{ public: int n_punti; Punto vicino[DIECI]; };


void   Forza(void);
double R_UNI();
void   Distanza(void);
void   Stringhe_Distanze(void);
void   Next(void);
void   StartAvanza(void);


#endif // AVANZA

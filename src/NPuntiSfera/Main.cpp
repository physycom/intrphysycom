#include "form.h"
#include <FL/Fl.H>
#include <stdio.h>
#include <stdlib.h>

FILE *fp1;
extern Frame_1 *scene;
extern void stampa();
extern void stampa(int);
extern void leggi();
extern void Next();
extern void CreateMyWindow();
extern void StartAvanza();

//-------------------------------------------------------------------------------------------------
void idle_cb(void *) {
  scene->redraw();
#if defined(MOSTRA)
  stampa(N_PUNTI);
#else
  stampa();
  for (int i = 0; i < 100; i++)
    Next();
#endif
}
// ********************************************************************************************************
int main(int argc, char **argv) {
  fp1 = fopen(FILE_OUTPUT, "w");
  CreateMyWindow();
#if defined(MOSTRA)
  leggi();
#else
  StartAvanza();
#endif
  Fl::add_idle(idle_cb, 0);
  Fl::run();
  return 0;
}
// ********************************************************************************************************

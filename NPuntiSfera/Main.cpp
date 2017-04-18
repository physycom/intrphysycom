#include <stdio.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include "form.h"

FILE   *fp1;
extern Frame_1   *scene;
extern void stampa(void);
extern void stampa(int);
extern void leggi(void);
extern void Next(void);
extern void CreateMyWindow(void);
extern void StartAvanza(void);

//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{
  scene->redraw();
  #if defined (MOSTRA)
    stampa(N_PUNTI);
  #else
    stampa();
    for( int i=0; i< 100; i++ ) Next();
  #endif    
}
// ********************************************************************************************************
int main(int argc, char **argv) {
  fp1 = fopen (FILE_OUTPUT, "w");
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

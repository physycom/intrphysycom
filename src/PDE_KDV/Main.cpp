#include <FL/Fl.H>
#include <stdio.h>
//#include "guicon.h"
#include "Frame_1.h"
#include "form.h"

extern Frame_1 *scene;
//-------------------------------------------------------------------------------------------------
void idle_cb(void *) { scene->redraw(); }
// ********************************************************************************************************
int main(int argc, char **argv) {
  //RedirectIOToConsole();
  CreateMyWindow();
  Fl::add_idle(idle_cb, 0);
  Fl::run();
  return 0;
}
// ********************************************************************************************************

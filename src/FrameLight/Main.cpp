#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __CYGWIN__
#include <windef.h>
#endif

#include "Frame_1.h"
#include "form.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

//
extern Frame_1 *scene;
//-------------------------------------------------------------------------------------------------
void idle_cb(void *) { scene->redraw(); }
// ********************************************************************************************************
int main(int argc, char **argv) {
  CreateMyWindow();
  Fl::add_idle(idle_cb, 0);
  Fl::run();
  return 0;
}
// ********************************************************************************************************

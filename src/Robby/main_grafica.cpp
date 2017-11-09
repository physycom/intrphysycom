#include "form.h"
#include "frame.h"
#include "includes.h"
#include <FL/Fl.H>

extern Frame *scene;
extern int robby_main();
///-------------------------------------------------------------------------------------------------
void idle_cb(void *) { scene->redraw(); }
//-------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {

  robby_main();
  CreateMyWindow();
  Fl::add_idle(idle_cb, 0);
  Fl::run();
  return 0;
}
//-------------------------------------------------------------------------------------------------

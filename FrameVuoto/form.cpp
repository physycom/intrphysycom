#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "Frame.h"
#include "form.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 400


Frame        *scene;

//-------------------------------------------------------------------------------------------------
void CreateMyWindow(void) {
  int w_est,h_est;
  
  w_est= 23+SCREEN_WIDTH+23;   h_est= 23+SCREEN_HEIGHT+23;
  Fl_Window    *form;     
  form=   new Fl_Window(w_est,h_est,"FSC");
          new Fl_Box(FL_DOWN_FRAME,20,20,SCREEN_WIDTH+6,SCREEN_HEIGHT+6,"");
  scene=  new Frame(23,23,SCREEN_WIDTH,SCREEN_HEIGHT, 0);
  //form->resizable(scene);

  form->end();
  form->show();
  scene->show();
}
//-------------------------------------------------------------------------------------------------



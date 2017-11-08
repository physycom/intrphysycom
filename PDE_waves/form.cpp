#include "form.h"

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600


Fl_Window       *form;
Frame_1         *scene;

//-------------------------------------------------------------------------------------------------
void CreateMyWindow(void) {
  int w_est,h_est;
  
  w_est= 23+SCREEN_WIDTH+23;   h_est= 23+SCREEN_HEIGHT+23;
     
  form=   new Fl_Window(w_est,h_est,"Eq. Onde");
          new Fl_Box(FL_DOWN_FRAME,20,20,SCREEN_WIDTH+6,SCREEN_HEIGHT+6,"");
  scene=  new Frame_1(23,23,SCREEN_WIDTH,SCREEN_HEIGHT, 0);

  form->end();
  form->show();
  scene->show();
}
//-------------------------------------------------------------------------------------------------



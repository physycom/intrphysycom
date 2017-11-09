#include "form.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

Fl_Window *form;
Frame_1 *scene;
Fl_Button *button;
Fl_Value_Slider *ruotaX, *ruotaY, *ruotaZ, *zoom;
Fl_Multiline_Output *linee;

void exit_callback(Fl_Widget *) { form->hide(); }
void ruotaX_callback(Fl_Widget *) { scene->ruotaX = 180 * ruotaX->value(); }
void ruotaY_callback(Fl_Widget *) { scene->ruotaY = 180 * ruotaY->value(); }
void ruotaZ_callback(Fl_Widget *) { scene->ruotaZ = 180 * ruotaZ->value(); }
void zoom_callback(Fl_Widget *) { scene->zoom = zoom->value(); }
//-------------------------------------------------------------------------------------------------

void CreateMyWindow() {
  int w_est, h_est;

  w_est = 23 + SCREEN_WIDTH + 230 + 23;
  h_est = 23 + SCREEN_HEIGHT + 23;

  form = new Fl_Window(w_est, h_est, "FSC Esempio_1");
  new Fl_Box(FL_DOWN_FRAME, 20, 20, SCREEN_WIDTH + 6, SCREEN_HEIGHT + 6, "");
  scene = new Frame_1(23, 23, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  ruotaX = new Fl_Value_Slider(w_est - 230, 20, 210, 20, "Ruota X");
  ruotaY = new Fl_Value_Slider(w_est - 230, 70, 210, 20, "Ruota Y");
  ruotaZ = new Fl_Value_Slider(w_est - 230, 120, 210, 20, "Ruota Z");
  zoom = new Fl_Value_Slider(w_est - 230, 170, 210, 20, "Zoom");
  linee = new Fl_Multiline_Output(w_est - 230, 220, 210, 70, "");

  button = new Fl_Button(w_est - 230, h_est - 130, 210, 110, "Exit");

  ruotaX->type(FL_HOR_NICE_SLIDER);
  ruotaX->bounds(-1, 1);
  ruotaX->value(scene->ruotaX = 0);
  ruotaY->type(FL_HOR_NICE_SLIDER);
  ruotaY->bounds(-1, 1);
  ruotaY->value(scene->ruotaY = 0);
  ruotaZ->type(FL_HOR_NICE_SLIDER);
  ruotaZ->bounds(-1, 1);
  ruotaZ->value(scene->ruotaZ = 0);
  zoom->type(FL_HOR_NICE_SLIDER);
  zoom->bounds(0.1, 10);
  zoom->value(scene->zoom = 3.0);
  ruotaX->callback(ruotaX_callback);
  ruotaY->callback(ruotaY_callback);
  ruotaZ->callback(ruotaZ_callback);
  zoom->callback(zoom_callback);

  button->callback(exit_callback);

  form->end();
  form->show();
  scene->show();
}
//-------------------------------------------------------------------------------------------------

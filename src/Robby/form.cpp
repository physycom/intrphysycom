#include "form.h"
#include "draw.h"
#include "frame.h"
#include "includes.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Window.H>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

Fl_Window *form;
Frame *scene;
Fl_Button *button1;
void exit_cb(Fl_Widget *) { form->hide(); }

//-------------------------------------------------------------------------------------------------
void CreateMyWindow() {
  int w_est, h_est;

  w_est = 23 + SCREEN_WIDTH + 123;
  h_est = 23 + SCREEN_HEIGHT + 23;

  form = new Fl_Window(20, 20, w_est, h_est, "Robby");
  new Fl_Box(FL_DOWN_FRAME, 20, 20, SCREEN_WIDTH + 6, SCREEN_HEIGHT + 6, "");
  scene = new Frame(23, 23, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  form->resizable(scene);
  // ------------  Exit -----------------------------------------------------
  button1 = new Fl_Button(w_est - 103, h_est - 93, 80, 70, "Exit");
  button1->callback(exit_cb);

  form->end();
  form->show();
  scene->show();
}
//-------------------------------------------------------------------------------------------------

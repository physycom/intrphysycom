#ifndef FORM_HPP
#define FORM_HPP

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Radio_Light_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Window.H>

#include "Frame_1.h"
#include "def.h"

void exit_callback(Fl_Widget *);
void ruotaX_callback(Fl_Widget *);
void ruotaY_callback(Fl_Widget *);
void ruotaZ_callback(Fl_Widget *);
void zoom_callback(Fl_Widget *);
void CreateMyWindow();

#endif // FORM_HPP

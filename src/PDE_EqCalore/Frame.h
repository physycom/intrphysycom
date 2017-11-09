#pragma once

#include "draw.h"
#include <FL/Fl_Box.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glu.h>
#include <math.h>

class Frame : public Fl_Gl_Window {
  void draw();
  void init();

public:
  Frame(int x, int y, int w, int h, const char *l = 0)
      : Fl_Gl_Window(x, y, w, h, l) {}
};

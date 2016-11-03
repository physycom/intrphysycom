#pragma once

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif
#ifdef __CYGWIN__ 
#include <windef.h> 
#endif 

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>

class Frame_1 : public Fl_Gl_Window {
  int handle(int);
  void draw();
  void init();
public:
  double ruotaX, ruotaY, ruotaZ;
  GLfloat zoom;
  Frame_1(int x, int y, int w, int h, const char *l = 0) : Fl_Gl_Window(x, y, w, h, l) {}
};



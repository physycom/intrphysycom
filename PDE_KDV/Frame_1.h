#ifndef FRAME_1_HPP
#define FRAME_1_HPP

#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/gl.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <math.h>
#include "draw.h"



class Frame_1 : public Fl_Gl_Window {
  void draw();
  void init();
public:
  Frame_1(int x,int y,int w,int h,const char *l=0) : Fl_Gl_Window(x,y,w,h,l) {}
};


#endif // FRAME_1_HPP

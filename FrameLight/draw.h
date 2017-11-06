#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __CYGWIN__
#include <windef.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>
//#include <FL/glut.h>
#include <cmath>


void draw_palla();
void draw_tetra();
void draw_cube();
void draw_scene();
void normale9f(float, float, float, float, float, float, float, float, float);


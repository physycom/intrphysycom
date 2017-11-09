#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __CYGWIN__
#include <windef.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>
#include <math.h>

void draw_scene();

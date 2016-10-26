#pragma once
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif

#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <cmath>


void draw_palla();
void draw_tetra();
void draw_cube();
void draw_scene();
void normale9f(float, float, float, float, float, float, float, float, float);


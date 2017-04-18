#ifndef DRAW_HPP
#define DRAW_HPP

#include <FL/gl.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <math.h>



void draw_scene(void);
void draw_init(void);




#endif // DRAW_HPP

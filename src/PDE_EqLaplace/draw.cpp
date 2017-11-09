#include "draw.h"
#include "EqLaplace.h"
#include "dati.h"
#include <FL/gl.h>

#define QUADRO 1

extern double **u, *x, *y;

// ********************************************************************************************************
void draw_init() {
  float L = 0.02f;
  glNewList(QUADRO, GL_COMPILE);
  glBegin(GL_QUADS);
  glVertex3f(L, L, 0.0);
  glVertex3f(-L, L, 0.0);
  glVertex3f(-L, -L, 0.0);
  glVertex3f(L, -L, 0.0);
  glEnd();
  glEndList();
}
// ********************************************************************************************************
void draw_scene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (int n = 0; n < 20; n++)
    Next2(); // Sleep(10);

  glColor3f(1.0, 1.0, 0.0);
  for (int i = 0; i < NN; i++) {
    glBegin(GL_LINE_STRIP);
    for (int j = 0; j < NN; j++)
      glVertex3d(x[i], y[j], u[i][j]);
    glEnd();
  }
  for (int j = 0; j < NN; j++) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < NN; i++)
      glVertex3d(x[i], y[j], u[i][j]);
    glEnd();
  }
}
// ********************************************************************************************************

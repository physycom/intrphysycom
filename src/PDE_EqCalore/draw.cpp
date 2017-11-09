#include "draw.h"
#include <time.h>

#define DOMINIO 1
#define QUADRO 7

extern double u[];
extern int nmax;
extern void EqCalore();
extern void sleep(clock_t wait);
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

  glNewList(DOMINIO, GL_COMPILE);
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  glVertex3f(-5.0f, 0.0f, 0.0f);
  glVertex3f(+5.0f, 0.0f, 0.0f);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(-5.0f, -1.0f, 0.0f);
  glVertex3f(-5.0f, +1.0f, 0.0f);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(5.0f, -1.0f, 0.0f);
  glVertex3f(5.0f, +1.0f, 0.0f);
  glEnd();
  glEndList();
}
// ********************************************************************************************************
void draw_scene() {
  int n;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  EqCalore(); // Sleep(10);
  glPushMatrix();
  glScalef(1.0, 2.0, 1.0);
  glCallList(DOMINIO);

  glColor3f(1.0, 0.0, 0.0);
  for (n = 0; n < nmax; n++) {
    double xn = -5.0 + n * 10.0 / nmax;
    glPushMatrix();
    glTranslated(xn, u[n] / 10.0, 0);
    glCallList(QUADRO);
    glPopMatrix();
  }
  glPopMatrix();
}
// ********************************************************************************************************

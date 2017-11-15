#include "draw.h"

#define DOMINIO 1
#define QUADRO 7

extern double x[], ud[];
extern int nmax;
extern void KDV();

// ********************************************************************************************************
void draw_init() {
  float L = 0.04f;
  glNewList(QUADRO, GL_COMPILE);
  glBegin(GL_QUADS);
  glVertex3f(L, L, 0.0f);
  glVertex3f(-L, L, 0.0f);
  glVertex3f(-L, -L, 0.0f);
  glVertex3f(L, -L, 0.0f);
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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  KDV();
  glPushMatrix();
  // glScalef(1.0,2.0,1.0);
  glCallList(DOMINIO);

  glColor3f(1.0, 1.0, 0.0);
  for (int n = 0; n < nmax; n++) {
    glPushMatrix();
    glTranslated(x[n], ud[n], 0);
    glCallList(QUADRO);
    glPopMatrix();
  }
}
// ********************************************************************************************************

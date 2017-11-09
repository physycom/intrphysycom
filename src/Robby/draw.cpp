#include "draw.h"
#include "robby.h"
#include "includes.h"
#include <FL/Fl.H>
#include <FL/Fl_Output.H>
#include <FL/fl_draw.H>
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>
#include <math.h>

extern int **A, i_robby, j_robby;
extern void segui_robby();
#define DOMINIO 1
#define CAN 2
#define ROBBY 3

// ********************************************************************************************************
void draw_init() {

  gl_font(FL_HELVETICA_BOLD, 26);
  double L;
  L = 4.8;
  glNewList(ROBBY, GL_COMPILE);
  glBegin(GL_QUADS);
  glVertex3d(-L, -L, 0.0);
  glVertex3d(L, -L, 0.0);
  glVertex3d(L, L, 0.0);
  glVertex3d(-L, L, 0.0);
  glEnd();
  glEndList();
  L = 2.0;
  glNewList(CAN, GL_COMPILE);
  glBegin(GL_QUADS);
  glVertex3d(-L, -L, 0.0);
  glVertex3d(L, -L, 0.0);
  glVertex3d(L, L, 0.0);
  glVertex3d(-L, L, 0.0);
  glEnd();
  glEndList();
  L = 100.0;
  glNewList(DOMINIO, GL_COMPILE);
  for (int i = 0; i < 11; i++) {
    glBegin(GL_LINES);
    glVertex3d(0.0 + i * L / 10, 0.0, 0.0);
    glVertex3d(0.0 + i * L / 10, L, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0 + i * L / 10, 0.0);
    glVertex3d(L, 0.0 + i * L / 10, 0.0);
    glEnd();
  }
  glEndList();
}
// ********************************************************************************************************
void draw_robby() {
  double L = 10.0;
  glColor3d(1.0, 1.0, 1.0);
  for (int j = 1; j < Nmax - 1; j++)
    for (int i = 1; i < Nmax - 1; i++) {
      if (A[i][j] == 1) {
        glPushMatrix();
        glTranslated(-5.0 + i * L, -5.0 + j * L, 0.3);
        glCallList(CAN);
        glPopMatrix();
      }
    }
  glColor3d(0.0, 1.0, 0.0);
  glPushMatrix();
  glTranslated(-5.0 + i_robby * L, -5.0 + j_robby * L, 0.3);
  glCallList(ROBBY);
  glPopMatrix();
  glColor3d(1.0, 1.0, 1.0);
}
// ********************************************************************************************************
void draw_scene() {
  segui_robby();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glColor3d(1.0, 1.0, 0.0);
  glCallList(DOMINIO);
  draw_robby();
  glPopMatrix();
  cin.get();
}
// ********************************************************************************************************
